#pragma once

#include "basicthread3startparams.h"

namespace INCLUDE_SERVICES{


namespace BASE_THREAD3{

typedef struct tagTHREADNAME_INFO
{
   DWORD dwType; // must be 0x1000
   char * szName; // pointer to name (in user addr space)
   DWORD dwThreadID; // thread ID (-1=caller thread)
   DWORD dwFlags; // reserved for future use, must be zero
} THREADNAME_INFO;

//static DWORD WINAPI MyThreadFunction( LPVOID lpThreadParameter );
//#include <basicthread3.h>
//using namespace INCLUDE_SERVICES::BASE_THREAD3;

class CBasicThread3
{
public:
	CBasicThread3(void);
	virtual ~CBasicThread3(void);

public:
	bool IsThreadRunning(void) const;
	inline DWORD GetWrappedThreadID(void) const { return m_dwRunningThreadID; };	//15 February 2005 21:47:09

protected:
	bool PostThreadMsg(const DWORD dwMsg, WPARAM wParam, LPARAM lParam);

protected:
	bool StartBaseThread(
				const CString & strDbgThrdName
				, LPTHREAD_START_ROUTINE pThreadFunc
				, LPVOID pParams
			);

	DWORD StopBaseThread(const DWORD dwWaitMSecs);

private:
	static DWORD WINAPI TF_MainWrapper( LPVOID lpThreadParameter );
	static void SetThreadName(const DWORD dwThreadID, LPCTSTR szThreadName);

	HANDLE m_hndlThread;
	DWORD m_dwRunningThreadID;
};



}	//end of namespace BASE_THREAD



}	//end of namespace INCLUDE_SERVICES
