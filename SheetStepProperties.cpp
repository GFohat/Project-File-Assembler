// SheetStepProperties.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "SheetStepProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSheetStepProperties

IMPLEMENT_DYNAMIC(CSheetStepProperties, CPropertySheet)

//CSheetStepProperties::CSheetStepProperties(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
//:	CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
//{
//}

CSheetStepProperties::CSheetStepProperties(
										const CPfaDataListItem &	rData
										, const CString &			strDfltSrc
										, const CString &			strDfltDest
										, LPCTSTR					pszCaption
										, CWnd*						pParentWnd		/*= NULL*/
										, UINT						iSelectPage		/*= 0*/
									)
:	CPropertySheet	(pszCaption, pParentWnd, iSelectPage)
	, m_data		(rData)
{
	ATLTRACE(_T("CSheetStepProperties::CSheetStepProperties %s\n"), pszCaption);

	//remove the 'Help' button
	m_psh.dwFlags &= ~PSH_HASHELP;

	m_pageStepDetails.m_psp.dwFlags		&= ~PSP_HASHELP;
	//m_pageStepType.m_psp.dwFlags		&= ~PSP_HASHELP;

	m_pageStepDetails.SetDefaults(strDfltSrc, strDfltDest);

	AddAllPages();
}

CSheetStepProperties::~CSheetStepProperties()
{
}


BEGIN_MESSAGE_MAP(CSheetStepProperties, CPropertySheet)
	//{{AFX_MSG_MAP(CSheetStepProperties)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSheetStepProperties message handlers
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 13:18:29
	DESCRIP:	
	IN:
	OUT:
*/
void CSheetStepProperties::AddAllPages(void)
{
	//AddPage(&m_pageStepType);
	AddPage(&m_pageStepDetails);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 13:20:45
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CSheetStepProperties::OnInitDialog() 
{
	CDataHandler::ConnectDb();

	BOOL bResult = CPropertySheet::OnInitDialog();
	
	CDC * pdc = GetDC();
	InitFonts(pdc);
	ReleaseDC(pdc);

	InitTabCtrl(GetTabControl());

	GetDlgItem(IDOK)			->SetFont(GetTheFont(eFont_Buttons));
	GetDlgItem(IDCANCEL)		->SetFont(GetTheFont(eFont_Buttons));
	GetDlgItem(ID_APPLY_NOW)	->SetFont(GetTheFont(eFont_Buttons));

	for(int iPage = 0 ; iPage < GetPageCount() ; iPage++){
		SetActivePage(iPage);
	}

	SetActivePage(0);

	//m_pageStepType.SetAppearance();
	m_pageStepDetails.SetAppearance();
	
	return bResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 13:42:53
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CSheetStepProperties::DestroyWindow() 
{
	CDataHandler::DisconnectDb();	
	return CPropertySheet::DestroyWindow();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 09:08:26
	DESCRIP:	
	inline void SetStepType			(const int iType)		{ m_iStepType			= iType; }
	inline void	SetSourceFile		(const CString & str)	{ m_strSourceFile		= str; }
	inline void	SetSourceDir		(const CString & str)	{ m_strSourceDir		= str; }
	inline void	SetDestDirectory	(const CString & str)	{ m_strDestDirectory	= str; }
	inline void	SetDestFile			(const CString & str)	{ m_strDestFile			= str; }
	IN:
	OUT:
*/
void CSheetStepProperties::SaveData(void)
{
	//m_pageStepType.PageToData(m_data);
	m_pageStepDetails.PageToData(m_data);

	CDataHandler::SaveData(m_data);
}
