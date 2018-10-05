// PageBatFiles.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "PageBatFiles.h"

#include "PfaMainSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageBatFiles property page

IMPLEMENT_DYNCREATE(CPageBatFiles, CPropertyPage)

CPageBatFiles::CPageBatFiles() 
:	CPropertyPage			(CPageBatFiles::IDD)
	, m_bRunBatWaitRqrd		(false)
	, CBrushHolder			(CONS_COLOURS::crefPAGE_BACK)
{
	//{{AFX_DATA_INIT(CPageBatFiles)
	m_strCurBatFile = _T("");
	m_strCurRsltsFile = _T("");
	//}}AFX_DATA_INIT
}

CPageBatFiles::~CPageBatFiles()
{
}

void CPageBatFiles::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageBatFiles)
	DDX_Control(pDX, IDC_RED_BATCH_CONTENTS, m_redBatchContents);
	DDX_Control	(pDX,	IDC_LCTRL_BATFILES,			m_lctrlBatFiles);
	DDX_Control	(pDX,	IDC_RED_RECV,				m_redRecv);
	DDX_Text	(pDX,	IDC_ED_CUR_BATFILE,			m_strCurBatFile);
	DDX_Text	(pDX,	IDC_ED_CUR_RESULTSFILE,		m_strCurRsltsFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageBatFiles, CPropertyPage)
	//{{AFX_MSG_MAP(CPageBatFiles)
	ON_BN_CLICKED		(IDC_BN_RUN_BATFILE,		OnBnRunBatfile)
	ON_BN_CLICKED		(IDC_BN_OPEN_RSLTS,			OnBnOpenRslts)
	ON_BN_CLICKED		(IDC_BN_TEST_PIPE,			OnBnTestPipe)
	ON_WM_CTLCOLOR		()
	ON_NOTIFY			(NM_CLICK, IDC_LCTRL_BATFILES, OnClickLctrlBatfiles)
	//}}AFX_MSG_MAP

	ON_MESSAGE	(eWM_PIPE_DATA_RECEIVED,		OnWMPipeDataReceived)
	ON_MESSAGE	(eWM_PIPE_INSTANCE_STARTUP,		OnWMPipeInstanceStartup)
	ON_MESSAGE	(eWM_PIPE_INSTANCE_SHUTDOWN,	OnWMPipeInstanceShutdown)
	ON_MESSAGE	(eWM_REARRANGE_CONTROLS,		OnWMRearrangeControls)
	ON_MESSAGE	(eWM_SET_APPEARANCE,			OnWMSetAppearance)
	ON_MESSAGE	(eWM_SET_APPEARANCE,			OnWMSetAppearance)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageBatFiles message handlers

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 09:28:10
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageBatFiles::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CString strPipeName		(_T("ISBuildPipe"));
	CString strServerName	(_T("."));

	m_strFullPipeName.Format(_T("\\\\%s\\Pipe\\%s"), strServerName, strPipeName);

	CPipeServerThreadParams params(m_strFullPipeName, 0, GetSafeHwnd());

	StartPipeServerThread(params);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 11:06:33
	DESCRIP:	
	IN:
	OUT:
*/
LRESULT CPageBatFiles::OnWMSetAppearance(WPARAM wParam, LPARAM lParam)
{
	InitCharFormats();
	InitListBox();
	InitRichEdBox();

	GetDlgItem(IDC_ED_CUR_BATFILE)		->SetFont(GetMainSheet()->GetTheFont(eFont_EdBoxes));
	GetDlgItem(IDC_ED_CUR_RESULTSFILE)	->SetFont(GetMainSheet()->GetTheFont(eFont_EdBoxes));
	GetDlgItem(IDC_BN_TEST_PIPE)		->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));

	GetMainSheet()->SetDlgItemFont(this, IDC_RED_BATCH_CONTENTS,	eFont_EdBoxes);

	m_redBatchContents.SetBackgroundColor(FALSE, crefREADONLY_BACK);

	EnableCmdBtns();

	ClearRecvText();

	return TRUE;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 12:18:01
	DESCRIP:	afx_msg LRESULT OnWMRearrangeControls
	IN:
	OUT:
