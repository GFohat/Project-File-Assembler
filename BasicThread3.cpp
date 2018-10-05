#include "StdAfx.h"
#include "basicthread3.h"


namespace INCLUDE_SERVICES{


namespace BASE_THREAD3{


CBasicThread3::CBasicThread3(void)
:	m_hndlThread			(0)
	, m_dwRunningThreadID	(0L)
{
}

CBasicThread3::~CBasicThread3(void)
{
	StopBaseThread(5000L);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   08 February 2005 22:37:55	
	DESC:		
	IN:
	OUT:
*/
bool CBasicThread3::IsThreadRunning(void) const
{
	const bool bRunID	= m_dwRunningThreadID ? true : false;
	const bool bHandle	= m_hndlThread ? true : false;
	const bool bValid	= (m_hndlThread != INVALID_HANDLE_VALUE);

	//these should keep in lockstep with each other
	//either they're all false or they're all true
	//RUBBISH!
	//ATLASSERT(bRunID == bHandle);
	//ATLASSERT(bRunID == bValid);

	return bRunID && bHandle && bValid;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22-Nov-2005 07:47:25
	DESC:	
	IN:		
	OUT:	
*/
bool CBasicThread3::PostThreadMsg(const DWORD dwMsg, WPARAM wParam, LPARAM lParam)
{
	if(!IsThreadRunning())
		return false;

	BOOL bTX = ::PostThreadMessage(m_dwRunningThreadID, dwMsg, wParam, lParam);

	return bTX ? true : false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   08 February 2005 22:38:00	
	DESC:		
	IN:
	OUT:
*/
bool CBasicThread3::StartBaseThread(
								const CString & strDbgThrdName
								, LPTHREAD_START_ROUTINE pThreadFunc
								, LPVOID pParams
							)
{
	ATLASSERT(pThreadFunc);
	ATLASSERT(pParams);			//may be intentional - sorry!

	StopBaseThread(5000);

	CBasicThread3StartParams * pStart = new CBasicThread3StartParams;
	ATLASSERT(pStart);

	if(pStart){
		
		pStart->m_pParams = pParams;
		pStart->m_pThreadStartRoutine = pThreadFunc;
		pStart->m_strThreadName = strDbgThrdName;

		//Returns the handle to the newly created thread or NULL on failure
		m_hndlThread = ::CreateThread(
									0
									, 0
									, TF_MainWrapper
									, LPVOID(pStart)
									, 0
									, &m_dwRunningThreadID
								);

		ATLASSERT(m_hndlThread);
		if(!m_hndlThread){
			DWORD dwError = ::GetLastError();
			delete pStart;
			pStart = 0;
		}
	}

	ATLASSERT(m_hndlThread);
	ATLASSERT(m_hndlThread != INVALID_HANDLE_VALUE);

	return IsThreadRunning();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   08 February 2005 22:38:03	
	DESC:		
	IN:
	OUT:
*/
DWORD CBasicThread3::StopBaseThread(const DWORD dwWaitMSecs)
{
	DWORD dwWait = WAIT_OBJECT_0;

	if(IsThreadRunning()){
		::PostThreadMessage(m_dwRunningThreadID, WM_QUIT, 0, 0);

		dwWait = ::WaitForSingleObject(m_hndlThread, dwWaitMSecs);

		if(WAIT_OBJECT_0 != dwWait){

			CString strFailure;
			strFailure.Format(
						_T("!!!! TID %05u (0x%X - HANDLE 0x%X) is being TERMINATED !!!! (Wait result = 0x%X, GetLastError returns 0x%X)")
						, m_dwRunningThreadID
						, m_dwRunningThreadID
						, m_hndlThread
						, dwWait
						, ::GetLastError()
					);

#ifdef USING_CONSOLE

			g_console.WriteAnEvent(_T("%s"), strFailure);
#else

			ATLTRACE(_T("\n\n%s\n\n"), strFailure);

#endif	//USING_CONSOLE

			::TerminateThread(m_hndlThread, dwWait);
		}

		::CloseHandle(m_hndlThread);
		m_hndlThread		= 0;
		m_dwRunningThreadID = 0L;
	}

	return dwWait;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   10 February 2005 20:21:21	
	DESC:	
		Decodes its own start up params.
		Sets the threadname.
		Unwrap the address of the function that we want to call
		, which is the address of the function passed to StartBaseThread
		Call the function.
		Clean up.
	IN:
	OUT:
*/
/*static*/ 
DWORD WINAPI CBasicThread3::TF_MainWrapper( LPVOID lpThreadParameter )
{
	DWORD dwRet = 0L;

	CBasicThread3StartParams * pStartParams = reinterpret_cast<CBasicThread3StartParams *>(lpThreadParameter);
	ATLASSERT(pStartParams);

	if(pStartParams){
		SetThreadName(::GetCurrentThreadId(), pStartParams->m_strThreadName);

		ATLASSERT(pStartParams->m_pThreadStartRoutine);
		if(pStartParams->m_pThreadStartRoutine){
			dwRet = (pStartParams->m_pThreadStartRoutine(pStartParams->m_pParams));
		}

		delete pStartParams;
		pStartParams = 0;
	}

	return dwRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   10 February 2005 20:28:32	
	DESC:		
	IN:
	OUT:
*/
/*static*/ 
void CBasicThread3::SetThreadName(const DWORD dwThreadID, LPCTSTR szThreadName)
{
	THREADNAME_INFO info;

	info.dwType			= 0x1000;
	bool bNew			= false;

#ifdef UNICODE

	bNew				= true;
	int iWideLen		= int(_tcslen(szThreadName)) + 2;
	int iMBLen			= iWideLen;

	info.szName			= new char[iWideLen + 5];
	ZeroMemory(info.szName, iWideLen);
	
	int iResult = ::WideCharToMultiByte(
									CP_OEMCP		//uCodePage
									, 0	//dwFlags 
									, szThreadName
									, iWideLen
									, info.szName
									, iMBLen
									, 0
									, 0
								);

	info.szName[iMBLen] = 0;

	if(0 == iResult){
		DWORD dwErr = ::GetLastError();
		ATLTRACE(_T("WideCharToMultiByte - GetLastError = %u\n"), dwErr);
	}

#else	//#ifdef UNICODE

	USES_CONVERSION;

#pragma message("CBasicThread3::SetThreadName")
	//info.szName			= szThreadName;

#endif	//#ifdef UNICODE

	info.dwThreadID		= dwThreadID;
	info.dwFlags		= 0;

	__try
	{
		RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD), (DWORD*)&info );
	}

	__except(EXCEPTION_CONTINUE_EXECUTION)
	{
	}

	if(bNew && info.szName)
		delete [] info.szName;
}

}	//end of namespace BASE_THREAD



}	//end of namespace INCLUDE_SERVICES
