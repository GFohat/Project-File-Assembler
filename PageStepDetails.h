#if !defined(AFX_PAGESTEPDETAILS_H__3E6382A4_D138_4A0E_A772_607218902E28__INCLUDED_)
#define AFX_PAGESTEPDETAILS_H__3E6382A4_D138_4A0E_A772_607218902E28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageStepDetails.h : header file
//
#include "PfaDataListItem.h"

/////////////////////////////////////////////////////////////////////////////
// CPageStepDetails dialog
class CSheetStepProperties;

class CPageStepDetails : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageStepDetails)

// Construction
public:
	CPageStepDetails();
	~CPageStepDetails();

// Dialog Data
	//{{AFX_DATA(CPageStepDetails)
	enum { IDD = IDD_PAGE_STEP_DETAILS };
	CComboBox	m_cmboStepType;
	CRichEditCtrl	m_redTextSrcFile;
	CRichEditCtrl	m_redTextSrcDir;
	CRichEditCtrl	m_redTextDestFile;
	CRichEditCtrl	m_redTextDestDir;
	CEdit			m_edLabelSrcFile;
	CEdit			m_edLabelSrcDir;
	CEdit			m_edLabelDestFile;
	CEdit			m_edLabelDestDir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageStepDetails)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnApply();
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageStepDetails)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeRedTextDestdir();
	afx_msg void OnChangeRedTextDestfile();
	afx_msg void OnChangeRedTextSourcedir();
	afx_msg void OnChangeRedTextSrcfile();
	afx_msg void OnBnSrcFile();
	afx_msg void OnBnSrcDir();
	afx_msg void OnBnDestDir();
	afx_msg void OnSelchangeCmboStepType();
	afx_msg void OnBnDestDirDefault();
	afx_msg void OnBnSrcDirDefault();
	afx_msg void OnMsgfilterRedTextSrcfile(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CSheetStepProperties * GetMainSheet(void);

private:
	void RefreshLabels(void);
	void RefreshTexts(void);
	void RefreshCombo(void);

	void SetControlsForType(void);
	void EnableRichEdit(CRichEditCtrl & rRed, const bool bEnable);

private:
	CString m_strDfltSrcDir;		//may change
	CString m_strDfltDestDir;		//may change
	CString m_strOrigDfltSrcDir;	//should not change
	CString m_strOrigDfltDestDir;	//should not change

public:
	void SetAppearance(void);
	void SetDefaults(const CString & strDfltSrc, const CString & strDfltDest);

public:
	void PageToData(CPfaDataListItem & rItem) const;
	bool ValidateCurData(CString & strText) const;

private:
	bool Validate_Comment				(CString & strText) const;
	bool Validate_CopySingleDir			(CString & strText) const;
	bool Validate_CopyDirAndSubDirs		(CString & strText) const;
	bool Validate_DelDestFile			(CString & strText) const;
	bool Validate_CreateNewDir			(CString & strText) const;
	bool Validate_CopyFile				(CString & strText) const;
	
private:
	bool IsDlgItemEmpty		(const DWORD dwID) const;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESTEPDETAILS_H__3E6382A4_D138_4A0E_A772_607218902E28__INCLUDED_)
