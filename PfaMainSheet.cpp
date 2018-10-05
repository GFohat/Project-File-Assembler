// PfaMainSheet.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "PfaMainSheet.h"

#include "VersionNo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPfaMainSheet

IMPLEMENT_DYNAMIC(CPfaMainSheet, CPropertySheet)

CPfaMainSheet::CPfaMainSheet(LPCTSTR pszCaption)
:	CPropertySheet		(pszCaption)
	, m_pdlgSplash		(0)
	, m_pSplashThread	(0)
{
	ATLTRACE(_T("CPfaMainSheet::CPfaMainSheet\n"));

	m_psh.dwFlags |= PSH_NOAPPLYNOW;
	m_psh.dwFlags &= ~PSH_HASHELP;

	m_pageBatFiles		.m_psp.dwFlags		&= ~PSP_HASHELP;
	m_pageFileAssembler	.m_psp.dwFlags		&= ~PSP_HASHELP;
	m_pageInstallShield	.m_psp.dwFlags		&= ~PSP_HASHELP;
	m_pagePfaData		.m_psp.dwFlags		&= ~PSP_HASHELP;
	m_pageOptions		.m_psp.dwFlags		&= ~PSP_HASHELP;
	m_pageDataProps		.m_psp.dwFlags		&= ~PSP_HASHELP;
	m_pageLogging		.m_psp.dwFlags		&= ~PSP_HASHELP;
	m_pageLoggingOD		.m_psp.dwFlags		&= ~PSP_HASHELP;
	m_pageData			.m_psp.dwFlags		&= ~PSP_HASHELP;

	AddAllPages();
}

CPfaMainSheet::~CPfaMainSheet()
{
}


BEGIN_MESSAGE_MAP(CPfaMainSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CPfaMainSheet)
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI(ID_ACTION_COPYPROJECTFILES, OnUpdateActionCopyprojectfiles)
	ON_UPDATE_COMMAND_UI(ID_ACTION_VALIDATEPROJECT, OnUpdateActionValidateproject)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	//}}AFX_MSG_MAP

	ON_WM_INITMENUPOPUP()

	ON_MESSAGE(eWM_GET_FONT,			OnWMGetFont)
	ON_MESSAGE(eWM_PAGE_ACTIVATED,		OnWMPageActivated)
	ON_MESSAGE(eWM_SPLASH_INIT_DONE,	OnWMSplashInitDone)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPfaMainSheet message handlers
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 09:07:42
	DESCRIP:	
	IN:
	OUT:
