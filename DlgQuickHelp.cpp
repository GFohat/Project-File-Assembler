// DlgQuickHelp.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "DlgQuickHelp.h"
#include "VersionNo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const TCHAR szHELP_TEXT_FMT[] = {
	_T("Project File Assembler V%s\n")
	_T("\n")
	_T("'#' - Comment Line\n")
	_T("'*' - Wild Card (Copy the entire directory)\n")
	_T("'&' - Wild Card (Copy the entire directory inc. sub-folders)\n")
	_T("\n")
	_T("\n")
	_T("\n")
};

/////////////////////////////////////////////////////////////////////////////
// CDlgQuickHelp dialog


CDlgQuickHelp::CDlgQuickHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQuickHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQuickHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgQuickHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQuickHelp)
	DDX_Control(pDX, IDC_RED_HELPTEXT, m_redQuickHelp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQuickHelp, CDialog)
	//{{AFX_MSG_MAP(CDlgQuickHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQuickHelp message handlers

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 08:12:17
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CDlgQuickHelp::OnInitDialog() 
{
	CDialog::OnInitDialog();

	InitRichEdit();

	CString strText;

	strText.Format(szHELP_TEXT_FMT, STRFILEVER);
	m_redQuickHelp.SetWindowText(strText);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 08:17:58
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgQuickHelp::InitRichEdit(void)
{
#pragma message("CDlgQuickHelp::InitRichEdit")
	//m_redQuickHelp.SetFont(GetMainSheet()->GetFont());
}
