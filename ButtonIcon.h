#if !defined(AFX_BUTTONICON_H__DB3F8165_A062_4627_AEB1_F83D296BC11D__INCLUDED_)
#define AFX_BUTTONICON_H__DB3F8165_A062_4627_AEB1_F83D296BC11D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonIcon.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButtonIcon window

class CButtonIcon : public CButton
{
// Construction
public:
	CButtonIcon();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonIcon)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CButtonIcon();

	// Generated message map functions
protected:
	//{{AFX_MSG(CButtonIcon)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONICON_H__DB3F8165_A062_4627_AEB1_F83D296BC11D__INCLUDED_)