*/
void CPfaMainSheet::AddAllPages(void)
{
	AddPage(&m_pageFileAssembler);
	AddPage(&m_pagePfaData);
	AddPage(&m_pageBatFiles);
	AddPage(&m_pageInstallShield);
	//AddPage(&m_pageOptions);
	AddPage(&m_pageDataProps);
	//AddPage(&m_pageLogging);
	//AddPage(&m_pageLoggingOD);
	AddPage(&m_pageData);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 09:08:29
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPfaMainSheet::OnInitDialog() 
{
	ATLTRACE(_T("CPfaMainSheet::OnInitDialog start - TID: 0x%X...\n"), ::GetCurrentThreadId());

	BOOL bResult = CPropertySheet::OnInitDialog();

	InitSheet();
	InitMenu();
	InitTabCtrl(GetTabControl());

	InitSplash();

	//We now wait for the splash dialog to send us back a 'eWM_SPLASH_INIT_DONE'
	//message, so see OnWMSplashInitDone below for  
	
// 	CDC * pdc = GetDC();
// 	InitFonts(pdc);
// 	ReleaseDC(pdc);
// 
// 	CControlPopulator::ConnectDb();
// 
// 	InitSheet();
// 	InitMenu();
// 	InitTabCtrl(GetTabControl());
// 
// 	for(int iPage = 0 ; iPage < GetPageCount() ; iPage++){
// 		SetActivePage(iPage);
// 	}
// 
// 	SetActivePage(1);
// 
// 	m_pageBatFiles.PostMessage(eWM_SET_APPEARANCE, 0, 0);
// 	m_pagePfaData.PostMessage(eWM_SET_APPEARANCE, 0, 0);
// 	m_pageFileAssembler.PostMessage(eWM_SET_APPEARANCE, 0, 0);
// 	m_pageInstallShield.PostMessage(eWM_SET_APPEARANCE, 0, 0);
// 	m_pageDataProps.PostMessage(eWM_SET_APPEARANCE, 0, 0);
// 
// 	CString strTitle;
// 	
// #ifdef _DEBUG
// 	strTitle.Format(_T("Project File Assembler (Debug Build) V%s"), STRFILEVER);
// #else
// 	strTitle.Format(_T("Project File Assembler (Release Build) V%s"), STRFILEVER);
// #endif
// 
// 	SetWindowText(strTitle);
// 	
// 	ATLTRACE(_T("CPfaMainSheet::OnInitDialog Finished\n"));
// 
// 	ExitSplash();

 	ATLTRACE(_T("CPfaMainSheet::OnInitDialog Finished\n"));

	return bResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	04/05/2007 17:30:45
	DESCRIP:
	
		This is effectively a continuation of OnInitDialog() above.
		
		This is performed after the splash dialog has told
		us it has initialized itself.

		We can now carry on with our possibly long-running
		tasks such as database connection etc.

	IN:
	OUT:
*/
/*afx_msg*/ 
LRESULT CPfaMainSheet::OnWMSplashInitDone(WPARAM wParam, LPARAM lParam)
{
	ATLTRACE(_T("CPfaMainSheet::OnWMSplashInitDone Starting...\n"));

	CDC * pdc = GetDC();
	InitFonts(pdc);
	ReleaseDC(pdc);
	
	CDataHandler::ConnectDb();
	
	int iPage = 0;
	for(iPage = 0 ; iPage < GetPageCount() ; iPage++){
		SetActivePage(iPage);
	}
	
	SetActivePage(1);

	for(iPage = 0 ; iPage < GetPageCount() ; iPage++){
		GetPage(iPage)->PostMessage(eWM_SET_APPEARANCE, 0, 0);
	}

	
	CString strTitle;
	
#ifdef _DEBUG
	strTitle.Format(_T("Project File Assembler (Debug Build) V%s"), static_cast<LPCTSTR>(CA2CT(STRFILEVER)));
#else
	strTitle.Format(_T("Project File Assembler (Release Build) V%s"), STRFILEVER);
#endif
	
	SetWindowText(strTitle);
	
	ATLTRACE(_T("CPfaMainSheet::OnWMSplashInitDone Finished - calling ExitSplash()\n"));
	
	ExitSplash();

	return TRUE;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 10:02:47
	DESCRIP:	
	IN:
	OUT:
*/
void CPfaMainSheet::InitSplash(void)
{
	//m_pdlgSplash = new CDlgSplash(m_hWnd);
	//m_pdlgSplash->Create(IDD_DLG_SPLASH);
	//m_pdlgSplash->CenterWindow();
	//m_pdlgSplash->ShowWindow(SW_SHOW);

	m_pSplashThread 
			= reinterpret_cast<CSplashThreadUI * >(::AfxBeginThread(RUNTIME_CLASS(CSplashThreadUI), 0, 0, CREATE_SUSPENDED, 0));
	ATLASSERT(m_pSplashThread);

	if(m_pSplashThread){
		m_pSplashThread->SetTargetWnd(m_hWnd);
		m_pSplashThread->m_bAutoDelete = FALSE;
		m_pSplashThread->ResumeThread();
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 10:02:45
	DESCRIP:	
	IN:
	OUT:
*/
void CPfaMainSheet::ExitSplash(void)
{
	//if(m_pdlgSplash){
		//m_pdlgSplash->ShowWindow(SW_HIDE);
		//m_pdlgSplash->DestroyWindow();

		//delete m_pdlgSplash;
	//}

	if(m_pSplashThread){
		m_pSplashThread->PostThreadMessage(WM_QUIT, 0, 0);

		//wait for thread to stop
		DWORD dwWait = ::WaitForSingleObject(m_pSplashThread->m_hThread, 10000);

		if(m_pSplashThread){
			ATLASSERT(WAIT_OBJECT_0 == dwWait);

			if(WAIT_TIMEOUT == dwWait)
				::TerminateThread(m_pSplashThread->m_hThread, DWORD(-1L));

			m_pSplashThread->m_bAutoDelete = TRUE;
			m_pSplashThread->Delete();
			m_pSplashThread = 0;
		}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 08:10:41
	DESCRIP:	
			CMenu m_mnuPropPage;
			IDR_MNU_TEST_PPAGE_DATA

	IN:
	OUT:
*/
void CPfaMainSheet::InitMenu(void)
{
	m_mnuPropPage.LoadMenu(IDR_MNU_PPAGE_DATA);
	BOOL bSet = SetMenu(&m_mnuPropPage);
	ATLASSERT(bSet);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	24/04/2007 13:15:10
	DESCRIP:	
	IN:
	OUT:
*/
void CPfaMainSheet::EnableSheetMenuItem(const DWORD dwSubMenu, const DWORD dwItem, const bool bEnable)
{
	const UINT uENABLE	= MF_BYCOMMAND | MF_ENABLED;
	const UINT uDISABLE	= MF_BYCOMMAND | MF_DISABLED | MF_GRAYED;

	CMenu * pSubMenu = m_mnuPropPage.GetSubMenu(dwSubMenu);
	if(pSubMenu){
		pSubMenu->EnableMenuItem(dwItem, bEnable ? uENABLE : uDISABLE);
	}
	else
		ATLTRACE(_T("CPfaMainSheet::EnableSheetMenuItem - no submenu at %i\n"), dwSubMenu);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 15:04:57
	DESCRIP:	
	IN:
	OUT:
*/
//void CPfaMainSheet::OnOK()
//{
//	ATLTRACE(_T("CPfaMainSheet::OnOK\n"));
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 15:05:00
	DESCRIP:	
	IN:
	OUT:
*/
//void CPfaMainSheet::OnCancel()
//{
//	ATLTRACE(_T("CPfaMainSheet::OnCancel\n"));
//}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 11:49:18
	DESCRIP:	
	IN:
	OUT:
*/
void CPfaMainSheet::InitSheet(void)
{
	long iStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	
	iStyle |= WS_MINIMIZEBOX;
	iStyle |= WS_MAXIMIZEBOX;

	::SetWindowLong(m_hWnd, GWL_STYLE, iStyle);

	GetDlgItem(IDOK)->ShowWindow		(SW_HIDE);
	GetDlgItem(IDCANCEL)->ShowWindow	(SW_HIDE);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 11:52:04
	DESCRIP:	
	IN:
	OUT:
*/
void CPfaMainSheet::OnSize(UINT nType, int cx, int cy) 
{
	CPropertySheet::OnSize(nType, cx, cy);
	
	if(::IsWindow(m_hWnd)){
		CTabCtrl * pTab = GetTabControl();

		if(pTab && ::IsWindow(pTab->m_hWnd)){
			CRect rcClient;
			GetClientRect(rcClient);

			pTab->MoveWindow(rcClient);
		}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	31/03/2007 10:24:53
	DESCRIP:	
		eWM_GET_FONT
	IN:
	OUT:
*/
/*afx_msg*/ 
LRESULT CPfaMainSheet::OnWMGetFont(WPARAM wParam, LPARAM lParam)
{
	LRESULT lrRet = FALSE;
	ATLTRACE(_T("CPfaMainSheet::OnWMGetFont\n"));

	if(wParam >= 0 && wParam < eFont__LAST){

		CWnd * pWnd = reinterpret_cast<CWnd *>(lParam);
		ATLASSERT(pWnd && ::IsWindow(pWnd->m_hWnd));

		if(pWnd && ::IsWindow(pWnd->m_hWnd)){
			lrRet = TRUE;
			pWnd->SetFont(CPropSheetCommon::GetTheFont(eFont(wParam)));
		}
	}

	return lrRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	25/04/2007 09:31:07
	DESCRIP:	
	IN:
	OUT:
*/
/*afx_msg*/
LRESULT CPfaMainSheet::OnWMPageActivated(WPARAM wParam, LPARAM lParam)
{
	LRESULT lrRet = FALSE;
	//ATLTRACE(_T("CPfaMainSheet::OnWMPageActivated Page: %i - Active: %i\n"), wParam, lParam);

	ATLASSERT(wParam >= 0 && wParam < ePage__LAST);

	if(wParam >= 0 && wParam < ePage__LAST){
		BOOL bActivated = lParam ? TRUE : FALSE;
		
		m_mnuPropPage.DestroyMenu();

		if(bActivated){

			m_mnuPropPage.LoadMenu(dwMENU_IDS[wParam]);
			BOOL bSet = SetMenu(&m_mnuPropPage);
			ATLASSERT(bSet);
		}
	}


	return lrRet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 08:02:47
	DESCRIP:	
	IN:
		Return Value
			Nonzero if the message was translated and should not be dispatched; 
			0 if the message was not translated and should be dispatched.

	OUT:
*/
BOOL CPfaMainSheet::PreTranslateMessage(MSG* pMsg) 
{
	BOOL bProcessedLocally = FALSE;

	//this prevents the closure of the property sheets
	//when pressing <enter> or <escape>
	switch(pMsg->message){

		case WM_KEYDOWN:	
			{
				TCHAR ch = TCHAR(pMsg->wParam);

				switch(ch){
					case VK_RETURN:
					case VK_ESCAPE:
						bProcessedLocally = TRUE;
						ATLTRACE(_T("Close prevention!!!\n"));
						break;
				}

			}
			break;
	}

	if(!bProcessedLocally)
		bProcessedLocally = CPropertySheet::PreTranslateMessage(pMsg);

	return bProcessedLocally;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	25/04/2007 13:46:55
	DESCRIP:	
	IN:
	OUT:
*/
void CPfaMainSheet::OnUpdateActionCopyprojectfiles(CCmdUI* pCmdUI) 
{
	ATLTRACE(_T("CPfaMainSheet::OnUpdateActionCopyprojectfiles\n"));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	25/04/2007 13:46:52
	DESCRIP:	
	IN:
	OUT:
*/
void CPfaMainSheet::OnUpdateActionValidateproject(CCmdUI* pCmdUI) 
{
	ATLTRACE(_T("CPfaMainSheet::OnUpdateActionValidateproject\n"));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	25/04/2007 13:20:17
	DESCRIP:	
	IN:
	OUT:
*/
void CPfaMainSheet::OnFileExit() 
{
	PostMessage(WM_CLOSE);	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	25/04/2007 13:44:32
	DESCRIP:	
		KB Article ID : 242577 
	IN:
	OUT:
*/
void CPfaMainSheet::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu)
{
	ATLTRACE(_T("CPfaMainSheet::OnInitMenuPopup\n"));

	ASSERT(pPopupMenu != NULL);
	// Check the enabled state of various menu items.

	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// Determine if menu is popup in top-level menu and set m_pOther to
	// it if so (m_pParentMenu == NULL indicates that it is secondary popup).
	HMENU hParentMenu;

	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;	 // Parent == child for tracking popup.

	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = this;
		
		// Child windows don't have menus--need to go to the top!
		if (pParent != NULL &&
		   (hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0 ; nIndex < nIndexMax ; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					// When popup is found, m_pParentMenu is containing menu.
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();

	for(state.m_nIndex = 0 ; state.m_nIndex < state.m_nIndexMax ; state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // Menu separator or invalid cmd - ignore it.

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// Possibly a popup menu, route to first item of that popup.
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);

			if(
					state.m_pSubMenu == NULL 
					|| (state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 
					|| state.m_nID == (UINT)-1
				)
			{
				continue;		// First item of popup can't be routed to.
			}
			state.DoUpdate(this, TRUE);	 // Popups are never auto disabled.
		}
		else
		{
			// Normal menu item.
			// Auto enable/disable if frame window has m_bAutoMenuEnable
			// set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
		}

		// Adjust for menu deletions and additions.
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
		   
			while (state.m_nIndex < nCount && pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}

		state.m_nIndexMax = nCount;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/05/2007 07:36:14
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPfaMainSheet::DestroyWindow() 
{
	CDataHandler::DisconnectDb();
	
	return CPropertySheet::DestroyWindow();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/05/2007 08:32:20
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaMainSheet::GetOption(const eOPTION eOption, long & iValue)
{
	HRESULT hr = S_OK;

	CString strValue;

	try{
		THR( hr = GetOption(eOption, strValue) );

		iValue = _ttol(strValue);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		CDataHandler::HandleHR(e, _T("CPfaMainSheet::GetOption"), _T(""), _T(""), true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/05/2007 07:52:08
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaMainSheet::GetOption(const eOPTION eOption, CString & strValue)
{
	HRESULT hr = E_INVALIDARG;

	if(eOption >= 0 && eOption < eOpt__LAST){
		CString strName = szsOPT_NAMES		[eOption];
		CString strDflt = szsOPT_DEFAULTS	[eOption];

		hr = GetOption(strName, strDflt, strValue);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/05/2007 07:52:11
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaMainSheet::GetOption(const CString & strName, const CString & strDflt, CString & strValue)
{
	HRESULT hr = S_OK;

	bool bExists = false;
	CString strSQL;


	try{
		THR( hr = OptionExists(strName, bExists) );

		if(bExists){
			strSQL.Format(_T("SELECT szOptionValue FROM tblOptions WHERE szOptionName = '%s'"), strName);
			THR( hr = CDataHandler::LookupString(strSQL, strDflt, strValue) );
		}

		else{
			strValue = strDflt;
			THR( hr = SetOption(strName, strDflt) );
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		CDataHandler::HandleHR(e, _T("CPfaMainSheet::GetOption"), strName, _T(""), true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/05/2007 08:03:39
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaMainSheet::SetOption(const eOPTION eOption, const CString & strValue)
{
	HRESULT hr = E_INVALIDARG;

	if(eOption >= 0 && eOption < eOpt__LAST){
		CString strName = szsOPT_NAMES		[eOption];

		hr = SetOption(strName, strValue);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/05/2007 08:03:41
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaMainSheet::SetOption(const CString & strName, const CString & strValue)
{
	HRESULT hr = S_OK;

	CString strSQL;
	bool bExists = false;

	try{
		THR( hr = OptionExists(strName, bExists) );

		if(bExists)
			strSQL.Format(_T("UPDATE tblOptions SET szOptionValue = '%s' WHERE szOptionName = '%s'"), strValue, strName);
		else
			strSQL.Format(_T("INSERT INTO tblOptions (szOptionName, szOptionValue) VALUES ('%s', '%s')"), strName, strValue);

		THR( hr = CDataHandler::ExecSQL(strSQL, _T("CPfaMainSheet::SetOption"), 0) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		CDataHandler::HandleHR(e, _T("CPfaMainSheet::SetOption"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/05/2007 08:05:43
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaMainSheet::OptionExists(const CString & strName, bool & bExists)
{
	HRESULT hr = S_OK;

	bExists = false;

	CString strSQL;
	long iCount = 0L;

	strSQL.Format(_T("SELECT COUNT(*) AS iCount FROM tblOptions WHERE szOptionName = '%s'"), strName);

	try{
		THR( hr = CDataHandler::CountRecords(strSQL, iCount) );

		bExists = (iCount > 0L) ? true : false;
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		CDataHandler::HandleHR(e, _T("CPfaMainSheet::OptionExists"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/05/2007 08:27:33
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaMainSheet::ArchiveProject(
									const DWORD dwProjID
									, const CString & strProjectName
								)
{
	HRESULT hr = S_OK;

	try{
		THR( hr = CPfaArchiveHandler::ArchiveProject(
												CDataHandler::GetConnection()
												, strProjectName
												, dwProjID
											) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
	}

	return hr;
}
