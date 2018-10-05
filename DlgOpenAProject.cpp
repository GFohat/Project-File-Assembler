// DlgOpenAProject.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "DlgOpenAProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOpenAProject dialog


CDlgOpenAProject::CDlgOpenAProject(
								CFont * pFontList
								, CWnd* pParent /* = NULL */
							)
:	CDialog				(CDlgOpenAProject::IDD, pParent)
	, m_dwProjectID		(-1L)
	, m_strProjectName	(_T(""))
	, m_pFontList		(pFontList)
{
	//{{AFX_DATA_INIT(CDlgOpenAProject)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgOpenAProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOpenAProject)
	DDX_Control(pDX, IDC_LIST_EXIST_PROJECTS, m_listExistProjects);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOpenAProject, CDialog)
	//{{AFX_MSG_MAP(CDlgOpenAProject)
	ON_NOTIFY(NM_CLICK, IDC_LIST_EXIST_PROJECTS, OnClickListExistProjects)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_EXIST_PROJECTS, OnDblclkListExistProjects)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOpenAProject message handlers

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 15:06:17
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CDlgOpenAProject::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CDataHandler::ConnectDb();

	CString strSQL = szSQL_PROJECT_COMBO;

	DWORD dwExStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP;

	m_listExistProjects.SetExtendedStyle(dwExStyle);

	if(m_pFontList)
		m_listExistProjects.SetFont(m_pFontList);

	CDataHandler::InitListCtrl(strSQL, m_listExistProjects);
	CDataHandler::PopulateListCtrl(strSQL, m_listExistProjects, false);

	CHeaderCtrl * pHdr = m_listExistProjects.GetHeaderCtrl();

	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		for(DWORD dwLoop = 0L ; dwLoop < DWORD(pHdr->GetItemCount()) ; dwLoop++){
			m_listExistProjects.SetColumnWidth(dwLoop, LVSCW_AUTOSIZE_USEHEADER);
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 15:11:25
	DESCRIP:	
	IN:
	OUT:
*/
int CDlgOpenAProject::DoModal(DWORD & dwProjectID, CString & strProjectName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	int iReply = CDialog::DoModal();

	if(IDOK == iReply){
		
		//Have we still got a list control??? - NO!!!

		dwProjectID = m_dwProjectID;
		strProjectName = m_strProjectName;

		if(DWORD(-1L) == m_dwProjectID)
			iReply = IDCANCEL;
	}

	return iReply;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 15:19:56
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgOpenAProject::OnClickListExistProjects(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	
	NMLISTVIEW * pNmlv = reinterpret_cast<NMLISTVIEW *>(pNMHDR);

	if(pNmlv->iItem >= 0){
		m_strProjectName		= m_listExistProjects.GetItemText(pNmlv->iItem, 1);
		CString strProjectID	= m_listExistProjects.GetItemText(pNmlv->iItem, 0);

		m_dwProjectID			= _ttol(strProjectID);
	}
	else{
		m_dwProjectID = -1L;
		m_strProjectName.Empty();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/04/2007 08:33:05
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgOpenAProject::OnDblclkListExistProjects(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	
	NMLISTVIEW * pNmlv = reinterpret_cast<NMLISTVIEW *>(pNMHDR);

	if(pNmlv->iItem >= 0){
		m_strProjectName		= m_listExistProjects.GetItemText(pNmlv->iItem, 1);
		CString strProjectID	= m_listExistProjects.GetItemText(pNmlv->iItem, 0);

		m_dwProjectID			= _ttol(strProjectID);

		OnOK();
	}
	else{
		m_dwProjectID = -1L;
		m_strProjectName.Empty();
	}
}
