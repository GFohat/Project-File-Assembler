#if !defined(AFX_DLGINPUTBOX_H__D0791A50_027F_41D4_A046_C55F1ED71077__INCLUDED_)
#define AFX_DLGINPUTBOX_H__D0791A50_027F_41D4_A046_C55F1ED71077__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInputBox.h : header file
//

#include "dirbrowser.h"
using namespace DIR_BROWSER;

/////////////////////////////////////////////////////////////////////////////
// CDlgInputBox dialog

class CDlgInputBox 
:	public CDialog
	, public CDirBrowser
{
// Construction
public:
	CDlgInputBox(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInputBox)
	enum { IDD = IDD_DLG_STRING_REQUESTER };
	CString	m_strText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInputBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInputBox)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnBrowseDir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString m_strTitle;
	CString m_strPrompt;

public:
	INT_PTR DoModal(
				const CString & strTitle
				, const CString & strPrompt
				, CString & strText
			);

private:
	void SetAppearance(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINPUTBOX_H__D0791A50_027F_41D4_A046_C55F1ED71077__INCLUDED_)
