// PageData.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "PageData.h"

#include "PfaMainSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageData property page

IMPLEMENT_DYNCREATE(CPageData, CPropertyPage)

CPageData::CPageData() : CPropertyPage(CPageData::IDD)
{
	//{{AFX_DATA_INIT(CPageData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageData::~CPageData()
{
}

void CPageData::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageData)
	DDX_Control(pDX, IDC_AXSIMPLEDATAGRIDCTRL1, m_datagrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageData, CPropertyPage)
	//{{AFX_MSG_MAP(CPageData)
	//}}AFX_MSG_MAP

	ON_MESSAGE	(eWM_SET_APPEARANCE,			OnWMSetAppearance)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageData message handlers

BOOL CPageData::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_datagrid.ConnectBYUDL(CONS_UDL::szUDL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	2007-05-24 12:29:18
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageData::OnSetActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_Data, TRUE);

	CString strQuery;
	strQuery.Format(_T("%s ORDER BY iRecID DESC"), szSQL_LOG_LIST_ALL);

	m_datagrid.SetQuery(strQuery);
	
	return CPropertyPage::OnSetActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	2007-05-24 12:29:21
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageData::OnKillActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_Data, FALSE);
	
	return CPropertyPage::OnKillActive();
}

BEGIN_EVENTSINK_MAP(CPageData, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(CPageData)
	ON_EVENT(CPageData, IDC_AXSIMPLEDATAGRIDCTRL1, 1 /* ListCellClicked */, OnListCellClickedAxsimpledatagridctrl1, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CPageData, IDC_AXSIMPLEDATAGRIDCTRL1, 2 /* RowCountChanged */, OnRowCountChangedAxsimpledatagridctrl1, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	2007-05-24 12:41:09
	DESCRIP:	
	IN:
	OUT:
*/
void CPageData::OnListCellClickedAxsimpledatagridctrl1(long iItem, long iSubItem, LPCTSTR szColumnName, LPCTSTR szCellText) 
{
	CString strText = szCellText;
	GetDlgItem(IDC_ED_CLICKED)->SetWindowText(strText);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	2007-05-24 12:41:12
	DESCRIP:	
	IN:
	OUT:
*/
void CPageData::OnRowCountChangedAxsimpledatagridctrl1(long iNewCount) 
{
	CString strText;
	strText.Format(_T("%i items"), iNewCount);
	GetDlgItem(IDC_ED_CLICKED)->SetWindowText(strText);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	2007-05-24 12:42:30
	DESCRIP:	
	IN:
	OUT:
*/
LRESULT CPageData::OnWMSetAppearance(WPARAM wParam, LPARAM lParam)
{
	::AfxGetApp()->m_pMainWnd->SendMessage(
										eWM_GET_FONT
										, eFont_EdBoxes
										, LPARAM(GetDlgItem(IDC_ED_CLICKED))
									);
	return TRUE;
}
