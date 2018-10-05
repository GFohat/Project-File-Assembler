// PagePfaData.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "PagePfaData.h"

#include "PfaMainSheet.h"

#include ".\paramsshowfilepcposition.h"
using namespace PARAMS;

#include "ConstSQL.h"
using namespace CONS_SQL;

#include "ConstLists.h"
using namespace CONS_LISTS;

#include "SheetStepProperties.h"

#include "DlgInputBox.h"
#include "DlgAddFiles.h"
#include "DlgOpenAProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//this is shown in the list to indicate the default directory

//eg if default dir is 
	//'C:\Source'

//and path is 
	//'C:\Source\Foo'

//then the display in the list will be
	//'szDFLTDIRINDIC\Foo' (default '\Foo' if szDFLTDIRINDIC is empty)

const TCHAR szDFLTDIRINDIC[] = _T("");

/////////////////////////////////////////////////////////////////////////////
// CPagePfaData property page

IMPLEMENT_DYNCREATE(CPagePfaData, CPropertyPage)


CPagePfaData::CPagePfaData() 
:	CPropertyPage				(CPagePfaData::IDD)
	, m_iPrgrsMax				(0L)
	, m_dwCurProjID				(0L)
	, CBrushHolder				(CONS_COLOURS::crefPAGE_BACK)
	, m_dwCountFail_Items		(0L)
	, m_dwCountFail_SubItems	(0L)
	, m_dwCountOK_Items			(0L)
	, m_dwCountOK_SubItems		(0L)
{
	//{{AFX_DATA_INIT(CPagePfaData)
	m_bLockEdits = TRUE;
	m_dwRowCount = 0;
	//}}AFX_DATA_INIT
}

CPagePfaData::~CPagePfaData()
{
}

void CPagePfaData::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPagePfaData)
	DDX_Control	(pDX,	IDC_PRGRS_FILE,				m_prgrsFile);
	DDX_Control	(pDX,	IDC_PRGRS_BATCH,			m_prgrsBatch);
	DDX_Control	(pDX,	IDC_LST_PROJECT_ITEMS,		m_listProjectItems);
	DDX_Check	(pDX,	IDC_CHK_LOCK,				m_bLockEdits);
	DDX_Text	(pDX,	IDC_ED_ROW_COUNT,			m_dwRowCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPagePfaData, CPropertyPage)
	//{{AFX_MSG_MAP(CPagePfaData)
	ON_NOTIFY			(LVN_DELETEITEM,	IDC_LST_PROJECT_ITEMS,	OnDeleteitemLstProjectItems)
	ON_NOTIFY			(NM_CLICK,			IDC_LST_PROJECT_ITEMS,	OnClickLstProjectItems)
	ON_NOTIFY			(NM_DBLCLK,			IDC_LST_PROJECT_ITEMS,	OnDblclkLstProjectItems)
	ON_NOTIFY			(LVN_KEYDOWN,		IDC_LST_PROJECT_ITEMS,	OnKeydownLstProjectItems)
	ON_NOTIFY			(NM_RCLICK,			IDC_LST_PROJECT_ITEMS,	OnRclickLstProjectItems)
	ON_NOTIFY			(LVN_COLUMNCLICK,	IDC_LST_PROJECT_ITEMS,	OnColumnclickLstProjectItems)
	ON_NOTIFY			(NM_CUSTOMDRAW,		IDC_LST_PROJECT_ITEMS,	OnNMProjListCustomDraw)
	ON_COMMAND			(ID_CTXT_ADDASTEP,				OnCtxtAddastep)
	ON_COMMAND			(ID_CTXT_DELETEASTEP,			OnCtxtDeleteastep)
	ON_COMMAND			(ID_CTXT_EDITASTEP,				OnCtxtEditastep)
	ON_COMMAND			(ID_CTXT_REORDINATE,			OnCtxtReordinate)
	ON_BN_CLICKED		(IDC_BN_BROWSE_DFLT_DEST_DIR,	OnBnBrowseDfltDestDir)
	ON_BN_CLICKED		(IDC_BN_BROWSE_DFLT_SRC_DIR,	OnBnBrowseDfltSrcDir)
	ON_COMMAND			(ID_CTXT_COPYASTEP,				OnCtxtCopyastep)
	ON_COMMAND			(ID_CTXT_EXPLORESOURCE,			OnCtxtExploresource)
	ON_COMMAND			(ID_CTXT_EXPLOREDESTINATION,	OnCtxtExploredestination)
	ON_COMMAND			(ID_CTXT_ADDSINGLEFILES,		OnCtxtAddsinglefiles)
	ON_BN_CLICKED		(IDC_BN_SEL_ALL,				OnBnSelAll)
	ON_BN_CLICKED		(IDC_BN_SEL_NONE,				OnBnSelNone)
	ON_BN_CLICKED		(IDC_BN_SEL_INVERT,				OnBnSelInvert)
	ON_BN_CLICKED		(IDC_CHK_LOCK,					OnChkLock)
	ON_BN_CLICKED		(IDC_BN_SEL_HIGHLIGHTED,		OnBnSelHighlighted)
	ON_WM_CTLCOLOR		()
	ON_WM_MEASUREITEM	()
	ON_WM_DRAWITEM		()
	ON_COMMAND			(ID_ACTION_COPYPROJECTFILES,	OnActionCopyprojectfiles)
	ON_COMMAND			(ID_ACTION_VALIDATEPROJECT,		OnActionValidateproject)
	ON_BN_CLICKED			(IDC_BN_SELECT,					OnBnSelect)
	ON_BN_CLICKED			(IDC_BN_FILE_LIST,				OnBnFileList)
	ON_COMMAND				(ID_PROJECT_NEW,				OnProjectNew)
	ON_COMMAND				(ID_PROJECT_OPEN,				OnProjectOpen)
	ON_COMMAND				(ID_PROJECT_SAVEAS,				OnProjectSaveas)
	ON_COMMAND				(ID_PROJECT_DELETE,				OnProjectDelete)
	ON_UPDATE_COMMAND_UI	(ID_ACTION_COPYPROJECTFILES,	OnUpdateActionCopyprojectfiles)
	ON_UPDATE_COMMAND_UI	(ID_ACTION_VALIDATEPROJECT,		OnUpdateActionValidateproject)
	ON_UPDATE_COMMAND_UI	(ID_PROJECT_DELETE,				OnUpdateProjectDelete)
	ON_UPDATE_COMMAND_UI	(ID_PROJECT_NEW,				OnUpdateProjectNew)
	ON_UPDATE_COMMAND_UI	(ID_PROJECT_OPEN,				OnUpdateProjectOpen)
	ON_UPDATE_COMMAND_UI	(ID_PROJECT_SAVEAS,				OnUpdateProjectSaveas)
	ON_BN_CLICKED			(IDC_BN_EXPORT_CSV_TICKED,		OnBnExportCsvTicked)
	ON_BN_CLICKED			(IDC_BN_REFRESH,				OnBnRefresh)
	ON_COMMAND(ID_PROJECT_ARCHIVE_EXPORT, OnProjectArchiveExport)
	ON_COMMAND(ID_PROJECT_ARCHIVE_IMPORT, OnProjectArchiveImport)
	//}}AFX_MSG_MAP

	ON_CBN_CLOSEUP		(dwIDC_CMBO_STEPTYPE,		OnCloseupCmboStepType)
	ON_CBN_DROPDOWN		(dwIDC_CMBO_STEPTYPE,		OnDropDownCmboStepType)
	ON_CBN_SELCHANGE	(dwIDC_CMBO_STEPTYPE,		OnSelChangeCmboStepType)
	ON_CBN_KILLFOCUS	(dwIDC_CMBO_STEPTYPE,		OnKillFocusCmboStepType)

	ON_EN_KILLFOCUS		(dwIDC_RED_EDIT,			OnKillFocusRedEdit)
	ON_EN_CHANGE		(dwIDC_RED_EDIT,			OnChangeRedEdit)
	ON_NOTIFY			(EN_MSGFILTER,		dwIDC_RED_EDIT,		OnMsgfilterRedEdit)

	ON_MESSAGE			(eWM_SINGLE_OP_STATUS,				OnWMSingleOpStatus)
	ON_MESSAGE			(eWM_SINGLE_OP_RESULT,				OnWMSingleOpResult)
	ON_MESSAGE			(eWM_SINGLE_OP_VALIDATION,			OnWMSingleOpValidation)
	ON_MESSAGE			(eWM_SINGLEFILE_PC_POS,				OnWMSingleFilePCPos)
	ON_MESSAGE			(eWM_EVENT_REPORT,					OnWMEventReport)
	ON_MESSAGE			(eWM_SKIPPED_SINGLE_OP,				OnWMSkippedSingleOp)
	ON_MESSAGE			(eWM_SKIPPED_SINGLE_VALIDATION,		OnWMSkippedSingleValidation)
	ON_MESSAGE			(eWM_REFRESH_LIST,					OnWMRefreshList)
	ON_MESSAGE			(eWM_SET_APPEARANCE,				OnWMSetAppearance)

	ON_NOTIFY_EX		(TTN_NEEDTEXT,		0,				OnTTNeedText)


	//ON_COMMAND			(CONS_MENUS::PROJECT_MENU::eMnuID_PROJECT_DELETE,			OnProjectDelete)
	//ON_COMMAND			(CONS_MENUS::PROJECT_MENU::eMnuID_PROJECT_NEW,				OnProjectNew)
	//ON_COMMAND			(CONS_MENUS::PROJECT_MENU::eMnuID_PROJECT_OPEN,				OnProjectOpen)
	//ON_COMMAND			(CONS_MENUS::PROJECT_MENU::eMnuID_PROJECT_SAVE_AS,			OnProjectSaveas)

	//ON_COMMAND			(CONS_MENUS::ACTION_MENU::eMnuID_ACTION_COPY_FILES,			OnActionCopyprojectfiles)
	//ON_COMMAND			(CONS_MENUS::ACTION_MENU::eMnuID_ACTION_VALIDATE_FILES,		OnActionValidateproject)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPagePfaData message handlers

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/03/2007 14:02:31
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPagePfaData::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	//CControlPopulator::ConnectDb();
	EnableToolTips(TRUE);

	InitStepTypeCombo();
	InitEditBox();
	InitBrowseBn();

	CFileCopyThreadParams params(m_hWnd);
	CFileCopyThread::StartFileCopyThread(params);
	
	RefreshLockState();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/05/2007 10:31:23
	DESCRIP:	
		hdr			NMHDR structure that contains additional information about the 
					notification message. 

		lpszText	Address of a null-terminated string that will be displayed as the 
					tooltip text. If hinst specifies an instance handle, this member 
					must be the identifier of a string resource. 

		szText		Buffer that receives the tooltip text. An application can copy the 
					text to this buffer instead of specifying a string address or string 
					resource. 

		hinst		Handle to the instance that contains a string resource to be used as 
					the tooltip text. If lpszText is the address of the tooltip text string, 
					this member must be NULL. 

		uFlags		Flags that indicates how to interpret the idFrom member of the included 
					NMHDR structure. If this member is the TTF_IDISHWND flag, idFrom is the 
					tool's handle. Otherwise, it is the tool's identifier. 

					If you add the TTF_RTLREADING flag to this member while processing the 
					notification, then text on Hebrew or Arabic systems is displayed using 
					right-to-left reading order. 

					Version 4.70. If you add the TTF_DI_SETITEM flag to this member while 
					processing the notification, the tooltip control will retain the supplied 
					information and not request it again. 

		lParam		Version 4.70. Application-defined data associated with the tool. 	
	
	IN:
		id			Identifier of the control that sent the notification. Not used. 
					The control id is taken from the NMHDR structure.

		pTTTStruct	A pointer to the NMTTDISPINFO structure. This structure is also 
					discussed further in The TOOLTIPTEXT Structure.

		pResult		A pointer to result code you can set before you return. TTN_NEEDTEXT 
					handlers can ignore the pResult parameter. 
	OUT:
*/
/*afx_msg*/
BOOL CPagePfaData::OnTTNeedText(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
	const DWORD dwMAXTEXT = 79L;

	NMTTDISPINFO * pDispInfo = reinterpret_cast<NMTTDISPINFO *>(pNMHDR);

	if(pDispInfo){

		CString strText;

		DWORD dwCtlID = pNMHDR->idFrom;

		if(TTF_IDISHWND & pDispInfo->uFlags){
			
			CWnd * pwnd = CWnd::FromHandle(reinterpret_cast<HWND>(pNMHDR->idFrom));
			
			if(pwnd && ::IsWindow(pwnd->m_hWnd)){
				dwCtlID = pwnd->GetDlgCtrlID();
			}
		}

		switch(dwCtlID){
			case IDC_BN_REFRESH:				strText = _T("Refresh the list");				break;
												
			case IDC_BN_SEL_ALL:				strText = _T("Set ticks: All Items");			break;
			case IDC_BN_SEL_NONE:				strText = _T("Set ticks: No Items");			break;
			case IDC_BN_SEL_INVERT:				strText = _T("Set ticks: Invert Items");		break;
			case IDC_BN_SEL_HIGHLIGHTED:		strText = _T("Set ticks: Highlighted Items");	break;
			case IDC_BN_EXPORT_CSV:				strText = _T("Export list contents");			break;
			case IDC_BN_EXPORT_CSV_TICKED:		strText = _T("Export ticked list contents");	break;
												
			case IDC_CHK_LOCK:					strText = _T("Enable direct editing");			break;
												
			case IDC_ED_CUR_PROJECT:			strText = _T("Project Name");					break;
			case IDC_ED_ROW_COUNT:				strText = _T("Item Count");						break;
												
			case IDC_ED_DFLT_SRC_DIR:			strText = _T("Source Directory");				break;
			case IDC_ED_DFLT_DEST_DIR:			strText = _T("Destination Directory");			break;
			case IDC_BN_BROWSE_DFLT_SRC_DIR:	strText = _T("Browse Source Directory");		break;
			case IDC_BN_BROWSE_DFLT_DEST_DIR:	strText = _T("Browse Destination Directory");	break;
			case IDC_LST_PROJECT_ITEMS:			strText = _T("Project Steps");					break;
			case IDC_PRGRS_FILE:				strText = _T("Single File Progress");			break;
			case IDC_PRGRS_BATCH:				strText = _T("Overall Progress");				break;

			default:
				strText.Format(_T("Ctl ID 0x%X"), dwCtlID);
		}

		_tcscpy(pDispInfo->szText, strText.Left(dwMAXTEXT));
	}

	return TRUE;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	05/05/2007 21:03:23
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::RefreshLockState(void)
{
	if(m_bLockEdits)
		GetDlgItem(IDC_CHK_LOCK)->SetWindowText(_T("Edits Locked"));
	else
		GetDlgItem(IDC_CHK_LOCK)->SetWindowText(_T("Edits Enabled"));

}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 11:32:36
	DESCRIP:	
	m_cmboStepType.ResetContent();

	GetMainSheet()->PopulateComboBox(
									szSQL_STEPTYPE_COMBO
									, szFIELD_STEPTYPE_STRINGS
									, szFIELD_STEPTYPE_IDS
									, m_cmboStepType
								);

	IN:
	OUT:
*/
void CPagePfaData::InitStepTypeCombo(void)
{
	DWORD dwStyle = 0
				| WS_CHILD 
				| CBS_DROPDOWNLIST
			;

	CRect rc(0, 0, 250, 250);

	m_cmboStepType.Create		(dwStyle, rc, this, dwIDC_CMBO_STEPTYPE);

	//populate combo box
	GetMainSheet()->PopulateComboBox(
									szSQL_STEPTYPE_COMBO
									, szFIELD_STEPTYPE_STRINGS
									, szFIELD_STEPTYPE_IDS
									, m_cmboStepType
								);

	
	//use the same font as the list in which it will be shown...
	m_cmboStepType.SetFont		(GetMainSheet()->GetTheFont(eFont_List));
	m_cmboStepType.HideWindow	();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 11:42:59
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::InitEditBox(void)
{
	DWORD dwStyle = 0L
					| WS_CHILD
					| ES_NOHIDESEL
					| ES_CENTER
					| ES_AUTOHSCROLL
				;

	CRect rc(10, 10, 50, 50);

	m_redEditBox.Create		(dwStyle, rc, this, dwIDC_RED_EDIT);
	
	//use the same font as the list in which it will be shown...
	m_redEditBox.SetFont	(GetMainSheet()->GetTheFont(eFont_List));
	m_redEditBox.HideWindow	();

	m_redEditBox.SetBackgroundColor(FALSE, crefACTIVE_BACK);

	DWORD dwEvMask = m_redEditBox.GetEventMask();

	dwEvMask |= ENM_CHANGE;
	dwEvMask |= ENM_KEYEVENTS;
	dwEvMask |= ENM_MOUSEEVENTS;
	dwEvMask |= ENM_SCROLLEVENTS;

	m_redEditBox.SetEventMask(dwEvMask);

	////PARAFORMAT2 pf2;
	//::ZeroMemory(&pf2, sizeof(PARAFORMAT2));

	//pf2.cbSize		= sizeof(PARAFORMAT2);
	//pf2.dwMask		= PFM_ALIGNMENT;
	//pf2.wAlignment	= PFA_CENTER;

	////EM_SETPARAFORMAT 
	////wParam = 0;  // not used; must be zero 
	////lParam = (LPARAM) (PARAFORMAT FAR *) lpFmt; 
	//m_redEditBox.SendMessage(EM_SETPARAFORMAT, 0, reinterpret_cast<LPARAM>(&pf2));
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 11:48:51
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::InitBrowseBn(void)
{
	DWORD dwStyle = WS_CHILD;
	CRect rc(10, 10, 50, 50);

	m_bnBrowse.Create(_T("..."), dwStyle, rc, this, dwIDC_BN_BROWSE);
	
	//use the same font as the list in which it will be shown...
	m_bnBrowse.SetFont		(GetMainSheet()->GetTheFont(eFont_List));
	m_bnBrowse.ShowWindow	(SW_HIDE);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/03/2007 07:49:18
	DESCRIP:	
	IN:
	OUT:
*/
LPARAM CPagePfaData::OnWMSetAppearance(WPARAM wParam, LPARAM lParam)
{
	InitList();

	//buttons
	::AfxGetApp()->m_pMainWnd->SendMessage(eWM_GET_FONT, eFont_Buttons, LPARAM(GetDlgItem(IDC_BN_REFRESH)));
	
	GetMainSheet()->SetDlgItemFont(this, IDC_BN_SEL_ALL,			eFont_Buttons);
	GetMainSheet()->SetDlgItemFont(this, IDC_BN_SEL_NONE,			eFont_Buttons);
	GetMainSheet()->SetDlgItemFont(this, IDC_BN_SEL_INVERT,			eFont_Buttons);
	GetMainSheet()->SetDlgItemFont(this, IDC_BN_SEL_HIGHLIGHTED,	eFont_Buttons);
	GetMainSheet()->SetDlgItemFont(this, IDC_BN_EXPORT_CSV,			eFont_Buttons);
	GetMainSheet()->SetDlgItemFont(this, IDC_BN_EXPORT_CSV_TICKED,	eFont_Buttons);
	
	GetMainSheet()->SetDlgItemFont(this, IDC_CHK_LOCK,					eFont_Buttons);
	GetMainSheet()->SetDlgItemFont(this, IDC_BN_BROWSE_DFLT_SRC_DIR,	eFont_Buttons);
	GetMainSheet()->SetDlgItemFont(this, IDC_BN_BROWSE_DFLT_DEST_DIR,	eFont_Buttons);

	//title text boxes
	GetMainSheet()->SetDlgItemFont(this, IDC_ED_CUR_PROJECT,		eFont_EdBoxes_Title);
	GetMainSheet()->SetDlgItemFont(this, IDC_ED_ROW_COUNT,			eFont_EdBoxes_Title);

	//text boxes
	GetMainSheet()->SetDlgItemFont(this, IDC_ED_DFLT_SRC_DIR,		eFont_EdBoxes);
	GetMainSheet()->SetDlgItemFont(this, IDC_ED_DFLT_DEST_DIR,		eFont_EdBoxes);
	GetMainSheet()->SetDlgItemFont(this, IDC_STATIC_DFLT_SRC,		eFont_EdBoxes);
	GetMainSheet()->SetDlgItemFont(this, IDC_STATIC_DFLT_DEST,		eFont_EdBoxes);

	return TRUE;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 12:18:01
	DESCRIP:	
	IN:
	OUT:
*/
LRESULT CPagePfaData::OnWMRearrangeControls(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/03/2007 07:56:36
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::InitList(void)
{
	DWORD dwExStyle = 0
				| LVS_EX_GRIDLINES 
				| LVS_EX_FULLROWSELECT 
				| LVS_EX_INFOTIP 
				| LVS_EX_CHECKBOXES
				| LVS_EX_TRACKSELECT
			;

	m_listProjectItems.SetExtendedStyle(dwExStyle);
	m_listProjectItems.SetFont(GetMainSheet()->GetTheFont(eFont_List));

	for(DWORD dwLoop = 0L ; dwLoop < ePDataCol__LAST ; dwLoop++){
		m_listProjectItems.InsertColumn(
									dwLoop
									, szsCOL_NAMES_PFA_DATA		[dwLoop]
									, isCOL_FMTS_PFA_DATA		[dwLoop]
								);
	}

	CHeaderCtrl * pHdr = m_listProjectItems.GetHeaderCtrl();
	ATLASSERT(pHdr && ::IsWindow(pHdr->m_hWnd));

	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		pHdr->SetFont(GetMainSheet()->GetTheFont(eFont_ListHeader));
	}

	m_listProjectItems.SetHoverTime((DWORD(-2L) / 2L));


	SetListColWidths();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/03/2007 07:57:28
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::SetListColWidths(void)
{
	CHeaderCtrl * pHdr = m_listProjectItems.GetHeaderCtrl();

	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		for(DWORD dwLoop = 0L ; dwLoop < DWORD(pHdr->GetItemCount()) ; dwLoop++){
			m_listProjectItems.SetColumnWidth(dwLoop, LVSCW_AUTOSIZE_USEHEADER);
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/03/2007 14:02:28
	DESCRIP:	
	ePage_PfaDlg				= 0
	, ePage_PfaData
	, ePage_InstallShield
	, ePage_BatFiles
	IN:
	OUT:
*/
BOOL CPagePfaData::OnSetActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_PfaData, TRUE);
	return CPropertyPage::OnSetActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/03/2007 14:02:26
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPagePfaData::OnKillActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_PfaData, FALSE);
	return CPropertyPage::OnKillActive();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 10:50:25
	DESCRIP:	
	IN:
	OUT:
*/
CPfaMainSheet * CPagePfaData::GetMainSheet(void)
{
	CPfaMainSheet * pSheet = reinterpret_cast<CPfaMainSheet *>(GetParent());
	ATLASSERT(pSheet && ::IsWindow(pSheet->m_hWnd));
	return pSheet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/03/2007 18:43:20
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPagePfaData::DestroyWindow() 
{
	CFileCopyThread::StopFileCopyThread();

	//CControlPopulator::DisconnectDb();
	return CPropertyPage::DestroyWindow();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/03/2007 11:50:42
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPagePfaData::PopulateList(const CString & strSQL)
{		
	CWaitCursor wait;
	CDebugTimer debugtimer(::GetTickCount(), _T("CPagePfaData::PopulateList"));

	m_listProjectItems.DeleteAllItems();

	HRESULT hr = S_OK;
		
	CComPtr<ADODB::_Recordset> spRst = 0;

	//m_listProjectItems.LockWindowUpdate();
	m_listProjectItems.SendMessage(WM_SETREDRAW, FALSE, 0);
	m_dwRowCount = 0L;

	try{
		THR( hr = GetMainSheet()->OpenRecordSet(strSQL, true, spRst) );

		while(!spRst->BOF && !spRst->EndOfFile){

			THR( hr = AddListRow(spRst) );

			THR( hr = spRst->MoveNext() );
			m_dwRowCount++;
		}

		SetListColWidths();

		GetMainSheet()->LogDataEvent(
								eEvt_Debugging
								, _T("CPagePfaData::PopulateList")
								, strSQL
								, _T("%i msecs")
								, debugtimer.GetCurLapse()
							);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		GetMainSheet()->HandleHR(e, _T("CPagePfaData::PopulateList"), _T(""), strSQL, true);
	}

	//m_listProjectItems.UnlockWindowUpdate();
	m_listProjectItems.SendMessage(WM_SETREDRAW, TRUE, 0);
	//m_listProjectItems.Invalidate();

	UpdateData(FALSE);

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/03/2007 11:53:57
	DESCRIP:			
	IN:
	OUT:
*/
HRESULT CPagePfaData::AddListRow(const CComPtr<ADODB::_Recordset> & spRst)
{
	HRESULT hr = S_OK;

	CComPtr<ADODB::Fields>	spFieldsColl = 0;

	try{
		spFieldsColl = spRst->Fields;

		CPfaDataListItem * pNew = new CPfaDataListItem(spFieldsColl);

		int iCur = m_listProjectItems.GetItemCount();
		int iNew = m_listProjectItems.InsertItem(iCur, _T(""));

		CString strSrcDir	= GetShortDirStr(pNew->GetSourceDir(), IDC_ED_DFLT_SRC_DIR);
		CString strDestDir	= GetShortDirStr(pNew->GetDestDirectory(), IDC_ED_DFLT_DEST_DIR);

		m_listProjectItems.SetItemText(iNew, ePDataCol_StepNum,		pNew->GetStepNumStr());
		m_listProjectItems.SetItemText(iNew, ePDataCol_SubStepNum,	pNew->GetSubStepNumStr());
		m_listProjectItems.SetItemText(iNew, ePDataCol_StepType,	pNew->GetStepTypeStr());
		m_listProjectItems.SetItemText(iNew, ePDataCol_File,		pNew->GetSourceFile());
		m_listProjectItems.SetItemText(iNew, ePDataCol_Source,		strSrcDir);
		m_listProjectItems.SetItemText(iNew, ePDataCol_Destination, strDestDir);
		m_listProjectItems.SetItemText(iNew, ePDataCol_CopiedName,	pNew->GetDestFile());
		m_listProjectItems.SetItemText(iNew, ePDataCol_Status,		pNew->GetStepStatusStr());
		m_listProjectItems.SetItemText(iNew, ePDataCol_Created,		pNew->GetCreated());
		m_listProjectItems.SetItemText(iNew, ePDataCol_Modified,	pNew->GetModified());

		m_listProjectItems.SetItemData(iNew, reinterpret_cast<DWORD>(pNew));
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		GetMainSheet()->HandleHR(e, _T("CPagePfaData::AddListRow"), _T(""), _T(""), true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 09:20:47
	DESCRIP:
		
		what about:
			J:\Winlink\Link Scripts for Windows Latest Version (Work in Progress)_160407_18817
		
		and:
			J:\Winlink\Link Scripts for Windows Latest Version (Work in Progress)
		
		shows up as:
			_160407_18817
	IN:
	OUT:
*/
CString CPagePfaData::GetShortDirStr(const CString & strLong, const DWORD dwEditID) const
{
#pragma message ("CPagePfaData::GetShortDirStr needs work!")

	CString strShort(strLong);

	CString strRoot;
	GetDlgItemText(dwEditID, strRoot);

	int iLastSlash = strRoot.ReverseFind(_T('\\'));

	strShort.Replace(strRoot, _T(""));

	if(strShort.IsEmpty())
		strShort = szDFLTDIRINDIC;

	return strShort;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 09:32:06
	DESCRIP:	
	IN:
	OUT:
*/
CString CPagePfaData::GetLongDirStr(const CString & strShort, const DWORD dwEditID) const
{
	CString strLong;

	CString strRoot;
	GetDlgItemText(dwEditID, strRoot);

	CString strAdd(strShort);

	if(0 == strAdd.CompareNoCase(szDFLTDIRINDIC))
		strAdd.Empty();

	strLong = strRoot + strAdd;

	return strLong;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/03/2007 18:22:31
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnDeleteitemLstProjectItems(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLISTVIEW * pNMListView = reinterpret_cast<NMLISTVIEW *>(pNMHDR);

	CPfaDataListItem * pDel = 
			reinterpret_cast<CPfaDataListItem *>(m_listProjectItems.GetItemData(pNMListView->iItem));
	ATLASSERT(pDel);

	if(pDel){
		delete pDel;
		pDel = 0;
	}

	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/03/2007 09:27:03
	DESCRIP:	
	IN:
	OUT:
*/
/*afx_msg*/
void CPagePfaData::OnNMProjListCustomDraw(NMHDR * pNotifyStruct, LRESULT * pResult)
{
	* pResult = CDRF_DODEFAULT;

	NMLVCUSTOMDRAW * pLvcd = reinterpret_cast<NMLVCUSTOMDRAW *>(pNotifyStruct);

	if(pLvcd){
		switch(pLvcd->nmcd.dwDrawStage){
			case CDDS_PREPAINT:
				*pResult = CDRF_NOTIFYITEMDRAW;
				break;

			case CDDS_ITEMPREPAINT:
				*pResult = CDRF_NOTIFYSUBITEMDRAW;
				break;

			case CDDS_ITEM | CDDS_SUBITEM | CDDS_PREPAINT:
				{
					CPfaDataListItem * pData = GetDataAt(pLvcd->nmcd.dwItemSpec);
					ATLASSERT(pData);

					if(pData){
						pData->GetStepColouring(pLvcd->iSubItem, pLvcd->clrText, pLvcd->clrTextBk);
					
						//handle volatile properties...
						if(pData->HasUnreadStatus() && (ePDataCol_Status == pLvcd->iSubItem)){
							m_listProjectItems.SetItemText(pLvcd->nmcd.dwItemSpec, ePDataCol_Status, pData->GetStepStatusStr());
							m_listProjectItems.SetColumnWidth(ePDataCol_Status, LVSCW_AUTOSIZE);
							
							pData->SetUnreadStatus(false);
						}
					}


					*pResult = CDRF_NEWFONT;
				}
				break;

			default:
				ATLTRACE(_T("0x%X\n"), pLvcd->nmcd.dwDrawStage);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/03/2007 09:31:41
	DESCRIP:	
	IN:
	OUT:
*/
CPfaDataListItem * CPagePfaData::GetDataAt(const long iItem)
{
	CPfaDataListItem * pRet = 0;

	if(iItem >= 0 && iItem < m_listProjectItems.GetItemCount()){
		DWORD_PTR dwData = m_listProjectItems.GetItemData(iItem);

		if(dwData){
			pRet = reinterpret_cast<CPfaDataListItem *>(dwData);
		}
	}

	ATLASSERT(pRet);
	return pRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	29/03/2007 10:44:18
	DESCRIP:	
	IN:
	OUT:
*/
bool CPagePfaData::DataExistsAt(const long iItem)
{
	bool bExists = false;

	if(iItem >= 0 && iItem < m_listProjectItems.GetItemCount()){
		DWORD_PTR dwData = m_listProjectItems.GetItemData(iItem);

		if(dwData)
			bExists = true;
	}

	return bExists;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 08:14:42
	DESCRIP:	
	IN:
	OUT:
*/
// void CPagePfaData::OnBnCopyFiles() 
// {
// 	CPfaDataListItem * pData = 0;
// 
// 	StartProgress(m_listProjectItems.GetItemCount(), 0L);
// 
// 	//reset all statuses
// 	for(long iItem = 0L ; iItem < m_listProjectItems.GetItemCount() ; iItem ++){
// 		pData = GetDataAt(iItem);
// 		
// 		if(pData){
// 			pData->SetStepStatus(ePStatus_None);
// 			pData->SetUnreadStatus(true);
// 		}
// 	}
// 
// 	StartOperations(false);
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	31/03/2007 21:15:21
	DESCRIP:	
	IN:
	OUT:
*/
// void CPagePfaData::OnBnValidateProject() 
// {
// 	CPfaDataListItem * pData = 0;
// 
// 	StartProgress(m_listProjectItems.GetItemCount(), 0L);
// 
// 	//reset all statuses
// 	for(long iItem = 0L ; iItem < m_listProjectItems.GetItemCount() ; iItem ++){
// 		pData = GetDataAt(iItem);
// 		
// 		if(pData){
// 			pData->SetStepStatus(ePStatus_Validation);
// 			pData->SetUnreadStatus(true);
// 		}
// 	}
// 
// 	StartOperations(true);
// }
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::StartOperations(const bool bValidate)
{
	m_dwCountFail_Items		= 0L;
	m_dwCountFail_SubItems	= 0L;
	m_dwCountOK_Items		= 0L;
	m_dwCountOK_SubItems	= 0L;

	//sort by step number before we begin!

	//Note: the step column is the first column and is justified left.
	//If we don't override by sending LVCFMT_RIGHT as a format
	//then it may be sorted incorrectly as a string
	CListSorter::SortTheList(m_listProjectItems, ePDataCol_StepNum, LVCFMT_RIGHT, true);

	SendOpRequest(0L, bValidate);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 08:46:48
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::SendOpRequest(const long iItem, const bool bValidate)
{
	StartProgress(m_listProjectItems.GetItemCount(), iItem);

	m_listProjectItems.SetSelectionMark	(iItem);
	//m_listProjectItems.EnsureVisible	(iItem, FALSE);
	EnsureItemVisible(iItem);

	m_prgrsFile.SetRange(0, 100);
	m_prgrsFile.SetPos(0);

	if(iItem >= 0L && iItem < m_listProjectItems.GetItemCount()){

		CPfaDataListItem * pThisData = GetDataAt(iItem);

		if(pThisData){

			//don't process any step below iMINSTEPVAL since it will 
			//probably be a progress report or some thing else 8-]
			if(pThisData->IsActionable()){

				CPfaDataListItem * pNew = new CPfaDataListItem(*pThisData);
				ATLASSERT(pNew);

				if(pNew){
					DWORD dwMsg = bValidate ? eWM_VALIDATE_SINGLE_OP : eWM_DO_SINGLE_OP;

					bool bTX = CFileCopyThread::PostTargetThread(dwMsg, iItem, LPARAM(pNew));

					if(!bTX){
						delete pNew;
						pNew = 0;
					}
				}
			}

			//prevent recursive loop:
			//this is the user interface thread so we may need to handle a CANCEL or something
			//just post a message back to ourselves to allow the MFC message pump a chance to do it's bit
			else{
				DWORD dwSkipMsg = bValidate ? eWM_SKIPPED_SINGLE_VALIDATION : eWM_SKIPPED_SINGLE_OP ;
				PostMessage(dwSkipMsg, iItem, 0);
			}
		}
	}
	else{
		OnNoMoreItems();
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	15/05/2007 07:48:50
	DESCRIP:	
		MSGBOXPARAMS mbp;          
		
		mbp.cbSize = sizeof(mbp);     
		mbp.hwndOwner=NULL;     
		mbp.hInstance=hInst; 
		mbp.lpszText = lpstrErr;     
		mbp.lpszCaption = "Mosquito Error!";     
		mbp.dwStyle = MB_OK | MB_USERICON;     
		mbp.lpszIcon = MAKEINTRESOURCE(IDI_BUGICON);     
		mbp.dwContextHelpId = NULL;     
		mbp.lpfnMsgBoxCallback = NULL;     
		mbp.dwLanguageId = NULL;
		
		return MessageBoxIndirect(&mbp); 
	IN:
	OUT:
*/
void CPagePfaData::OnNoMoreItems(void)
{
	CFileCopyThread::PostTargetThread(eWM_NO_MORE_ITEMS, 0, 0);

	CString strMsg;
	strMsg.Format(
			_T("No More Items...\n\n")
			_T("%i items succeeded\n")
			_T("(%i subitem successes)\n\n")
			_T("%i items failed\n")
			_T("(%i subitem failures)\n")
			, m_dwCountOK_Items
			, m_dwCountOK_SubItems
			, m_dwCountFail_Items
			, m_dwCountFail_SubItems
		);

	WORD wResource = IDI_ICON_SUCCESS;

	if(m_dwCountFail_SubItems || m_dwCountFail_Items)
		wResource = IDI_ICON_FAILURE;

	//::AfxMessageBox(strMsg, dwMsgStyle);

	MSGBOXPARAMS mbp;
	::ZeroMemory(&mbp, sizeof(MSGBOXPARAMS));
	
	mbp.cbSize				= sizeof(mbp);     
	mbp.hwndOwner			= 0;     
	mbp.hInstance			= ::AfxGetInstanceHandle(); 
	mbp.lpszText			= strMsg;     
	mbp.lpszCaption			= _T("O p e r a t i o n   C o m p l e t e");     
	mbp.dwStyle				= MB_OK | MB_USERICON;     
	mbp.lpszIcon			= MAKEINTRESOURCE(wResource);     
	mbp.dwContextHelpId		= 0;     
	mbp.lpfnMsgBoxCallback	= 0;     
	mbp.dwLanguageId		= 0;
		
	::MessageBoxIndirect(&mbp); 
	
	ShowProgress(0L);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 09:04:22
	DESCRIP:	
		eWM_SINGLE_OP_STATUS		
			wparam is a list item index
			lparam is a status enum

		1) update our list item status with the new list item status
	IN:
	OUT:
*/
//afx_msg 
LRESULT CPagePfaData::OnWMSingleOpStatus(WPARAM wParam, LPARAM lParam)
{
	//ATLTRACE(_T("OnWMSingleOpStatus %i\n"), wParam);

	CPfaDataListItem * pThisData = GetDataAt(wParam);
	
	if(pThisData){
		ATLASSERT(lParam >= 0 && lParam < ePStatus__LAST);

		if(lParam >= 0 && lParam < ePStatus__LAST){
			pThisData->SetStepStatus(eSTEP_STATUS(lParam));
			pThisData->SetUnreadStatus(true);

			m_listProjectItems.SetColumnWidth(ePDataCol_Status, LVSCW_AUTOSIZE_USEHEADER);
			m_listProjectItems.Invalidate();
		}
	}

	return 0;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 11:12:14
	DESCRIP:	
	IN:
	OUT:
*/
/*afx_msg*/
LRESULT CPagePfaData::OnWMRefreshList(WPARAM wParam, LPARAM lParam)
{
	ATLTRACE(_T("CPagePfaData::OnWMRefreshList\n"));
	RefreshList(-1L);
	return 0;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 08:23:09
	DESCRIP:	
		1) Add a line to the list below the one currently being processed
		2) Send to a report file?
	IN:
	OUT:
*/
/*afx_msg*/
LRESULT CPagePfaData::OnWMEventReport(WPARAM wParam, LPARAM lParam)
{
	CFileCopyReport * pReport = reinterpret_cast<CFileCopyReport *>(lParam);
	ATLASSERT(pReport);

	if(pReport){

		OnWMEventReport(*pReport);

		delete pReport;
		pReport = 0;
	}

	return 0;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10/04/2007 08:29:44
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnWMEventReport(const CFileCopyReport & report)
{
	//the 'op number' should be the zero based list item index
	//of the item that has produced this report...
	DWORD dwInsertPos = report.GetOpNumber() + report.GetSubStep();

	int iNew = m_listProjectItems.InsertItem(dwInsertPos, _T(""));

	CPfaDataListItem * pNew = new CPfaDataListItem(report);

	m_listProjectItems.SetItemText(iNew, ePDataCol_StepNum,		pNew->GetStepNumStr());
	m_listProjectItems.SetItemText(iNew, ePDataCol_SubStepNum,	pNew->GetSubStepNumStr());
	m_listProjectItems.SetItemText(iNew, ePDataCol_StepType,	pNew->GetStepTypeStr());
	m_listProjectItems.SetItemText(iNew, ePDataCol_File,		pNew->GetSourceFile());
	m_listProjectItems.SetItemText(iNew, ePDataCol_Source,		pNew->GetSourceDir());
	m_listProjectItems.SetItemText(iNew, ePDataCol_Destination, pNew->GetDestDirectory());
	m_listProjectItems.SetItemText(iNew, ePDataCol_CopiedName,	pNew->GetDestFile());
	m_listProjectItems.SetItemText(iNew, ePDataCol_Status,		pNew->GetStepStatusStr());

	m_listProjectItems.SetItemData(iNew, reinterpret_cast<DWORD>(pNew));

	m_listProjectItems.SetSelectionMark	(iNew);
	//m_listProjectItems.EnsureVisible	(iNew, FALSE);
	EnsureItemVisible(iNew);

	if(report.Succeeded())
		m_dwCountOK_SubItems ++;

	else
		m_dwCountFail_SubItems ++;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 09:04:25
	DESCRIP:	
		eWM_SINGLE_OP_RESULT		
			wparam is a list item index
			lparam is a pointer to new CPfaDataListItem

		1) update our list item data with the new list item data
		2) send the next request
	IN:
	OUT:
*/
//afx_msg 
LRESULT CPagePfaData::OnWMSingleOpResult(WPARAM wParam, LPARAM lParam)
{
	//ATLTRACE(_T("OnWMSingleOpResult %i\n"), wParam);

	CPfaDataListItem * pRcv = reinterpret_cast<CPfaDataListItem *>(lParam);
	ATLASSERT(pRcv);

	if(pRcv){

		CPfaDataListItem * pThisData =  GetDataAt(wParam);
		
		if(pThisData){
			*pThisData = *pRcv;
			pThisData->SetUnreadStatus(true);

			if(pThisData->Succeeded())
				m_dwCountOK_Items ++;
			else
				m_dwCountFail_Items ++;
		}

		delete pRcv;
		pRcv = 0;
	}

	DWORD dwNextItem = wParam + 1;
	SendOpRequest(dwNextItem, false);

	return 0;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/04/2007 09:05:35
	DESCRIP:	
	IN:
	OUT:
*/
/*afx_msg*/ 
LRESULT CPagePfaData::OnWMSingleOpValidation(WPARAM wParam, LPARAM lParam)	//eWM_SINGLE_OP_VALIDATION
{
	CPfaDataListItem * pRcv = reinterpret_cast<CPfaDataListItem *>(lParam);
	ATLASSERT(pRcv);

	if(pRcv){

		CPfaDataListItem * pThisData =  GetDataAt(wParam);
		
		if(pThisData){
			*pThisData = *pRcv;
			pThisData->SetUnreadStatus(true);

			if(pThisData->Succeeded())
				m_dwCountOK_Items ++;
			else
				m_dwCountFail_Items ++;
		}

		delete pRcv;
		pRcv = 0;
	}

	DWORD dwNextItem = wParam + 1;
	SendOpRequest(dwNextItem, true);

	return 0;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 08:41:47
	DESCRIP:	
	IN:
	OUT:
*/
/*afx_msg*/
LRESULT CPagePfaData::OnWMSkippedSingleOp(WPARAM wParam, LPARAM lParam)
{
	DWORD dwNextItem = wParam + 1;
	SendOpRequest(dwNextItem, false);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/04/2007 09:13:49
	DESCRIP:	
	IN:
	OUT:
*/
/*afx_msg*/
LRESULT CPagePfaData::OnWMSkippedSingleValidation(WPARAM wParam, LPARAM lParam)
{
	DWORD dwNextItem = wParam + 1;
	SendOpRequest(dwNextItem, true);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 12:24:32
	DESCRIP:	
	IN:
	OUT:
*/
/*afx_msg*/
LRESULT CPagePfaData::OnWMSingleFilePCPos(WPARAM wParam, LPARAM lParam)
{
	CParamsShowFilePCPosition * pPos = reinterpret_cast<CParamsShowFilePCPosition *>(lParam);
	ATLASSERT(pPos);

	if(pPos){
		
		m_prgrsFile.SetPos(int(pPos->GetPercent()));

		delete pPos;
		pPos = 0;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 12:25:44
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnRclickLstProjectItems(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	NMLISTVIEW * pNmlv = reinterpret_cast<NMLISTVIEW *>(pNMHDR);

	CPoint ptMenu = pNmlv->ptAction;
	m_listProjectItems.ClientToScreen(&ptMenu);

	CMenu mnuListCtxt;
	mnuListCtxt.LoadMenu(IDR_MNU_CTXT_PFADATA);

	CMenu * pMnuFloat = mnuListCtxt.GetSubMenu(0);

	if(pMnuFloat){
		UINT	uNumSel			= m_listProjectItems.GetSelectedCount();

		bool	bTicked			= HasTickedItems	(m_listProjectItems);
		bool	bHasSrcDir		= HasDirectoryEntry	(pNmlv->iItem, ePDataCol_Source);
		bool	bHasDestDir		= HasDirectoryEntry	(pNmlv->iItem, ePDataCol_Destination);

		const UINT uENABLE	= MF_BYCOMMAND | MF_ENABLED;
		const UINT uDISABLE	= MF_BYCOMMAND | MF_DISABLED | MF_GRAYED;

		//these are always enabled...
		pMnuFloat->EnableMenuItem(ID_CTXT_ADDASTEP,				uENABLE);
		pMnuFloat->EnableMenuItem(ID_CTXT_ADDSINGLEFILES,		uENABLE);
		
		//these act on single items, so an item needs to be selected
		pMnuFloat->EnableMenuItem(ID_CTXT_EDITASTEP,			uNumSel ? uENABLE : uDISABLE);

		//these act on ticked items, so an item needs to be ticked
		pMnuFloat->EnableMenuItem(ID_CTXT_DELETEASTEP,			bTicked ? uENABLE : uDISABLE);
		pMnuFloat->EnableMenuItem(ID_CTXT_COPYASTEP,			bTicked ? uENABLE : uDISABLE);

		//directories
		pMnuFloat->EnableMenuItem(ID_CTXT_EXPLORESOURCE,		bHasSrcDir ? uENABLE : uDISABLE);
		pMnuFloat->EnableMenuItem(ID_CTXT_EXPLOREDESTINATION,	bHasDestDir ? uENABLE : uDISABLE);

		pMnuFloat->TrackPopupMenu(
								TPM_RIGHTBUTTON | TPM_LEFTALIGN
								, ptMenu.x
								, ptMenu.y
								, this
							);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 13:21:35
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnCtxtAddastep() 
{
	AddNewStep();
}			

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11/04/2007 15:18:23
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnCtxtAddsinglefiles() 
{
	DWORD dwProjID = 0L;

	bool bOK = GetCurProjectID(dwProjID);
	if(!bOK)
		return;

	CString strSrcDir;
	GetDlgItemText(IDC_ED_DFLT_SRC_DIR, strSrcDir);

	CPfaStepHolder stepholder;
	CDlgAddFiles dlg;

	//what step number do we start at?
	int iSelMark = m_listProjectItems.GetSelectionMark();
	CString strStepNum = m_listProjectItems.GetItemText(iSelMark, ePDataCol_StepNum);
	long iStepNum = _ttol(strStepNum);
	
	if(iStepNum < iMINSTEPVAL)
		iStepNum = iMINSTEPVAL;

	INT_PTR iReply = dlg.DoModal(strSrcDir, iStepNum, dwProjID, stepholder);

	if(IDOK == iReply){
		CString strRootDestDir;
		GetDlgItemText(IDC_ED_DFLT_DEST_DIR, strRootDestDir);

		CDlgInputBox dlgInput;
		dlgInput.DoModal(_T("Root destination directory"), _T("Choose a destination directory..."), strRootDestDir);

		
		//AddSingleFiles(dlg.GetFileList(), dlg.GetDirList(), dlg.m_strCurDir, strRootDestDir);
		AddSingleFiles(stepholder, dlg.m_strCurDir, strRootDestDir);

		RefreshList(iSelMark);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/05/2007 19:48:48
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::AddSingleFiles(
								CPfaStepHolder & stepholder
								, const CString & strRootSrcDir
								, const CString & strRootDestDir
							)
{
	CWaitCursor wait;
	
	CString strSingleDestDir;
	STEP_LIST::iterator it;
	CPfaStep * pAdjust = 0;

	CDebugTimer timer(_T("CPagePfaData::AddSingleFiles"));
	
	//this loop sets the destination directory for each item in the list
	for(it = stepholder.GetStepList().begin() ; it != stepholder.GetStepList().end() ; it ++){

		pAdjust = * it;
		ATLASSERT(pAdjust);
		
		if(pAdjust){
			strSingleDestDir = CalcBuiltDestDir(
											strRootSrcDir
											, pAdjust->GetSrcDir()	//straryDirs.GetAt(iItem)
											, strRootDestDir
										);

			pAdjust->SetDestDir(strSingleDestDir);
		}
	}
		
	GetMainSheet()->InsertNewSteps(stepholder);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 09:50:55
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::AddSingleFiles(
								const CStringArray & straryFiles
								, const CStringArray & straryDirs
								, const CString & strRootSrcDir
								, const CString & strRootDestDir
							)
{
	CWaitCursor wait;

	DWORD dwProjID = 0L;

	bool bOK = GetCurProjectID(dwProjID);
	if(!bOK)
		return;

	const long iMAXLIST = straryFiles.GetSize();
	ATLASSERT(iMAXLIST == straryDirs.GetSize());

	int iSelMark = m_listProjectItems.GetSelectionMark();
	CString strStepNum = m_listProjectItems.GetItemText(iSelMark, ePDataCol_StepNum);
	long iStepNum = _ttol(strStepNum);

	if(iStepNum < 1L)
		iStepNum = 1L;

	CString strSingleDestDir;
	StartProgress(iMAXLIST, 0L);

	for(long iItem = 0L ; iItem < iMAXLIST ; iItem ++){

		ShowProgress(iItem);

		strSingleDestDir = CalcBuiltDestDir(strRootSrcDir, straryDirs.GetAt(iItem), strRootDestDir);

		GetMainSheet()->InsertNewStep(
										dwProjID
										, iStepNum
										, ePST_CopyFile
										, straryFiles.GetAt(iItem)
										, straryDirs.GetAt(iItem)
										, strSingleDestDir
										, straryFiles.GetAt(iItem)
										, true
									);
		
		iStepNum ++;
	}

	ShowProgress(0);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 08:38:29
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::StartProgress(const long iMaxSteps, const long iCurStep)
{
	m_iPrgrsMax = iMaxSteps;
	ShowProgress(iCurStep);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 08:38:27
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::ShowProgress(const long iCurStep)
{
	double rlPercent = double(iCurStep * 100L) / double(m_iPrgrsMax ? m_iPrgrsMax : 1L);

	if(rlPercent < 0)
		rlPercent = 0;

	if(rlPercent > 100)
		rlPercent = 100;

	m_prgrsBatch.SetPos(short(rlPercent));
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 15:20:20
	DESCRIP:	

		1) We browsed a given root directory, including its sub-dirs:

			eg:		Root-+-File1
						 | 
						 +-File2
						 |
						 +-SubDir1-+-File1
								   |
								   +-File2

		2) We want to replicate the directory structure as seen in the source


	IN:
	OUT:
*/
CString CPagePfaData::CalcBuiltDestDir(
									const CString & strRootSrc
									, const CString & strFullSrc
									, const CString & strRootDest
								) const
{
	CString strRet(strRootDest);

	long iRootSrcLeng = strRootSrc.GetLength();
	long iFullSrcLeng = strFullSrc.GetLength();

	if(iFullSrcLeng > iRootSrcLeng){
		CString strExtra = strFullSrc.Right(iFullSrcLeng - iRootSrcLeng);
		strRet += strExtra;
	}

	return strRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	29/03/2007 11:33:27
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::RefreshList(const long iSetSelMark)
{
	DWORD dwProjID = 0L;

	bool bGotID = GetCurProjectID(dwProjID);

	if(bGotID){
		CString strSQL;
		strSQL.Format(				
					_T(" %s WHERE iProjectID = %i ")
					_T(" ORDER BY iStep ")
					, szSQL_ASSEMBLY_STEPS
					, dwProjID
				);

		PopulateList(strSQL);


		if(iSetSelMark >= 0){
			CListSorter::ReSortTheList(m_listProjectItems);

			m_listProjectItems.SetSelectionMark(iSetSelMark);

			EnsureItemVisible(iSetSelMark);

		}

		m_listProjectItems.SetFocus();
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/05/2007 08:44:14
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::EnsureItemVisible(const long iSetSelMark)
{
	//2007-05-16
	//if we simply ensure the selection is visible, it will be
	//right at the bottom of the list
	//this tries to move the selected one up to nearer the middle.
	long iMax				= m_listProjectItems.GetItemCount();
	long iItemsPerPage		= m_listProjectItems.GetCountPerPage();
	long iEnsureVisible		= iSetSelMark + (iItemsPerPage / 2);

	BOOL bPartialOK = TRUE;
	
	if(iEnsureVisible > iMax){
		iEnsureVisible = iSetSelMark;
		bPartialOK = FALSE;
	}


	m_listProjectItems.EnsureVisible(iEnsureVisible, bPartialOK);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	31/03/2007 09:37:00
	DESCRIP:	
	GetDlgItem(IDC_ED_DFLT_SRC_DIR)->SetFont(GetMainSheet()->GetTheFont(eFont_EdBoxes));
	GetDlgItem(IDC_ED_DFLT_DEST_DIR)->SetFont(GetMainSheet()->GetTheFont(eFont_EdBoxes));
	IN:
	OUT:
*/
void CPagePfaData::RefreshDfltDirs(void)
{
	DWORD dwProjID = 0L;

	bool bGotID = GetCurProjectID(dwProjID);

	if(bGotID){
		CEdit * pEditSrcDir		= reinterpret_cast	<CEdit *>	(GetDlgItem(IDC_ED_DFLT_SRC_DIR));
		CEdit * pEditDestDir	= reinterpret_cast	<CEdit *>	(GetDlgItem(IDC_ED_DFLT_DEST_DIR));

		CString strSQLSrcDir;
		strSQLSrcDir.Format(_T("SELECT szDefaultSourceDir FROM tblProjects WHERE iProjectID = %i"), dwProjID);
		GetMainSheet()->PopulateEditCtrl(strSQLSrcDir, pEditSrcDir);

		CString strSQLDestDir;
		strSQLDestDir.Format(_T("SELECT szDefaultDestDir FROM tblProjects WHERE iProjectID = %i"), dwProjID);
		GetMainSheet()->PopulateEditCtrl(strSQLDestDir, pEditDestDir);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	29/03/2007 11:36:42
	DESCRIP:	
	IN:
	OUT:
*/
bool CPagePfaData::GetCurProjectID(DWORD & dwProjID)
{
	bool bGotID = false;

	if(m_dwCurProjID && (m_dwCurProjID != DWORD(-1L))){
		dwProjID = m_dwCurProjID;
		bGotID = true;
	}

	return bGotID;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 13:21:33
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnCtxtDeleteastep() 
{
	DelTickedSteps();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	31/03/2007 12:55:56
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnCtxtCopyastep() 
{
	DWORD dwProjID = 0L;
	bool bGotProjID = GetCurProjectID(dwProjID);

	if(bGotProjID){
		const long iMAXITEMS = m_listProjectItems.GetItemCount();

		for(long iItem = 0L ; iItem < iMAXITEMS ; iItem++){

			if(m_listProjectItems.GetCheck(iItem)){
			
				CPfaDataListItem * pThisData = GetDataAt(iItem);

				if(pThisData){
					GetMainSheet()->CopyStep(dwProjID, pThisData->GetStepNum());
				}
			}
		}
		
		GetMainSheet()->ReOrdinateSteps(dwProjID);
		RefreshList(-1L);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	31/03/2007 12:59:19
	DESCRIP:	
	IN:
	OUT:
*/
bool CPagePfaData::HasTickedItems(CListCtrl & rList)
{
	bool bHasTicks = false;

	const long iMAXITEMS = rList.GetItemCount();

	for(long iItem = 0L ; iItem < iMAXITEMS && !bHasTicks; iItem++){

		if(rList.GetCheck(iItem))
			bHasTicks = true;
	}

	return bHasTicks;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 13:32:17
	DESCRIP:	
	IN:
	OUT:
*/
long CPagePfaData::NumTickedItems(CListCtrl & rList)
{
	long iNumTicks = 0L;

	const long iMAXITEMS = rList.GetItemCount();

	for(long iItem = 0L ; iItem < iMAXITEMS; iItem++){

		if(rList.GetCheck(iItem))
			iNumTicks ++;
	}

	return iNumTicks;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	04/04/2007 12:20:22
	DESCRIP:
		
		Quick and dirty check to see if a particular list
		item has a directory entry in a particular column.

		Used to enable / disable 'Explore ...' menu items.	

	IN:
	OUT:
*/
bool CPagePfaData::HasDirectoryEntry(const int iItem, const int iSubItem)
{
	bool bHasDir = false;

	if(iItem >= 0){
		CPfaDataListItem * pData = GetDataAt(iItem);

		if(pData){
			CString strText = pData->GetItemText(iSubItem);

			if(strText.GetLength() >= 3){	//"N:\" as a minimum
				if(_T(':') == strText.GetAt(1)){
					if(_T('\\') == strText.GetAt(2)){
						bHasDir = true;
					}
				}

				//2007-06-04	PGC
				//Support for a network drive... (eg "\\U607ST13\..."
				if(_T('\\') == strText.GetAt(0) && _T('\\') == strText.GetAt(1))
					bHasDir = true;
			}
		}
	}

	return bHasDir;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 13:21:31
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnCtxtEditastep() 
{
	EditCurrentStep();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10/04/2007 09:38:38
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::DelTickedSteps(void)
{
	DWORD dwProjID = 0L;
	bool bGotProjID = GetCurProjectID(dwProjID);
	long iNumTicks = NumTickedItems(m_listProjectItems);

	CString strQuery;
	strQuery.Format(_T("Delete %i checked items?"), iNumTicks);

	INT_PTR iReply = ::AfxMessageBox(strQuery, MB_YESNO | MB_ICONQUESTION);

	if(IDYES == iReply){

		if(bGotProjID){
			
			CDebugTimer timer(_T("CPagePfaData::DelTickedSteps"));

			const long iMAXITEMS = m_listProjectItems.GetItemCount();
			
			StartProgress(iMAXITEMS, 0L);

			for(long iItem = 0L ; iItem < iMAXITEMS ; iItem++){

				ShowProgress(iItem);

				if(m_listProjectItems.GetCheck(iItem)){
				
					CPfaDataListItem * pThisData = GetDataAt(iItem);

					if(pThisData){
						GetMainSheet()->DeleteStep(dwProjID, pThisData->GetStepNum());
					}
				}
			}

			ShowProgress(0L);
			
			GetMainSheet()->ReOrdinateSteps(dwProjID);
			RefreshList(-1L);
		}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10/04/2007 09:38:42
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::AddNewStep(void)
{
	long iCurListSel = m_listProjectItems.GetSelectionMark();
	DWORD dwCurProjID = 0L;

	bool bGotProj = GetCurProjectID(dwCurProjID);

	if(bGotProj){

		long iNewStep = 0L;
	
		//after the end of the list...
		//(step number MAX + 1)
		if(iCurListSel < 0){

			iNewStep = m_listProjectItems.GetItemCount() + 1L;

			GetMainSheet()->ReOrdinateSteps(dwCurProjID);
			GetMainSheet()->InsertNewStep(dwCurProjID, iNewStep);
		}

		//in middle of list...
		//(need to work out a step number)
		else{
			CPfaDataListItem * pThisData = GetDataAt(m_listProjectItems.GetSelectionMark());

			if(pThisData){
				iNewStep = pThisData->GetStepNum();
				GetMainSheet()->InsertNewStep(pThisData->GetProjectID(), iNewStep);
			}
		}

		RefreshList(iCurListSel);

		iNewStep --;

		m_listProjectItems.SetSelectionMark	(iNewStep);
		m_listProjectItems.SetItemState		(iNewStep, LVIS_SELECTED, LVIS_SELECTED);
		//m_listProjectItems.EnsureVisible	(iNewStep, FALSE);
		EnsureItemVisible(iNewStep);
	}
	else{
		::AfxMessageBox(_T("Please choose an existing project to add a step to."));
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 07:56:32
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::EditCurrentStep(void)
{
	int iCurSel = m_listProjectItems.GetSelectionMark();

	if(iCurSel >= 0){
		CPfaDataListItem * pThisData = GetDataAt(iCurSel);

		if(pThisData){
			CString strDfltSrc;
			CString strDfltDest;

			GetDlgItem(IDC_ED_DFLT_SRC_DIR)->GetWindowText(strDfltSrc);
			GetDlgItem(IDC_ED_DFLT_DEST_DIR)->GetWindowText(strDfltDest);

			CSheetStepProperties sheet(
									*pThisData
									, strDfltSrc
									, strDfltDest
									, _T("Step Properties")
								);
	
			int iReply = sheet.DoModal();

			CWaitCursor wait;

			//if we don't reconnect to the data, then it seems as though the new changes aren't
			//reflected in our old connection for 3 or 4 secs. May be a cache flushing function?
			GetMainSheet()->DisconnectDb();
			GetMainSheet()->ConnectDb();

			RefreshList(iCurSel);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 13:56:57
	DESCRIP:	
	IN:
	OUT:
*/
// void CPagePfaData::OnBnNewProject() 
// {
// 	DoNewProject();
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 21:15:42
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::DoNewProject(void)
{
	CDlgInputBox dlg;

	CString strProjectName;
	CString strDfltSrcDir;
	CString strDfltDestDir;

	INT_PTR iReply = dlg.DoModal(_T("New Project"), _T("Enter a new project name"), strProjectName);

	if(IDOK == iReply){
		iReply = dlg.DoModal(_T("New Project"), _T("Enter a default source directory"), strDfltSrcDir);

		if(IDOK == iReply){
			iReply = dlg.DoModal(_T("New Project"), _T("Enter a default destination directory"), strDfltDestDir);

			if(IDOK == iReply){
				m_listProjectItems.DeleteAllItems();

				GetMainSheet()->InsertNewProject(strProjectName, strDfltSrcDir, strDfltDestDir);
			}
		}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 21:15:44
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::DoDeleteProject(void)
{
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 21:15:48
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::DoProjectSaveAs(void)
{
	DWORD dwProjID = 0L;

	if(GetCurProjectID(dwProjID)){
		
		COleDateTime dt = COleDateTime::GetCurrentTime();

		CString strNewName;
		strNewName.Format(
						_T("%s %04i-%02i-%02i %02i.%02i.%02i")
						, m_strCurProject
						, dt.GetYear(), dt.GetMonth(), dt.GetDay()
						, dt.GetHour(), dt.GetMinute(), dt.GetSecond()
					);

		CDlgInputBox dlg;

		INT_PTR iReply = dlg.DoModal(_T("Save Project As..."), _T("Choose a new name"), strNewName);

		if(IDOK == iReply){
			
			CWaitCursor wait;

			GetMainSheet()->CopyExistingProject(dwProjID, strNewName);
			//m_listProjectItems.DeleteAllItems();
		}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 21:15:52
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::DoProjectOpen(void)
{
	CDlgOpenAProject dlg(GetMainSheet()->GetTheFont(eFont_List));

	DWORD dwProjID = 0L;
	CString strProjectName;

	INT_PTR iReply = dlg.DoModal(dwProjID, strProjectName);
	ATLTRACE(_T("%i - %s\n"), dwProjID, strProjectName);

	if(IDOK == iReply){
		m_strCurProject		= strProjectName;
		SetDlgItemText(IDC_ED_CUR_PROJECT, strProjectName);
		m_dwCurProjID		= dwProjID;
	
		RefreshDfltDirs();
		RefreshList(-1L);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	29/03/2007 15:49:39
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnCtxtReordinate() 
{
	DWORD dwProjID = 0L;
	bool bGotProjID = GetCurProjectID(dwProjID);

	if(bGotProjID){
		GetMainSheet()->ReOrdinateSteps(dwProjID);
		RefreshList(-1L);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	29/03/2007 19:29:40
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnClickLstProjectItems(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	
	NMLISTVIEW * pNmLv = reinterpret_cast<NMLISTVIEW *>(pNMHDR);
	DWORD dwProjID = 0L;
	bool bGotProjID = GetCurProjectID(dwProjID);

	bool bHandled = false;

	if(pNmLv && bGotProjID){

		if(!m_bLockEdits){
			//which column was clicked?
			switch(pNmLv->iSubItem){
				
				//special case shows a drop down combo for 'step type'
				case ePDataCol_StepType:	bHandled = OnClickedStepType	(*pNmLv);	break;

				//these subitems are editable, and we don't need a 'dir browse' for them
				case ePDataCol_StepNum:		bHandled = EditSingleCell		(*pNmLv, false);	break;
				case ePDataCol_Created:		bHandled = EditSingleCell		(*pNmLv, false);	break;

				//these subitems are editable, and we request a 'dir browse' for them
				case ePDataCol_File:		bHandled = EditSingleCell		(*pNmLv, true);		break;
				case ePDataCol_Source:		bHandled = EditSingleCell		(*pNmLv, true);		break;
				case ePDataCol_Destination:	bHandled = EditSingleCell		(*pNmLv, true);		break;
				case ePDataCol_CopiedName:	bHandled = EditSingleCell		(*pNmLv, true);		break;

				//these subitems are not editable...
				case ePDataCol_Status:		bHandled = false;		break;
				case ePDataCol_Modified:	bHandled = false;		break;
			}
		}

		//2007-05-14
		//removed: user must actually click on the tick-box

		//if we didn't edit anything, just toggle the check mark
		//if(!bHandled){
		//	BOOL bChecked = m_listProjectItems.GetCheck(pNmLv->iItem);
		//
		//	UINT uHitFlags = 0L;
		//	int iHit = m_listProjectItems.HitTest(pNmLv->ptAction, &uHitFlags);
		//	
		//	//this appears to be backwards.
		//	//we get LVHT_ONITEMICON when we DON'T hit the checkbox
		//	if((LVHT_ONITEMICON & uHitFlags) || (LVHT_ONITEMLABEL & uHitFlags)){
		//		bChecked = ! bChecked;
		//		m_listProjectItems.SetCheck(pNmLv->iItem, bChecked);
		//	}
		//}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 21:20:10
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::DoActionValidate(void)
{
	StartOperations(true);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 21:20:06
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::DoActionCopyFiles(void)
{
	StartOperations(false);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 13:22:15
	DESCRIP:	
	IN:
	OUT:
*/
bool CPagePfaData::GetCellRect(const NMLISTVIEW & rNmlv, CListCtrl & rList, CRect & rcCell)
{
	bool bOK = true;

	CRect rcList;
	CRect rcListClient;
	
	rList.GetWindowRect(rcList);
	rList.GetClientRect(rcListClient);

	//int iListBorder = (rcList.Width() - rcListClient.Width()) / 2;
	int iListBorderX = 2;
	int iListBorderY = 2;

	ScreenToClient(rcList);

	rList.GetItemRect(rNmlv.iItem, rcCell, LVIR_BOUNDS);
	int iScroll = rList.GetScrollPos(SB_HORZ);

	rcCell.left		= rcList.left + iListBorderX - iScroll;
	rcCell.right	= rcList.left;

	rcCell.top		+= (rcList.top + iListBorderY);
	rcCell.bottom	+= (rcList.top + iListBorderY);

	for(int iLoop = 0 ; iLoop < rNmlv.iSubItem ; iLoop++)
		rcCell.left += rList.GetColumnWidth(iLoop);

	rcCell.right = rcCell.left + rList.GetColumnWidth(rNmlv.iSubItem);
	
	if(rcCell.left < rcList.left){
		rcCell.left = rcList.left;
	}

	if(rcCell.right > rcList.right){
		rcCell.right = rcList.right;
	}

	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 12:33:41
	DESCRIP:	
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
	IN:
	OUT:
*/
bool CPagePfaData::OnClickedStepType(const NMLISTVIEW & rNmlv)
{
	bool bHandled = false;

	CPfaDataListItem * pData = GetDataAt(rNmlv.iItem);

	if(pData){
		CString strText = m_listProjectItems.GetItemText(rNmlv.iItem, rNmlv.iSubItem);

		CRect rcCell;
		GetCellRect(rNmlv, m_listProjectItems, rcCell);

		m_cmboStepType.ShowWindow(							
								SW_SHOW						//int nCmdShow
								, rNmlv.iItem				//, const long iItem
								, rNmlv.iSubItem			//, const long iSubItem
								, pData->GetProjectID()		//, const long iProjectID
								, pData->GetStepNum()		//, const long iStepNumber
								, rcCell
								, strText
							);

		bHandled = true;
	}

	return bHandled;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 14:56:31
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnSelChangeCmboStepType()
{
	ATLTRACE(_T("OnSelChangeCmboStepType\n"));	

	int iSel = m_listProjectItems.GetSelectionMark();			
	GetMainSheet()->CommitEditedCell(m_cmboStepType);

	RefreshList(iSel);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 09:45:32
	DESCRIP:	
	IN:
	OUT:
*/
bool CPagePfaData::EditSingleCell(const NMLISTVIEW & rNmlv, const bool bAddDirBrowse)
{
	if(rNmlv.iItem < 0L)
		return false;

	bool bHandled = false;

	CPfaDataListItem * pData = GetDataAt(rNmlv.iItem);

	if(pData){

		CString strText = pData->GetItemText(rNmlv.iSubItem);
		//CString strText = m_listProjectItems.GetItemText(rNmlv.iItem, rNmlv.iSubItem);

		CRect rcCell;
		GetCellRect(rNmlv, m_listProjectItems, rcCell);

		CRect rcBrowseBn;
		
		rcBrowseBn.top		= rcCell.top;
		rcBrowseBn.bottom	= rcCell.bottom;
		rcBrowseBn.right	= rcCell.right;
		rcBrowseBn.left		= rcBrowseBn.right - rcBrowseBn.Height();

		rcCell.right = rcBrowseBn.left;

		m_redEditBox.ShowWindow(
							SW_SHOW						//int nCmdShow
							, rNmlv.iItem				//, const long iItem
							, rNmlv.iSubItem			//, const long iSubItem
							, pData->GetProjectID()		//, const long iProjectID
							, pData->GetStepNum()		//, const long iStepNumber
							, rcCell
							, strText
						);

		m_bnBrowse.MoveWindow(rcBrowseBn);
		m_bnBrowse.ShowWindow(SW_SHOW);

		bHandled = true;
	}

	return bHandled;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 07:29:09
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnDblclkLstProjectItems(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	DWORD dwProjID = 0L;
	bool bGotProjID = GetCurProjectID(dwProjID);

	bool bEditCurrent = true;

	NMLISTVIEW * pNmLv = reinterpret_cast<NMLISTVIEW *>(pNMHDR);
	ATLASSERT(pNmLv);

	if(pNmLv){


		//if nothing else did anything, do the default
		if(bEditCurrent)
			EditCurrentStep();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 22:53:37
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnBnBrowseDfltDestDir() 
{
	CDlgInputBox dlg;
	CString strText;

	GetDlgItem(IDC_ED_DFLT_DEST_DIR)->GetWindowText(strText);

	INT_PTR iReply = dlg.DoModal(_T("Destination"), _T("Choose a default destination directory"), strText);

	if(IDOK == iReply){

		DWORD dwProjID = 0L;
		bool bOK = GetCurProjectID(dwProjID);

		if(bOK){
			GetMainSheet()->SetProjectDirectory(dwProjID, strText, false);
			RefreshDfltDirs();
			RefreshList(m_listProjectItems.GetSelectionMark());
		}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 22:53:39
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnBnBrowseDfltSrcDir() 
{
	CDlgInputBox dlg;
	CString strText;

	GetDlgItem(IDC_ED_DFLT_SRC_DIR)->GetWindowText(strText);

	INT_PTR iReply = dlg.DoModal(_T("Source"), _T("Choose a default source directory"), strText);

	if(IDOK == iReply){

		DWORD dwProjID = 0L;
		bool bOK = GetCurProjectID(dwProjID);

		if(bOK){
			GetMainSheet()->SetProjectDirectory(dwProjID, strText, true);
			RefreshDfltDirs();
			RefreshList(m_listProjectItems.GetSelectionMark());
		}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	04/04/2007 12:26:20
	DESCRIP:	
		ePDataCol_Source
	IN:
	OUT:
*/
void CPagePfaData::OnCtxtExploresource() 
{
	int	iCurListSel	= m_listProjectItems.GetSelectionMark();

	if(iCurListSel >= 0){
		CPfaDataListItem * pData = GetDataAt(iCurListSel);

		if(pData){
			//CString strText = m_listProjectItems.GetItemText(iCurListSel, ePDataCol_Source);
			//CString strDir = GetLongDirStr(strText, IDC_ED_DFLT_SRC_DIR);
			CString strDir = pData->GetSourceDir();
			
			GetMainSheet()->ExploreDirectory(m_hWnd, strDir);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	04/04/2007 12:26:17
	DESCRIP:	
		ePDataCol_Destination
		CString strSrcDir	= GetShortDirStr(pNew->GetSourceDir(), IDC_ED_DFLT_SRC_DIR);
		CString strDestDir	= GetShortDirStr(pNew->GetDestDirectory(), IDC_ED_DFLT_DEST_DIR);
	IN:
	OUT:
*/
void CPagePfaData::OnCtxtExploredestination() 
{
	int	iCurListSel	= m_listProjectItems.GetSelectionMark();

	if(iCurListSel >= 0){
		CPfaDataListItem * pData = GetDataAt(iCurListSel);

		if(pData){
			//CString strText = m_listProjectItems.GetItemText(iCurListSel, ePDataCol_Destination);
			//CString strDir = GetLongDirStr(strText, IDC_ED_DFLT_DEST_DIR);
			CString strDir = pData->GetDestDirectory();

			GetMainSheet()->ExploreDirectory(m_hWnd, strDir);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10/04/2007 09:16:49
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnKeydownLstProjectItems(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLVKEYDOWN * pLVKey = reinterpret_cast<NMLVKEYDOWN * >(pNMHDR);

	switch(pLVKey->wVKey){

		case VK_DELETE:		DelTickedSteps();		break;
		case VK_INSERT:		AddNewStep();			break;

		//case VK_SPACE:		ATLTRACE(_T("OnKeydownLstProjectItems VK_SPACE\n"));		break;
		//case VK_PRIOR:		ATLTRACE(_T("OnKeydownLstProjectItems VK_PRIOR\n"));		break;
		//case VK_NEXT:			ATLTRACE(_T("OnKeydownLstProjectItems VK_NEXT\n"));			break;
		//case VK_END:			ATLTRACE(_T("OnKeydownLstProjectItems VK_END\n"));			break;
		//case VK_HOME:			ATLTRACE(_T("OnKeydownLstProjectItems VK_HOME\n"));			break;
		//case VK_LEFT:			ATLTRACE(_T("OnKeydownLstProjectItems VK_LEFT\n"));			break;
		//case VK_UP:			ATLTRACE(_T("OnKeydownLstProjectItems VK_UP\n"));			break;
		//case VK_RIGHT:		ATLTRACE(_T("OnKeydownLstProjectItems VK_RIGHT\n"));		break;
		//case VK_DOWN:			ATLTRACE(_T("OnKeydownLstProjectItems VK_DOWN\n"));			break;
		//case VK_SELECT:		ATLTRACE(_T("OnKeydownLstProjectItems VK_SELECT\n"));		break;
		//case VK_PRINT:		ATLTRACE(_T("OnKeydownLstProjectItems VK_PRINT\n"));		break;
		//case VK_EXECUTE:		ATLTRACE(_T("OnKeydownLstProjectItems VK_EXECUTE\n"));		break;
		//case VK_SNAPSHOT:		ATLTRACE(_T("OnKeydownLstProjectItems VK_SNAPSHOT\n"));		break;
		//case VK_HELP:			ATLTRACE(_T("OnKeydownLstProjectItems VK_HELP\n"));			break;

		default:
			ATLTRACE(_T("OnKeydownLstProjectItems 0x%X\n"), pLVKey->wVKey);
	}
	
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 10:46:48
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnBnSelAll() 
{
	CListTickSetter::SetTicksAll(m_listProjectItems);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 10:46:50
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnBnSelNone() 
{
	CListTickSetter::SetTicksNone(m_listProjectItems);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 10:46:53
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnBnSelInvert() 
{
	CListTickSetter::SetTicksInvert(m_listProjectItems);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 09:04:09
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnBnSelHighlighted() 
{
	CListTickSetter::SetTicksHighlighted(m_listProjectItems);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 13:32:31
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnKillFocusRedEdit() 
{
	ATLTRACE(_T("OnKillFocusRedEdit\n"));	
	
	//int iCurSel = m_listProjectItems.GetSelectionMark();
	//GetMainSheet()->CommitEditedCell(m_redEditBox);
	//RefreshList(iCurSel);

	m_redEditBox.HideWindow();
	m_bnBrowse.ShowWindow(SW_HIDE);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	04/05/2007 08:09:26
	DESCRIP:	
	IN:
	OUT:
*/
/*afx_msg*/
void CPagePfaData::OnChangeRedEdit()
{
	//Note: this may trigger at unexpected times:
	//eg: click a cell to edit it, don't actually change anything, and 
	//the change message may be sent
	//(edit box changed from "" to the cell text by us initializing it!)

	//click another cell, and the change message is sent
	//edit box was still the previous cell text, changes to new cell text

	ATLTRACE(_T("OnChangeRedEdit\n"));	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 14:42:39
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnKillFocusCmboStepType() 
{
	ATLTRACE(_T("OnKillFocusCmboStepType\n"));	
	m_cmboStepType.HideWindow();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 14:56:26
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnCloseupCmboStepType()
{
	ATLTRACE(_T("OnCloseupCmboStepType\n"));	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 14:56:29
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnDropDownCmboStepType()
{
	ATLTRACE(_T("OnDropDownCmboStepType\n"));	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 13:51:23
	DESCRIP:	
	IN:
		EN_MSGFILTER 
		wParam = (WPARAM) (UINT) uID; 
		lParam = (LPARAM) (MSGFILTER) lpMsgFilter;
	OUT:
*/
void CPagePfaData::OnMsgfilterRedEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;

	MSGFILTER *pMsgFilter = reinterpret_cast<MSGFILTER *>(pNMHDR);

	switch(pMsgFilter->msg){
		case WM_KEYUP:	OnKeyUpCellEdit(*pMsgFilter, *pResult);		break;

		case WM_KEYDOWN:
		case WM_CHAR:
			break;

		default:
			ATLTRACE(_T("OnMsgfilterRedEdit - msg = 0x%05X\n"), pMsgFilter->msg);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	04/05/2007 07:51:11
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnKeyUpCellEdit(const MSGFILTER & msgfilter, LRESULT & rResult)
{
	TCHAR ch = TCHAR(msgfilter.wParam);
	
	ATLTRACE(_T("OnKeyUpCellEdit (0x%X, %c)\n"), ch, ch);	

	rResult = TRUE;

	switch(ch){
		case VK_TAB:		//note: TAB just triggers a 'Lost focus' message, not a key-up
		case VK_RETURN:
			{
				int iCurSel = m_listProjectItems.GetSelectionMark();
				GetMainSheet()->CommitEditedCell(m_redEditBox);
				RefreshList(iCurSel);
				m_bnBrowse.ShowWindow(SW_HIDE);
			}
			break;

		case VK_ESCAPE:
			GetMainSheet()->CancelEditedCell(m_redEditBox);
			m_bnBrowse.ShowWindow(SW_HIDE);
			break;

		default:
			rResult = FALSE;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 15:08:17
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnOK() 
{
	ATLTRACE(_T("CPagePfaData::OnOK\n"));	
	
	CPropertyPage::OnOK();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 15:08:15
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnCancel() 
{
	ATLTRACE(_T("CPagePfaData::OnCancel\n"));	
	
	CPropertyPage::OnCancel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 08:06:38
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPagePfaData::PreTranslateMessage(MSG* pMsg) 
{
	return CPropertyPage::PreTranslateMessage(pMsg);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 12:44:32
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnChkLock() 
{
	UpdateData();

	RefreshLockState();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 13:54:10
	DESCRIP:	
	IN:
	OUT:
*/
// void CPagePfaData::OnBnSaveAs() 
// {
// 	DoProjectSaveAs();
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:		
	DESC:
	IN:
	OUT:
*/
void CPagePfaData::OnColumnclickLstProjectItems(NMHDR* pNMHDR, LRESULT* pResult) 
{
	static bool bAsc = false;
	bAsc = !bAsc;

	NMLISTVIEW * pNMListView = reinterpret_cast<NMLISTVIEW*>(pNMHDR);
	// TODO: Add your control notification handler code here

	//Note: the step column is the first column and is justified left.
	//If we don't override by sending LVCFMT_RIGHT as a format
	//then it will be sorted incorrectly as a string
	if(ePDataCol_StepNum == pNMListView->iSubItem)
		CListSorter::SortTheList(m_listProjectItems, pNMListView->iSubItem, LVCFMT_RIGHT, bAsc);
	
	else
		CListSorter::SortTheList(m_listProjectItems, pNMListView->iSubItem, bAsc);
	
	*pResult = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:		
	DESC:	
	IN:		
	OUT:	
*/
// void CPagePfaData::OnBnExportCsv() 
// {
// 	DoExportCSV(false);
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/05/2007 13:00:35
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnBnExportCsvTicked() 
{
	DoExportCSV(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/05/2007 12:56:27
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::DoExportCSV(const bool bTickedOnly)
{
	const static TCHAR szFILTER[] = _T("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||");

	CString strFileName;
	COleDateTime dtNow = COleDateTime::GetCurrentTime();

	strFileName.Format(
					_T("%04i-%02i-%02i %02i%02i%02i.csv")
					, dtNow.GetYear(), dtNow.GetMonth(), dtNow.GetDay()
					, dtNow.GetHour(), dtNow.GetMinute(), dtNow.GetSecond()
				);

	CFileDialog dlg(
					TRUE
					, _T(".csv")		//LPCTSTR lpszDefExt = NULL
					, strFileName		//LPCTSTR lpszFileName = NULL
					, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT	//DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
					, szFILTER			//LPCTSTR lpszFilter = NULL
					, this				//CWnd* pParentWnd = NULL
				);

	INT_PTR iReply = dlg.DoModal();

	if(IDOK == iReply){

		CWaitCursor wait;

		BOOL bTicked = FALSE;

		CStdioFile fil;
		CString strCSVFile = dlg.GetPathName();

		DWORD dwOFlags = CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::shareDenyNone | CFile::typeText;
		BOOL bOK = fil.Open(strCSVFile, dwOFlags);

		if(bOK){
			const long iMAX = m_listProjectItems.GetItemCount();
			CPfaDataListItem * pData = 0;

			for(long iItem = 0 ; iItem < iMAX ; iItem ++){
				pData = GetDataAt(iItem);

				if(pData){
					
					bTicked = m_listProjectItems.GetCheck(iItem);

					if(bTicked || (!bTickedOnly)){
						fil.WriteString(pData->GetCSVFileText());
						fil.WriteString(_T("\n"));
					}
				}
			}

			fil.Close();

			iReply = ::AfxMessageBox(_T("Open the file?"), MB_YESNO | MB_ICONQUESTION);
			if(IDYES == iReply)
				::ShellExecute(m_hWnd, _T("open"), strCSVFile, _T(""), _T(""), SW_NORMAL);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/04/2007 12:26:51
	DESCRIP:	
	IN:
	OUT:
*/
HBRUSH CPagePfaData::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return CBrushHolder::GetBrush(hbr);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 08:24:18
	DESCRIP:	
		IDR_MNU_PROJECT
		ID_PROJECT_DELETE
		ID_PROJECT_NEW
		ID_PROJECT_OPEN
		ID_PROJECT_SAVEAS
	IN:
	OUT:
*/
//void CPagePfaData::OnBnProject() 
//{
//	CRect rcBn;
//	GetDlgItem(IDC_BN_PROJECT)->GetWindowRect(rcBn);
//
//	CMenu menu;
//	menu.LoadMenu(IDR_MNU_PROJECT);
//
//	CMenu * pMnuFloat = menu.GetSubMenu(0);
//	ATLASSERT(pMnuFloat);
//
//	if(pMnuFloat){
//		DWORD dwProjID = 0L;
//		bool bGotProj = GetCurProjectID(dwProjID);
//
//		const UINT uENABLE	= MF_BYCOMMAND | MF_ENABLED;
//		const UINT uDISABLE	= MF_BYCOMMAND | MF_DISABLED | MF_GRAYED;
//
//		//these are always enabled...
//		pMnuFloat->EnableMenuItem(ID_PROJECT_NEW,				uENABLE);
//		pMnuFloat->EnableMenuItem(ID_PROJECT_OPEN,				uENABLE);
//
//		//these depend upon whether or not we've got an open project...
//		pMnuFloat->EnableMenuItem(ID_PROJECT_DELETE, bGotProj ? uENABLE : uDISABLE);
//		pMnuFloat->EnableMenuItem(ID_PROJECT_SAVEAS, bGotProj ? uENABLE : uDISABLE);
//
//		pMnuFloat->TrackPopupMenu(
//							TPM_LEFTALIGN
//							| TPM_LEFTBUTTON
//							, rcBn.left
//							, rcBn.bottom
//							, this
//						);
//	}
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 10:59:02
	DESCRIP:	
		nFlags
			Specifies information about the state of the new menu item when it is added 
			to the menu. It consists of one or more of the values listed in the Remarks 
			section.

		nIDNewItem
			Specifies either the command ID of the new menu item or, if nFlags is set to 
			MF_POPUP, the menu handle (HMENU) of a pop-up menu. The nIDNewItem parameter 
			is ignored (not needed) if nFlags is set to MF_SEPARATOR.

		lpszNewItem
			Specifies the content of the new menu item. The nFlags parameter is used to 
			interpret lpszNewItem in the following way:

			nFlags			Interpretation of lpszNewItem 

			MF_OWNERDRAW	Contains an application-supplied 32-bit value that the 
							application can use to maintain additional data associated 
							with the menu item. This 32-bit value is available to the 
							application when it processes WM_MEASUREITEM and WM_DRAWITEM 
							messages. The value is stored in the itemData member of the 
							structure supplied with those messages. 

			MF_STRING		Contains a pointer to a null-terminated string. This is the 
							default interpretation. 

			MF_SEPARATOR	The lpszNewItem parameter is ignored (not needed). 

	IN:
	OUT:
*/
// void CPagePfaData::OnBnProject() 
// {
// //	using namespace CONS_MENUS::PROJECT_MENU;
// //
// //	CRect rcBn;
// //	GetDlgItem(IDC_BN_PROJECT)->GetWindowRect(rcBn);
// //
// //	CMenu menu;
// //	//menu.LoadMenu(IDR_MNU_PROJECT);
// //	menu.CreatePopupMenu();
// //
// //	DWORD dwAppendFlags = MF_ENABLED | MF_STRING;
// //
// //	for(DWORD dwLoop = eMnuID_PROJECT__FIRST ; dwLoop < eMnuID_PROJECT__LAST ; dwLoop++){
// //		menu.AppendMenu(
// //						dwAppendFlags
// //						, dwLoop
// //						, szsMENU_TEXTS_PROJECT [dwLoop - eMnuID_PROJECT__FIRST]
// //					);
// //	}
// //
// //	DWORD dwProjID = 0L;
// //	bool bGotProj = GetCurProjectID(dwProjID);
// //
// //	const UINT uENABLE	= MF_BYCOMMAND | MF_ENABLED;
// //	const UINT uDISABLE	= MF_BYCOMMAND | MF_DISABLED | MF_GRAYED;
// //
// //	//these are always enabled...
// //	menu.EnableMenuItem(eMnuID_PROJECT_NEW,		uENABLE);
// //	menu.EnableMenuItem(eMnuID_PROJECT_OPEN,	uENABLE);
// //
// //	//these depend upon whether or not we've got an open project...
// //	menu.EnableMenuItem(eMnuID_PROJECT_DELETE, bGotProj ? uENABLE : uDISABLE);
// //	menu.EnableMenuItem(eMnuID_PROJECT_SAVE_AS, bGotProj ? uENABLE : uDISABLE);
// //
// //	menu.TrackPopupMenu(
// //						TPM_LEFTALIGN
// //						| TPM_LEFTBUTTON
// //						, rcBn.left
// //						, rcBn.bottom
// //						, this
// //					);
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 08:31:10
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnProjectDelete() 
{
	DoDeleteProject();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 08:31:00
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnProjectNew() 
{
	DoNewProject();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 08:30:55
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnProjectOpen() 
{
	DoProjectOpen();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 08:30:51
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnProjectSaveas() 
{
	DoProjectSaveAs();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 09:26:55
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	CPropertyPage::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 09:26:52
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	switch(lpDrawItemStruct->itemID){
		case ID_PROJECT_DELETE:
		case ID_PROJECT_NEW:
		case ID_PROJECT_OPEN:
		case ID_PROJECT_SAVEAS:
			ATLTRACE(_T("Draw Item Project Menu...\n"));
			break;

		default:
			ATLTRACE(_T("Draw Item ID %i...\n"), lpDrawItemStruct->itemID);
			break;
	}
	
	CPropertyPage::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 09:41:41
	DESCRIP:	
		ID_ACTION_COPYPROJECTFILES
		ID_ACTION_VALIDATEPROJECT
	IN:
	OUT:
*/
//void CPagePfaData::OnBnAction() 
//{
//	CRect rcBn;
//	GetDlgItem(IDC_BN_ACTION)->GetWindowRect(rcBn);
//
//	CMenu menu;
//	menu.LoadMenu(IDR_MNU_ACTION);
//
//	CMenu * pMnuFloat = menu.GetSubMenu(0);
//	ATLASSERT(pMnuFloat);
//
//	if(pMnuFloat){
//		DWORD dwProjID = 0L;
//		bool bGotProj = GetCurProjectID(dwProjID);
//
//		const UINT uENABLE	= MF_BYCOMMAND | MF_ENABLED;
//		const UINT uDISABLE	= MF_BYCOMMAND | MF_DISABLED | MF_GRAYED;
//
//		//these depend upon whether or not we've got an open project...
//		pMnuFloat->EnableMenuItem(ID_ACTION_COPYPROJECTFILES, bGotProj ? uENABLE : uDISABLE);
//		pMnuFloat->EnableMenuItem(ID_ACTION_VALIDATEPROJECT, bGotProj ? uENABLE : uDISABLE);
//
//		pMnuFloat->TrackPopupMenu(
//							TPM_LEFTALIGN
//							| TPM_LEFTBUTTON
//							, rcBn.left
//							, rcBn.bottom
//							, this
//						);
//	}
//}

// void CPagePfaData::OnBnAction() 
// {
// // 	using namespace CONS_MENUS::ACTION_MENU;
// // 
// // 	CRect rcBn;
// // 	GetDlgItem(IDC_BN_ACTION)->GetWindowRect(rcBn);
// // 
// // 	CMenu menu;
// // 	//menu.LoadMenu(IDR_MNU_PROJECT);
// // 	menu.CreatePopupMenu();
// // 
// // 	DWORD dwAppendFlags = MF_ENABLED | MF_STRING;
// // 
// // 	DWORD dwProjID = 0L;
// // 	bool bGotProj = GetCurProjectID(dwProjID);
// // 	const UINT uENABLE	= MF_BYCOMMAND | MF_ENABLED;
// // 	const UINT uDISABLE	= MF_BYCOMMAND | MF_DISABLED | MF_GRAYED;
// // 
// // 	for(DWORD dwLoop = eMnuID_ACTION__FIRST ; dwLoop < eMnuID_ACTION__LAST ; dwLoop++){
// // 		menu.AppendMenu(
// // 						dwAppendFlags
// // 						, dwLoop
// // 						, szsMENU_TEXTS_ACTION [dwLoop - eMnuID_ACTION__FIRST]
// // 					);
// // 	}
// // 
// // 	//these depend upon whether or not we've got an open project...
// // 	menu.EnableMenuItem(eMnuID_ACTION_COPY_FILES,		bGotProj ? uENABLE : uDISABLE);
// // 	menu.EnableMenuItem(eMnuID_ACTION_VALIDATE_FILES,	bGotProj ? uENABLE : uDISABLE);
// // 
// // 	menu.TrackPopupMenu(
// // 						TPM_LEFTALIGN
// // 						| TPM_LEFTBUTTON
// // 						, rcBn.left
// // 						, rcBn.bottom
// // 						, this
// // 					);
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 09:42:41
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnActionCopyprojectfiles() 
{
	DoActionCopyFiles();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 09:42:46
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnActionValidateproject() 
{
	DoActionValidate();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/04/2007 09:11:41
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnBnSelect() 
{
	// TODO: Add your control notification handler code here
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/04/2007 09:11:44
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnBnFileList() 
{
	// TODO: Add your control notification handler code here
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/04/2007 11:17:55
	DESCRIP:	
	ON_UPDATE_COMMAND_UI(ID_ACTION_COPYPROJECTFILES, OnUpdateActionCopyprojectfiles)
	ON_UPDATE_COMMAND_UI(ID_ACTION_VALIDATEPROJECT, OnUpdateActionValidateproject)
	ON_UPDATE_COMMAND_UI(ID_PROJECT_DELETE, OnUpdateProjectDelete)
	ON_UPDATE_COMMAND_UI(ID_PROJECT_NEW, OnUpdateProjectNew)
	ON_UPDATE_COMMAND_UI(ID_PROJECT_OPEN, OnUpdateProjectOpen)
	ON_UPDATE_COMMAND_UI(ID_PROJECT_SAVEAS, OnUpdateProjectSaveas)
	IN:
	OUT:
*/
void CPagePfaData::OnUpdateActionCopyprojectfiles(CCmdUI* pCmdUI) 
{
	ATLTRACE(_T("CPagePfaData::OnUpdateActionCopyprojectfiles\n"));

	const UINT uENABLE	= MF_BYCOMMAND | MF_ENABLED;
	const UINT uDISABLE	= MF_BYCOMMAND | MF_DISABLED | MF_GRAYED;

	DWORD dwProjID = 0L;
	bool bGotProjID = GetCurProjectID(dwProjID);

	//if(pCmdUI->m_pMenu){
	//	pCmdUI->m_pMenu->EnableMenuItem(ID_ACTION_COPYPROJECTFILES, bGotProjID ? uENABLE : uDISABLE);
	//}

	GetMainSheet()->EnableSheetMenuItem(1, ID_ACTION_COPYPROJECTFILES, bGotProjID);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/04/2007 11:17:53
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnUpdateActionValidateproject(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/04/2007 11:17:51
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnUpdateProjectDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/04/2007 11:17:48
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnUpdateProjectNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/04/2007 11:17:44
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnUpdateProjectOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/04/2007 11:17:43
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnUpdateProjectSaveas(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/05/2007 12:15:44
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnBnRefresh() 
{
	int iCurSel = m_listProjectItems.GetSelectionMark();
	RefreshList(iCurSel);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/05/2007 08:24:40
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnProjectArchiveExport() 
{
	DWORD dwProjID = 0L;

	if(GetCurProjectID(dwProjID)){
		
		CString strProject;

		GetDlgItemText(IDC_ED_CUR_PROJECT, strProject);
		GetMainSheet()->ArchiveProject(dwProjID, strProject);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/05/2007 08:24:37
	DESCRIP:	
	IN:
	OUT:
*/
void CPagePfaData::OnProjectArchiveImport() 
{
	// TODO: Add your command handler code here
	
}
