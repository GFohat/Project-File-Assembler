#if !defined(AFX_PAGELOGGING_H__E9B45105_B66B_410F_AF71_17B25DABA176__INCLUDED_)
#define AFX_PAGELOGGING_H__E9B45105_B66B_410F_AF71_17B25DABA176__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageLogging.h : header file
//
#include "ListColumnsHelper.h"
#include "LogEntryData.h"
#include "XLateFieldText.h"

#include "tblLogging.H"
using namespace OLEDB;

class CPfaMainSheet;

/////////////////////////////////////////////////////////////////////////////
// CPageLogging dialog

class CPageLogging 
:	public CPropertyPage
	, public CListColumnsHelper
	, public CXLateFieldText
{
// Construction
public:
	CPageLogging();   // standard constructor
	~CPageLogging();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageLogging)
	enum { IDD = IDD_PAGE_LOGGING_ADO };
	CRichEditCtrl	m_redLogText;
	CRichEditCtrl	m_redLogSource;
	CRichEditCtrl	m_redLogSQL;
	CListCtrl		m_listCategories;
	CListCtrl		m_listLog;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageLogging)
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
	//{{AFX_MSG(CPageLogging)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListCategories			(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnClickListLog					(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnItemchangingListLog			(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnItemchangedListLog			(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnDeleteitemListLog			(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnNMCustomDrawLogList			(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnNMCustomDrawCategoryList		(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnGetdispinfoListLog(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOdcachehintListLog(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	afx_msg LRESULT OnWMSetAppearance			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMRefreshLogList			(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()

private:
	void InitLists				(void);
	void RefreshLogList001		(void);
	void RefreshLogList002		(void);
	void AddListRow				(const CLogEntryData & data);
	void InitCategoryList		(void);
	void RefreshCategoryList	(void);
	void RefreshDetailedText	(const int iListItem);

	void SetColouring(const CString & strCat, COLORREF & crefFG, COLORREF & crefBG);
	void SetColouring(const int iType, COLORREF & crefFG, COLORREF & crefBG);

	CString GetLogListSQL(void) const;

private:
	CPfaMainSheet * GetMainSheet(void);
	CtblLogging	m_tblLogging;
	CSession	m_session;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGELOGGING_H__E9B45105_B66B_410F_AF71_17B25DABA176__INCLUDED_)
