#include "StdAfx.h"
#include "pipeserverthread.h"

#include "ConstPipe.h" //namespace CONS_PIPE
using namespace CONS_PIPE;

//extern CConsoleOut2 theConsole;

namespace PIPE_SERVER{


CPipeServerThread::CPipeServerThread(void)
{
}

CPipeServerThread::~CPipeServerThread(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12-Jul-2006 15:25:47
	DESC:	
	IN:		
	OUT:	
*/
bool CPipeServerThread::StartPipeServerThread(const CPipeServerThreadParams & rParams)
{
	bool bOK = false;

	CPipeServerThreadParams * pParams = new CPipeServerThreadParams(rParams);
	ATLASSERT(pParams);

	if(pParams){
		CString strThrdName(_T("Pipe Server Thread"));

		bOK = CBasicThread3::StartBaseThread(
										strThrdName
										, TF_PipeServerWrapper
										, LPVOID(pParams)
									);
		ATLASSERT(bOK);

		if(!bOK){
			delete pParams;
			pParams = 0;
		}
	}

	return bOK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12-Jul-2006 15:25:51
	DESC:	
	IN:		
	OUT:	
*/
void CPipeServerThread::StopPipeServerThread(void)
{
	CBasicThread3::StopBaseThread(5000l);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12-Jul-2006 15:32:19
	DESC:	
	IN:		
	OUT:	
*/
/*static*/ 
DWORD WINAPI CPipeServerThread::TF_PipeServerWrapper(LPVOID lpThreadParams)
{
	DWORD dwRet = DWORD(-1L);

	CPipeServerThreadParams * pParams = reinterpret_cast<CPipeServerThreadParams *>(lpThreadParams);
	ATLASSERT(pParams);

	if(pParams){
		
		//::CoInitialize(0);

		dwRet = TF_PipeServerMainLoop(*pParams);

		//::CoUninitialize();
		
		delete pParams;
		pParams = 0;
	}

	return dwRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12-Jul-2006 15:32:23
	DESC:	
	IN:		
	OUT:	
*/
/*static*/ 
DWORD CPipeServerThread::TF_PipeServerMainLoop(const CPipeServerThreadParams & rParams)
{
	DWORD dwRet = NOERROR;

	bool bConnected; 
	DWORD dwThreadId; 
	HANDLE hPipe	= 0;
	HANDLE hThread	= 0; 
	
	bool bContinue = true;

	// The main loop creates an instance of the named pipe and 
	// then waits for a client to connect to it. When the client 
	// connects, a thread is created to handle communications 
	// with that client, and the loop is repeated. 
	while(bContinue) 
	{ 
		TF_CreatePipe(hPipe, rParams);

		if (hPipe == INVALID_HANDLE_VALUE) 
		{
			ATLTRACE(_T("CreatePipe failed\n")); 
			bContinue = false;
			continue;
		}
	 
		//bConnected = ConnectNamedPipe(hPipe, NULL) ? 
		//	TRUE : (GetLastError() == ERROR_PIPE_CONNECTED); 
		bConnected = TF_WaitPipeConnection(hPipe, bContinue, rParams);
 
		if(bConnected && bContinue) 
		{ 
			CPipeServerInstanceThreadParams * pInstParams 
					= new CPipeServerInstanceThreadParams(
														rParams.GetTgtHWnd()
														, rParams.GetTgtTID()
														, hPipe
													);
			ATLASSERT(pInstParams);

			// Create a thread for this client. 
			hThread = ::CreateThread( 
								NULL						// no security attribute 
								, 0							// default stack size 
								, TFInst_InstanceThreadWrap	// thread proc
								, reinterpret_cast<LPVOID>(pInstParams)			// thread parameter 
								, 0							// not suspended 
								, &dwThreadId				// returns thread ID 
							);
			ATLASSERT(hThread);

			if(hThread){
				TF_CloseIfValid(hThread); 
			}
			else{
				ATLTRACE(_T("CreateThread failed\n")); 
				bContinue = false;
			}
		} 
		else 
			// The client could not connect, so close the pipe. 
			TF_CloseIfValid(hPipe); 

	}//while(bContinue)

	TF_CloseIfValid(hThread);
	TF_CloseIfValid(hPipe);

	return dwRet;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   13 July 2006 06:55:11	
	DESC:		
	IN:
	OUT:
*/
/*static*/ 
void CPipeServerThread::TF_CreatePipe(HANDLE & hPipe, const CPipeServerThreadParams & rParams)
{
	hPipe = ::CreateNamedPipe( 
							rParams.GetPipeName()			// pipe name 
							, PIPE_ACCESS_DUPLEX 			// read/write access 
								| FILE_FLAG_OVERLAPPED		// overlapped
							, PIPE_TYPE_MESSAGE				// message type pipe 
								| PIPE_READMODE_MESSAGE		// message-read mode 
								| PIPE_WAIT					// blocking mode 
							, PIPE_UNLIMITED_INSTANCES		// max. instances  
							, dwOUT_BUF_SIZE				// output buffer size 
							, dwIN_BUF_SIZE					// input buffer size 
							, NMPWAIT_USE_DEFAULT_WAIT		// client time-out 
							, NULL							// default security attribute 
						);

	//theConsole.WriteAnEvent(_T("%s - handle = 0x%X"), rParams.GetPipeName(), hPipe);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	17-Jul-2006 07:39:10
	DESC:	
	IN:		
	OUT:	
*/
/*static*/ 
//void CPipeServerThread::TF_CreatePipe(CHandleWrapper & hPipe, const CPipeServerThreadParams & rParams)
//{
//	hPipe = ::CreateNamedPipe( 
//							rParams.GetFullPipeName()		// pipe name 
//							, PIPE_ACCESS_DUPLEX 			// read/write access 
//								| FILE_FLAG_OVERLAPPED		// overlapped
//							, PIPE_TYPE_MESSAGE				// message type pipe 
//								| PIPE_READMODE_MESSAGE		// message-read mode 
//								| PIPE_WAIT					// blocking mode 
//							, PIPE_UNLIMITED_INSTANCES		// max. instances  
//							, dwOUT_BUF_SIZE				// output buffer size 
//							, dwIN_BUF_SIZE					// input buffer size 
//							, NMPWAIT_USE_DEFAULT_WAIT		// client time-out 
//							, NULL							// default security attribute 
//						);
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   13 July 2006 06:58:48	
	DESC:		
	IN:
	OUT:
*/
/*static*/ 
bool CPipeServerThread::TF_WaitPipeConnection(
												HANDLE & hPipe
												, bool & bContinueLoop
												, const CPipeServerThreadParams & rParams
											)
{
	const DWORD dwNUMEVTS = 1L;
	const DWORD dwEVT_OLAP = 0L;

	bool bPipeConnected = false;

	HANDLE hEvents[dwNUMEVTS];

	hEvents[dwEVT_OLAP] = ::CreateEvent(0, FALSE, FALSE, 0);

	OVERLAPPED olap;
	::ZeroMemory(&olap, sizeof(OVERLAPPED));

	olap.hEvent = hEvents[0];

	// Start waiting for the client to connect; if it succeeds, 
	// the function returns a nonzero value. If the function
	// returns zero, check GetLastError. 
	 
	BOOL bConnectAttempt = ConnectNamedPipe(hPipe, &olap);

	if(bConnectAttempt){
		bPipeConnected = true;
	}

	else{
		DWORD dwErr = ::GetLastError();

		switch(dwErr){
			case ERROR_PIPE_CONNECTED:	bPipeConnected = true;	break;
			case ERROR_IO_PENDING:
				{
					ATLTRACE(_T("PipeServer: WAIT STARTING...\n"));

					DWORD dwWait = ::MsgWaitForMultipleObjects(
															dwNUMEVTS
															, hEvents
															, FALSE
															, INFINITE
															, QS_ALLINPUT
														);

					switch(dwWait){
						case dwEVT_OLAP + WAIT_OBJECT_0:
							ATLTRACE(_T("PipeServer: WAIT FINISHED...Connection\n"));
							bPipeConnected = true;
							break;
					}
				}
				break;
		}
	}
			//TRUE : (GetLastError() == ERROR_PIPE_CONNECTED); 

	bContinueLoop = TF_ProcessMessages(rParams);

	for(DWORD dwLoop = 0L ; dwLoop < dwNUMEVTS ; dwLoop++){
		TF_CloseIfValid(hEvents[dwLoop]);
	}

	return bPipeConnected;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	17-Jul-2006 07:40:21
	DESC:	
	IN:		
	OUT:	
*/
//bool CPipeServerThread::TF_WaitPipeConnection(
//												CHandleWrapper & hPipe
//												, bool & bContinueLoop
//												, const CPipeServerThreadParams & rParams
//											)
//{
//	const DWORD dwNUMEVTS = 1L;
//	const DWORD dwEVT_OLAP = 0L;
//
//	bool bPipeConnected = false;
//
//	HANDLE hEvents[dwNUMEVTS];
//
//	hEvents[dwEVT_OLAP] = ::CreateEvent(0, FALSE, FALSE, 0);
//
//	OVERLAPPED olap;
//	::ZeroMemory(&olap, sizeof(OVERLAPPED));
//
//	olap.hEvent = hEvents[0];
//
//	// Start waiting for the client to connect; if it succeeds, 
//	// the function returns a nonzero value. If the function
//	// returns zero, check GetLastError. 
//	 
//	BOOL bConnectAttempt = ConnectNamedPipe(hPipe, &olap);
//
//	if(bConnectAttempt){
//		bPipeConnected = true;
//	}
//
//	else{
//		DWORD dwErr = ::GetLastError();
//
//		switch(dwErr){
//			case ERROR_PIPE_CONNECTED:	bPipeConnected = true;	break;
//			case ERROR_IO_PENDING:
//				{
//					ATLTRACE(_T("WAIT STARTING...\n"));
//
//					DWORD dwWait = ::MsgWaitForMultipleObjects(
//															dwNUMEVTS
//															, hEvents
//															, FALSE
//															, INFINITE
//															, QS_ALLINPUT
//														);
//
//					ATLTRACE(_T("WAIT FINISHED...%i\n"), dwWait);
//
//					switch(dwWait){
//						case dwEVT_OLAP + WAIT_OBJECT_0:
//							bPipeConnected = true;
//							break;
//					}
//				}
//				break;
//		}
//	}
//			//TRUE : (GetLastError() == ERROR_PIPE_CONNECTED); 
//
//	bContinueLoop = TF_ProcessMessages(rParams);
//
//	return bPipeConnected;
//}	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   13 July 2006 07:25:33	
	DESC:		
	IN:
	OUT:
*/
/*static*/ 
bool CPipeServerThread::TF_ProcessMessages(const CPipeServerThreadParams & rParams)
{
	bool bContinue = true;

	MSG msg;

	while(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
		switch(msg.message){
			case WM_QUIT:	
				ATLTRACE(_T("PipeServer: WM_QUIT Received...\n"));
				bContinue = false;	
				break;

			default:
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
		}
	}

	return bContinue;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   13 July 2006 07:37:16	
	DESC:		
	IN:
	OUT:
*/
/*static*/ 
void CPipeServerThread::TF_CloseIfValid(HANDLE & hPipe)
{
	if(hPipe && (INVALID_HANDLE_VALUE != hPipe))
		::CloseHandle(hPipe);

	hPipe = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   13 July 2006 07:39:23	
	DESC:		
	IN:
	OUT:
*/
/*static*/ 
DWORD WINAPI CPipeServerThread::TFInst_InstanceThreadWrap(LPVOID lpThreadParams)
{
	DWORD dwRet = DWORD(-1L);

	// The thread's parameter is a handle to a pipe instance. 
	CPipeServerInstanceThreadParams * pParams 
			= reinterpret_cast<CPipeServerInstanceThreadParams *>(lpThreadParams); 
	ATLASSERT(pParams);

	if(pParams){
		//hPipe = reinterpret_cast<HANDLE>(lpThreadParams); 
		//hPipe = pParams->GetPipeHandle();
	 
		dwRet = TFInst_InstanceThreadMain(*pParams);

		delete pParams;
		pParams = 0;
	}

	return NOERROR;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   18 July 2006 21:59:49	
	DESC:		
	IN:
	OUT:
*/
/*static*/ 
DWORD CPipeServerThread::TFInst_InstanceThreadMain(const CPipeServerInstanceThreadParams & rStartInst)
{
	DWORD dwErr = NOERROR;

	TCHAR szReceive		[dwIN_BUF_SIZE + 5]; 
	//TCHAR chReply		[dwIN_BUF_SIZE]; 
	CString strReply;

	DWORD cbBytesRead	= 0L;
	DWORD cbReplyBytes	= 0L;
	DWORD cbWritten		= 0L; 

	BOOL fSuccess; 
	HANDLE hPipe = rStartInst.GetPipeHandle(); 

	TFInst_OnStartup(rStartInst);

#pragma message("Infinite loop!")

	while (1) 
	{ 
		// Read client requests from the pipe. 
		fSuccess = ::ReadFile( 
							hPipe							// handle to pipe 
							, szReceive						// buffer to receive data 
							, dwIN_BUF_SIZE * sizeof(TCHAR)	// size of buffer 
							, &cbBytesRead					// number of bytes read 
							, NULL							// not overlapped I/O 
						);

		if (! fSuccess || cbBytesRead == 0) 
			break; 

		szReceive[cbBytesRead] = 0;
		ATLTRACE(_T("%4i bytes received\n"), cbBytesRead);

		//TFInst_GetAnswerToRequest(szReceive, strReply, cbReplyBytes, rStartInst); 
		TFInst_OnReceived(szReceive, rStartInst);
	 
		// Write the reply to the pipe. 
		//fSuccess = ::WriteFile( 
		//					hPipe			// handle to pipe 
		//					, strReply		// buffer to write from 
		//					, cbReplyBytes	// number of bytes to write 
		//					, &cbWritten	// number of bytes written 
		//					, NULL			// not overlapped I/O 
		//				);
		//
		//if (! fSuccess || cbReplyBytes != cbWritten) 
		//	break; 
	} 
 
	// Flush the pipe to allow the client to read the pipe's contents 
	// before disconnecting. Then disconnect the pipe, and close the 
	// handle to this pipe instance. 
	::FlushFileBuffers		(hPipe); 
	::DisconnectNamedPipe	(hPipe); 
	::CloseHandle			(hPipe); 

	TFInst_OnShutdown(rStartInst);

	return dwErr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10/04/2007 10:45:31
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/ 
void CPipeServerThread::TFInst_OnReceived(
										const CString & strReceived
										, const CPipeServerInstanceThreadParams & rStartInst
									)
{
	DWORD dwNumChars = strReceived.GetLength();
	TCHAR * pszRcvd = new TCHAR[dwNumChars + 5];
	ATLASSERT(pszRcvd);

	if(pszRcvd){
		
		_tcscpy(pszRcvd, strReceived);

		bool bTX = rStartInst.PostTargetMessage(eWM_PIPE_DATA_RECEIVED, LPARAM(pszRcvd));
		ATLASSERT(bTX);

		if(!bTX){
			delete [] pszRcvd;
			pszRcvd = 0;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/04/2007 09:51:29
	DESCRIP:	
		eWM_PIPE_INSTANCE_STARTUP			//no args
	IN:
	OUT:
*/
/*static*/
void CPipeServerThread::TFInst_OnStartup(const CPipeServerInstanceThreadParams & rStartInst)
{
	ATLTRACE(_T("Pipe Instance Startup...\n"));
	rStartInst.PostTargetMessage(eWM_PIPE_INSTANCE_STARTUP, 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/04/2007 09:51:27
	DESCRIP:	
		eWM_PIPE_INSTANCE_SHUTDOWN		//no args
	IN:
	OUT:
*/
/*static*/
void CPipeServerThread::TFInst_OnShutdown(const CPipeServerInstanceThreadParams & rStartInst)
{
	ATLTRACE(_T("... Pipe Instance Shutdown\n"));
	rStartInst.PostTargetMessage(eWM_PIPE_INSTANCE_SHUTDOWN, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   13 July 2006 07:45:23	
	DESC:		
	IN:
	OUT:
*/
/*static*/ 
void CPipeServerThread::TFInst_GetAnswerToRequest(
											const CString & strRequest
											, CString & strReply
											, DWORD & dwToWrite
											, const CPipeServerInstanceThreadParams & rStartInst
										)
{
	CString strACKNAK = _T("NAK");

	DWORD dwNumChars = strRequest.GetLength();
	TCHAR * pszRequest = new TCHAR[dwNumChars + 5];
	ATLASSERT(pszRequest);

	if(pszRequest){
		
		_tcscpy(pszRequest, strRequest);

		bool bTX = rStartInst.PostTargetMessage(eWM_PIPE_DATA_RECEIVED, LPARAM(pszRequest));
		ATLASSERT(bTX);

		if(bTX)
			strACKNAK = _T("ACK");
		else{
			delete [] pszRequest;
			pszRequest = 0;
		}
	}


	CSystemTime2 dtsys;
	strReply.Format(_T("[%s] [%s] [%s]"), dtsys.GetTimeStr(), strACKNAK, strRequest);
	dwToWrite = (strReply.GetLength() + 1) * sizeof(TCHAR);
}


}	// end of namespace PIPE_SERVER
