#if !defined(AFX_BUILDLISTING_H__A971FB77_2C79_4C95_BC22_BABE75154A17__INCLUDED_)
#define AFX_BUILDLISTING_H__A971FB77_2C79_4C95_BC22_BABE75154A17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuildListing.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuildListing dialog

class CBuildListing : public CDialog
{
// Construction
public:
	BOOL OnInitDialog();
	CBuildListing(CWnd* pParent = NULL);   // standard constructor
	LPITEMIDLIST  ConvertPathToLpItemIdList(const char *pszPath);


// Dialog Data
	//{{AFX_DATA(CBuildListing)
	enum { IDD = IDD_DIALOG_BUILD };
	CEdit	m_EditDestinationDir;
	CEdit	m_EditSourceDir;
	CStatic	m_LblFileName;
	CListCtrl	m_listctrl;
	CString	m_EditDestDir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuildListing)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBuildListing)
	afx_msg void OnBtnFileName();
	afx_msg void OnBtnSource();
	afx_msg void OnBtnDestDir();
	afx_msg void OnBtnBuildList();
	afx_msg void OnBtnScanDir();
	afx_msg void OnBtnCheckAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strDestPath;
	CString m_strSourcePath;
	CString m_strFilePath;

private:
	void InitList(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUILDLISTING_H__A971FB77_2C79_4C95_BC22_BABE75154A17__INCLUDED_)
