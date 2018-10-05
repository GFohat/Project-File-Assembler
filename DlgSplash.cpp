// DlgSplash.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "DlgSplash.h"

#include "VersionNo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSplash dialog


CDlgSplash::CDlgSplash(HWND hwndTarget, CWnd* pParent /*=NULL*/)
:	CDialog			(CDlgSplash::IDD, pParent)
	, m_hWndTarget	(hwndTarget)
{
	//{{AFX_DATA_INIT(CDlgSplash)
	//}}AFX_DATA_INIT
}


void CDlgSplash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSplash)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSplash, CDialog)
	//{{AFX_MSG_MAP(CDlgSplash)
	//}}AFX_MSG_MAP

	ON_MESSAGE( eWM_SPLASH_START_PIC_INIT,		OnWMSplashStartPicInit)
	ON_MESSAGE( eWM_SPLASH_PIC_INIT_DONE,		OnWMSplashPicInitDone)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSplash message handlers

BOOL CDlgSplash::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRect rcClient;
	GetClientRect(rcClient);

	//CDC * pdc = GetDC();
	//m_fontSplash.InitFont(pdc, isFONT_POINTS[eFont_Splash], isFONT_WEIGHTS[eFont_Splash], szsFONT_FACE[eFont_Splash]);
	//ReleaseDC(pdc);

	//m_rcText.top			= rcClient.top;
	//m_rcText.bottom			= m_rcText.top + (rcClient.Height() / 2);
	//m_rcText.left			= rcClient.left;
	//m_rcText.right			= rcClient.right;

	//m_rcPicture.top			= m_rcText.bottom;
	//m_rcPicture.bottom		= rcClient.bottom;
	//m_rcPicture.left		= rcClient.left;
	//m_rcPicture.right		= rcClient.right;

	m_rcText	= rcClient;
	m_rcPicture = rcClient;
	InitText	(m_rcText);
	//InitPicture	(m_rcPicture);


	PostMessage(eWM_SPLASH_START_PIC_INIT);

	

//	ATLASSERT(::IsWindow(m_hWndTarget));
//	if(::IsWindow(m_hWndTarget))
//		::PostMessage(m_hWndTarget, eWM_SPLASH_INIT_DONE, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	09/05/2007 08:31:29
	DESCRIP:	
	IN:
	OUT:
*/
LRESULT CDlgSplash::OnWMSplashStartPicInit(WPARAM wParam, LPARAM lParam)
{
	ExitText();

	ATLTRACE(_T("CDlgSplash::OnWMSplashStartPicInit\n"));
	InitPicture	(m_rcPicture);
	PostMessage(eWM_SPLASH_PIC_INIT_DONE);
	return TRUE;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	09/05/2007 08:31:31
	DESCRIP:	
	IN:
	OUT:
*/
LRESULT CDlgSplash::OnWMSplashPicInitDone(WPARAM wParam, LPARAM lParam)
{
	ATLTRACE(_T("CDlgSplash::OnWMSplashPicInitDone\n"));
	ATLASSERT(::IsWindow(m_hWndTarget));
	if(::IsWindow(m_hWndTarget))
		::PostMessage(m_hWndTarget, eWM_SPLASH_INIT_DONE, 0, 0);
	return TRUE;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	09/05/2007 08:31:23
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgSplash::SetText(const CString & strText)
{
	m_strText = strText;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 11:16:29
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgSplash::InitText(const CRect & rcMove)
{
	DWORD dwStyle = 0 
				| ES_CENTER
				| ES_MULTILINE
				| ES_READONLY
				| ES_AUTOVSCROLL
			;

	CString strSplash;

	if(m_strText.IsEmpty())
		strSplash.Format(_T("\n\n\nProject File Assembler %s"), STRFILEVER);
	else
		strSplash = m_strText;

	m_redText.Create				(dwStyle, rcMove, this, 5555);
	m_redText.SetBackgroundColor	(FALSE, crefACTIVE_BACK);
	m_redText.SetFont				(m_fontSplash.GetFont());
	m_redText.SetWindowText			(strSplash);
	m_redText.MoveWindow			(rcMove);
	m_redText.ShowWindow			(SW_SHOW);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 11:16:27
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgSplash::ExitText(void)
{
	if(::IsWindow(m_redText.m_hWnd)){
		m_redText.ShowWindow(SW_HIDE);
		m_redText.DestroyWindow();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	05/05/2007 12:45:37
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgSplash::InitPicture(const CRect & rcMove)
{
	TCHAR szModuleFileName[_MAX_PATH + 5] = {0};

	::GetModuleFileName(0, szModuleFileName, _MAX_PATH);

	TCHAR szDrive	[_MAX_DRIVE]	= {0};
	TCHAR szDir		[_MAX_DIR]		= {0};

	_tsplitpath(szModuleFileName, szDrive, szDir, 0, 0);
	CString strPic;
	strPic.Format(_T("%s%sSplash.jpg"), szDrive, szDir);

	//CString strPic(_T("C:\\winlink\\DEVELOP\\Project File Assembler\\Graphics\\aah logo - banner 2.jpg"));
	//CString strPic(_T("C:\\winlink\\DEVELOP\\Project File Assembler\\Graphics\\AAH Logo Large.jpg"));
	//CString strPic(_T("F:\\Users\\Pete\\Documents\\Visual Studio Projects\\AAH\\Project File Assembler\\Debug\\splash.jpg"));
	

	CDebugTimer tmr(_T("CDlgSplash::InitPicture"));

	HRESULT hr = CPictureHelper::LoadPicture(strPic);

	if(SUCCEEDED(hr)){
	
		CDC * pdc = GetDC();
		CPictureHelper::RenderPicture(pdc, rcMove, false, 0, 0, 1.0);
		ReleaseDC(pdc);	

	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	05/05/2007 12:45:35
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgSplash::ExitPicture(void)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 11:20:17
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CDlgSplash::DestroyWindow() 
{
	ExitPicture();
	ExitText();
	
	return CDialog::DestroyWindow();
}
