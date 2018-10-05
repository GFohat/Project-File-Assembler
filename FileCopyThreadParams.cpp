// FileCopyThreadParams.cpp: implementation of the CFileCopyThreadParams class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "FileCopyThreadParams.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileCopyThreadParams::CFileCopyThreadParams(HWND hwndTarget)
:	m_hwndTarget	(hwndTarget)
{

}

CFileCopyThreadParams::~CFileCopyThreadParams()
{

}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 08:35:29
	DESCRIP:	
	IN:
	OUT:
*/
const CFileCopyThreadParams & CFileCopyThreadParams::operator = (const CFileCopyThreadParams & src)
{
#pragma message ("CFileCopyThreadParams::operator =")

	m_hwndTarget = src.m_hwndTarget;

	return * this;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 09:01:25
	DESCRIP:	
	IN:
	OUT:
*/
bool CFileCopyThreadParams::PostTargetMessage(DWORD dwMsg, WPARAM wParam, LPARAM lParam) const
{
	BOOL bTX = ::PostMessage(m_hwndTarget, dwMsg, wParam, lParam);
	return bTX ? true : false;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 14:59:53
	DESCRIP:	
	IN:
	OUT:
*/
/*virtual*/
bool CFileCopyThreadParams::DoCreateDirectory(void)
{
	return true;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 14:59:50
	DESCRIP:	
	IN:
	OUT:
*/
/*virtual*/
bool CFileCopyThreadParams::DoEmptyDirectory(void)
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 14:59:48
	DESCRIP:	
	IN:
	OUT:
*/
/*virtual*/
void CFileCopyThreadParams::ReportFCEvent(const CFileCopyReport & report)
{
	CFileCopyReport * pSend = new CFileCopyReport(report);
	ATLASSERT(pSend);

	if(pSend){
		bool bTX = PostTargetMessage(eWM_EVENT_REPORT, 0, LPARAM(pSend));

		if(!bTX){
			delete pSend;
			pSend = 0;
		}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 09:31:54
	DESCRIP:	
	IN:
	OUT:
*/
/*virtual*/
void CFileCopyThreadParams::ReportDIEvent(const CFileCopyReport & report)
{
	ReportFCEvent(report);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 09:53:34
	DESCRIP:	
	IN:
	OUT:
*/
/*virtual*/
void CFileCopyThreadParams::OnNewDirectory(const CString & strDir, const DWORD dwOPNumber, const DWORD dwStepNumber)
{
	CDirInitHandler::IsNewDestinationDir(strDir, dwOPNumber, dwStepNumber);
}
