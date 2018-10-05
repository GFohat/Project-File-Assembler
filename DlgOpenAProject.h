#if !defined(AFX_DLGOPENAPROJECT_H__2B383591_0E9F_4E72_8C13_11A53CDF41D0__INCLUDED_)
#define AFX_DLGOPENAPROJECT_H__2B383591_0E9F_4E72_8C13_11A53CDF41D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOpenAProject.h : header file
//

#include "ControlPopulator.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgOpenAProject dialog

class CDlgOpenAProject 
:	public		CDialog
	, public	CDataHandler
{
// Construction
public:
	CDlgOpenAProject(
					CFont * pFontList
					, CWnd* pParent = NULL
				);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOpenAProject)
	enum { IDD = IDD_DLG_OPEN_PROJECT };
	CListCtrl	m_listExistProjects;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOpenAProject)
	public:
	virtual int DoModal(DWORD & dwProjectID, CString & strProjectName);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOpenAProject)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListExistProjects(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListExistProjects(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString m_strProjectName;
	DWORD m_dwProjectID;

private:
	CFont * m_pFontList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPENAPROJECT_H__2B383591_0E9F_4E72_8C13_11A53CDF41D0__INCLUDED_)
