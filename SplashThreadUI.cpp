// SplashThreadUI.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "SplashThreadUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*static*/ HWND CSplashThreadUI::s_hWndTarget = 0;

/////////////////////////////////////////////////////////////////////////////
// CSplashThreadUI

IMPLEMENT_DYNCREATE(CSplashThreadUI, CWinThread)

CSplashThreadUI::CSplashThreadUI()
:	m_pdlgSplash	(0)
{
}

CSplashThreadUI::~CSplashThreadUI()
{
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	09/05/2007 07:46:31
	DESCRIP:	
	IN:
	OUT:
*/
void CSplashThreadUI::SetTargetWnd(HWND hwnd)
{
	s_hWndTarget = hwnd;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 13:52:48
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CSplashThreadUI::InitInstance()
{
	::CoInitialize(0);

	ATLTRACE(_T("CSplashThreadUI::InitInstance() - TID: 0x%X\n"), ::GetCurrentThreadId());

	m_pdlgSplash = new CDlgSplash(s_hWndTarget);

	m_pdlgSplash->SetText		(_T("CSplashThreadUI"));
	m_pdlgSplash->Create		(IDD_DLG_SPLASH);
	m_pdlgSplash->CenterWindow	();
	m_pdlgSplash->ShowWindow	(SW_SHOW);

	m_pMainWnd = m_pdlgSplash;

	//BOOL bTX = ::PostMessage(s_hWndTarget, eWM_SPLASH_INIT_DONE, 0, 0);
	//ATLASSERT(bTX);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 13:52:51
	DESCRIP:	
	IN:
	OUT:
*/
int CSplashThreadUI::ExitInstance()
{
	ATLTRACE(_T("CSplashThreadUI::ExitInstance() - TID: 0x%X\n"), ::GetCurrentThreadId());

	if(m_pdlgSplash){
		m_pdlgSplash->ShowWindow(SW_HIDE);
		m_pdlgSplash->DestroyWindow();

		delete m_pdlgSplash;
		m_pdlgSplash = 0;
	}

	::CoUninitialize();

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSplashThreadUI, CWinThread)
	//{{AFX_MSG_MAP(CSplashThreadUI)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplashThreadUI message handlers
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	09/05/2007 07:32:24
	DESCRIP:	
	IN:
	OUT:
*/
/*virtual*/
int CSplashThreadUI::Run()
{
	ATLTRACE(_T("CSplashThreadUI::Run() - TID: 0x%X\n"), ::GetCurrentThreadId());

	return CWinThread::Run();
}
