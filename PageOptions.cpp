// PageOptions.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "PageOptions.h"

#include "PfaMainSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageOptions property page

IMPLEMENT_DYNCREATE(CPageOptions, CPropertyPage)

CPageOptions::CPageOptions() : CPropertyPage(CPageOptions::IDD)
{
	//{{AFX_DATA_INIT(CPageOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageOptions::~CPageOptions()
{
}

void CPageOptions::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageOptions)
	DDX_Control(pDX, IDC_AXSIMPLEDATAGRIDCTRL1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageOptions, CPropertyPage)
	//{{AFX_MSG_MAP(CPageOptions)
	//}}AFX_MSG_MAP

	ON_MESSAGE	(eWM_SET_APPEARANCE,			OnWMSetAppearance)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageOptions message handlers

BOOL CPageOptions::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_grid.ConnectBYUDL(szUDL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/04/2007 08:24:18
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageOptions::OnSetActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_Options, TRUE);

	m_grid.SetQuery(szSQL_LOG_LIST_ALL);
	
	return CPropertyPage::OnSetActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/04/2007 08:24:16
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageOptions::OnKillActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_Options, FALSE);
	
	return CPropertyPage::OnKillActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/04/2007 08:27:27
	DESCRIP:	
	IN:
	OUT:
*/
CPfaMainSheet * CPageOptions::GetMainSheet(void)
{
	CPfaMainSheet * pSheet = reinterpret_cast<CPfaMainSheet *>(GetParent());
	ATLASSERT(pSheet && ::IsWindow(pSheet->m_hWnd));
	return pSheet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 20:33:28
	DESCRIP:	
	IN:
	OUT:
*/
/*afx_msg*/
LRESULT CPageOptions::OnWMSetAppearance(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}