*/
/*afx_msg*/
LRESULT CPageBatFiles::OnWMRearrangeControls(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/03/2007 20:44:59
	DESCRIP:	
	
	UINT		cbSize;
	_WPAD		_wPad1;
	DWORD		dwMask;
	DWORD		dwEffects;
	LONG		yHeight;
	LONG		yOffset;
	COLORREF	crTextColor;
	BYTE		bCharSet;
	BYTE		bPitchAndFamily;
	char		szFaceName[LF_FACESIZE];
	_WPAD		_wPad2;

	WORD		wWeight;			//Font weight (LOGFONT value)		
	SHORT		sSpacing;			//Amount to space between letters	
	COLORREF	crBackColor;		//Background color					
	LCID		lcid;				//Locale ID						
	DWORD		dwReserved;			//Reserved. Must be 0				
	SHORT		sStyle;				//Style handle						
	WORD		wKerning;			//Twip size above which to kern char pair
	BYTE		bUnderlineType;		//Underline type					
	BYTE		bAnimation;			//Animated text like marching ants	
	BYTE		bRevAuthor;			//Revision author index			

	IN:
	OUT:
*/
void CPageBatFiles::InitCharFormats(void)
{
	eRCV_LINE_TYPE eType;

	for(int iLoop = 0 ; iLoop < eRlt__LAST ; iLoop++){
		
		eType = eRCV_LINE_TYPE(iLoop);

		::ZeroMemory(&(m_charformats[iLoop]), sizeof(CHARFORMAT2));

		m_charformats[iLoop].cbSize				= sizeof(CHARFORMAT2);				//UINT		

		_tcscpy(m_charformats[iLoop].szFaceName, szsFONT_FACE_RCVTXT[eType]);		//char	[LF_FACESIZE]	
		
		m_charformats[iLoop].dwMask				= GetCFMask		(eType);			//DWORD		
		m_charformats[iLoop].dwEffects			= GetCFEffects	(eType);			//DWORD		
		
		m_charformats[iLoop].yHeight			= isFONT_HEIGHTS_RCVTXT[eType];		//LONG		
		m_charformats[iLoop].wWeight			= isFONT_WEIGHTS_RCVTXT[eType];		//WORD		Font weight (LOGFONT value)		
		m_charformats[iLoop].crTextColor		= crefsLINE_FORE_RCVTXT[eType];		//COLORREF	
		m_charformats[iLoop].crBackColor		= crefsLINE_BACK_RCVTXT[eType];		//COLORREF	Background color					
		
		m_charformats[iLoop].yOffset			= 0;								//LONG		
		m_charformats[iLoop].bCharSet			= 0;								//BYTE		
		m_charformats[iLoop].bPitchAndFamily	= 0;								//BYTE		
		m_charformats[iLoop].sSpacing			= 0;								//SHORT		Amount to space between letters	
		m_charformats[iLoop].lcid				= 0;								//LCID		Locale ID						
		m_charformats[iLoop].dwReserved			= 0;								//DWORD		Reserved. Must be 0				
		m_charformats[iLoop].sStyle				= 0;								//SHORT		Style handle						
		m_charformats[iLoop].wKerning			= 0;								//WORD		Twip size above which to kern char pair
		m_charformats[iLoop].bUnderlineType		= 0;								//BYTE		Underline type					
		m_charformats[iLoop].bAnimation			= 0;								//BYTE		Animated text like marching ants	
		m_charformats[iLoop].bRevAuthor			= 0;								//BYTE		Revision author index			
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/03/2007 07:35:47
	DESCRIP:	
	IN:
	OUT:
*/
DWORD CPageBatFiles::GetCFMask(const eRCV_LINE_TYPE eType) const
{
	DWORD dwBaseMask = 0L;
	
	dwBaseMask |= CFM_BACKCOLOR;		//The crBackColor member is valid. 
	dwBaseMask |= CFM_COLOR;			//The crTextColor member is valid unless the CFE_AUTOCOLOR flag is set in the dwEffects member. 
	dwBaseMask |= CFM_FACE;				//The szFaceName member is valid. 
	dwBaseMask |= CFM_SIZE;				//The yHeight member is valid. 
	dwBaseMask |= CFM_WEIGHT;			//The wWeight member is valid. 

	//dwBaseMask |= CFM_ANIMATION;		//The bAnimation member is valid. 
	//dwBaseMask |= CFM_CHARSET;		//The bCharSet member is valid. 
	//dwBaseMask |= CFM_KERNING;		//The wKerning member is valid. 
	//dwBaseMask |= CFM_LCID;			//The lcid member is valid. 
	//dwBaseMask |= CFM_OFFSET;			//The yOffset member is valid. 
	//dwBaseMask |= CFM_REVAUTHOR;		//The bRevAuthor member is valid. 
	//dwBaseMask |= CFM_SPACING;		//The sSpacing member is valid. 
	//dwBaseMask |= CFM_STYLE;			//The sStyle member is valid. 
	//dwBaseMask |= CFM_UNDERLINETYPE;	//The bUnderlineType member is valid. 
	
	//Set the following values to indicate the valid attributes of the dwEffects member: Value Meaning 
	
	dwBaseMask |= CFM_STRIKEOUT;		//The CFE_STRIKEOUT value is valid. 
	dwBaseMask |= CFM_UNDERLINE;		//The CFE_UNDERLINE value is valid. 
	
	//dwBaseMask |= CFM_ALLCAPS;		//The CFE_ALLCAPS value is valid. 
	//dwBaseMask |= CFM_BOLD;			//The CFE_BOLD value is valid. 
	//dwBaseMask |= CFM_DISABLED;		//The CFE_DISABLED value is valid. 
	//dwBaseMask |= CFM_EMBOSS;			//The CFE_EMBOSS value is valid. 
	//dwBaseMask |= CFM_HIDDEN;			//The CFE_HIDDEN value is valid. 
	//dwBaseMask |= CFM_IMPRINT;		//The CFE_IMPRINT value is valid. 
	//dwBaseMask |= CFM_ITALIC;			//The CFE_ITALIC value is valid. 
	//dwBaseMask |= CFM_LINK;			//The CFE_LINK value is valid. 
	//dwBaseMask |= CFM_OUTLINE;		//The CFE_OUTLINE value is valid. 
	//dwBaseMask |= CFM_PROTECTED;		//The CFE_PROTECTED value is valid. 
	//dwBaseMask |= CFM_REVISED;		//The CFE_REVISION value is valid. 
	//dwBaseMask |= CFM_SHADOW;			//The CFE_SHADOW value is valid. 
	//dwBaseMask |= CFM_SMALLCAPS;		//The CFE_SMALLCAPS value is valid. 
	//dwBaseMask |= CFM_SUBSCRIPT;		//The CFE_SUBSCRIPT and CFE_SUPERSCRIPT values are valid. 
	//dwBaseMask |= CFM_SUPERSCRIPT;	//Same as CFM_SUBSCRIPT. 

	return dwBaseMask;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/03/2007 07:35:50
	DESCRIP:	
	IN:
	OUT:
*/
DWORD CPageBatFiles::GetCFEffects(const eRCV_LINE_TYPE eType) const
{
	DWORD dwBaseEffects = 0L;

	switch(eType){
		case eRlt_HighLight:
			//dwBaseEffects |= CFE_BOLD;			//Characters are bold. 
			break;

		case eRlt_Error:
			//dwBaseEffects |= CFE_BOLD;			//Characters are bold. 
			break;

		case eRlt_Normal:
			break;

		case eRlt_Warning:
			break;

		default:
			ATLASSERT(false);
	}

	//dwBaseEffects |= CFE_ALLCAPS;			//Characters are all capital letters. Does not affect the way the control displays the text.  
	//dwBaseEffects |= CFE_AUTOCOLOR;		//The text color is the return value ofGetSysColor (COLOR_WINDOWTEXT). If this flag is set, the crTextColor member is ignored. 
	//dwBaseEffects |= CFE_DELETED;			//Marks the characters as deleted. 
	//dwBaseEffects |= CFE_EMBOSS;			//Characters are embossed. Does not affect how the control displays the text.  
	//dwBaseEffects |= CFE_HIDDEN;			//Characters are not displayed. Does not affect how the control displays the text.  
	//dwBaseEffects |= CFE_IMPRINT			//Characters are displayed as imprinted characters. Does not affect how the control displays the text.  
	//dwBaseEffects |= CFE_ITALIC;			//Characters are italic. 
	//dwBaseEffects |= CFE_LINK;			//A rich edit control can send EN_LINK notification messages when it receives mouse messages while the mouse pointer is over text with the CFE_LINK effect. 
	//dwBaseEffects |= CFE_OUTLINE;			//Characters are displayed as outlined characters. Does not affect how the control displays the text.  
	//dwBaseEffects |= CFE_PROTECTED;		//Characters are protected; an attempt to modify them will cause an EN_PROTECTED notification message. 
	//dwBaseEffects |= CFE_REVISION;		//Marks the characters as revised. 
	//dwBaseEffects |= CFE_SHADOW;			//Characters are displayed as shadowed characters. Does not affect how the control displays the text.  
	//dwBaseEffects |= CFE_SMALLCAPS;		//Characters are in small capital letters. Does not affect how the control displays the text.  
	//dwBaseEffects |= CFE_STRIKEOUT;		//Characters are struck out. 
	//dwBaseEffects |= CFE_SUBSCRIPT;		//Characters are subscript. The CFE_SUPERSCRIPT and CFE_SUBSCRIPT values are mutually exclusive. For both values, the control automatically calculates an offset and a smaller font size. Alternatively, you can use the yHeight and yOffset members to explicitly specify font size and offset for subscript and superscript characters. 
	//dwBaseEffects |= CFE_SUPERSCRIPT;		//Characters are superscript.  
	//dwBaseEffects |= CFE_UNDERLINE;		//Characters are underlined. 

	return dwBaseEffects;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 09:28:07
	DESCRIP:	
	ePage_PfaDlg				= 0
	, ePage_PfaData
	, ePage_InstallShield
	, ePage_BatFiles
	IN:
	OUT:
*/
BOOL CPageBatFiles::OnSetActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_BatFiles, TRUE);
	
	return CPropertyPage::OnSetActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 09:28:04
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageBatFiles::OnKillActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_BatFiles, FALSE);
	
	return CPropertyPage::OnKillActive();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 09:44:42
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::InitListBox(void)
{
	DWORD dwExStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP;

	m_lctrlBatFiles.SetExtendedStyle	(dwExStyle);
	m_lctrlBatFiles.SetFont				(GetMainSheet()->GetTheFont(eFont_List));
	m_lctrlBatFiles.DeleteAllItems		();

	//int nCol, LPCTSTR lpszColumnHeading, int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1 
	CRect rcList;
	m_lctrlBatFiles.GetClientRect(rcList);
	int iScrollWid = ::GetSystemMetrics(SM_CXVSCROLL);

	m_lctrlBatFiles.InsertColumn(
							0L, _T("Batch Files"), LVCFMT_LEFT, rcList.Width() - iScrollWid
						);

	int iCur = 0;
	int iNew = 0;

	for(DWORD dwItem = 0L ; dwItem < eBF__LAST ; dwItem++){
		iCur = m_lctrlBatFiles.GetItemCount();
		iNew = m_lctrlBatFiles.InsertItem(iCur, szsBAT_FILE_TITLES[dwItem]);
		m_lctrlBatFiles.SetItemData(iNew, dwItem);
	}

	CHeaderCtrl * pHdr = m_lctrlBatFiles.GetHeaderCtrl();
	ATLASSERT(pHdr && ::IsWindow(pHdr->m_hWnd));

	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		pHdr->SetFont(GetMainSheet()->GetTheFont(eFont_ListHeader));
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 09:29:46
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::InitRichEdBox(void)
{
	//m_redRecv.SetFont(GetMainSheet()->GetFont(eFont_RecvText));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 09:59:04
	DESCRIP:	
	IN:
	OUT:
*/
//void CPageBatFiles::OnSelchangeListBatfiles() 
//{
//	int iCurSel = m_listBatFiles.GetCurSel();
//
//	m_strCurBatFile.Empty();
//	m_strCurRsltsFile.Empty();
//	m_strCurRunDir.Empty();
//
//	if(iCurSel >= 0){
//
//		DWORD dwWhich = m_listBatFiles.GetItemData(iCurSel);
//		ASSERT(dwWhich < eBF__LAST);
//
//		if(dwWhich < eBF__LAST){
//			m_strCurBatFile		= szsBAT_FILE_FILENAMES			[dwWhich];
//			m_strCurRunDir		= szsBAT_FILE_RUNDIRS			[dwWhich];
//			m_strCurRsltsFile	= szsRESULT_FILE_FILENAMES		[dwWhich];
//			m_bRunBatWaitRqrd	= bsWAIT_REQUIRED				[dwWhich];
//		}
//	}
//
//	UpdateData(FALSE);
//	EnableCmdBtns();
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/04/2007 13:34:04
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::OnClickLctrlBatfiles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	NMLISTVIEW * pNmlv = reinterpret_cast<NMLISTVIEW *>(pNMHDR);
	
	m_strCurBatFile.Empty();
	m_strCurRsltsFile.Empty();
	m_strCurRunDir.Empty();

	if(pNmlv->iItem >= 0L){

		DWORD dwWhich = m_lctrlBatFiles.GetItemData(pNmlv->iItem);
		ASSERT(dwWhich < eBF__LAST);

		if(dwWhich < eBF__LAST){
			m_strCurBatFile		= szsBAT_FILE_FILENAMES			[dwWhich];
			m_strCurRunDir		= szsBAT_FILE_RUNDIRS			[dwWhich];
			m_strCurRsltsFile	= szsRESULT_FILE_FILENAMES		[dwWhich];
			m_bRunBatWaitRqrd	= bsWAIT_REQUIRED				[dwWhich];
			
			LoadBatchContents(m_strCurBatFile);
		}
	}

	UpdateData(FALSE);
	EnableCmdBtns();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 12:11:02
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::EnableCmdBtns(void)
{
	GetDlgItem(IDC_BN_RUN_BATFILE)	->EnableWindow( ! m_strCurBatFile.IsEmpty());
	GetDlgItem(IDC_BN_OPEN_RSLTS)	->EnableWindow( ! m_strCurRsltsFile.IsEmpty());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 10:06:01
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::OnBnRunBatfile() 
{
	ClearRecvText();

	CBuildReporter::InitReporting(m_strCurRsltsFile);
	
	CBuildReporter::ReportLine(_T("--------------------------------------------------"));
	CBuildReporter::ReportLine(_T("Output from ") + m_strCurBatFile);

	if(m_bRunBatWaitRqrd)
		RunBatAndWait(INFINITE);

	else
		RunBatAndDontWait();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 08:17:21
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::RunBatAndWait(const DWORD dwTimeOutMSecs)
{
	CWaitCursor wait;

	if(!m_strCurBatFile.IsEmpty()){

		STARTUPINFO startupinfo;
		::ZeroMemory(&startupinfo, sizeof(STARTUPINFO));

		startupinfo.cb = sizeof(STARTUPINFO);

		PROCESS_INFORMATION processinfo;
		::ZeroMemory(&processinfo, sizeof(PROCESS_INFORMATION));

		//To run a batch file, you must start the command interpreter; 
		//set lpApplicationName to cmd.exe and 
		//set lpCommandLine to the name of the batch file.

		TCHAR szCmdLine[MAX_PATH + 10];
		_stprintf(szCmdLine, _T(" /C \"%s\""), m_strCurBatFile);

		TCHAR szRunDir[MAX_PATH + 10];
		_stprintf(szRunDir, _T("%s"), m_strCurRunDir);

		BOOL bOK = ::CreateProcess(
								_T("C:\\Windows\\System32\\cmd.exe")
								, szCmdLine		//cmd line
								, 0				//sec attrib
								, 0				//sec attrib
								, FALSE			//inherit handles
								, 0				//CREATE_NEW_CONSOLE	//creation flags
								, 0				//lpEnv
								, szRunDir		//lpCurDir
								, &startupinfo	//startup info
								, &processinfo	//process info
							);

		if(bOK){
			DWORD dwWait = ::WaitForSingleObject(processinfo.hProcess, dwTimeOutMSecs);

			if(processinfo.hProcess)
				::CloseHandle(processinfo.hProcess);

			if(processinfo.hThread)
				::CloseHandle(processinfo.hThread);
		}
		else{
			DWORD dwErr = ::GetLastError();
			CString strErr;
			strErr.Format(_T("CreateProcess error 0x%X (%i)\n"), dwErr, dwErr);
			::AfxMessageBox(strErr, MB_ICONERROR);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 08:17:24
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::RunBatAndDontWait(void)
{
	if(!m_strCurBatFile.IsEmpty()){

		STARTUPINFO startupinfo;
		::ZeroMemory(&startupinfo, sizeof(STARTUPINFO));

		startupinfo.cb = sizeof(STARTUPINFO);

		PROCESS_INFORMATION processinfo;
		::ZeroMemory(&processinfo, sizeof(PROCESS_INFORMATION));

		//To run a batch file, you must start the command interpreter; 
		//set lpApplicationName to cmd.exe and 
		//set lpCommandLine to the name of the batch file.

		TCHAR szCmdLine[MAX_PATH + 10];
		_stprintf(szCmdLine, _T(" /C \"%s\""), m_strCurBatFile);

		TCHAR szRunDir[MAX_PATH + 10];
		_stprintf(szRunDir, _T("%s"), m_strCurRunDir);

		BOOL bOK = ::CreateProcess(
								_T("C:\\Windows\\System32\\cmd.exe")
								, szCmdLine		//cmd line
								, 0				//process sec attrib
								, 0				//thread sec attrib
								, FALSE			//inherit handles
								, 0				//CREATE_NEW_CONSOLE	//creation flags
								, 0				//lpEnv
								, szRunDir		//lpCurDir
								, &startupinfo	//startup info
								, &processinfo	//process info
							);

		if(bOK){
			::CloseHandle(processinfo.hThread);
			::CloseHandle(processinfo.hProcess);
		}
		else{
			DWORD dwErr = ::GetLastError();
			CString strErr;
			strErr.Format(_T("CreateProcess error 0x%X (%i)\n"), dwErr, dwErr);
			::AfxMessageBox(strErr, MB_ICONERROR);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 10:06:08
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::OnBnOpenRslts() 
{
	CBuildReporter::ExitReporting();

	if(!m_strCurRsltsFile.IsEmpty()){

		HINSTANCE hinst = ::ShellExecute(
										0
										, _T("open")
										, m_strCurRsltsFile
										, 0		//params
										, 0		//directory
										, SW_MAXIMIZE	//show cmd
									);

		//Returns a value greater than 32 if successful
		//The only thing that can be done with the returned HINSTANCE is 
		//to cast it to an int and compare it with the value 32 or one of the error codes

		int iRet = int(hinst);

		if(iRet <= 32){
			::AfxMessageBox(_T("Error opening file:\n") + m_strCurRsltsFile);
		}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/04/2007 09:56:17
	DESCRIP:	
	IN:
	OUT:
*/
/*afx_msg*/
LRESULT CPageBatFiles::OnWMPipeInstanceStartup(WPARAM wParam, LPARAM lParam)
{
	ATLTRACE(_T("CPageBatFiles::OnWMPipeInstanceStartup\n"));
	return TRUE;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/04/2007 09:56:19
	DESCRIP:	
	IN:
	OUT:
*/
/*afx_msg*/
LRESULT CPageBatFiles::OnWMPipeInstanceShutdown(WPARAM wParam, LPARAM lParam)
{
	ATLTRACE(_T("CPageBatFiles::OnWMPipeInstanceShutdown\n"));
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	15/03/2007 18:07:10
	DESCRIP:	

		TCHAR * pszRequest = new TCHAR[dwNumChars + 5]

	IN:
	OUT:
*/
/*afx_msg*/
LRESULT CPageBatFiles::OnWMPipeDataReceived(WPARAM wParam, LPARAM lParam)
{
	LRESULT lrRet = 0;

	TCHAR * pszRequest = reinterpret_cast<TCHAR *>(lParam);
	ATLASSERT(pszRequest);

	if(pszRequest){

		CString strRqst = pszRequest;

		OnWMPipeDataReceived(strRqst);
		CBuildReporter::ReportLine(strRqst);

		delete [] pszRequest;
		pszRequest = 0;
	}


	return lrRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	15/03/2007 18:30:19
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::OnWMPipeDataReceived(const CString & strMsg)
{
	//static CString so it will save the remainder of an incomplete
	//line until the next call...
	/*
		we might receive:

			"text text text\n"
			"text te"				<-- we need to remember this for the next call

		followed by:

				   "xt text\n"		<-- this is the new line fragment
			"text text text\n"
	*/
	static CString strLine;

	TCHAR chProbe = 0;

	long iMaxChar = strMsg.GetLength();

	for(long iCharPos = 0 ; iCharPos < iMaxChar ; iCharPos++){
		chProbe = strMsg.GetAt(iCharPos);
		strLine += chProbe;

		if(0x0A == chProbe){
			AddRcvTextLine(strLine);
			strLine.Empty();
		}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/03/2007 08:43:21
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::AddRcvTextLine(const CString & strLine)
{
	eRCV_LINE_TYPE eType = GetLineType(strLine);

	long iChars = m_redRecv.GetTextLength();

	m_redRecv.SetSel(iChars, iChars);

	//m_redRecv.SetSelectionCharFormat(m_charformats[eType]);
	m_redRecv.SendMessage(
						EM_SETCHARFORMAT
						, SCF_SELECTION
						, reinterpret_cast<LPARAM>(&(m_charformats[eType]))
					);

	m_redRecv.ReplaceSel(strLine);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/03/2007 08:35:29
	DESCRIP:	
	
		"0 error(s), 0 warning(s)"
		int iFind = strLine.Find(_T("warning"));

		if(iFind < 0)
			iFind = strLine.Find(_T("error"));

		if(iFind >= 0){

			//default to an 'error' unless we find the specific phrase "0 error(s), 0 warning(s)"
			//NOTE: This means that we are treating 'warnings' as 'errors'!
			eType = eRlt_Error;
			iFind = strLine.Find(_T("0 error(s), 0 warning(s)"));
		
			//this is a success line at the end of the InstallShield build process
			if(iFind >= 0)
				eType = eRlt_HighLight;
			
			//handle a warning line
			else{
				iFind = strLine.Find(_T("0 error(s)"));
			}
		}

		else{
			iFind = strLine.Find(_T("IsCmdBld.exe"));

			//this is a 'title' line starting a new build of a new InstallShield project
			if(iFind >= 0){
				eType = eRlt_HighLight;
			}
		}
	IN:
	OUT:
*/
eRCV_LINE_TYPE CPageBatFiles::GetLineType(const CString & strLine) const
{
	eRCV_LINE_TYPE eType = eRlt_Normal;

	bool bZeroErrCount	= IsInString(strLine, _T("0 error(s)"));
	bool bZeroWarnCount	= IsInString(strLine, _T("0 warning(s)"));
	bool bHasError		= IsInString(strLine, _T("error"));
	bool bHasWarning	= IsInString(strLine, _T("warning"));
	bool bHasCmdLine	= IsInString(strLine, _T("IsCmdBld.exe"));

	bool bNoErrNoWarns	= bZeroErrCount && bZeroWarnCount;

	//no errors, no warnings is what we want at the end of the build
	if(bNoErrNoWarns){
		eType = eRlt_HighLight;
	}
	
	//not 'no error no warn', but still has an 'error'
	else if(bHasError && !bZeroErrCount){
		eType = eRlt_Error;
	}
	
	//not 'no error no warn', not an error, but still has a 'warning'
	else if(bHasWarning && !bZeroWarnCount){
		eType = eRlt_Warning;
	}

	//start of a build
	else if(bHasCmdLine){
		eType = eRlt_HighLight;
	}

	return eType;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10/04/2007 15:01:31
	DESCRIP:	
	IN:
	OUT:
*/
bool CPageBatFiles::IsInString(const CString & strSearchBody, const CString & strPhrase) const
{
	int iFind = strSearchBody.Find(strPhrase);

	return (iFind >= 0) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 09:24:04
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageBatFiles::DestroyWindow() 
{
	CPipeServerThread::StopPipeServerThread();
		
	return CPropertyPage::DestroyWindow();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 10:50:25
	DESCRIP:	
	IN:
	OUT:
*/
CPfaMainSheet * CPageBatFiles::GetMainSheet(void)
{
	CPfaMainSheet * pSheet = reinterpret_cast<CPfaMainSheet *>(GetParent());
	ATLASSERT(pSheet && ::IsWindow(pSheet->m_hWnd));
	return pSheet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 22:16:00
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::OnBnTestPipe() 
{
	ClearRecvText();

	STARTUPINFO startupinfo;
	::ZeroMemory(&startupinfo, sizeof(STARTUPINFO));

	startupinfo.cb = sizeof(STARTUPINFO);

	PROCESS_INFORMATION processinfo;
	::ZeroMemory(&processinfo, sizeof(PROCESS_INFORMATION));

	//To run a batch file, you must start the command interpreter; 
	//set lpApplicationName to cmd.exe and 
	//set lpCommandLine to the name of the batch file.

	TCHAR szCmdLine[MAX_PATH + 10];
	_stprintf(szCmdLine, _T(" /C dir C:\\ > %s"), m_strFullPipeName);

	TCHAR szRunDir[MAX_PATH + 10];
	_stprintf(szRunDir, _T("C:\\"));

	BOOL bOK = ::CreateProcess(
							_T("C:\\Windows\\System32\\cmd.exe")
							, szCmdLine		//cmd line
							, 0				//sec attrib
							, 0				//sec attrib
							, FALSE			//inherit handles
							, 0				//CREATE_NEW_CONSOLE	//creation flags
							, 0				//lpEnv
							, szRunDir		//lpCurDir
							, &startupinfo	//startup info
							, &processinfo	//process info
						);

	if(bOK){
		::CloseHandle(processinfo.hThread);
		::CloseHandle(processinfo.hProcess);
	}
	else{
		DWORD dwErr = ::GetLastError();
		CString strErr;
		strErr.Format(_T("CreateProcess error 0x%X (%i)\n"), dwErr, dwErr);
		::AfxMessageBox(strErr, MB_ICONERROR);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 22:23:04
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::ClearRecvText(void)
{
	//clear...
	m_redRecv.SetWindowText(_T(""));

	CString strLine(m_strFullPipeName + _T("\n"));

	eRCV_LINE_TYPE eType = eRlt_HighLight;

	long iChars = m_redRecv.GetTextLength();

	m_redRecv.SetSel(iChars, iChars);

	m_redRecv.SendMessage(
						EM_SETCHARFORMAT
						, SCF_SELECTION
						, reinterpret_cast<LPARAM>(&(m_charformats[eType]))
					);

	m_redRecv.ReplaceSel(strLine);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 07:59:26
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::OnOK() 
{
	ATLTRACE(_T("CPageBatFiles::OnOK\n"));	
	
	CPropertyPage::OnOK();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 07:59:25
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::OnCancel() 
{
	ATLTRACE(_T("CPageBatFiles::OnCancel\n"));	
	
	CPropertyPage::OnCancel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/04/2007 12:25:46
	DESCRIP:	
	IN:
	OUT:
*/
HBRUSH CPageBatFiles::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return CBrushHolder::GetBrush(hbr);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11/05/2007 13:11:27
	DESCRIP:	
	IN:
	OUT:
*/
void CPageBatFiles::LoadBatchContents(const CString & strBatFile)
{
	CString strText(_T(""));
	CString strLine;

	CStdioFile batfil;
	DWORD dwFlags = 
					CFile::modeRead
					| CFile::shareDenyNone   
					| CFile::typeText
				;

	BOOL bOpened = batfil.Open(strBatFile, dwFlags);

	if(bOpened){

		while(batfil.ReadString(strLine)){
			strText += strLine;
			strText += _T("\n");
		}

		batfil.Close();
	}
	else{
		strText = _T("Failed to open file ") + strBatFile;
	}

	m_redBatchContents.SetWindowText(strText);
}
