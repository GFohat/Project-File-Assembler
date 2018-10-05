#include "StdAfx.h"
#include "pipeserverthreadparams.h"


namespace PIPE_SERVER{


CPipeServerThreadParams::CPipeServerThreadParams(const CString & strPipeName, const DWORD dwTIDTgt, const HWND hWndTgt)
:	m_strPipeName	(strPipeName)
	, m_dwTIDTgt	(dwTIDTgt)
	, m_hWndTgt		(hWndTgt)
{
}

CPipeServerThreadParams::CPipeServerThreadParams(const CPipeServerThreadParams & src)
{
	* this = src;
}

CPipeServerThreadParams::~CPipeServerThreadParams(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11-Jul-2006 14:20:36
	DESC:	
	IN:		
	OUT:	
*/
const CPipeServerThreadParams & CPipeServerThreadParams::operator = (const CPipeServerThreadParams & src)
{
#pragma message(">>>>    ")

	m_strPipeName	= src.m_strPipeName;
	m_dwTIDTgt		= src.m_dwTIDTgt;
	m_hWndTgt		= src.m_hWndTgt;

	return * this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12-Jul-2006 07:11:21
	DESC:	
	IN:		
	OUT:	
*/
bool CPipeServerThreadParams::PostTargetMessage(const DWORD dwMsg, const LPARAM lParam) const
{
	BOOL bOK = FALSE;

	if(m_dwTIDTgt)
		bOK = ::PostThreadMessage(m_dwTIDTgt, dwMsg, ::GetCurrentThreadId(), lParam);

	else if(m_hWndTgt)
		bOK = ::PostMessage(m_hWndTgt, dwMsg, ::GetCurrentThreadId(), lParam);

	ATLASSERT(bOK);

	return bOK ? true : false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12-Jul-2006 13:47:15
	DESC:	
	IN:		
	OUT:	
*/
//CString CPipeServerThreadParams::GetFullPipeName(void) const
//{
//	CString strRet;
//
//	strRet.Format(_T("\\\\.\\Pipe\\%s"), m_strPipeName);
//
//	return strRet;
//}

}	// end of namespace PIPE_SERVER
