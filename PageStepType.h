#if !defined(AFX_PAGESTEPTYPE_H__2FF1C5CA_7BB5_4117_A07A_29B546B01A18__INCLUDED_)
#define AFX_PAGESTEPTYPE_H__2FF1C5CA_7BB5_4117_A07A_29B546B01A18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageStepType.h : header file
//
#include "PfaDataListItem.h"

/////////////////////////////////////////////////////////////////////////////
// CPageStepType dialog
class CSheetStepProperties;

class CPageStepType 
:	public CPropertyPage
{
// Construction
public:
	CPageStepType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageStepType)
	enum { IDD = IDD_PAGE_STEP_TYPE };
	CComboBox	m_cmboStepType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageStepType)
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
	//{{AFX_MSG(CPageStepType)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCmboStepType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CSheetStepProperties * GetMainSheet(void);

private:
	void RefreshCombo(void);

public:
	void SetAppearance(void);
	void PageToData(CPfaDataListItem & rItem) const;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESTEPTYPE_H__2FF1C5CA_7BB5_4117_A07A_29B546B01A18__INCLUDED_)
