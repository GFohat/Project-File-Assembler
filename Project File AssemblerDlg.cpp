// Project File AssemblerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Project File Assembler.h"
#include "Project File AssemblerDlg.h"
//#include <fstream.h>
#include <direct.h>
#include "BuildListing.h"

#include "VersionNo.h"

#include "ConstLists.h"
#include <fstream>
using namespace CONS_LISTS;

#include "ConstTokens.h"
using namespace CONS_TOKENS;

#include "ConstMsgs.h"
using namespace CONS_MSGS;

#include "DlgQuickHelp.h"

#include "PfaMainSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectFileAssemblerDlg dialog

CProjectFileAssemblerDlg::CProjectFileAssemblerDlg(CWnd* pParent /*=NULL*/)
:	CPropertyPage			(CProjectFileAssemblerDlg::IDD)
	, m_iNumCsvFileLines	(0L)
	, CBrushHolder			(CONS_COLOURS::crefPAGE_BACK)
{
	//{{AFX_DATA_INIT(CProjectFileAssemblerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjectFileAssemblerDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectFileAssemblerDlg)
	DDX_Control	(pDX, IDC_BTN_BUILD_LISTNG, m_btnBuildListing);
	DDX_Control	(pDX, IDC_BUTTON1,			m_btn1);
	DDX_Control	(pDX, IDC_BUTTON3,			m_btn3);
	//DDX_Control	(pDX, IDOK,					m_btnOK);
	DDX_Control	(pDX, IDC_CHECK1,			m_ChkCreateDir);
	DDX_Control	(pDX, IDC_CHECK2,			m_ChkClearDir);
	DDX_Control	(pDX, IDC_LBL_FILEPATH,		m_lblFilePath);
	DDX_Control	(pDX, IDC_LIST1,			m_listctrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProjectFileAssemblerDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CProjectFileAssemblerDlg)
	ON_WM_SYSCOMMAND		()
	ON_WM_PAINT				()
	ON_WM_QUERYDRAGICON		()
	ON_BN_CLICKED			(IDC_BUTTON1,				OnBtnCopyFiles)
	ON_BN_CLICKED			(IDC_BUTTON3,				OnBtnBrowse)
	ON_BN_CLICKED			(IDC_BTN_BUILD_LISTNG,		OnBtnBuildListng)
	ON_BN_CLICKED			(IDC_BN_QUICK_HELP,			OnBnQuickHelp)
	ON_WM_CTLCOLOR()
	ON_MESSAGE				(eWM_BEGIN_IMMEDIATE,		OnWMBeginImmediate )
	ON_MESSAGE				(eWM_SINGLEFILE_PC_POS,		OnWMSingleFilePCPos )
	ON_NOTIFY				(NM_CUSTOMDRAW, IDC_LIST1, OnNMListCustomDraw)
	//}}AFX_MSG_MAP

	ON_MESSAGE	(eWM_SET_APPEARANCE,			OnWMSetAppearance)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectFileAssemblerDlg message handlers

BOOL CProjectFileAssemblerDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//DWORD dwStyle = ListView_GetExtendedListViewStyle(m_listctrl);
	//ListView_SetExtendedListViewStyle(m_listctrl, dwStyle | LVS_EX_CHECKBOXES);
	
	row = -1;


	if(m_strCmdLine.IsEmpty())
	{
		m_bFromCmdLine = false;

		CString strTitle;
		strTitle.Format(_T("Project File Assembler - %s"), STRFILEVER);
		SetWindowText(strTitle);
	}
	else
	{
		m_bFromCmdLine = true;
		PostMessage(eWM_BEGIN_IMMEDIATE, 0, 0);
	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 11:06:33
	DESCRIP:	
	IN:
	OUT:
*/
LPARAM CProjectFileAssemblerDlg::OnWMSetAppearance(WPARAM wParam, LPARAM lParam)
{
	InitList();
		
	GetDlgItem(IDC_LBL_FILEPATH)	->SetFont(GetMainSheet()->GetTheFont(eFont_EdBoxes));
	GetDlgItem(IDC_BUTTON3)			->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_BN_QUICK_HELP)	->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_CHECK1)			->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_CHECK2)			->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_BUTTON1)			->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_BTN_BUILD_LISTNG)->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 12:18:01
	DESCRIP:	
	IN:
	OUT:
