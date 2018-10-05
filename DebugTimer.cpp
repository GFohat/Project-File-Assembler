#include "StdAfx.h"
#include "debugtimer.h"



namespace INCLUDE_SERVICES{


namespace DBGTMR{

CDebugTimer::CDebugTimer(const CString & strName)
:	m_dwStartTickCount	(::GetTickCount())
	, m_bReported		(false)
	, m_strName			(strName)
{
}

CDebugTimer::CDebugTimer(
					const DWORD dwStartTickCount
					, const CString & strName
				)
:	m_dwStartTickCount	(dwStartTickCount)
	, m_bReported		(false)
	, m_strName			(strName)
{
	//disable if zero
	if(!m_dwStartTickCount)
		m_bReported = true;
}

CDebugTimer::~CDebugTimer(void)
{
	if(!m_bReported)
		ReportTime(false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   02 March 2005 20:39:56	
	DESC:		
	IN:
	OUT:
*/
void CDebugTimer::ReportTime(const bool bResetStopwatch)
{
	m_bReported = true;

#ifdef _DEBUG
	SYSTEMTIME dtsys;
	memset(&dtsys, 0, sizeof(SYSTEMTIME));
	::GetLocalTime(&dtsys);

	ATLTRACE(
			_T("%02i:%02i:%02i.%03i> (%05i msecs) %s\n")
			, dtsys.wHour, dtsys.wMinute, dtsys.wSecond, dtsys.wMilliseconds
			, ::GetTickCount() - m_dwStartTickCount
			, m_strName
		);
#endif

	if(bResetStopwatch)
		ResetStopWatch(::GetTickCount());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   02 March 2005 20:49:24	
	DESC:		
	IN:
	OUT:
*/
void CDebugTimer::ResetStopWatch(const DWORD dwStartTickCount)
{
	m_dwStartTickCount = dwStartTickCount;
	m_bReported = false;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	08/05/2007 09:00:24
	DESCRIP:	
	IN:
	OUT:
*/
DWORD CDebugTimer::GetCurLapse(void) const
{
	DWORD dwLapse = ::GetTickCount();
	dwLapse -= m_dwStartTickCount;

	return dwLapse;
}



}	//end of namespace DBGTMR



}	//end of namespace INCLUDE_SERVICES
