#if !defined(AFX_PAGEDATAPROPS_H__02EF8279_D69D_42AC_817C_283F197205B5__INCLUDED_)
#define AFX_PAGEDATAPROPS_H__02EF8279_D69D_42AC_817C_283F197205B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageDataProps.h : header file
//

class CPfaMainSheet;

/////////////////////////////////////////////////////////////////////////////
// CPageDataProps dialog

class CPageDataProps : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageDataProps)

// Construction
public:
	CPageDataProps();
	~CPageDataProps();

// Dialog Data
	//{{AFX_DATA(CPageDataProps)
	enum { IDD = IDD_PAGE_DATA_PROPS };
	CListCtrl	m_listDataProps;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageDataProps)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageDataProps)
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDataPropListCustomDraw			(NMHDR * pNotifyStruct, LRESULT * pResult);
	//}}AFX_MSG
	
	
	afx_msg LRESULT OnWMSetAppearance			(WPARAM wParam, LPARAM lParam);
	

	DECLARE_MESSAGE_MAP()

public:
	// void SetAppearance(void);

private:
	CPfaMainSheet * GetMainSheet(void);
	void InitPropList(void);
	void RefreshPropList(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEDATAPROPS_H__02EF8279_D69D_42AC_817C_283F197205B5__INCLUDED_)
