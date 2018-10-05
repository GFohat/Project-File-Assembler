// PageLogging.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "PageLogging.h"

#include "ConstSQL.h"
using namespace CONS_SQL;

#include "PfaMainSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageLogging dialog


CPageLogging::CPageLogging()
:	CPropertyPage(CPageLogging::IDD)
{
	//{{AFX_DATA_INIT(CPageLogging)
	//}}AFX_DATA_INIT
}

CPageLogging::~CPageLogging()
{
}

void CPageLogging::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageLogging)
	DDX_Control(pDX, IDC_RED_LOG_TEXT,		m_redLogText);
	DDX_Control(pDX, IDC_RED_LOG_SOURCE,	m_redLogSource);
	DDX_Control(pDX, IDC_RED_LOG_SQL,		m_redLogSQL);
	DDX_Control(pDX, IDC_LIST_CATEGORIES,	m_listCategories);
	DDX_Control(pDX, IDC_LIST_LOG,			m_listLog);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageLogging, CPropertyPage)
	//{{AFX_MSG_MAP(CPageLogging)
	ON_NOTIFY	(NM_CLICK,			IDC_LIST_CATEGORIES,	OnClickListCategories)
	ON_NOTIFY	(NM_CLICK,			IDC_LIST_LOG,			OnClickListLog)
	ON_NOTIFY	(LVN_ITEMCHANGING,	IDC_LIST_LOG,			OnItemchangingListLog)
	ON_NOTIFY	(LVN_ITEMCHANGED,	IDC_LIST_LOG,			OnItemchangedListLog)
	ON_NOTIFY	(LVN_DELETEITEM,	IDC_LIST_LOG,			OnDeleteitemListLog)
	ON_NOTIFY	(NM_CUSTOMDRAW,		IDC_LIST_LOG,			OnNMCustomDrawLogList)
	ON_NOTIFY	(NM_CUSTOMDRAW,		IDC_LIST_CATEGORIES,	OnNMCustomDrawCategoryList)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_LOG, OnGetdispinfoListLog)
	ON_NOTIFY(LVN_ODCACHEHINT, IDC_LIST_LOG, OnOdcachehintListLog)
	//}}AFX_MSG_MAP

	ON_MESSAGE	(eWM_SET_APPEARANCE,			OnWMSetAppearance)
	ON_MESSAGE	(eWM_REFRESH_LOG_LIST,			OnWMRefreshLogList)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageLogging message handlers
	
