#include "StdAfx.h"
#include "pipeserverinstancethreadparams.h"


namespace PIPE_SERVER{


CPipeServerInstanceThreadParams::CPipeServerInstanceThreadParams(
															const HWND hwndTgt
															, const DWORD dwTgtTID
															, const HANDLE hPipe
														)
:	m_hPipe			(hPipe)
	, m_dwTgtTID	(dwTgtTID)
	, m_hwndTgt		(hwndTgt)
{
}

CPipeServerInstanceThreadParams::~CPipeServerInstanceThreadParams(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19-Jul-2006 07:44:54
	DESC:	
	IN:		
	OUT:	
*/
bool CPipeServerInstanceThreadParams::PostTargetMessage(const DWORD dwMsg, const LPARAM lParam) const
{
	BOOL bOK = FALSE;

	if(m_dwTgtTID)
		bOK = ::PostThreadMessage(m_dwTgtTID, dwMsg, ::GetCurrentThreadId(), lParam);

	else if(m_hwndTgt)
		bOK = ::PostMessage(m_hwndTgt, dwMsg, ::GetCurrentThreadId(), lParam);

	ATLASSERT(bOK);

	return bOK ? true : false;
}



}	//end of namespace PIPE_SERVER
