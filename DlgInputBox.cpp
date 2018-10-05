// DlgInputBox.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "DlgInputBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInputBox dialog


CDlgInputBox::CDlgInputBox(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInputBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInputBox)
	m_strText = _T("");
	m_strPrompt = _T("");
	//}}AFX_DATA_INIT
}


void CDlgInputBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInputBox)
	DDX_Text(pDX, IDC_ED_TEXT, m_strText);
	DDX_Text(pDX, IDC_ED_PROMPT, m_strPrompt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInputBox, CDialog)
	//{{AFX_MSG_MAP(CDlgInputBox)
	ON_BN_CLICKED(IDC_BN_BROWSE_DIR, OnBnBrowseDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInputBox message handlers

BOOL CDlgInputBox::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetAppearance();

	SetWindowText(m_strTitle);
	GetDlgItem(IDC_ED_TEXT)->SetFocus();
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	31/03/2007 10:30:03
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgInputBox::SetAppearance(void)
{
	CFont * pFontEdit = 0;

	BOOL bOK = FALSE;

	bOK = ::AfxGetApp()->m_pMainWnd->SendMessage(eWM_GET_FONT, eFont_EdBoxes, LPARAM(GetDlgItem(IDC_ED_TEXT)));
	bOK = ::AfxGetApp()->m_pMainWnd->SendMessage(eWM_GET_FONT, eFont_EdBoxes, LPARAM(GetDlgItem(IDC_ED_PROMPT)));
	bOK = ::AfxGetApp()->m_pMainWnd->SendMessage(eWM_GET_FONT, eFont_Buttons, LPARAM(GetDlgItem(IDOK)));
	bOK = ::AfxGetApp()->m_pMainWnd->SendMessage(eWM_GET_FONT, eFont_Buttons, LPARAM(GetDlgItem(IDCANCEL)));
	bOK = ::AfxGetApp()->m_pMainWnd->SendMessage(eWM_GET_FONT, eFont_Buttons, LPARAM(GetDlgItem(IDC_BN_BROWSE_DIR)));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	29/03/2007 10:22:28
	DESCRIP:	
	IN:
	OUT:
*/
INT_PTR CDlgInputBox::DoModal(
							const CString & strTitle
							, const CString & strPrompt
							, CString & strText
						)
{
	INT_PTR iReply = IDCANCEL;

	m_strTitle		= strTitle;
	m_strPrompt		= strPrompt;
	m_strText		= strText;

	iReply = CDialog::DoModal();

	if(IDOK == iReply)
		strText = m_strText;

	return iReply;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 22:55:25
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgInputBox::OnBnBrowseDir() 
{
	UpdateData(TRUE);

	CString strBrowse = m_strText;

	bool bDone = CDirBrowser::BrowseForDirectory(m_strPrompt, strBrowse);

	if(bDone){
		m_strText = strBrowse;
		UpdateData(FALSE);
	}
}
