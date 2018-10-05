#pragma once

#include "pipes\pipeserverthreadparams.h"
#include "pipes\pipeserverinstancethreadparams.h"

#include "basicthread3.h"
using namespace INCLUDE_SERVICES::BASE_THREAD3;

namespace PIPE_SERVER{


class CPipeServerThread
:	public CBasicThread3
{
public:
	CPipeServerThread(void);
	~CPipeServerThread(void);

public:
	bool StartPipeServerThread(const CPipeServerThreadParams & rParams);
	void StopPipeServerThread(void);

private:
	static DWORD WINAPI TF_PipeServerWrapper(LPVOID lpThreadParams);

	static DWORD	TF_PipeServerMainLoop	(const CPipeServerThreadParams & rParams);

	static void		TF_CreatePipe			(HANDLE & hPipe, const CPipeServerThreadParams & rParams);
	//static void		TF_CreatePipe			(CHandleWrapper & hPipe, const CPipeServerThreadParams & rParams);

	static bool TF_WaitPipeConnection(
									HANDLE & hPipe
									, bool & bContinueLoop
									, const CPipeServerThreadParams & rParams
								);
	//static bool TF_WaitPipeConnection(
	//								CHandleWrapper & hPipe
	//								, bool & bContinueLoop
	//								, const CPipeServerThreadParams & rParams
	//							);

	static bool TF_ProcessMessages(const CPipeServerThreadParams & rParams);
	static void TF_CloseIfValid(HANDLE & hPipe);

private:
	static DWORD WINAPI TFInst_InstanceThreadWrap(LPVOID lpThreadParams);
	static DWORD        TFInst_InstanceThreadMain(const CPipeServerInstanceThreadParams & rStartInst);

	static void TFInst_OnReceived(
								const CString & strReceived
								, const CPipeServerInstanceThreadParams & rStartInst
							);

	static void TFInst_OnStartup(
								const CPipeServerInstanceThreadParams & rStartInst
							);

	static void TFInst_OnShutdown(
								const CPipeServerInstanceThreadParams & rStartInst
							);

	static void TFInst_GetAnswerToRequest(
								const CString & strRequest
								, CString & strReply
								, DWORD & dwToWrite
								, const CPipeServerInstanceThreadParams & rStartInst
							);
};


}	// end of namespace PIPE_SERVER

/*
DWORD WINAPI InstanceThread(LPVOID); 
VOID GetAnswerToRequest(LPTSTR, LPTSTR, LPDWORD); 
 
int _tmain(VOID) 
{ 
	BOOL fConnected; 
	DWORD dwThreadId; 
	HANDLE hPipe, hThread; 
	LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe"); 
	 
	// The main loop creates an instance of the named pipe and 
	// then waits for a client to connect to it. When the client 
	// connects, a thread is created to handle communications 
	// with that client, and the loop is repeated. 
	 
	for (;;) 
	{ 
		hPipe = CreateNamedPipe( 
			lpszPipename,             // pipe name 
			PIPE_ACCESS_DUPLEX,       // read/write access 
			PIPE_TYPE_MESSAGE |       // message type pipe 
			PIPE_READMODE_MESSAGE |   // message-read mode 
			PIPE_WAIT,                // blocking mode 
			PIPE_UNLIMITED_INSTANCES, // max. instances  
			BUFSIZE,                  // output buffer size 
			BUFSIZE,                  // input buffer size 
			NMPWAIT_USE_DEFAULT_WAIT, // client time-out 
			NULL);                    // default security attribute 

		if (hPipe == INVALID_HANDLE_VALUE) 
		{
			printf("CreatePipe failed"); 
			return 0;
		}
	 
		// Wait for the client to connect; if it succeeds, 
		// the function returns a nonzero value. If the function
		// returns zero, GetLastError returns ERROR_PIPE_CONNECTED. 
	 
		fConnected = ConnectNamedPipe(hPipe, NULL) ? 
			TRUE : (GetLastError() == ERROR_PIPE_CONNECTED); 
 
		if (fConnected) 
		{ 
			// Create a thread for this client. 
			hThread = CreateThread( 
				NULL,              // no security attribute 
				0,                 // default stack size 
				InstanceThread,    // thread proc
				(LPVOID) hPipe,    // thread parameter 
				0,                 // not suspended 
				&dwThreadId);      // returns thread ID 

			if (hThread == NULL) 
			{
				printf("CreateThread failed"); 
				return 0;
			}
			else 
				CloseHandle(hThread); 
		} 
		else 
			// The client could not connect, so close the pipe. 
			CloseHandle(hPipe); 
   }

   return 1; 
} 
 
DWORD WINAPI InstanceThread(LPVOID lpvParam) 
{ 
	TCHAR chRequest[BUFSIZE]; 
	TCHAR chReply[BUFSIZE]; 
	DWORD cbBytesRead, cbReplyBytes, cbWritten; 
	BOOL fSuccess; 
	HANDLE hPipe; 
	 
	// The thread's parameter is a handle to a pipe instance. 
	 
	hPipe = (HANDLE) lpvParam; 
	 
	while (1) 
	{ 
		// Read client requests from the pipe. 
		fSuccess = ReadFile( 
			hPipe,        // handle to pipe 
			chRequest,    // buffer to receive data 
			BUFSIZE*sizeof(TCHAR), // size of buffer 
			&cbBytesRead, // number of bytes read 
			NULL);        // not overlapped I/O 

		if (! fSuccess || cbBytesRead == 0) 
			break; 
		
		GetAnswerToRequest(chRequest, chReply, &cbReplyBytes); 
	 
		// Write the reply to the pipe. 
		fSuccess = WriteFile( 
			hPipe,        // handle to pipe 
			chReply,      // buffer to write from 
			cbReplyBytes, // number of bytes to write 
			&cbWritten,   // number of bytes written 
			NULL);        // not overlapped I/O 

		if (! fSuccess || cbReplyBytes != cbWritten) break; 
	} 
 
	// Flush the pipe to allow the client to read the pipe's contents 
	// before disconnecting. Then disconnect the pipe, and close the 
	// handle to this pipe instance. 
	FlushFileBuffers(hPipe); 
	DisconnectNamedPipe(hPipe); 
	CloseHandle(hPipe); 

	return 1;
}

VOID GetAnswerToRequest(LPTSTR chRequest, 
   LPTSTR chReply, LPDWORD pchBytes)
{
   _tprintf( TEXT("%s\n"), chRequest );
   lstrcpy( chReply, TEXT("Default answer from server") );
   *pchBytes = (lstrlen(chReply)+1)*sizeof(TCHAR);
}

*/