*/
LRESULT CProjectFileAssemblerDlg::OnWMRearrangeControls(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 07:07:11
	DESCRIP:	
		m_listctrl.InsertColumn(0,"File");
		m_listctrl.InsertColumn(1,"Source");
		m_listctrl.InsertColumn(2,"Destination");
		m_listctrl.InsertColumn(3,"Copied Name");
		m_listctrl.InsertColumn(4,"Status");
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::InitList(void)
{
	DWORD dwExStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;

	m_listctrl.SetExtendedStyle(dwExStyle);
	m_listctrl.SetFont(GetMainSheet()->GetTheFont(eFont_List));

	for(DWORD dwLoop = 0L ; dwLoop < ePCol__LAST ; dwLoop++){
		m_listctrl.InsertColumn(
							dwLoop
							, szsCOL_NAMES_PFA[dwLoop]
							, isCOL_FMTS_PFA[dwLoop]
						);
	}

	CHeaderCtrl * pHdr = m_listctrl.GetHeaderCtrl();
	ATLASSERT(pHdr && ::IsWindow(pHdr->m_hWnd));

	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		pHdr->SetFont(GetMainSheet()->GetTheFont(eFont_ListHeader));
	}

	SetListColWidths();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 09:03:00
	DESCRIP:	
	IN:
	OUT:
*/
/*afx_msg*/
void CProjectFileAssemblerDlg::OnNMListCustomDraw(NMHDR * pNotifyStruct, LRESULT * pResult)
{
	* pResult = CDRF_DODEFAULT;

	NMLVCUSTOMDRAW * pLvcd = reinterpret_cast<NMLVCUSTOMDRAW *>(pNotifyStruct);

	if(pLvcd){
		switch(pLvcd->nmcd.dwDrawStage){
			case CDDS_PREPAINT:
				*pResult = CDRF_NOTIFYITEMDRAW;
				break;

			case CDDS_ITEMPREPAINT:
				{
					CString strFile = m_listctrl.GetItemText(pLvcd->nmcd.dwItemSpec, ePCol_File);
					CString strStatus = m_listctrl.GetItemText(pLvcd->nmcd.dwItemSpec, ePCol_Status);
					SetLineColouring(strFile, strStatus, pLvcd->clrText, pLvcd->clrTextBk);
					*pResult = CDRF_NEWFONT;
				}
				break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 09:12:56
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::SetLineColouring(
											const CString & strText
											, const CString & strStatus
											, COLORREF & crefFg
											, COLORREF & crefBg
										) const
{
	if(0 == strStatus.CompareNoCase(szsSTATUS_NAMES_PFA[ePStatus_FileDeleteFailed])){
		crefFg = WHITE;
		crefBg = RED;
	}

	else if(0 == strStatus.CompareNoCase(szsSTATUS_NAMES_PFA[ePStatus_CopyFileFailed])){
		crefFg = WHITE;
		crefBg = RED;
	}

	else{
		TCHAR chSig = strText.IsEmpty() ? 0 : strText.GetAt(0);

		eCSV_LINE_TYPE eType = XLateLineType(strText);

		ATLASSERT(eType >= 0 && eType < eCLT__LAST);

		if(eType >= 0 && eType < eCLT__LAST){
			crefFg = crefsLINE_FORE[eType];
			crefBg = crefsLINE_BACK[eType];
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 08:02:35
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::SetListColWidths(void)
{
	for(DWORD dwLoop = 0L ; dwLoop < ePCol__LAST ; dwLoop++){
		m_listctrl.SetColumnWidth(dwLoop, LVSCW_AUTOSIZE_USEHEADER);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CPropertyPage::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProjectFileAssemblerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPropertyPage::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProjectFileAssemblerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 07:38:20
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::OnBtnCopyFiles() 
{
	//CopyFiles001();
	CopyFiles002();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 20:09:43
	DESCRIP:	
		Original 'OnBtnCopyFiles()'
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::CopyFiles001(void)
{
	::AfxMessageBox(L"CProjectFileAssemblerDlg::CopyFiles001");

	//CWaitCursor wait;

	//m_listctrl.DeleteAllItems();
	//
	//if(m_strFilePath.IsEmpty())
	//{
	//	AfxMessageBox(_T("No csv file selected"));
	//	return;
	//}

	//InitProgress(m_strFilePath);
	//long iCurLine = 0L;
	//
	//TCHAR buf [2000];

	//CString sBuf, sFile, sTo, sFrom,sNewName, sMsg, sRem/*, sTmp*/;
	//
	//int pos;
	//row = -1;

	//std::ifstream f;
	//f.open(m_strFilePath);

	//while(f.good())
	//{
	//	//07/03/2007 14:17:51
	//	iCurLine ++;
	//	ShowProgress(iCurLine);

	//	sBuf.Empty();
	//	sFile.Empty();
	//	sFrom.Empty();
	//	sTo.Empty();
	//	sNewName.Empty();
	//	
	//	row++;

	//	f.getline(buf, sizeof(buf));

	//	if(!f.good())
	//		break;

	//	sBuf = buf;
	//	//sTmp = sBuf;
	//	//sTmp.MakeUpper();
	//
	//	pos			= sBuf.Find(szCOMMA, 0);
	//	sFile		= sBuf.Left(pos);
	//	
	//	sBuf		= sBuf.Right(sBuf.GetLength() - pos - 1);
	//	pos			= sBuf.Find(szCOMMA, 0);
	//	sFrom		= sBuf.Left(pos);
	//	
	//	sBuf		= sBuf.Right(sBuf.GetLength() - pos - 1);
	//	pos			= sBuf.Find(szCOMMA, 0);
	//	sTo			= sBuf.Left(pos);

	//	sNewName	= sBuf.Right(sBuf.GetLength() - pos - 1);
	//	
	//	sRem		= sFile.Left(1);
	//
	//	
	//	if(sRem == szIGNORE_LINE)
	//	{
	//		AddListRow(szSEPARATOR, sFrom, sTo, sNewName, ePStatus_IgnoredLine);
	//		continue;
	//	
	//	}
	//	if(CheckDestinationDir(sTo, sMsg) != 0)
	//	{
	//		row--;
	//		continue;
	//	}
	//	if(sFile == szWILDCARD)
	//	{
	//		CopyAllFilesInDirectory(sFrom, sTo);
	//		continue;
	//	}

	//	//07/03/2007 11:19:27
	//	if(sFile == szINCSUBFOLDERS){
	//		CopyDirectoryComplete(sFrom, sTo);
	//		continue;
	//	}

	//	AddListRow(sFile, sFrom, sTo, sNewName, ePStatus_Copying);
	//	
	//	if(sFile.IsEmpty() || sFrom.IsEmpty())
	//	{	
	//		if(sTo.IsEmpty())
	//			ShowStatus(ePStatus_IncompleteLine);
	//		
	//		else
	//			ShowStatus(ePStatus_DirCreationOnly);
	//		
	//		continue;
	//	}

	//	sFrom += szBACKSLASH + sFile;

	//	if( ! m_finder.FindFile(sFrom))
	//	{
	//		ShowStatus(ePStatus_SourceNonExistent);
	//		CString str = sFrom + " - Source File does not exist";
	//		m_lstFail.Add(str);
	//		continue;
	//	}

	//
	//	if( ! sNewName.IsEmpty())
	//	{
	//		sTo += szBACKSLASH + sNewName;
	//	}
	//	
	//	CopySingleFile002(sFrom, sTo);
	//}

	//if(m_bFromCmdLine)
	//	OnCopyOperationDone_CMD();
	//else
	//	OnCopyOperationDone_GUI();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 20:09:46
	DESCRIP:	
		New 'OnBtnCopyFiles()'
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::CopyFiles002(void)
{
	CWaitCursor wait;

	m_listctrl.DeleteAllItems();
	CDirInitHandler::ResetContent();
	m_lstFail.RemoveAll();
	
	if(m_strFilePath.IsEmpty())
	{
		::AfxMessageBox(_T("No csv file selected"));
		return;
	}

	CReportHelper::InitReport(m_strFilePath);
	InitProgress(m_strFilePath);

	//the main part starts here...
	BOOL bOK = ProcessCsvFile();

	if(!bOK)
		::AfxMessageBox(_T("Failed to process ") + m_strFilePath);

	CReportHelper::ExitReport(!m_bFromCmdLine);

	if(m_bFromCmdLine)
		OnCopyOperationDone_CMD();
	else
		OnCopyOperationDone_GUI();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 20:16:30
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CProjectFileAssemblerDlg::ProcessCsvFile(void)
{
	long iCurLine = 0L;

	CStdioFile csvfil;
	UINT uFlags = 
				CFile::modeRead
				| CFile::shareDenyNone
				| CFile::typeText
				| CFile::modeNoTruncate
			;

	BOOL bOK = csvfil.Open(m_strFilePath, uFlags);

	if(bOK){
		CString strLine;

		while(bOK && csvfil.ReadString(strLine)){

			iCurLine ++;
			ShowProgress(iCurLine);

			bOK = ProcessCsvLine(iCurLine, strLine);
		}

		csvfil.Close();
	}

	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 20:21:14
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CProjectFileAssemblerDlg::ProcessCsvLine(const long iLineNum, const CString & strLine)
{
	BOOL bOK = TRUE;
	CStringArray aryItems;

	CCsvHelper::CsvLineToStrings(strLine, aryItems, eCI__LAST);
	ATLTRACE(_T("%04i: %s\n"), iLineNum, strLine);

	bOK = ProcessCsvItems(iLineNum, aryItems);

	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 20:46:44
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CProjectFileAssemblerDlg::ProcessCsvItems(const long iLineNum, const CStringArray & aryItems)
{
	BOOL bOK = TRUE;

	eCSV_LINE_TYPE eType = XLateLineType(aryItems.GetAt(0));

	if(eCLT_Comment != eType){
		bool bIsNewDir = CDirInitHandler::IsNewDestinationDir(aryItems.GetAt(eCI_DestDir), iLineNum, iLineNum);
		if(bIsNewDir){
			CReportHelper::RptDirCreated(aryItems.GetAt(eCI_DestDir));
		}
	}

	switch(eType){
		case eCLT_Comment:				bOK = Process_Comment			(iLineNum, aryItems);	break;
		case eCLT_CopySingleFile:		bOK = Process_CopySingleFile	(iLineNum, aryItems);	break;
		case eCLT_CopySingleDir:		bOK = Process_CopySingleDir		(iLineNum, aryItems);	break;
		case eCLT_CopyDirAndSubDirs:	bOK = Process_CopyDirAndSubDirs	(iLineNum, aryItems);	break;
		case eCLT_CreateNewDir:			bOK = Process_CreateNewDir		(iLineNum, aryItems);	break;

		default:
			::AfxMessageBox(_T("ProcessCsvItems: Unhandled line type\n") + aryItems.GetAt(0));
			break;
	}

	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 07:35:19
	DESCRIP:
		Just copy the text into the list control, as it may
		contain some titles or interesting notes etc.
	IN:
	OUT:
*/
BOOL CProjectFileAssemblerDlg::Process_Comment(const long iLineNum, const CStringArray & aryItems)
{
	BOOL bOK = TRUE;

	AddListRow(
			aryItems.GetAt			(eCI_File)			//file
			, aryItems.GetAt		(eCI_SourceDir)		//source
			, aryItems.GetAt		(eCI_DestDir)		//dest
			, aryItems.GetAt		(eCI_CopiedName)	//copied
			, ePStatus_IgnoredLine						//status
		);
			
	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 07:35:21
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CProjectFileAssemblerDlg::Process_CopySingleFile(const long iLineNum, const CStringArray & aryItems)
{
	BOOL bOK = TRUE;

	CString strSource	= aryItems.GetAt(eCI_SourceDir) + szBACKSLASH + aryItems.GetAt(eCI_File);
	CString strDest		= aryItems.GetAt(eCI_DestDir)	+ szBACKSLASH + aryItems.GetAt(eCI_CopiedName);

	//ensure destination exists...
	CreateNewDirectory002(aryItems.GetAt(eCI_DestDir));

	AddListRow(_T("COPY FILE"), strSource, strDest, _T(""), ePStatus_CopyFile);
	CopySingleFile002(strSource, strDest);

	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 07:35:24
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CProjectFileAssemblerDlg::Process_CopySingleDir(const long iLineNum, const CStringArray & aryItems)
{
	BOOL bOK = TRUE;

	AddListRow(
			_T("COPY DIR")
			, aryItems.GetAt(eCI_SourceDir)
			, aryItems.GetAt(eCI_DestDir)
			, _T("")
			, ePStatus_Copying
		);

	CopyAllFilesInDirectory(aryItems.GetAt(eCI_SourceDir), aryItems.GetAt(eCI_DestDir));

	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 07:35:27
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CProjectFileAssemblerDlg::Process_CopyDirAndSubDirs(const long iLineNum, const CStringArray & aryItems)
{
	BOOL bOK = TRUE;

	AddListRow(
			_T("COPY DIR AND SUBS")
			, aryItems.GetAt(eCI_SourceDir)
			, aryItems.GetAt(eCI_DestDir)
			, _T("")
			, ePStatus_Copying
		);

	CopyDirectoryComplete(aryItems.GetAt(eCI_SourceDir), aryItems.GetAt(eCI_DestDir));

	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 07:35:29
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CProjectFileAssemblerDlg::Process_CreateNewDir(const long iLineNum, const CStringArray & aryItems)
{
	BOOL bOK = TRUE;

	AddListRow(
			_T("CREATE DIR")
			, _T("")
			, aryItems.GetAt(eCI_DestDir)
			, _T("")
			, ePStatus_DirCreationOnly
		);

	CreateNewDirectory002(aryItems.GetAt(eCI_DestDir));

	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 07:24:15
	DESCRIP:	
	IN:
	OUT:
*/
eCSV_LINE_TYPE CProjectFileAssemblerDlg::XLateLineType(const CString & strCsvIndicator) const
{
	eCSV_LINE_TYPE eType = eCLT_Comment;

	const TCHAR chTEST = strCsvIndicator.IsEmpty() ? 0 : strCsvIndicator.GetAt(0);

	switch(chTEST){
		case 0:			eType = eCLT_CreateNewDir;			break;
		case _T('#'):	eType = eCLT_Comment;				break;
		case _T('&'):	eType = eCLT_CopyDirAndSubDirs;		break;
		case _T('*'):	eType = eCLT_CopySingleDir;			break;
	
		default:		eType = eCLT_CopySingleFile;		break;
	}

	return eType;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 09:52:48
	DESCRIP:	
	IN:
	OUT:
*/
/*virtual*/
bool CProjectFileAssemblerDlg::DoCreateDirectory(void)
{
	bool bDoCreate = false;

	UpdateData();

	if(BST_CHECKED == m_ChkCreateDir.GetCheck())
		bDoCreate = true;

	return bDoCreate;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 09:52:55
	DESCRIP:	
	IN:
	OUT:
*/
/*virtual*/
bool CProjectFileAssemblerDlg::DoEmptyDirectory(void)
{
	bool bDoEmpty = false;

	UpdateData();

	if(BST_CHECKED == m_ChkClearDir.GetCheck())
		bDoEmpty = true;

	return bDoEmpty;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 09:55:39
	DESCRIP:	
	IN:
	OUT:
*/
/*virtual*/
void CProjectFileAssemblerDlg::OnNewDirectory(const CString & strDir, const DWORD dwOPNumber, const DWORD dwStepNumber)
{
	CDirInitHandler::IsNewDestinationDir(strDir, dwOPNumber, dwStepNumber);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 14:17:57
	DESCRIP:	
		How many lines are in this file?
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::InitProgress(const CString & strCsvFile)
{
	m_iNumCsvFileLines = 0L;

	CStdioFile fil;
	UINT uFlags = 
				CFile::modeRead
				| CFile::shareDenyNone
				| CFile::typeText
				| CFile::modeNoTruncate
			;

	BOOL bOK = fil.Open(strCsvFile, uFlags);

	if(bOK){
		CString strLine;

		while(fil.ReadString(strLine))
			m_iNumCsvFileLines ++;

		fil.Close();
	}

	CProgressCtrl * pCtrl = reinterpret_cast<CProgressCtrl *>(GetDlgItem(IDC_PROGRESS_ASSEMBLER));
	ASSERT(pCtrl && ::IsWindow(pCtrl->m_hWnd));

	if(pCtrl && ::IsWindow(pCtrl->m_hWnd)){
		pCtrl->SetRange(0, 100);
	}

	//IDC_PROGRESS_FILE
	pCtrl = reinterpret_cast<CProgressCtrl *>(GetDlgItem(IDC_PROGRESS_FILE));
	ASSERT(pCtrl && ::IsWindow(pCtrl->m_hWnd));

	if(pCtrl && ::IsWindow(pCtrl->m_hWnd)){
		pCtrl->SetRange(0, 100);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 14:17:59
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::ShowProgress(const long iCurFileLine)
{
	double rlPercentage = (100.0 * double(iCurFileLine)) / double(m_iNumCsvFileLines ? m_iNumCsvFileLines : 1);

	CProgressCtrl * pCtrl = reinterpret_cast<CProgressCtrl *>(GetDlgItem(IDC_PROGRESS_ASSEMBLER));
	ASSERT(pCtrl && ::IsWindow(pCtrl->m_hWnd));

	if(pCtrl && ::IsWindow(pCtrl->m_hWnd)){
		pCtrl->SetPos(int(rlPercentage));
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 11:20:45
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::CopyDirectoryComplete(const CString & strFrom, const CString & strTo)
{
	AddListRow(_T("Dir including subdirs..."), strFrom, strTo, _T(""), ePStatus_DirIncSubDirs);

	CreateNewDirectory002(strTo);

	if(m_ChkClearDir.GetCheck())
		DeleteDirContent(strTo);

	CString strWild = strFrom + szWILDCARDFILE;

	CString strFound;
	CString strNewFrom;
	CString strNewTo;

	WIN32_FIND_DATA data;

	HANDLE hFind = ::FindFirstFile(strWild, &data);

	if(hFind && (INVALID_HANDLE_VALUE != hFind)){

		do{

			strFound	= data.cFileName;

			strNewFrom	= strFrom + szBACKSLASH + strFound;
			strNewTo	= strTo + szBACKSLASH + strFound;
			
			if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
				if(strFound != _T(".")){
					if(strFound != _T("..")){

						CopyDirectoryComplete(strNewFrom, strNewTo);
					}
				}
			}
			else{
				AddListRow(strFound, strFrom, strTo, strFound, ePStatus_CopyFile);
				CopySingleFile002(strNewFrom, strNewTo);
			}

		} while(::FindNextFile(hFind, &data));

		::FindClose(hFind);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 08:33:52
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::AddListRow(
										const CString & strFile
										, const CString & strSource
										, const CString & strDestination
										, const CString & strCopiedName
										, const DWORD dwStatus
									)
{
	int iCur = m_listctrl.GetItemCount();
	int iNew = m_listctrl.InsertItem(iCur, _T(""));

	m_listctrl.SetItemText(iNew, ePCol_File,		strFile);
	m_listctrl.SetItemText(iNew, ePCol_Source,		strSource);
	m_listctrl.SetItemText(iNew, ePCol_Destination, strDestination);
	m_listctrl.SetItemText(iNew, ePCol_CopiedName,	strCopiedName);

	CString strStatus = dwStatus < ePStatus__LAST ? szsSTATUS_NAMES_PFA[dwStatus] : _T("");

	m_listctrl.SetItemText(iNew, ePCol_Status,	strStatus);
	
	m_listctrl.SetSelectionMark(iNew);
		
	m_listctrl.EnsureVisible(iNew, FALSE);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 11:05:02
	DESCRIP:	
	IN:
	OUT:
*/
/*virtual*/ 
void CProjectFileAssemblerDlg::ReportDIEvent(const CFileCopyReport & report)
{
	AddListRow(
				report.GetFile()
				, report.GetSource()
				, report.GetDestination()
				, report.GetCopiedName()
				, report.GetStatus()
			);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 09:38:31
	DESCRIP:	
	IN:
	OUT:
*/
/*virtual*/ 
void CProjectFileAssemblerDlg::ReportFCEvent(const CFileCopyReport & report)
{
	AddListRow(
				report.GetFile()
				, report.GetSource()
				, report.GetDestination()
				, report.GetCopiedName()
				, report.GetStatus()
			);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 07:43:02
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::OnCopyOperationDone_CMD(void)
{
	if(m_lstFail.GetSize() > 0)
		WriteResultExit(_T("FAIL"));
	else
		WriteResultExit(_T("OK"));
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 08:03:51
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::OnCopyOperationDone_GUI(void)
{
	const int iFAILCOUNT	= m_lstFail.GetSize();
	const int iDISPLAYMAX	= 20;

	CString strMessage;
	UINT uType = iFAILCOUNT ? MB_ICONSTOP : MB_ICONINFORMATION;
	
	if(iFAILCOUNT == 0)		
		strMessage = _T("File copy process complete. All files copied successfully");
	
	//only display up to iDISPLAYMAX failures
	else if(iFAILCOUNT < iDISPLAYMAX)
	{	
		strMessage = _T("The following files failed to copy\n");
		
		for(int iLoop = 0 ; iLoop < iFAILCOUNT ; iLoop++){
			strMessage += m_lstFail.GetAt(iLoop);
			strMessage += _T("\n");
		}

	}

	//more than iDISPLAYMAX items failed - just show how many, 
	//else the message box will get too big
	else
		strMessage.Format(_T("%i files failed to copy"), iFAILCOUNT);

	//show the message
	::AfxMessageBox(strMessage, uType);

	DumpListReport();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 09:50:36
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::DumpListReport(void)
{
	int iReply = ::AfxMessageBox(_T("Save a report?"), MB_YESNO);

	if(IDYES == iReply){
		CWaitCursor wait;

		CStdioFile file;
		CString strFileName;

		CreateDumpFile(file, strFileName);

		CString strLine;
		const int iROWCOUNT = m_listctrl.GetItemCount();

		for(int iLine = 0 ; iLine < iROWCOUNT ; iLine++){
			strLine = GetListRowText(iLine);

			file.WriteString(strLine);
			file.WriteString(_T("\n"));
		}

		file.Close();

		::AfxMessageBox(_T("Results dumped to ") + strFileName, MB_ICONINFORMATION);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 10:01:41
	DESCRIP:	
	IN:
	OUT:
*/
CString CProjectFileAssemblerDlg::GetListRowText(const int iRow)
{
	CString strRet;
	
	for(DWORD dwLoop = 0L ; dwLoop < ePCol__LAST ; dwLoop++){
		
		if(!strRet.IsEmpty())
			strRet += szCOMMA;

		strRet += m_listctrl.GetItemText(iRow, dwLoop);
	}

	return strRet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 09:53:38
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::CreateDumpFile(CStdioFile & iofile, CString & strFileName)
{
	SYSTEMTIME dtsys;
	::GetLocalTime(&dtsys);

	TCHAR szCurDir[MAX_PATH + 5] = {0};
	::GetCurrentDirectory(MAX_PATH, szCurDir);

	strFileName.Format(
					_T("%s\\Pfa Reports\\%04i-%02i-%02i %02i%02i%02i.csv")
					, szCurDir
					, dtsys.wYear, dtsys.wMonth, dtsys.wDay
					, dtsys.wHour, dtsys.wMinute, dtsys.wSecond
				);

	if(iofile.m_pStream)
		iofile.Close();

	UINT uFlags = 
				CFile::modeWrite
				| CFile::shareDenyNone
				| CFile::modeCreate
				| CFile::modeNoTruncate
				| CFile::typeText
			;

	BOOL bOpened  = iofile.Open(
							strFileName
							, uFlags
						);

	ASSERT(bOpened);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 07:52:38
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::WriteResultExit(const CString & strResult)
{
	const DWORD dwBUFSIZE = MAX_PATH;

	::AfxMessageBox(L"CProjectFileAssemblerDlg::WriteResultExit!");

	//TCHAR szBuffer[dwBUFSIZE + 5] = {0};

	//_getcwd(szBuffer, dwBUFSIZE);

	//CString strFile = szBuffer;
	//strFile += _T("\\PFARes.ini");

	//WritePrivateProfileString(_T("Result"), _T("copyres"), strResult, strFile);
	_exit(0);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 08:47:20
	DESCRIP:	
		Change the latest list row item's status
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::ShowStatus(const DWORD dwStatus)
{
	int iRow = m_listctrl.GetItemCount() - 1;

	if(iRow >= 0)
		ShowStatus(iRow, dwStatus);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 07:32:34
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::ShowStatus(const int iRow, const DWORD dwStatus)
{
	if(dwStatus < ePStatus__LAST)
		m_listctrl.SetItemText(iRow, ePCol_Status, szsSTATUS_NAMES_PFA[dwStatus]);
	else
		m_listctrl.SetItemText(iRow, ePCol_Status, szsSTATUS_NAMES_PFA[ePStatus_None]);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 08:12:27
	DESCRIP:	
	IN:
	OUT:
*/
int CProjectFileAssemblerDlg::CheckDestinationDir(CString Path, CString & Err)
{
	if(HasDirBeenProcessed(Path))
		return 0;

	m_dirlist.Add(Path);

	//int pos;

	if(!m_finder.FindFile(Path))
	{
		if(m_ChkCreateDir.GetCheck())
		{
			return CreateNewDirectory002(Path);
		}
		else
		{
			Err = "Could not find destination directory";
			return 3;
		}
	}
	else // means directory already exists so lets check if we need to clear it 
	{
		if(m_ChkClearDir.GetCheck())
			DeleteDirContent(Path);
	}

	m_strDirsProcessed += Path + _T(" ");
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 11:02:53
	DESCRIP:	
	IN:
	OUT:
*/
int CProjectFileAssemblerDlg::CreateNewDirectory001(const CString & strDir)
{
	CString sDir;
	CString sTmp;

	sTmp = strDir;
		
	int pos = 0;				

	while(TRUE)
	{
		pos = sTmp.Find(szBACKSLASH, pos + 1);

		if(pos < 0){
			if( ! sTmp.IsEmpty())
			{
				sDir += sTmp;
				sTmp.Empty();
			}
			else
				break;
		}
		else
			sDir += sTmp.Left(pos);

		sTmp = sTmp.Right(sTmp.GetLength() - pos);

		if( ! m_finder.FindFile(sDir) && (sDir.Find(szBACKSLASH, 0) > 0))
		{
			AddListRow(szCREATING_DIR, szSEPARATOR, sDir, _T(""), ePStatus_None);

			if(_tmkdir(sDir) != 0)
			{
				DWORD dwErr = ::GetLastError();
				::AfxMessageBox(_T("Failed to create directory:\n") + sDir);
				ShowStatus(ePStatus_DirCreationFailed);
				return 2;
			}
			else
				ShowStatus(ePStatus_DirCreationOK);

			row++;
		}
		
	}//end of while

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 13:40:09
	DESCRIP:
		Checks and, if required, creates directories up to and including
		the passed argument.

eg:

Checking existence of C:
Checking existence of C:\WINLINK
Checking existence of C:\WINLINK\Installation
Checking existence of C:\WINLINK\Installation\INSTALLSHIELD 10
Checking existence of C:\WINLINK\Installation\INSTALLSHIELD 10\eMas
Checking existence of C:\WINLINK\Installation\INSTALLSHIELD 10\eMas\Source
Checking existence of C:\WINLINK\Installation\INSTALLSHIELD 10\eMas\Source\Abstract Layer
Checking existence of C:\WINLINK\Installation\INSTALLSHIELD 10\eMas\Source\Abstract Layer\Installs

	IN:
	OUT:
*/
int CProjectFileAssemblerDlg::CreateNewDirectory002(const CString & strDir)
{
	const TCHAR chSLASH = _T('\\');
	const long iMAX = strDir.GetLength();

	TCHAR chProbe = 0;
	long iCharPos = 0;
	CString strDirCheck;
	DWORD dwErr = NOERROR;
	BOOL bCreated = FALSE;

	for(iCharPos = 0 ; iCharPos < iMAX ; iCharPos++){
		chProbe = strDir.GetAt(iCharPos);

		if(chSLASH == chProbe){
			strDirCheck = strDir.Left(iCharPos);
			TRACE(_T("Checking existence of %s\n"), strDirCheck);

			bCreated = ::CreateDirectory(strDirCheck, 0);

			if(bCreated)
				AddListRow(_T("Create new directory"), _T(""), strDirCheck, _T(""), ePStatus_DirCreationOK);
			
			else{
				dwErr = ::GetLastError();
				
				if(ERROR_ALREADY_EXISTS != dwErr){
					AddListRow(_T("Create new directory"), _T(""), strDirCheck, _T(""), ePStatus_DirCreationFailed);
					::AfxMessageBox(_T("Failed to create directory:\n") + strDirCheck);
				}
			}
		}
	}

	//path to new directory should now be in place, so create it...
	::CreateDirectory(strDir, 0);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 09:04:18
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::DeleteDirContent(const CString & strDir)
{
	BOOL bWorking = m_finder.FindFile(strDir + szWILDCARDFILE);
	CString strFile;
	BOOL bDeleted = FALSE;

	AddListRow(szSEPARATOR, szSEPARATOR, strDir, _T(""), ePStatus_DirBeingEmptied);

	while(bWorking)
	{
		bWorking = m_finder.FindNextFile();
		strFile = m_finder.GetFilePath();

		if(m_finder.IsDots() || m_finder.IsDirectory())
			continue;
		
		AddListRow(szDELETING_FILE, szSEPARATOR, strFile, _T(""), ePStatus_None);
		
		bDeleted = DeleteFile(strFile);

		//09/03/2007 15:12:17
		if(!bDeleted){
			DWORD dwErr = ::GetLastError();
			TRACE(_T("DeleteFile failed, GetLastError returned 0x%X (%i)\n"), dwErr, dwErr);

			//read-only file...
			if(ERROR_ACCESS_DENIED == dwErr){

			}
		}

		ShowStatus(bDeleted ? ePStatus_FileDeleteOK : ePStatus_FileDeleteFailed);

		row++;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 10:57:14
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::OnBtnBrowse() 
{
	const static TCHAR szFILTER[] = _T("Comma Separated Values (*.csv)|*.csv|");

	CFileDialog fd( 
				true
				, NULL
				, _T("")
				, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST
				, szFILTER
				, this 
			);

#pragma message(">>>> Broaden this <<<<")

	fd.m_ofn.lpstrInitialDir = _T("C:\\WinLink\\Installation\\InstallShield 12");
	
	if( fd.DoModal() == IDOK )
	{
		m_strFilePath = fd.GetPathName();
		m_lblFilePath.SetWindowText(m_strFilePath);
		CCsvHelper::CsvToListCtrl(m_strFilePath, m_listctrl);
		SetListColWidths();
	}
	
}

void CProjectFileAssemblerDlg::OnBtnBuildListng() 
{
	CBuildListing bl;
	bl.DoModal();
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 08:19:08
	DESCRIP:
		Must be case-insensitive.
	IN:
	OUT:
*/
bool CProjectFileAssemblerDlg::HasDirBeenProcessed(const CString & strDir) const
{
	bool bHasProcessed = false;

	const DWORD dwMAX = m_dirlist.GetSize();
	CString strProbe;

	for(DWORD dwLoop = 0L ; dwLoop < dwMAX && !bHasProcessed ; dwLoop++){
		strProbe = m_dirlist.GetAt(dwLoop);

		if(0 == strProbe.CompareNoCase(strDir))
			bHasProcessed = true;
	}

	return bHasProcessed;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	
	DESCRIP:	
	IN:
	OUT:
*/
int CProjectFileAssemblerDlg::CopyAllFilesInDirectory(const CString & sFrom, const CString & sTo)
{
//	if(sFrom == "?")
//	{
//		while(TRUE)
//		{
//			AfxMessageBox("All files are to be copied to " + sTo + ".\nPlease select the source folder from the next dialog");
//
//			CFolderDialog dlg( &sFrom);
//			if (dlg.DoModal() == IDOK)
//			{
//				if(m_finder.FindFile(sFrom + "\\*.*"))
//				{
//					if(AfxMessageBox("Copy all files from " + sFrom + " to " + sTo + "?", MB_YESNO)==IDYES)
//						break;
//				}
//				else
//					AfxMessageBox("Cannot find source directory");
//			}
//			else
//				continue;
//		}
//	
//	}
	
	//m_listctrl.InsertItem(row + 1,"______________");
	//row++;
	//m_listctrl.InsertItem(row + 1,"COPY ALL FILES");
	//m_listctrl.SetItemText(row,1,sFrom);
	//m_listctrl.SetItemText(row,2,sTo);
	//row++;
	//m_listctrl.InsertItem(row + 1,"______________");
	//row++;

	AddListRow(szSEPARATOR, _T(""), _T(""), _T(""), ePStatus_None);
	AddListRow(_T("COPY ALL FILES"), sFrom, sTo, _T(""), ePStatus_None);
	AddListRow(szSEPARATOR, _T(""), _T(""), _T(""), ePStatus_None);

	CString strName;
	CString strSourceFile;
	CString strDestFile;

	BOOL bWorking = m_finder.FindFile(sFrom + szWILDCARDFILE);

	CreateNewDirectory002(sTo);

	while(bWorking)
	{	
		bWorking	= m_finder.FindNextFile();
		strName		= m_finder.GetFileName();

		if(m_finder.IsDots()||m_finder.IsDirectory())
			continue;
	
		AddListRow(strName, sFrom, sTo, strName, ePStatus_CopyFile);
		
		strSourceFile	= sFrom + szBACKSLASH + strName;
		strDestFile		= sTo	+ szBACKSLASH + strName;

		CopySingleFile002(strSourceFile, strDestFile);
			
		row++;
	}
	row--;
	
	
	return 0;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	09/03/2007 14:09:15
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::CopySingleFile002(const CString & strSrcFile, const CString & strDestFile)
{
	using namespace PARAMS;

	DWORD dwCopyFlags = 0L;

	CParamsCopyProgress prgrsparams(m_hWnd);
	BOOL bCancel = FALSE;

	BOOL bOK = ::CopyFileEx(
							strSrcFile
							, strDestFile
							, CopyProgressRoutine
							, LPVOID(&prgrsparams)
							, &bCancel
							, dwCopyFlags
						);

	if(bOK){
		ShowStatus(ePStatus_CopyFileOK);

		CReportHelper::RptFileCopied(strSrcFile, strDestFile);
	}
	else{
		ShowStatus(ePStatus_CopyFileFailed);
		
		CString strFailed;
		strFailed.Format(
						_T("Error 0x%X Copying \"%s\" to \"%s\"")
						, ::GetLastError()
						, strSrcFile
						, strDestFile
					);

		m_lstFail.Add(strFailed);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	09/03/2007 14:42:43
	DESCRIP:	
	IN:
	OUT:
*/
LRESULT CProjectFileAssemblerDlg::OnWMSingleFilePCPos(WPARAM wParam, LPARAM lParam)
{
	using namespace PARAMS;

	CParamsShowFilePCPosition * pFilePrgrs = reinterpret_cast<CParamsShowFilePCPosition *>(lParam);
	ASSERT(pFilePrgrs);

	if(pFilePrgrs){

		double rlPercent = pFilePrgrs->GetPercent();

		CProgressCtrl * pCtrl = reinterpret_cast<CProgressCtrl *>(GetDlgItem(IDC_PROGRESS_FILE));
		ASSERT(pCtrl && ::IsWindow(pCtrl->m_hWnd));

		if(pCtrl && ::IsWindow(pCtrl->m_hWnd)){
			pCtrl->SetPos(int(rlPercent));
		}

		delete pFilePrgrs;
		pFilePrgrs = 0;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	09/03/2007 14:11:38
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
DWORD CALLBACK CProjectFileAssemblerDlg::CopyProgressRoutine(
							LARGE_INTEGER		liTotalFileSize          // file size
							, LARGE_INTEGER		liTotalBytesTransferred  // bytes transferred
							, LARGE_INTEGER		liStreamSize             // bytes in stream
							, LARGE_INTEGER		liStreamBytesTransferred // bytes transferred for stream
							, DWORD				dwStreamNumber           // current stream
							, DWORD				dwCallbackReason         // callback reason
							, HANDLE			hSourceFile              // handle to source file
							, HANDLE			hDestinationFile         // handle to destination file
							, LPVOID			lpData                   // from CopyFileEx
						)
{
	using namespace PARAMS;

	DWORD dwRet = PROGRESS_CONTINUE;

	CParamsCopyProgress * pParams 
			= reinterpret_cast<CParamsCopyProgress *>(lpData);

	if(pParams){
		double rlPercent = double(liTotalBytesTransferred.QuadPart) / double(liTotalFileSize.QuadPart);
		rlPercent *= 100.0f;

		DWORD dwTimesSeen = pParams->SeenInCPR();

		//ShowCopyProgress(rlPercent, hSourceFile, hDestinationFile, *pParams);

		DWORD dwInstance = 0L;
		CParamsShowFilePCPosition * pSFPP 
				= new CParamsShowFilePCPosition(
										liTotalFileSize
										, liTotalBytesTransferred
										, dwStreamNumber
										, dwCallbackReason
									);

		_ASSERTE(pSFPP);
		
		BOOL bTX = pParams->SendMsg(
								eWM_SINGLEFILE_PC_POS
								, 0
								, LPARAM(pSFPP)
							);
		_ASSERTE(bTX);

		if(!bTX){
			delete pSFPP;
			pSFPP = 0;
		}
	}

	return dwRet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 09:40:46
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::CopySingleFile001(const CString & sFrom, const CString & sTo)
{
	SHFILEOPSTRUCT fileop;
	CString strFrom = sFrom;
	CString sTitle = _T("Copying ") + sFrom;
	strFrom += _T('\0');

	memset(&fileop, 0, sizeof(SHFILEOPSTRUCT));

	fileop.wFunc = FO_COPY;		//Need to perform the copy operation
	fileop.pTo	 = sTo;			//Destination folder
	fileop.pFrom = strFrom ;	//Source folder
	
	fileop.fFlags = 
				FOF_FILESONLY 
				| FOF_NOCONFIRMATION 
				| FOF_SIMPLEPROGRESS 
				| FOF_NOCONFIRMMKDIR 
				| FOF_MULTIDESTFILES
			;	
	
	fileop.lpszProgressTitle = sTitle;
	
	//Returns zero if successful
	int iResult = SHFileOperation(&fileop);

	if(iResult != 0)
	{
		ShowStatus(ePStatus_CopyFileFailed);
		CString strFail = "Failed to copy ";
				strFail += sFrom + " to " + sTo;
		m_lstFail.Add(strFail);
	}
	else
		ShowStatus(ePStatus_CopyFileOK);
	

	if (fileop.fAnyOperationsAborted == TRUE)
		ShowStatus(ePStatus_UserCancelled);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/03/2007 09:49:22
	DESCRIP:	
	IN:
	OUT:
*/
LRESULT CProjectFileAssemblerDlg::OnWMBeginImmediate(WPARAM wParam, LPARAM lParam)
{
	if(m_bFromCmdLine)
	{
		m_strFilePath = m_strCmdLine;

		m_lblFilePath.SetWindowText(m_strFilePath);

		m_ChkClearDir.SetCheck		(BST_CHECKED);
		m_ChkCreateDir.SetCheck		(BST_CHECKED);

		m_ChkClearDir.EnableWindow		(FALSE);
		m_ChkCreateDir.EnableWindow		(FALSE);
		m_btnBuildListing.EnableWindow	(FALSE);

		m_btn1.EnableWindow				(FALSE);
		m_btn3.EnableWindow				(FALSE);
		
		OnBtnCopyFiles();
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 08:10:10
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::OnBnQuickHelp() 
{
	CDlgQuickHelp dlg;
	dlg.DoModal();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 10:36:22
	DESCRIP:	
	IN:
	OUT:
*/
CPfaMainSheet * CProjectFileAssemblerDlg::GetMainSheet(void)
{
	CPfaMainSheet * pSheet = reinterpret_cast<CPfaMainSheet *>(GetParent());
	ATLASSERT(pSheet && ::IsWindow(pSheet->m_hWnd));
	return pSheet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 08:01:16
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::OnOK() 
{
	ATLTRACE(_T("CProjectFileAssemblerDlg::OnOK\n"));	
	
	CPropertyPage::OnOK();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 08:01:14
	DESCRIP:	
	IN:
	OUT:
*/
void CProjectFileAssemblerDlg::OnCancel() 
{
	ATLTRACE(_T("CProjectFileAssemblerDlg::OnCancel\n"));	
	
	CPropertyPage::OnCancel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/04/2007 12:27:17
	DESCRIP:	
	IN:
	OUT:
*/
HBRUSH CProjectFileAssemblerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return CBrushHolder::GetBrush(hbr);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	25/04/2007 13:08:17
	DESCRIP:	
	ePage_PfaDlg				= 0
	, ePage_PfaData
	, ePage_InstallShield
	, ePage_BatFiles
	IN:
	OUT:
*/
BOOL CProjectFileAssemblerDlg::OnSetActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_PfaDlg, TRUE);
	
	return CPropertyPage::OnSetActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	25/04/2007 13:08:15
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CProjectFileAssemblerDlg::OnKillActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_PfaDlg, FALSE);
	
	return CPropertyPage::OnKillActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	25/04/2007 13:17:59
	DESCRIP:	
	IN:
	OUT:
*/
//void CProjectFileAssemblerDlg::OnFileExit() 
//{
//	PostMessage(WM_CLOSE);
//}
