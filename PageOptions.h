//{{AFX_INCLUDES()
#include "axsimpledatagrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_PAGEOPTIONS_H__C6C95114_8E07_4AD5_A44E_7CA59FCEF9C9__INCLUDED_)
#define AFX_PAGEOPTIONS_H__C6C95114_8E07_4AD5_A44E_7CA59FCEF9C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageOptions.h : header file
//

class CPfaMainSheet;

/////////////////////////////////////////////////////////////////////////////
// CPageOptions dialog

class CPageOptions : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageOptions)

// Construction
public:
	CPageOptions();
	~CPageOptions();

// Dialog Data
	//{{AFX_DATA(CPageOptions)
	enum { IDD = IDD_PAGE_OPTIONS };
	CAxSimpleDataGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageOptions)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageOptions)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LRESULT OnWMSetAppearance			(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	CPfaMainSheet * GetMainSheet(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEOPTIONS_H__C6C95114_8E07_4AD5_A44E_7CA59FCEF9C9__INCLUDED_)