/*afx_msg*/
LRESULT CPageLogging::OnWMSetAppearance(WPARAM wParam, LPARAM lParam)
{
	InitLists();
	InitCategoryList();
	RefreshCategoryList();

	GetMainSheet()->SetDlgItemFont(this, IDC_RED_LOG_TEXT, eFont_EdBoxes);
	GetMainSheet()->SetDlgItemFont(this, IDC_RED_LOG_SOURCE, eFont_EdBoxes);
	GetMainSheet()->SetDlgItemFont(this, IDC_RED_LOG_SQL, eFont_EdBoxes);

	m_redLogText.SetBackgroundColor(FALSE, crefREADONLY_BACK);
	m_redLogSource.SetBackgroundColor(FALSE, crefREADONLY_BACK);
	m_redLogSQL.SetBackgroundColor(FALSE, crefREADONLY_BACK);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11/05/2007 13:42:56
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::InitLists(void)
{
	DWORD dwExStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP;

	m_listLog.SetExtendedStyle	(dwExStyle);
	m_listLog.SetFont			(GetMainSheet()->GetTheFont(eFont_List));
	m_listLog.DeleteAllItems	();

	CHeaderCtrl * pHdr = m_listLog.GetHeaderCtrl();
	ATLASSERT(pHdr && ::IsWindow(pHdr->m_hWnd));

	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		pHdr->SetFont(GetMainSheet()->GetTheFont(eFont_ListHeader));
	}

	GetMainSheet()->InitListCtrl(szSQL_LOG_LIST_ALL, m_listLog);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11/05/2007 21:48:50
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::InitCategoryList(void)
{
	DWORD dwExStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP | LVS_EX_CHECKBOXES;
	
	m_listCategories.SetExtendedStyle	(dwExStyle);
	m_listCategories.SetFont			(GetMainSheet()->GetTheFont(eFont_List));
	m_listCategories.DeleteAllItems		();

	m_listCategories.InsertColumn(0, _T("Categories"));
	
	//not sure if we will have a header, may just be icons?
	CHeaderCtrl * pHdr = m_listCategories.GetHeaderCtrl();
	//ATLASSERT(pHdr && ::IsWindow(pHdr->m_hWnd));
	
	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		pHdr->SetFont(GetMainSheet()->GetTheFont(eFont_ListHeader));
	}

}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11/05/2007 13:51:05
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::RefreshLogList001(void)
{
	CWaitCursor wait;
	CDebugTimer timer(_T("CPageLogging::RefreshLogList001"));
	
	m_listLog.DeleteAllItems();
	m_listLog.SetRedraw(FALSE);

	CString strSQL(GetLogListSQL());

	//GetMainSheet()->PopulateListCtrl(strSQL, m_listLog, true);
	
	CComPtr<ADODB::_Recordset> spRst = 0;

	HRESULT hr = S_OK;

	CLogEntryData data;

	try{
		THR( hr = GetMainSheet()->OpenRecordSet(strSQL, true, spRst) );

		ATLTRACE(_T("Recordset open\n"));
		timer.ReportTime(false);

//		while(!spRst->BOF && !spRst->EndOfFile){
//
//			data.SetData(m_tblLogging);
//
//			AddListRow(data);
//			
//			THR( hr = spRst->MoveNext() );
//		}

		timer.ReportTime(false);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
	}

	CListColumnsHelper::AutoSizeListColumns(m_listLog);

	m_listLog.SetRedraw(TRUE);
	m_listLog.Invalidate();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/05/2007 13:14:15
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::AddListRow(const CLogEntryData & data)
{
	CLogEntryData * pNew = new CLogEntryData(data);
	ATLASSERT(pNew);

	if(pNew){
		int iCur = m_listLog.GetItemCount();
		int iNew = m_listLog.InsertItem(iCur, _T(""));

		CString strRecID;

		strRecID.Format(_T("%i"), pNew->GetRecID());

		m_listLog.SetItemText(iNew, eLogCol_RecID,		strRecID);
		m_listLog.SetItemText(iNew, eLogCol_When,		pNew->GetWhen()		.Left(dwMAX_LIST_CELL_TEXT));
		m_listLog.SetItemText(iNew, eLogCol_strType,	pNew->GetTypeStr()	.Left(dwMAX_LIST_CELL_TEXT));
		m_listLog.SetItemText(iNew, eLogCol_Logon,		pNew->GetLogon()	.Left(dwMAX_LIST_CELL_TEXT));
		m_listLog.SetItemText(iNew, eLogCol_Machine,	pNew->GetMachine()	.Left(dwMAX_LIST_CELL_TEXT));
		m_listLog.SetItemText(iNew, eLogCol_Source,		pNew->GetSource()	.Left(dwMAX_LIST_CELL_TEXT));
		m_listLog.SetItemText(iNew, eLogCol_Text,		pNew->GetText()		.Left(dwMAX_LIST_CELL_TEXT));
		m_listLog.SetItemText(iNew, eLogCol_SQL,		pNew->GetSQL()		.Left(dwMAX_LIST_CELL_TEXT));

		m_listLog.SetItemData(iNew, reinterpret_cast<DWORD>(pNew));
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/05/2007 19:44:48
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::RefreshLogList002(void)
{
	if(eEvt__LAST !=  m_listCategories.GetItemCount()){
		return;
	}

	CWaitCursor wait;
	CDebugTimer timer(_T("CPageLogging::RefreshLogList002"));
	
	m_listLog.DeleteAllItems();
	m_listLog.SetRedraw(FALSE);

	CString strSQL(GetLogListSQL());
	CString strTemp;
	CSystemTime2 dtsys;

	HRESULT hr = S_OK;

	CLogEntryData data;

	try{
		THR( hr = m_tblLogging.Open(strSQL, m_session) );
		THR( hr = m_tblLogging.MoveFirst() );

		ATLTRACE(_T("Recordset open\n"));
		timer.ReportTime(false);

		while(S_OK == hr){
			
			data.SetData(m_tblLogging);
			AddListRow(data);
			
			THR( hr = m_tblLogging.MoveNext() );
		}

		timer.ReportTime(false);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
	}

	m_tblLogging.Close();

	CListColumnsHelper::AutoSizeListColumns(m_listLog);

	m_listLog.SetRedraw(TRUE);
	m_listLog.Invalidate();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11/05/2007 21:41:53
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::RefreshCategoryList(void)
{
	m_listCategories.DeleteAllItems();

	//eEvt__LAST
	int iNew = 0;
	for(DWORD dwLoop = 0L ; dwLoop < eEvt__LAST ; dwLoop++){
		iNew = m_listCategories.InsertItem(dwLoop, szsEVENT_TYPE_NAMES[dwLoop]);

		m_listCategories.SetItemData	(iNew, dwLoop);
		m_listCategories.SetCheck		(iNew, TRUE);
	}
	
	CListColumnsHelper::AutoSizeListColumns(m_listCategories);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11/05/2007 22:31:42
	DESCRIP:	
	IN:
	OUT:
*/
CString CPageLogging::GetLogListSQL(void) const
{
	CString strSQL;
	CString strSQLInPhrase;
	CString strAdd;

	BOOL bChecked = FALSE;
	DWORD dwItemData = 0L;

	for(DWORD dwLoop = 0L ; dwLoop < eEvt__LAST ; dwLoop++){
		bChecked = m_listCategories.GetCheck(dwLoop);
		
		strAdd.Empty();

		if(bChecked){
			//strAdd = m_listCategories.GetItemText(dwLoop, 0);
			strAdd.Format(_T("%i"), m_listCategories.GetItemData(dwLoop));
		
			if( ! strSQLInPhrase.IsEmpty())
				strSQLInPhrase += _T(", ");
			
			//strSQLInPhrase += _T("'") + strAdd + _T("'");
			strSQLInPhrase += strAdd;
		}
	}

	if(strSQLInPhrase.IsEmpty())
		strSQLInPhrase = _T("12345");

	strSQL.Format(_T("%s WHERE iType IN (%s) ORDER BY iRecID DESC"), szSQL_LOG_LIST_ALL, strSQLInPhrase);
	
	//TOP n
// 	strSQL.Format(
// 				szSQL_LOG_LIST_TOP_NUMERIC
// 				, 5000
// 				, strSQLInPhrase
// 			);

	ATLTRACE(_T("%s\n"), strSQL);

	return strSQL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11/05/2007 13:44:23
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageLogging::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	HRESULT hr = m_tblLogging.OpenSession(szUDL, m_session);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/04/2007 08:27:27
	DESCRIP:	
	IN:
	OUT:
*/
CPfaMainSheet * CPageLogging::GetMainSheet(void)
{
	CPfaMainSheet * pSheet = reinterpret_cast<CPfaMainSheet *>(GetParent());
	ATLASSERT(pSheet && ::IsWindow(pSheet->m_hWnd));
	return pSheet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 07:43:38
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageLogging::OnSetActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_Logging, TRUE);
	RefreshLogList002();
	
	return CPropertyPage::OnSetActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 07:43:36
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageLogging::OnKillActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_Logging, FALSE);
	
	return CPropertyPage::OnKillActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11/05/2007 22:24:23
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::OnClickListCategories(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NMLISTVIEW * pListView = reinterpret_cast<NMLISTVIEW *>(pNMHDR);

	if(pListView){

		//if we refresh the list now, the check boxes
		//won't have had time to update themselves
		//in the category list, so we just send
		//ourselves a reminder...
		PostMessage(eWM_REFRESH_LOG_LIST, 0, 0);
	}
	
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/05/2007 07:57:12
	DESCRIP:	
	IN:
	OUT:
*/
/*afx_msg*/ 
LRESULT CPageLogging::OnWMRefreshLogList(WPARAM wParam, LPARAM lParam)
{
	RefreshLogList002();
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/05/2007 07:40:53
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::OnClickListLog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLISTVIEW * pNMListView = reinterpret_cast<NMLISTVIEW *>(pNMHDR);

	if(pNMListView){

		RefreshDetailedText(pNMListView->iItem);
		
	}
	
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	15/05/2007 18:02:13
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::RefreshDetailedText(const int iListItem)
{
	if(iListItem >= 0){
		DWORD dwData = m_listLog.GetItemData(iListItem);

		CLogEntryData * pRead = reinterpret_cast<CLogEntryData *>(dwData);
		ATLASSERT(pRead);

		m_redLogText	.SetWindowText(pRead->GetText());
		m_redLogSource	.SetWindowText(pRead->GetSource());
		m_redLogSQL		.SetWindowText(pRead->GetSQL());

//		CString strRecID = m_listLog.GetItemText(iListItem, 0);
//		DWORD dwRecID = _ttol(strRecID);
//		
//		CString strSQL;
//		strSQL.Format(_T("SELECT szText FROM tblLogging WHERE iRecID = %i"), dwRecID);
//		GetMainSheet()->PopulateEditCtrl(strSQL, &m_redLogText);
//		
//		strSQL.Format(_T("SELECT szSource FROM tblLogging WHERE iRecID = %i"), dwRecID);
//		GetMainSheet()->PopulateEditCtrl(strSQL, &m_redLogSource);
//		
//		strSQL.Format(_T("SELECT szSQL FROM tblLogging WHERE iRecID = %i"), dwRecID);
//		GetMainSheet()->PopulateEditCtrl(strSQL, &m_redLogSQL);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/05/2007 18:00:48
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::OnItemchangingListLog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	
	NMLISTVIEW * pNMListView = reinterpret_cast<NMLISTVIEW *>(pNMHDR);
	
	if(pNMListView){
		
		//ATLTRACE(_T("OnItemchangingListLog item %i\n"), pNMListView->iItem);
		
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/05/2007 18:00:52
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::OnItemchangedListLog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	
	NMLISTVIEW * pNMListView = reinterpret_cast<NMLISTVIEW *>(pNMHDR);
	
	if(pNMListView){
		
		//ATLTRACE(
		//		_T("OnItemchangedListLog item %i - from old 0x%X to new 0x%X\n")
		//		, pNMListView->iItem
		//		, pNMListView->uOldState
		//		, pNMListView->uNewState
		//	);
		
		if(pNMListView->uNewState & LVIS_SELECTED)
			RefreshDetailedText(pNMListView->iItem);
		
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/05/2007 13:30:39
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::OnDeleteitemListLog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	NMLISTVIEW * pNMListView = reinterpret_cast<NMLISTVIEW *>(pNMHDR);

	if(pNMListView){
		DWORD dwData = m_listLog.GetItemData(pNMListView->iItem);

		CLogEntryData * pDel = reinterpret_cast<CLogEntryData *>(dwData);
		ATLASSERT(pDel);

		if(pDel){
			delete pDel;
			pDel = 0;
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/05/2007 14:57:26
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::OnNMCustomDrawLogList(NMHDR * pNMHDR, LRESULT * pResult)
{
	* pResult = CDRF_DODEFAULT;

	NMLVCUSTOMDRAW * pLvcd = reinterpret_cast<NMLVCUSTOMDRAW *>(pNMHDR);

	if(pLvcd){
		switch(pLvcd->nmcd.dwDrawStage){
			case CDDS_PREPAINT:
				*pResult = CDRF_NOTIFYITEMDRAW;
				break;

			case CDDS_ITEMPREPAINT:
				{
					//CString strType = m_listLog.GetItemText(pLvcd->nmcd.dwItemSpec, eLogCol_strType);
					DWORD dwData = m_listLog.GetItemData(pLvcd->nmcd.dwItemSpec);
					CLogEntryData * pData = reinterpret_cast<CLogEntryData *>(dwData);
					ATLASSERT(pData);

					if(pData)
						SetColouring(pData->GetTypeNum(), pLvcd->clrText, pLvcd->clrTextBk);

				}
				*pResult = CDRF_NEWFONT;
				break;


			default:
				ATLTRACE(_T("0x%X\n"), pLvcd->nmcd.dwDrawStage);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/05/2007 14:57:29
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::OnNMCustomDrawCategoryList(NMHDR * pNMHDR, LRESULT * pResult)
{
	* pResult = CDRF_DODEFAULT;

	NMLVCUSTOMDRAW * pLvcd = reinterpret_cast<NMLVCUSTOMDRAW *>(pNMHDR);

	if(pLvcd){
		switch(pLvcd->nmcd.dwDrawStage){
			case CDDS_PREPAINT:
				*pResult = CDRF_NOTIFYITEMDRAW;
				break;

			case CDDS_ITEMPREPAINT:
				{
					//Only one column!
					//CString strType = m_listCategories.GetItemText(pLvcd->nmcd.dwItemSpec, 0);
					int iType = m_listCategories.GetItemData(pLvcd->nmcd.dwItemSpec);
					SetColouring(iType, pLvcd->clrText, pLvcd->clrTextBk);

				}
				*pResult = CDRF_NEWFONT;
				break;


			default:
				ATLTRACE(_T("0x%X\n"), pLvcd->nmcd.dwDrawStage);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/05/2007 15:06:24
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::SetColouring(const CString & strCat, COLORREF & crefFG, COLORREF & crefBG)
{
	bool bFound = false;

	for(DWORD dwLoop = 0L ; (dwLoop < eEvt__LAST) && !bFound ; dwLoop++){
		if(0 == strCat.CompareNoCase(szsEVENT_TYPE_NAMES[dwLoop])){
			
			bFound = true;
			
			crefFG = crefEVENT_FORE[dwLoop];
			crefBG = crefEVENT_BACK[dwLoop];
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/05/2007 06:26:57
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::SetColouring(const int iType, COLORREF & crefFG, COLORREF & crefBG)
{
	if(iType >= 0 && iType < eEvt__LAST){
		crefFG = crefEVENT_FORE[iType];
		crefBG = crefEVENT_BACK[iType];
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/05/2007 19:43:32
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageLogging::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	//m_tblLogging.CloseSession();
	m_session.Close();
	
	return CPropertyPage::DestroyWindow();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/05/2007 07:58:00
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::OnGetdispinfoListLog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	NMLVDISPINFO * pDispInfo = reinterpret_cast<NMLVDISPINFO *>(pNMHDR);
	// TODO: Add your control notification handler code here

	pDispInfo->item.mask;
	pDispInfo->item.iSubItem;
	pDispInfo->item.iItem;
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/05/2007 07:58:03
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLogging::OnOdcachehintListLog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	NMLVCACHEHINT * pCacheHint = reinterpret_cast<NMLVCACHEHINT*>(pNMHDR);
	// TODO: Add your control notification handler code here
	
}
