#pragma once

//#include "Pipes\namedpipeclient.h"

namespace PIPE_CLIENT{


class CNamedPipeClient
{
public:
	CNamedPipeClient(void);
	~CNamedPipeClient(void);

public:
	HRESULT SendToPipe(
						const CString & strServerName
						, const CString & strPipeName
						, const CString & strMsg
						, CString & strReply
						, CString & strError
					) const;

	HRESULT SendToPipe(
						const CString & strPipeFullName
						, const CString & strMsg
						, CString & strReply
						, CString & strError
					) const;

private:
	HRESULT ConnectToPipeServer(
						HANDLE & hPipe
						, const CString & strPipeFullName
						, const DWORD dwTimeOutMSecs
						, CString & strError
					) const;

	HRESULT AdjustPipeMode(
						HANDLE & hPipe
						, CString & strError
					) const;

	HRESULT WritePipeMessage(
						HANDLE & hPipe
						, const CString & strMsg
						, CString & strError
					) const;

	HRESULT ReadPipeMessage(
						HANDLE & hPipe
						, CString & strMsg
						, CString & strError
					) const;

	void HandlePipeError(
				const CString & strFunction
				, const CString & strStage
				, const DWORD dwError
				, CString & strError
			) const;
};


}	// end of namespace PIPE_CLIENT

/*
	HANDLE hPipe; 
	LPTSTR lpvMessage=TEXT("Default message from client"); 
	TCHAR chBuf[BUFSIZE]; 
	BOOL fSuccess; 
	DWORD cbRead, cbWritten, dwMode; 
	LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe"); 

	if( argc > 1 )
		lpvMessage = argv[1];
	 
	// Try to open a named pipe; wait for it, if necessary. 
	 
	while (1) 
	{ 
		hPipe = CreateFile( 
			lpszPipename,   // pipe name 
			GENERIC_READ |  // read and write access 
			GENERIC_WRITE, 
			0,              // no sharing 
			NULL,           // default security attributes
			OPEN_EXISTING,  // opens existing pipe 
			0,              // default attributes 
			NULL);          // no template file 
	 
	// Break if the pipe handle is valid. 
	 
		if (hPipe != INVALID_HANDLE_VALUE) 
			break; 
	 
		// Exit if an error other than ERROR_PIPE_BUSY occurs. 
	 
		if (GetLastError() != ERROR_PIPE_BUSY) 
		{
			printf("Could not open pipe"); 
			return 0;
		}
	 
		// All pipe instances are busy, so wait for 20 seconds. 
	 
		if (!WaitNamedPipe(lpszPipename, 20000)) 
		{ 
			printf("Could not open pipe"); 
			return 0;
		} 
	} 
	 
	// The pipe connected; change to message-read mode. 
	 
	dwMode = PIPE_READMODE_MESSAGE; 
	fSuccess = SetNamedPipeHandleState( 
		hPipe,    // pipe handle 
		&dwMode,  // new pipe mode 
		NULL,     // don't set maximum bytes 
		NULL);    // don't set maximum time 
	if (!fSuccess) 
	{
		printf("SetNamedPipeHandleState failed"); 
		return 0;
	}
	 
	// Send a message to the pipe server. 
	 
	fSuccess = WriteFile( 
		hPipe,                  // pipe handle 
		lpvMessage,             // message 
		(lstrlen(lpvMessage)+1)*sizeof(TCHAR), // message length 
		&cbWritten,             // bytes written 
		NULL);                  // not overlapped 
	if (!fSuccess) 
	{
		printf("WriteFile failed"); 
		return 0;
	}
	 
	do 
	{ 
	// Read from the pipe. 
	 
		fSuccess = ReadFile( 
			hPipe,    // pipe handle 
			chBuf,    // buffer to receive reply 
			BUFSIZE*sizeof(TCHAR),  // size of buffer 
			&cbRead,  // number of bytes read 
			NULL);    // not overlapped 
	 
		if (! fSuccess && GetLastError() != ERROR_MORE_DATA) 
			break; 
	 
		_tprintf( TEXT("%s\n"), chBuf ); 
	} while (!fSuccess);  // repeat loop if ERROR_MORE_DATA 

	getch();
	 
	CloseHandle(hPipe); 
	 
	return 0; 

*/