//{{AFX_INCLUDES()
#include "axsimpledatagrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_PAGEDATA_H__FB80863F_B272_4BD2_AED6_A4F6C9014356__INCLUDED_)
#define AFX_PAGEDATA_H__FB80863F_B272_4BD2_AED6_A4F6C9014356__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageData dialog

class CPageData : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageData)

// Construction
public:
	CPageData();
	~CPageData();

// Dialog Data
	//{{AFX_DATA(CPageData)
	enum { IDD = IDD_PAGE_DATA };
	CAxSimpleDataGrid	m_datagrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageData)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageData)
	virtual BOOL OnInitDialog();
	afx_msg void OnListCellClickedAxsimpledatagridctrl1(long iItem, long iSubItem, LPCTSTR szColumnName, LPCTSTR szCellText);
	afx_msg void OnRowCountChangedAxsimpledatagridctrl1(long iNewCount);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg LRESULT OnWMSetAppearance			(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEDATA_H__FB80863F_B272_4BD2_AED6_A4F6C9014356__INCLUDED_)
