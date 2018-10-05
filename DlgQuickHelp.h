#if !defined(AFX_DLGQUICKHELP_H__AF49955F_BC28_4468_83A4_58D0269E8050__INCLUDED_)
#define AFX_DLGQUICKHELP_H__AF49955F_BC28_4468_83A4_58D0269E8050__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQuickHelp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQuickHelp dialog

class CDlgQuickHelp : public CDialog
{
// Construction
public:
	CDlgQuickHelp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQuickHelp)
	enum { IDD = IDD_DLG_HELP };
	CRichEditCtrl	m_redQuickHelp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQuickHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQuickHelp)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void InitRichEdit(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQUICKHELP_H__AF49955F_BC28_4468_83A4_58D0269E8050__INCLUDED_)
