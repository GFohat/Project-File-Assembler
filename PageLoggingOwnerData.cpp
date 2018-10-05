// PageLoggingOwnerData.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "PageLoggingOwnerData.h"

#include "ConstSQL.h"
using namespace CONS_SQL;

#include "PfaMainSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageLoggingOwnerData dialog


CPageLoggingOwnerData::CPageLoggingOwnerData()
:	CPropertyPage			(CPageLoggingOwnerData::IDD)
	, CListCacheItemHolder(
						eLogCol__LAST		//const ROWTYPE dwNumColumns
						, 5000L				//, const DWORD_PTR dwMaxCacheItems
						, 200L				//, const DWORD_PTR dwNumToPrefetch
						, 200L				//, const DWORD_PTR dwNumToWhither
					)
{
	//{{AFX_DATA_INIT(CPageLoggingOwnerData)
	//}}AFX_DATA_INIT
}

CPageLoggingOwnerData::~CPageLoggingOwnerData()
{
}

void CPageLoggingOwnerData::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageLoggingOwnerData)
	DDX_Control(pDX, IDC_RED_LOG_TEXT,		m_redLogText);
	DDX_Control(pDX, IDC_RED_LOG_SOURCE,	m_redLogSource);
	DDX_Control(pDX, IDC_RED_LOG_SQL,		m_redLogSQL);
	DDX_Control(pDX, IDC_LIST_CATEGORIES,	m_listCategories);
	DDX_Control(pDX, IDC_LIST_LOG,			m_listLog);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageLoggingOwnerData, CPropertyPage)
	//{{AFX_MSG_MAP(CPageLoggingOwnerData)
	ON_NOTIFY	(NM_CLICK,			IDC_LIST_CATEGORIES,	OnClickListCategories)
	ON_NOTIFY	(NM_CLICK,			IDC_LIST_LOG,			OnClickListLog)
	ON_NOTIFY	(LVN_ITEMCHANGING,	IDC_LIST_LOG,			OnItemchangingListLog)
	ON_NOTIFY	(LVN_ITEMCHANGED,	IDC_LIST_LOG,			OnItemchangedListLog)
	ON_NOTIFY	(LVN_DELETEITEM,	IDC_LIST_LOG,			OnDeleteitemListLog)
	ON_NOTIFY	(NM_CUSTOMDRAW,		IDC_LIST_LOG,			OnNMCustomDrawLogList)
	ON_NOTIFY	(NM_CUSTOMDRAW,		IDC_LIST_CATEGORIES,	OnNMCustomDrawCategoryList)
	ON_NOTIFY	(LVN_GETDISPINFO,	IDC_LIST_LOG,			OnGetdispinfoListLog)
	ON_NOTIFY	(LVN_ODCACHEHINT, 	IDC_LIST_LOG,			OnOdcachehintListLog)
	//}}AFX_MSG_MAP

	ON_MESSAGE	(eWM_SET_APPEARANCE,			OnWMSetAppearance)
	ON_MESSAGE	(eWM_REFRESH_LOG_LIST,			OnWMRefreshLogList)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageLoggingOwnerData message handlers
	
