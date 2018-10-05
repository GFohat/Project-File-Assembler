#if !defined(AFX_PAGEINSTALLSHIELD_H__143E51DB_9911_4CAA_BD38_E34B60DA92A0__INCLUDED_)
#define AFX_PAGEINSTALLSHIELD_H__143E51DB_9911_4CAA_BD38_E34B60DA92A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageInstallShield.h : header file
//
#include "ListGeneralFiles.h"

/////////////////////////////////////////////////////////////////////////////
// CPageInstallShield dialog

class CPfaMainSheet;

class CPageInstallShield 
:	public		CPropertyPage
	, public	CBrushHolder
	, public	CListGeneralFiles
{
	DECLARE_DYNCREATE(CPageInstallShield)

// Construction
public:
	CPageInstallShield();
	~CPageInstallShield();

// Dialog Data
	//{{AFX_DATA(CPageInstallShield)
	enum { IDD = IDD_PAGE_INSTALLSHIELD };
	CListCtrl	m_lctrlISMedia;
	CListCtrl	m_lctrlISProjects;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageInstallShield)
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL DestroyWindow();
	virtual void OnOK();
	virtual void OnCancel();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageInstallShield)
	afx_msg void OnRdoIs10();
	afx_msg void OnRdoIs12();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnLaunchIs();
	afx_msg void OnBnExplore();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	afx_msg LRESULT OnWMRearrangeControls		(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMSetAppearance			(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()

private:
	void InitLists(void);

	void PopulateProjectList	(const CString & strRootDir);
	
	void HandleFoundDirectory(
						const CString & strRootDir
						, const CString & strFound
						, const WIN32_FIND_DATA & data
					);

	void HandleFoundFile(
						const CString & strRootDir
						, const CString & strFound
						, const WIN32_FIND_DATA & data
					);

private:
	CPfaMainSheet * GetMainSheet(void);

public:
	//void SetAppearance(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEINSTALLSHIELD_H__143E51DB_9911_4CAA_BD38_E34B60DA92A0__INCLUDED_)
