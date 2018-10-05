// PageDataProps.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "PageDataProps.h"

#include "PfaMainSheet.h"

#include "ConstLists.h"
using namespace CONS_LISTS;

#include "ConstColours.h"
using namespace CONS_COLOURS;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageDataProps property page

IMPLEMENT_DYNCREATE(CPageDataProps, CPropertyPage)

CPageDataProps::CPageDataProps() 
:	CPropertyPage(CPageDataProps::IDD)
{
	//{{AFX_DATA_INIT(CPageDataProps)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageDataProps::~CPageDataProps()
{
}

void CPageDataProps::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageDataProps)
	DDX_Control(pDX, IDC_LIST_DATA_PROPS, m_listDataProps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageDataProps, CPropertyPage)
	//{{AFX_MSG_MAP(CPageDataProps)
	ON_NOTIFY			(NM_CUSTOMDRAW,		IDC_LIST_DATA_PROPS,	OnNMDataPropListCustomDraw)
	//}}AFX_MSG_MAP
	ON_MESSAGE	(eWM_SET_APPEARANCE,		OnWMSetAppearance)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageDataProps message handlers

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 07:43:41
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageDataProps::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	InitPropList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 07:43:38
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageDataProps::OnSetActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_DataProps, TRUE);
	RefreshPropList();
	
	return CPropertyPage::OnSetActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 07:43:36
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageDataProps::OnKillActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_DataProps, FALSE);
	
	return CPropertyPage::OnKillActive();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 10:50:00
	DESCRIP:	
	IN:
	OUT:
*/
CPfaMainSheet * CPageDataProps::GetMainSheet(void)
{
	CPfaMainSheet * pSheet = reinterpret_cast<CPfaMainSheet *>(GetParent());
	ATLASSERT(pSheet && ::IsWindow(pSheet->m_hWnd));
	return pSheet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 07:46:19
	DESCRIP:	
	IN:
	OUT:
*/
LPARAM CPageDataProps::OnWMSetAppearance(WPARAM wParam, LPARAM lParam)
{
	m_listDataProps.SetFont(GetMainSheet()->GetTheFont(eFont_List));

	CHeaderCtrl * pHdr = m_listDataProps.GetHeaderCtrl();
	ATLASSERT(pHdr && ::IsWindow(pHdr->m_hWnd));

	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		pHdr->SetFont(GetMainSheet()->GetTheFont(eFont_ListHeader));
	}

	return TRUE;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 07:53:19
	DESCRIP:	
	IN:
	OUT:
*/
void CPageDataProps::InitPropList(void)
{
	DWORD dwExStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP;

	m_listDataProps.SetExtendedStyle	(dwExStyle);
	m_listDataProps.DeleteAllItems		();

	CRect rcList;
	m_listDataProps.GetWindowRect(rcList);

	const int iSCRLWID	= 5 + ::GetSystemMetrics(SM_CXVSCROLL);;
	const int iCOLWID	= (rcList.Width() - iSCRLWID) / eDPCol__LAST;

	//int nCol, LPCTSTR lpszColumnHeading, int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1 
	for(DWORD dwCol = 0L ; dwCol < eDPCol__LAST ; dwCol ++){
		m_listDataProps.InsertColumn(
						dwCol
						, szsCOL_NAMES_DATAPROPCOLS		[dwCol]
						, isCOL_FMTS_DATAPROPCOLS		[dwCol]
						, iCOLWID
					);
	}

}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 08:01:07
	DESCRIP:	
	IN:
	OUT:
*/
void CPageDataProps::RefreshPropList(void)
{
	GetMainSheet()->ReadDataSourceProps(m_listDataProps);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 08:18:18
	DESCRIP:	
	IN:
	OUT:
*/
/*afx_msg*/
void CPageDataProps::OnNMDataPropListCustomDraw(NMHDR * pNotifyStruct, LRESULT * pResult)
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
					CString strTest = m_listDataProps.GetItemText(pLvcd->nmcd.dwItemSpec, eDPCol_Value);

					if(0 == strTest.CompareNoCase(_T("DB_E_ERRORSOCCURRED"))){
						pLvcd->clrTextBk = LIGHTRED;
					}
					else{
						if(pLvcd->nmcd.dwItemSpec % 2)
							pLvcd->clrTextBk = LIGHTGREEN;
						
						else
							pLvcd->clrTextBk = WHITE;
					}
				}

				*pResult = CDRF_NEWFONT;
				break;

			//case CDDS_ITEM | CDDS_SUBITEM | CDDS_PREPAINT:
			//	{
			//		CPfaDataListItem * pData = GetDataAt(pLvcd->nmcd.dwItemSpec);
			//		ATLASSERT(pData);
			//
			//		if(pData){
			//			pData->GetStepColouring(pLvcd->iSubItem, pLvcd->clrText, pLvcd->clrTextBk);
			//		
			//			//handle volatile properties...
			//			if(pData->HasUnreadStatus() && (ePDataCol_Status == pLvcd->iSubItem)){
			//				m_listProjectItems.SetItemText(pLvcd->nmcd.dwItemSpec, ePDataCol_Status, pData->GetStepStatusStr());
			//				m_listProjectItems.SetColumnWidth(ePDataCol_Status, LVSCW_AUTOSIZE);
			//				
			//				pData->SetUnreadStatus(false);
			//			}
			//		}
			//
			//
			//		*pResult = CDRF_NEWFONT;
			//	}
			//	break;

			default:
				ATLTRACE(_T("0x%X\n"), pLvcd->nmcd.dwDrawStage);
		}
	}
}