/*afx_msg*/
LRESULT CPageLoggingOwnerData::OnWMSetAppearance(WPARAM wParam, LPARAM lParam)
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
void CPageLoggingOwnerData::InitLists(void)
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
void CPageLoggingOwnerData::InitCategoryList(void)
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
//void CPageLoggingOwnerData::RefreshLogList001(void)
//{
//	CWaitCursor wait;
//	CDebugTimer timer(_T("CPageLoggingOwnerData::RefreshLogList001"));
//	
//	m_listLog.DeleteAllItems();
//	m_listLog.SetRedraw(FALSE);
//
//	CString strSQL(GetLogListSQL());
//
//	//GetMainSheet()->PopulateListCtrl(strSQL, m_listLog, true);
//	
//	CComPtr<ADODB::_Recordset> spRst = 0;
//
//	HRESULT hr = S_OK;
//
//	CLogEntryData data;
//
//	try{
//		THR( hr = GetMainSheet()->OpenRecordSet(strSQL, true, spRst) );
//
//		ATLTRACE(_T("Recordset open\n"));
//		timer.ReportTime(false);
//
//		while(!spRst->BOF && !spRst->EndOfFile){
//
//			data.SetRecID	(XLateFieldNumber	(spRst, _T("iRecID")) );
//
//			data.SetLogon	(XLateFieldText		(spRst, _T("szLogon")) );
//			data.SetMachine	(XLateFieldText		(spRst, _T("szMachine")) );
//			data.SetSource	(XLateFieldText		(spRst, _T("szSource")) );
//			data.SetSQL		(XLateFieldText		(spRst, _T("szSQL")) );
//			data.SetText	(XLateFieldText		(spRst, _T("szText")) );
//			data.SetType	(XLateFieldText		(spRst, _T("szType")) );
//			data.SetWhen	(XLateFieldText		(spRst, _T("dtWhen")) );
//
//			AddListRow(data);
//			
//			THR( hr = spRst->MoveNext() );
//		}
//
//		timer.ReportTime(false);
//	}
//	//----------------------------------------------------------
//	catch(_com_error & e){
//		hr = e.Error();
//		ASSERT(false);
//	}
//
//	CListColumnsHelper::AutoSizeListColumns(m_listLog);
//
//	m_listLog.SetRedraw(TRUE);
//	m_listLog.Invalidate();
//}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/05/2007 13:14:15
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLoggingOwnerData::AddListRow(const CLogEntryData & data)
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
// void CPageLoggingOwnerData::RefreshLogList001(void)
// {
// 	CWaitCursor wait;
// 	CDebugTimer timer(_T("CPageLoggingOwnerData::RefreshLogList002"));
// 	
// 	m_listLog.DeleteAllItems();
// 	m_listLog.SetRedraw(FALSE);
// 
// 	CString strSQL(GetLogListSQL());
// 	CString strTemp;
// 	CSystemTime2 dtsys;
// 
// 	HRESULT hr = S_OK;
// 
// 	CLogEntryData data;
// 
// 	try{
// 		if(m_strSQL != strSQL){
// 			
// 			if(m_tblLogging.m_spRowset)
// 				m_tblLogging.Close();
// 
// 			THR( hr = m_tblLogging.Open(strSQL, m_session) );
// 			m_strSQL = strSQL;
// 		}
// 
// 		THR( hr = m_tblLogging.MoveFirst() );
// 
// 		ATLTRACE(_T("Recordset open\n"));
// 		timer.ReportTime(false);
// 
// 		while(S_OK == hr){
// 			
// 			data.SetData(m_tblLogging);
// 
// 			AddListRow(data);
// 			
// 			THR( hr = m_tblLogging.MoveNext() );
// 		}
// 
// 		timer.ReportTime(false);
// 	}
// 	//----------------------------------------------------------
// 	catch(_com_error & e){
// 		hr = e.Error();
// 		ASSERT(false);
// 	}
// 
// 	CListColumnsHelper::AutoSizeListColumns(m_listLog);
// 
// 	m_listLog.SetRedraw(TRUE);
// 	m_listLog.Invalidate();
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/05/2007 07:44:47
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLoggingOwnerData::RefreshLogList(void)
{
	CWaitCursor wait;
	CDebugTimer timer(_T("CPageLoggingOwnerData::RefreshLogList"));

	CString strSQL(GetLogListSQL());

	HRESULT hr = S_OK;

	try{
		//if(m_strSQL != strSQL){
			
			if(m_tblLogging.m_spRowset)
				m_tblLogging.Close();
			
			THR( hr = m_tblLogging.Open(strSQL, m_session) );
			m_strSQL = strSQL;

			CListCacheItemHolder::ClearCache();
		//}
		
		long iRecCount = 0L;
		THR( hr = m_tblLogging.MoveFirst() );

		THR( hr = GetMainSheet()->CountRecords(m_strSQL, iRecCount) );
		//while(S_OK == hr){
		//	iRecCount ++;
		//
		//	THR( hr = m_tblLogging.MoveNext() );	
		//}

		ATLTRACE(_T("%i records...\n"), iRecCount);

		m_listLog.SetItemCount(iRecCount);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
		GetMainSheet()->HandleHR(e, _T("CPageLoggingOwnerData::RefreshLogList"), _T(""), strSQL, false);
	}

	CListColumnsHelper::AutoSizeListColumns(m_listLog);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11/05/2007 21:41:53
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLoggingOwnerData::RefreshCategoryList(void)
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
CString CPageLoggingOwnerData::GetLogListSQL(void) const
{
	CString strSQL;

	if(eEvt__LAST !=  m_listCategories.GetItemCount()){
		strSQL = szSQL_LOG_LIST_ALL;
	}
	else{
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

		strSQL.Format(_T("%s WHERE iType IN (%s) ORDER BY iRecID DESC "), szSQL_LOG_LIST_ALL, strSQLInPhrase);
		//strSQL.Format(_T("%s WHERE iType IN (%s) "), szSQL_LOG_LIST_ALL, strSQLInPhrase);
	
	}
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
BOOL CPageLoggingOwnerData::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	DWORD dwStyle = ::GetWindowLong(m_listLog.m_hWnd, GWL_STYLE);
	
	dwStyle |= LVS_OWNERDATA;
	::SetWindowLong(m_listLog.m_hWnd, GWL_STYLE, dwStyle);
	dwStyle = ::GetWindowLong(m_listLog.m_hWnd, GWL_STYLE);
	
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
CPfaMainSheet * CPageLoggingOwnerData::GetMainSheet(void)
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
BOOL CPageLoggingOwnerData::OnSetActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_LoggingOwnerData, TRUE);
	RefreshLogList();
	
	return CPropertyPage::OnSetActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 07:43:36
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageLoggingOwnerData::OnKillActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_LoggingOwnerData, FALSE);
	
	return CPropertyPage::OnKillActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11/05/2007 22:24:23
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLoggingOwnerData::OnClickListCategories(NMHDR* pNMHDR, LRESULT* pResult) 
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
LRESULT CPageLoggingOwnerData::OnWMRefreshLogList(WPARAM wParam, LPARAM lParam)
{
	RefreshLogList();
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/05/2007 07:40:53
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLoggingOwnerData::OnClickListLog(NMHDR* pNMHDR, LRESULT* pResult) 
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
void CPageLoggingOwnerData::RefreshDetailedText(const int iListItem)
{
	if(iListItem >= 0){
		HRESULT hr = m_tblLogging.MoveToPosition(iListItem);

		if(SUCCEEDED(hr)){
			m_redLogText	.SetWindowText(m_tblLogging.m_szText);
			m_redLogSource	.SetWindowText(m_tblLogging.m_szSource);
			m_redLogSQL		.SetWindowText(m_tblLogging.m_szSQL);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/05/2007 18:00:48
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLoggingOwnerData::OnItemchangingListLog(NMHDR* pNMHDR, LRESULT* pResult) 
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
void CPageLoggingOwnerData::OnItemchangedListLog(NMHDR* pNMHDR, LRESULT* pResult) 
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
void CPageLoggingOwnerData::OnDeleteitemListLog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	NMLISTVIEW * pNMListView = reinterpret_cast<NMLISTVIEW *>(pNMHDR);

	if(pNMListView){
		DWORD dwData = m_listLog.GetItemData(pNMListView->iItem);

		CLogEntryData * pDel = reinterpret_cast<CLogEntryData *>(dwData);
		//ATLASSERT(pDel);

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
void CPageLoggingOwnerData::OnNMCustomDrawLogList(NMHDR * pNMHDR, LRESULT * pResult)
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
					HRESULT hr = m_tblLogging.MoveToPosition(pLvcd->nmcd.dwItemSpec);
					if(SUCCEEDED(hr))
						SetColouring(m_tblLogging.m_iType, pLvcd->clrText, pLvcd->clrTextBk);
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
void CPageLoggingOwnerData::OnNMCustomDrawCategoryList(NMHDR * pNMHDR, LRESULT * pResult)
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
void CPageLoggingOwnerData::SetColouring(const CString & strCat, COLORREF & crefFG, COLORREF & crefBG)
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
void CPageLoggingOwnerData::SetColouring(const int iType, COLORREF & crefFG, COLORREF & crefBG)
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
BOOL CPageLoggingOwnerData::DestroyWindow() 
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
void CPageLoggingOwnerData::OnGetdispinfoListLog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	NMLVDISPINFO * pDispInfo = reinterpret_cast<NMLVDISPINFO *>(pNMHDR);
	// TODO: Add your control notification handler code here

	CListCacheItemHolder::GetDispInfo(*pDispInfo);

	//are these mutually exclusive? - probably not
	if(pDispInfo->item.mask & LVIF_TEXT ){
		//OnGetDispInfoText(*pDispInfo, pResult);
	}

	if(pDispInfo->item.mask & LVIF_IMAGE){
		//ATLTRACE(_T("OnGetdispinfoListLog mask = LVIF_IMAGE\n"));
		//OnDispInfoText(*pDispInfo, pResult);
	}
	
	if(pDispInfo->item.mask & LVIF_INDENT ){
		//ATLTRACE(_T("OnGetdispinfoListLog mask = LVIF_INDENT\n"));
		//OnDispInfoText(*pDispInfo, pResult);
	}
	
	if(pDispInfo->item.mask & LVIF_PARAM){
		//ATLTRACE(_T("OnGetdispinfoListLog mask = LVIF_PARAM\n"));
		//OnDispInfoText(*pDispInfo, pResult);
	}
	
	if(pDispInfo->item.mask & LVIF_STATE){
		//ATLTRACE(_T("OnGetdispinfoListLog mask = LVIF_STATE\n"));
		//OnDispInfoText(*pDispInfo, pResult);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/05/2007 10:53:38
	DESCRIP:	
	IN:
	OUT:
*/
//void CPageLoggingOwnerData::OnGetDispInfoText(NMLVDISPINFO & dispinfo, LRESULT * pResult)
//{
//	HRESULT hr = S_OK;
//
//	try{
//		THR( hr = m_tblLogging.MoveToPosition(dispinfo.item.iItem) );
//
//		const DWORD dwLEN = dispinfo.item.cchTextMax;
//		const DWORD dwMAX = (dwLEN > dwMAX_LIST_CELL_TEXT) ? dwMAX_LIST_CELL_TEXT : dwLEN;
//
//		_tcsncpy(
//				dispinfo.item.pszText
//				, m_tblLogging.GetLimitedText(dispinfo.item.iSubItem, dwMAX)
//				, dwMAX
//			);
//	}
//	//----------------------------------------------------------
//	catch(_com_error & e){
//		hr = e.Error();
//		ASSERT(false);
//	}
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/05/2007 09:14:46
	DESCRIP:	
	IN:
	OUT:
*/
//void CPageLoggingOwnerData::OnGetDispInfoText(NMLVDISPINFO & dispinfo, LRESULT * pResult)
//{
//	CListCacheItemHolder::GetDispInfo
//}
//	


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/05/2007 09:09:10
	DESCRIP:
		This should cache a set of values for a single data row...
	IN:
	OUT:
*/
/*virtual*/
HRESULT CPageLoggingOwnerData::RetrieveDataRow(const ROWTYPE dwRow, CListCacheItem & rItem)
{
	HRESULT hr = S_OK;

	rItem.ResetData(_T("<eRr>"));

	try{
		THR( hr = m_tblLogging.MoveToPosition(dwRow) );

		//const DWORD dwLEN = dispinfo.item.cchTextMax;
		//const DWORD dwMAX = (dwLEN > dwMAX_LIST_CELL_TEXT) ? dwMAX_LIST_CELL_TEXT : dwLEN;

		for(DWORD dwLoop = 0L ; dwLoop < eLogCol__LAST ; dwLoop ++){
			
			rItem.SetRowItem(
							dwLoop
							, m_tblLogging.GetLimitedText(dwLoop, dwMAX_LIST_CELL_TEXT)
						);
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
	}

	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/05/2007 07:58:03
	DESCRIP:	
	IN:
	OUT:
*/
void CPageLoggingOwnerData::OnOdcachehintListLog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	NMLVCACHEHINT * pCacheHint = reinterpret_cast<NMLVCACHEHINT*>(pNMHDR);

	if(pCacheHint)
		CListCacheItemHolder::CacheHint(*pCacheHint, false);
}
