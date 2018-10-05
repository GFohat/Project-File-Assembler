// PageStepDetails.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "PageStepDetails.h"

#include "SheetStepProperties.h"

#include "ConstStepDetails.h"
using namespace CONS_STEP_DETAILS;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageStepDetails property page

IMPLEMENT_DYNCREATE(CPageStepDetails, CPropertyPage)

CPageStepDetails::CPageStepDetails() : CPropertyPage(CPageStepDetails::IDD)
{
	//{{AFX_DATA_INIT(CPageStepDetails)
	//}}AFX_DATA_INIT
}

CPageStepDetails::~CPageStepDetails()
{
}

void CPageStepDetails::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageStepDetails)
	DDX_Control(pDX,	IDC_CMBO_STEP_TYPE,			m_cmboStepType);
	DDX_Control(pDX,	IDC_RED_TEXT_SRCFILE,		m_redTextSrcFile);
	DDX_Control(pDX,	IDC_RED_TEXT_SOURCEDIR,		m_redTextSrcDir);
	DDX_Control(pDX,	IDC_RED_TEXT_DESTFILE,		m_redTextDestFile);
	DDX_Control(pDX,	IDC_RED_TEXT_DESTDIR,		m_redTextDestDir);
	DDX_Control(pDX,	IDC_ED_LABEL_SRCFILE,		m_edLabelSrcFile);
	DDX_Control(pDX,	IDC_ED_LABEL_SOURCEDIR,		m_edLabelSrcDir);
	DDX_Control(pDX,	IDC_ED_LABEL_DESTFILE,		m_edLabelDestFile);
	DDX_Control(pDX,	IDC_ED_LABEL_DESTDIR,		m_edLabelDestDir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageStepDetails, CPropertyPage)
	//{{AFX_MSG_MAP(CPageStepDetails)
	ON_EN_CHANGE		(IDC_RED_TEXT_DESTDIR,		OnChangeRedTextDestdir)
	ON_EN_CHANGE		(IDC_RED_TEXT_DESTFILE,		OnChangeRedTextDestfile)
	ON_EN_CHANGE		(IDC_RED_TEXT_SOURCEDIR,	OnChangeRedTextSourcedir)
	ON_EN_CHANGE		(IDC_RED_TEXT_SRCFILE,		OnChangeRedTextSrcfile)
	ON_BN_CLICKED		(IDC_BN_SRC_FILE,			OnBnSrcFile)
	ON_BN_CLICKED		(IDC_BN_SRC_DIR,			OnBnSrcDir)
	ON_BN_CLICKED		(IDC_BN_DEST_DIR,			OnBnDestDir)
	ON_CBN_SELCHANGE	(IDC_CMBO_STEP_TYPE,		OnSelchangeCmboStepType)
	ON_BN_CLICKED(IDC_BN_DEST_DIR_DEFAULT, OnBnDestDirDefault)
	ON_BN_CLICKED(IDC_BN_SRC_DIR_DEFAULT, OnBnSrcDirDefault)
	ON_NOTIFY(EN_MSGFILTER, IDC_RED_TEXT_SRCFILE, OnMsgfilterRedTextSrcfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageStepDetails message handlers

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 07:53:00
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageStepDetails::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	RefreshCombo();
	SetControlsForType();
	RefreshTexts();

	DWORD dwEvMask = m_redTextSrcFile.GetEventMask();

	dwEvMask |= ENM_CHANGE;

	m_redTextDestDir.SetEventMask	(dwEvMask);
	m_redTextDestFile.SetEventMask	(dwEvMask);
	m_redTextSrcDir.SetEventMask	(dwEvMask);
	m_redTextSrcFile.SetEventMask	(dwEvMask);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 07:52:57
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageStepDetails::OnSetActive() 
{
	RefreshLabels();
	
	return CPropertyPage::OnSetActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 07:52:54
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageStepDetails::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnKillActive();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 13:33:29
	DESCRIP:	
	IN:
	OUT:
*/
CSheetStepProperties * CPageStepDetails::GetMainSheet(void)
{
	CSheetStepProperties * pSheet = reinterpret_cast<CSheetStepProperties *>(GetParent());
	ATLASSERT(pSheet && ::IsWindow(pSheet->m_hWnd));
	return pSheet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 08:25:27
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::RefreshLabels(void)
{
	//future: text should depend on current step type...
	//m_edLabelSrcFile.SetWindowText	(_T("File"));
	//m_edLabelSrcDir.SetWindowText	(_T("Source"));
	//m_edLabelDestDir.SetWindowText	(_T("Destination"));
	//m_edLabelDestFile.SetWindowText	(_T("Copied Name"));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	31/03/2007 11:02:49
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::RefreshCombo(void)
{
	m_cmboStepType.ResetContent();

	GetMainSheet()->PopulateComboBox(
									szSQL_STEPTYPE_COMBO
									, szFIELD_STEPTYPE_STRINGS
									, szFIELD_STEPTYPE_IDS
									, m_cmboStepType
								);

	int iStepType = GetMainSheet()->GetCurData().GetStepType();

	const int iMAX = m_cmboStepType.GetCount();
	bool bFound = false;
	int iTest = 0;

	//looking for the item who's data matches the current step type
	for(int iItem = 0 ; iItem < iMAX && !bFound ; iItem++){
		iTest = m_cmboStepType.GetItemData(iItem);

		if(iTest == iStepType){
			bFound = true;
			m_cmboStepType.SetCurSel(iItem);
		}
	}

	ATLASSERT(bFound);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	31/03/2007 11:33:01
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::SetControlsForType(void)
{
	int iCurSel = m_cmboStepType.GetCurSel();

	if(iCurSel >= 0){
		int iStepType = m_cmboStepType.GetItemData(iCurSel);
		ATLASSERT(iStepType >= 0 && iStepType < ePST__LAST);

		if(iStepType >= 0 && iStepType < ePST__LAST){
			
			//the labels...
			m_edLabelSrcFile.SetWindowText	(szsLABEL_0_TEXTS[iStepType]);
			m_edLabelSrcDir.SetWindowText	(szsLABEL_1_TEXTS[iStepType]);
			m_edLabelDestDir.SetWindowText	(szsLABEL_2_TEXTS[iStepType]);
			m_edLabelDestFile.SetWindowText	(szsLABEL_3_TEXTS[iStepType]);

			//the rich edit text boxes...
			EnableRichEdit(m_redTextSrcFile,	bsENABLE_EDIT_0[iStepType]);
			EnableRichEdit(m_redTextSrcDir,		bsENABLE_EDIT_1[iStepType]);
			EnableRichEdit(m_redTextDestDir,	bsENABLE_EDIT_2[iStepType]);
			EnableRichEdit(m_redTextDestFile,	bsENABLE_EDIT_3[iStepType]);

			//the buttons...
			GetDlgItem(IDC_BN_SRC_FILE)		->EnableWindow(bsENABLE_EDIT_0[iStepType]);
			GetDlgItem(IDC_BN_SRC_DIR)		->EnableWindow(bsENABLE_EDIT_1[iStepType]);
			GetDlgItem(IDC_BN_DEST_DIR)		->EnableWindow(bsENABLE_EDIT_2[iStepType]);
			GetDlgItem(IDC_BN_DEST_FILE)	->EnableWindow(bsENABLE_EDIT_3[iStepType]);
		}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	31/03/2007 11:37:53
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::EnableRichEdit(CRichEditCtrl & rRed, const bool bEnable)
{
	rRed.SetBackgroundColor(FALSE, bEnable ? WHITE : GRAY);
	rRed.EnableWindow(bEnable);
	
	if(!bEnable)
		rRed.SetWindowText(_T(""));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 08:25:30
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::RefreshTexts(void)
{
	m_redTextSrcFile.SetWindowText	(GetMainSheet()->GetCurData().GetSourceFile());
	m_redTextSrcDir.SetWindowText	(GetMainSheet()->GetCurData().GetSourceDir());
	m_redTextDestDir.SetWindowText	(GetMainSheet()->GetCurData().GetDestDirectory());
	m_redTextDestFile.SetWindowText	(GetMainSheet()->GetCurData().GetDestFile());

	SetModified(FALSE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 08:49:26
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::SetAppearance(void)
{
	m_edLabelDestDir.SetFont	(GetMainSheet()->GetTheFont(eFont_EdBoxes));
	m_edLabelDestFile.SetFont	(GetMainSheet()->GetTheFont(eFont_EdBoxes));
	m_edLabelSrcDir.SetFont		(GetMainSheet()->GetTheFont(eFont_EdBoxes));
	m_edLabelSrcFile.SetFont	(GetMainSheet()->GetTheFont(eFont_EdBoxes));

	m_redTextDestDir.SetFont	(GetMainSheet()->GetTheFont(eFont_EdBoxes));
	m_redTextDestFile.SetFont	(GetMainSheet()->GetTheFont(eFont_EdBoxes));
	m_redTextSrcDir.SetFont		(GetMainSheet()->GetTheFont(eFont_EdBoxes));
	m_redTextSrcFile.SetFont	(GetMainSheet()->GetTheFont(eFont_EdBoxes));

	m_cmboStepType.SetFont		(GetMainSheet()->GetTheFont(eFont_Combo));

	
	GetDlgItem(IDC_BN_SRC_FILE)			->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_BN_SRC_DIR)			->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_BN_SRC_DIR_DEFAULT)	->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_BN_DEST_DIR)			->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_BN_DEST_DIR_DEFAULT)	->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_BN_DEST_FILE)		->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	31/03/2007 11:57:28
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::SetDefaults(const CString & strDfltSrc, const CString & strDfltDest)
{
	m_strOrigDfltSrcDir		= m_strDfltSrcDir		= strDfltSrc;
	m_strOrigDfltDestDir	= m_strDfltDestDir		= strDfltDest;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 09:19:48
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::PageToData(CPfaDataListItem & rItem) const
{
	CString str;

	m_redTextDestDir.GetWindowText(str);
	rItem.SetDestDirectory(str);

	m_redTextDestFile.GetWindowText(str);
	rItem.SetDestFile(str);

	m_redTextSrcDir.GetWindowText(str);
	rItem.SetSourceDir(str);

	m_redTextSrcFile.GetWindowText(str);
	rItem.SetSourceFile(str);

	int iCurSel = m_cmboStepType.GetCurSel();

	if(iCurSel >= 0){
		int iStepType = m_cmboStepType.GetItemData(iCurSel);
		rItem.SetStepType(iStepType);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02/04/2007 11:29:29
	DESCRIP:	
	IN:
	OUT:
*/
bool CPageStepDetails::ValidateCurData(CString & strText) const
{
	bool bValid = false;

	int iCurSel = m_cmboStepType.GetCurSel();

	if(iCurSel >= 0){
		int iStepType = m_cmboStepType.GetItemData(iCurSel);

		switch(iStepType){
			case ePST_Comment:				bValid = Validate_Comment			(strText);		break;
			case ePST_CopySingleDir:		bValid = Validate_CopySingleDir		(strText);		break;
			case ePST_CopyDirAndSubDirs:	bValid = Validate_CopyDirAndSubDirs	(strText);		break;
			case ePST_DelDestFile:			bValid = Validate_DelDestFile		(strText);		break;
			case ePST_CreateNewDir:			bValid = Validate_CreateNewDir		(strText);		break;
			case ePST_CopyFile:				bValid = Validate_CopyFile			(strText);		break;
		}
	}
	else{
		strText += _T("\nStep type is invalid");
	}

	return bValid;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02/04/2007 11:42:45
	DESCRIP:	
	IN:
	OUT:
*/
bool CPageStepDetails::IsDlgItemEmpty(const DWORD dwID) const
{
	CString strText;
	GetDlgItemText(dwID, strText);
	return strText.IsEmpty() ? true : false;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02/04/2007 11:36:59
	DESCRIP:	
	IN:
	OUT:
*/
bool CPageStepDetails::Validate_Comment(CString & strText) const
{
	bool bOK = true;

	//no conditions, allow anything
	//check lengths?
	//check '#' for possible export back to a csv file?

	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02/04/2007 11:37:04
	DESCRIP:
		IDC_RED_TEXT_SRCFILE
		IDC_RED_TEXT_SOURCEDIR
		IDC_RED_TEXT_DESTFILE
		IDC_RED_TEXT_DESTDIR
	IN:
	OUT:
*/
bool CPageStepDetails::Validate_CopySingleDir(CString & strText) const
{
	bool bOK = true;

	if( ! IsDlgItemEmpty(IDC_RED_TEXT_SRCFILE)){
		bOK = false;
		strText += _T("\n\"Source file\" field must be empty");
	}

	if(IsDlgItemEmpty(IDC_RED_TEXT_SOURCEDIR)){
		bOK = false;
		strText += _T("\n\"Source Directory\" field must not be empty");
	}

	if(IsDlgItemEmpty(IDC_RED_TEXT_DESTDIR)){
		bOK = false;
		strText += _T("\n\"Destination Directory\" field must not be empty");
	}

	if( ! IsDlgItemEmpty(IDC_RED_TEXT_DESTFILE)){
		bOK = false;
		strText += _T("\n\"Destination File\" field must be empty");
	}

	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02/04/2007 11:37:08
	DESCRIP:	
	IN:
	OUT:
*/
bool CPageStepDetails::Validate_CopyDirAndSubDirs(CString & strText) const
{
	bool bOK = true;

	if( ! IsDlgItemEmpty(IDC_RED_TEXT_SRCFILE)){
		bOK = false;
		strText += _T("\n\"Source file\" field must be empty");
	}

	if(IsDlgItemEmpty(IDC_RED_TEXT_SOURCEDIR)){
		bOK = false;
		strText += _T("\n\"Source Directory\" field must not be empty");
	}

	if(IsDlgItemEmpty(IDC_RED_TEXT_DESTDIR)){
		bOK = false;
		strText += _T("\n\"Destination Directory\" field must not be empty");
	}

	if( ! IsDlgItemEmpty(IDC_RED_TEXT_DESTFILE)){
		bOK = false;
		strText += _T("\n\"Destination File\" field must be empty");
	}

	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02/04/2007 11:37:13
	DESCRIP:	
	IN:
	OUT:
*/
bool CPageStepDetails::Validate_DelDestFile(CString & strText) const
{
	//never valid!
	bool bOK = false;

	strText += _T("\nDelete Destination File is not yet implemented!");

	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02/04/2007 11:37:16
	DESCRIP:	
	IN:
	OUT:
*/
bool CPageStepDetails::Validate_CreateNewDir(CString & strText) const
{
	bool bOK = true;

	if( ! IsDlgItemEmpty(IDC_RED_TEXT_SRCFILE)){
		bOK = false;
		strText += _T("\n\"Source file\" field must be empty");
	}

	if( ! IsDlgItemEmpty(IDC_RED_TEXT_SOURCEDIR)){
		bOK = false;
		strText += _T("\n\"Source Directory\" field must be empty");
	}

	if(IsDlgItemEmpty(IDC_RED_TEXT_DESTDIR)){
		bOK = false;
		strText += _T("\n\"Destination Directory\" field must not be empty");
	}

	if( ! IsDlgItemEmpty(IDC_RED_TEXT_DESTFILE)){
		bOK = false;
		strText += _T("\n\"Destination File\" field must be empty");
	}

	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02/04/2007 11:37:21
	DESCRIP:	
	IN:
	OUT:
*/
bool CPageStepDetails::Validate_CopyFile(CString & strText) const
{
	bool bOK = true;

	if(IsDlgItemEmpty(IDC_RED_TEXT_SRCFILE)){
		bOK = false;
		strText += _T("\n\"Source file\" field must not be empty");
	}

	if(IsDlgItemEmpty(IDC_RED_TEXT_SOURCEDIR)){
		bOK = false;
		strText += _T("\n\"Source Directory\" field must not be empty");
	}

	if(IsDlgItemEmpty(IDC_RED_TEXT_DESTDIR)){
		bOK = false;
		strText += _T("\n\"Destination Directory\" field must not be empty");
	}

	if(IsDlgItemEmpty(IDC_RED_TEXT_DESTFILE)){
		bOK = false;
		strText += _T("\n\"Destination File\" field must not be empty");
	}

	return bOK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 08:56:45
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::OnChangeRedTextDestdir() 
{
	SetModified(TRUE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 08:56:42
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::OnChangeRedTextDestfile() 
{
	SetModified(TRUE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 08:56:39
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::OnChangeRedTextSourcedir() 
{
	SetModified(TRUE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 08:56:35
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::OnChangeRedTextSrcfile() 
{
	SetModified(TRUE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 09:33:10
	DESCRIP:	
		Return Value

		Nonzero if the changes are accepted; otherwise 0. 

	IN:
	OUT:
*/
BOOL CPageStepDetails::OnApply() 
{
	BOOL bAccept = FALSE;
	CString strMsgText;

	bool bValid = ValidateCurData(strMsgText);

	if(bValid){
		GetMainSheet()->SaveData();
		
		bAccept = CPropertyPage::OnApply();
	}
	else{
		::AfxMessageBox(_T("Current data is invalid:") + strMsgText);
	}

	return bAccept;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 09:33:08
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::OnOK() 
{
	CString strMsg;

	bool bValid = ValidateCurData(strMsg);

	if(bValid){
		GetMainSheet()->SaveData();
		
		CPropertyPage::OnOK();
	}
	else{
		::AfxMessageBox(_T("Current data is invalid") + strMsg);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 09:53:27
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::OnBnSrcFile() 
{
	CString strBrowsedDir;
	CString strBrowsedFile;

	CString strBrowsed;
	
	m_redTextSrcDir.GetWindowText(strBrowsedDir);
	m_redTextSrcFile.GetWindowText(strBrowsedFile);

	strBrowsed = strBrowsedDir + _T("\\") + strBrowsedFile;

	bool bOK = GetMainSheet()->BrowseForFile(_T("Choose a source file"), strBrowsedDir, strBrowsed);

	if(bOK){
		TCHAR szDrive	[_MAX_DRIVE]	= {0};
		TCHAR szDir		[_MAX_DIR]		= {0};
		TCHAR szFName	[_MAX_FNAME]	= {0};
		TCHAR szFExt	[_MAX_EXT]		= {0};

		_tsplitpath(strBrowsed, szDrive, szDir, szFName, szFExt);

		strBrowsedDir.Format(_T("%s%s"), szDrive, szDir);
		strBrowsedFile.Format(_T("%s%s"), szFName, szFExt);

		m_redTextSrcDir.SetWindowText(strBrowsedDir);
		m_redTextSrcFile.SetWindowText(strBrowsedFile);
		m_redTextDestFile.SetWindowText(strBrowsedFile);

		SetModified(TRUE);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 09:53:23
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::OnBnSrcDir() 
{
	CString strBrowsedDir = m_strDfltSrcDir;

	//m_redTextSrcDir.GetWindowText(strBrowsedDir);

	bool bOK = GetMainSheet()->BrowseForDirectory(_T("Choose a source directory"), strBrowsedDir);

	if(bOK){
		m_redTextSrcDir.SetWindowText(strBrowsedDir);
		m_strDfltSrcDir = strBrowsedDir;

		SetModified(TRUE);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11/04/2007 11:01:23
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::OnBnSrcDirDefault() 
{
	CString strBrowsedDir = m_strOrigDfltSrcDir;

	//m_redTextSrcDir.GetWindowText(strBrowsedDir);

	bool bOK = GetMainSheet()->BrowseForDirectory(_T("Choose a source directory"), strBrowsedDir);

	if(bOK){
		m_redTextSrcDir.SetWindowText(strBrowsedDir);
		m_strDfltSrcDir = strBrowsedDir;

		SetModified(TRUE);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 09:53:21
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::OnBnDestDir() 
{
	CString strBrowsedDir = m_strDfltDestDir;

	bool bOK = GetMainSheet()->BrowseForDirectory(_T("Choose a destination directory"), strBrowsedDir);

	if(bOK){
		m_redTextDestDir.SetWindowText(strBrowsedDir);
		m_strDfltDestDir = strBrowsedDir;

		SetModified(TRUE);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11/04/2007 11:01:06
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::OnBnDestDirDefault() 
{
	CString strBrowsedDir = m_strOrigDfltDestDir;

	bool bOK = GetMainSheet()->BrowseForDirectory(_T("Choose a destination directory"), strBrowsedDir);

	if(bOK){
		m_redTextDestDir.SetWindowText(strBrowsedDir);
		m_strDfltDestDir = strBrowsedDir;

		SetModified(TRUE);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	31/03/2007 11:16:08
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepDetails::OnSelchangeCmboStepType() 
{
	SetControlsForType();
}

void CPageStepDetails::OnMsgfilterRedTextSrcfile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	MSGFILTER *pMsgFilter = reinterpret_cast<MSGFILTER *>(pNMHDR);
	// TODO: The control will not send this notification unless you override the
	// CPropertyPage::OnInitDialog() function to send the EM_SETEVENTMASK message
	// to the control with either the ENM_KEYEVENTS or ENM_MOUSEEVENTS flag 
	// ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
