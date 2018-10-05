#include "StdAfx.h"
#include "namedpipeclient.h"

#include "ConstPipe.h" //namespace CONS_PIPE

namespace PIPE_CLIENT{


CNamedPipeClient::CNamedPipeClient(void)
{
}

CNamedPipeClient::~CNamedPipeClient(void)
{
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   13 July 2006 19:14:31	
	DESC:		
	IN:
	OUT:
*/
HRESULT CNamedPipeClient::SendToPipe(
								const CString & strServerName
								, const CString & strPipeName
								, const CString & strMsg
								, CString & strReply
								, CString & strError
							) const
{
	CString strFullPipeName;
	strFullPipeName.Format(_T("\\\\%s\\Pipe\\%s"), strServerName, strPipeName);

	return SendToPipe(strFullPipeName, strMsg, strReply, strError);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12-Jul-2006 14:41:57
	DESC:	
	IN:		
	OUT:	
*/
HRESULT CNamedPipeClient::SendToPipe(
								const CString & strPipeFullName
								, const CString & strMsg
								, CString & strReply
								, CString & strError
							) const
{
	HRESULT hr = S_OK;
	HANDLE hPipe = 0L; 

	strError = _T("<No Error>");


	strReply.Empty();

	try{
		// Try to open a named pipe; wait for it, if necessary. 
		THR( hr = ConnectToPipeServer(hPipe, strPipeFullName, 20000L, strError) );

		// The pipe connected; change to message-read mode. 
		THR( hr = AdjustPipeMode(hPipe, strError) );
			
		// Send a message to the pipe server. 
		THR( hr = WritePipeMessage(hPipe, strMsg, strError) );
		
		//read any reply, probably just ACK / NAK
		THR( hr = ReadPipeMessage(hPipe, strReply, strError) );

		ATLTRACE(_T("CNamedPipeClient::SendToPipe, reply = \"%s\"\n"), strReply);

		/*******************************************************************************\

			Leave these bits in just for the example, but no reply will be expected
			- replies are planned to be asynchronous to a different pipe
			- just 'ACK' or something?

		\*******************************************************************************/
	}
	//-----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ATLASSERT(false);
	}

	if(hPipe)
		::CloseHandle(hPipe); 

	return hr;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02-Aug-2006 07:29:45
	DESC:	
	IN:		
	OUT:	
*/
HRESULT CNamedPipeClient::ReadPipeMessage(
										HANDLE & hPipe
										, CString & strMsg
										, CString & strError
									) const
{
	HRESULT hr = S_OK;

	static TCHAR szBuffer[CONS_PIPE::dwIN_BUF_SIZE + 5];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	BOOL fSuccess; 
	DWORD cbRead; 

	do{ 
		// Read from the pipe. 
		fSuccess = ::ReadFile( 
							hPipe							// pipe handle 
							, szBuffer						// buffer to receive reply 
							, CONS_PIPE::dwIN_BUF_SIZE * sizeof(TCHAR)	// size of buffer 
							, &cbRead						// number of bytes read 
							, NULL							// not overlapped 
						);
		
		if (! fSuccess && ::GetLastError() != ERROR_MORE_DATA) 
			break; 
		
		strMsg += szBuffer;

	} while (!fSuccess);  // repeat loop if ERROR_MORE_DATA 

	return hr;
}

	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	17-Jul-2006 13:56:11
	DESC:	
	IN:		
	OUT:	
*/
HRESULT CNamedPipeClient::WritePipeMessage(
										HANDLE & hPipe
										, const CString & strMsg
										, CString & strError
									) const
{
	DWORD dwWritten = 0L;
	CString strLocal(strMsg);

	DWORD dwMsgLen = (strLocal.GetLength() + 1) * sizeof(TCHAR);

	BOOL bOK = ::WriteFile( 
						hPipe					// pipe handle 
						, strLocal.GetBuffer(strLocal.GetLength())	// message 
						, dwMsgLen				// message length 
						, &dwWritten			// bytes written 
						, NULL					// not overlapped 
					);

	strLocal.ReleaseBuffer();

	if (!bOK) 
		HandlePipeError(_T("CNamedPipeClient::WritePipeMessage"), _T("::WriteFile"), 0L, strError); 

	return bOK ? S_OK : E_FAIL;
}

	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	17-Jul-2006 13:52:18
	DESC:	
	IN:		
	OUT:	
*/
HRESULT CNamedPipeClient::AdjustPipeMode(
									HANDLE & hPipe
									, CString & strError
								) const
{
	DWORD dwMode = PIPE_READMODE_MESSAGE; 

	BOOL bOK = ::SetNamedPipeHandleState( 
										hPipe		// pipe handle 
										, &dwMode	// new pipe mode 
										, NULL		// don't set maximum bytes 
										, NULL		// don't set maximum time 
									);
	if (!bOK) 
		HandlePipeError(_T(""), _T("::SetNamedPipeHandleState"), 0L, strError); 

	return bOK ? S_OK : E_FAIL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14-Jul-2006 08:34:32
	DESC:	
	IN:		
	OUT:	
*/
HRESULT CNamedPipeClient::ConnectToPipeServer(
										HANDLE & hPipe
										, const CString & strPipeFullName
										, const DWORD dwTimeOutMSecs
										, CString & strError
									) const
{
	bool bAttempting = true;
	bool bConnected = false;

	// Try to open a named pipe; wait for it, if necessary. 
	while (bAttempting) 
	{ 
		hPipe = ::CreateFile( 
						strPipeFullName		// pipe name 
						, GENERIC_READ |	// read and write access 
							GENERIC_WRITE 
						, 0					// no sharing 
						, NULL				// default security attributes
						, OPEN_EXISTING		// opens existing pipe 
						, 0					// default attributes 
						, NULL				// no template file 
					);
	 
		// Break if the pipe handle is valid.
		if (hPipe != INVALID_HANDLE_VALUE){
			bConnected = true;
			bAttempting = false;
		}
		else{
			// Exit if an error other than ERROR_PIPE_BUSY occurs. 
			if (GetLastError() == ERROR_PIPE_BUSY) 
			{
				if (!::WaitNamedPipe(strPipeFullName, dwTimeOutMSecs)) 
				{ 
					HandlePipeError(_T(""), _T("::WaitNamedPipe"), 0L, strError); 
					bConnected = false;
					bAttempting = false;
				} 
			}
			else{
				HandlePipeError(_T(""), _T("::CreateFile"), 0L, strError);
				bConnected = false;
				bAttempting = false;
			}
		}
	} 

	return bConnected ? S_OK : E_FAIL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   13 July 2006 19:21:14	
	DESC:		
	IN:
	OUT:
*/
void CNamedPipeClient::HandlePipeError(
									const CString & strFunction
									, const CString & strStage
									, const DWORD dwError
									, CString & strError
								) const
{
	DWORD dwPipeError = dwError ? dwError : ::GetLastError();

	switch(dwPipeError){
		case ERROR_FILE_NOT_FOUND:
			strError.Format(_T("ERROR_FILE_NOT_FOUND %s from %s"), strStage, strFunction);
			break;

		case ERROR_IO_PENDING:
			strError.Format(_T("ERROR_IO_PENDING %s from %s"), strStage, strFunction);
			break;

		case ERROR_BROKEN_PIPE:
			strError.Format(_T("ERROR_BROKEN_PIPE %s from %s"), strStage, strFunction);
			break;

		case ERROR_NO_DATA:
			strError.Format(_T("ERROR_NO_DATA %s from %s"), strStage, strFunction);
			break;

		case ERROR_PIPE_NOT_CONNECTED:
			strError.Format(_T("ERROR_PIPE_NOT_CONNECTED %s from %s"), strStage, strFunction);
			break;

		case ERROR_PIPE_BUSY:
			strError.Format(_T("ERROR_PIPE_BUSY %s from %s"), strStage, strFunction);
			break;

		case ERROR_ACCESS_DENIED:
			strError.Format(_T("ERROR_ACCESS_DENIED %s from %s"), strStage, strFunction);
			break;

		default:
			strError.Format(_T("Error %d in %s from %s"), dwPipeError, strStage, strFunction);
	}

	ATLTRACE(_T("%s\n"), strError);
}


}	// end of namespace PIPE_CLIENT
