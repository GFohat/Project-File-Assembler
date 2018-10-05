#include "stdafx.h"
#include ".\paramscopyprogress.h"

namespace PARAMS{


CParamsCopyProgress::CParamsCopyProgress(const HWND hwndMsgTarget)
:	m_hwndMsgTarget		(hwndMsgTarget)
	, m_dwSeenInCPR		(0L)
{
}

CParamsCopyProgress::~CParamsCopyProgress(void)
{
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   04 November 2004 18:50:05	
	DESC:		
	IN:
	OUT:
*/
BOOL CParamsCopyProgress::PostMsg(const DWORD dwMsg, WPARAM wParam, LPARAM lParam) const
{
	BOOL bTX = FALSE;
	
	//bTX = ::PostThreadMessage(m_dwThrdMsgTarget, dwMsg, wParam, lParam);
	bTX = ::PostMessage(m_hwndMsgTarget, dwMsg, wParam, lParam);

	_ASSERTE(bTX);
	return bTX;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	09/03/2007 14:57:05
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CParamsCopyProgress::SendMsg(const DWORD dwMsg, WPARAM wParam, LPARAM lParam) const
{
	BOOL bTX = FALSE;
	
	//bTX = ::PostThreadMessage(m_dwThrdMsgTarget, dwMsg, wParam, lParam);
	bTX = ::SendMessage(m_hwndMsgTarget, dwMsg, wParam, lParam);

	//_ASSERTE(bTX);
	return bTX;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   07 November 2004 18:23:11	
	DESC:		
	IN:
	OUT:
*/
DWORD CParamsCopyProgress::SeenInCPR(void)
{
	m_dwSeenInCPR ++;
	return m_dwSeenInCPR;
}

};	//end of namespace PARAMS
