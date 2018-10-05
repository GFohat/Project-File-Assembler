#if !defined(AFX_PAGELOGGINGOWNERDATA_H__E9B45105_B66B_410F_AF71_17B25DABA176__INCLUDED_)
#define AFX_PAGELOGGINGOWNERDATA_H__E9B45105_B66B_410F_AF71_17B25DABA176__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageLoggingOwnerData.h : header file
//
#include "ListColumnsHelper.h"
#include "LogEntryData.h"
#include "XLateFieldText.h"


#include "listcacheitemholder.h"
using namespace LIST_CACHE;


#include "tblLogging.H"
using namespace OLEDB;


class CPfaMainSheet;

/////////////////////////////////////////////////////////////////////////////
// CPageLoggingOwnerData dialog

class CPageLoggingOwnerData 
:	public CPropertyPage
	, public CListColumnsHelper
	, public CXLateFieldText
	, public CListCacheItemHolder
{
// Construction
public:
	CPageLoggingOwnerData();   // standard constructor
	~CPageLoggingOwnerData();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageLoggingOwnerData)
	enum { IDD = IDD_PAGE_LOGGING };
	CRichEditCtrl	m_redLogText;
	CRichEditCtrl	m_redLogSource;
	CRichEditCtrl	m_redLogSQL;
	CListCtrl		m_listCategories;
	CListCtrl		m_listLog;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageLoggingOwnerData)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageLoggingOwnerData)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListCategories			(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnClickListLog					(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnItemchangingListLog			(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnItemchangedListLog			(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnDeleteitemListLog			(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnNMCustomDrawLogList			(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnNMCustomDrawCategoryList		(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnGetdispinfoListLog			(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnOdcachehintListLog			(NMHDR * pNMHDR, LRESULT * pResult);
	//}}AFX_MSG

	afx_msg LRESULT OnWMSetAppearance			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMRefreshLogList			(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()

private:
	void OnGetDispInfoText(NMLVDISPINFO & dispinfo, LRESULT * pResult);
	virtual HRESULT RetrieveDataRow(const ROWTYPE dwRow, CListCacheItem & rItem);

private:
	void InitLists				(void);
	//void RefreshLogList001	(void);
	void RefreshLogList			(void);
	void AddListRow				(const CLogEntryData & data);
	void InitCategoryList		(void);
	void RefreshCategoryList	(void);
	void RefreshDetailedText	(const int iListItem);

	void SetColouring(const CString & strCat, COLORREF & crefFG, COLORREF & crefBG);
	void SetColouring(const int iType, COLORREF & crefFG, COLORREF & crefBG);

	CString GetLogListSQL(void) const;

private:
	CPfaMainSheet * GetMainSheet(void);

private:
	CtblLogging		m_tblLogging;
	CString			m_strSQL;
	CSession		m_session;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGELOGGINGOWNERDATA_H__E9B45105_B66B_410F_AF71_17B25DABA176__INCLUDED_)
