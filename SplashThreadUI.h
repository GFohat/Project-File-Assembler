#if !defined(AFX_SPLASHTHREADUI_H__A949FC6E_227D_4AFC_B0D5_0BE25E9BFDEB__INCLUDED_)
#define AFX_SPLASHTHREADUI_H__A949FC6E_227D_4AFC_B0D5_0BE25E9BFDEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplashThreadUI.h : header file
//
#include "DlgSplash.h"



/////////////////////////////////////////////////////////////////////////////
// CSplashThreadUI thread

class CSplashThreadUI : public CWinThread
{
	DECLARE_DYNCREATE(CSplashThreadUI)
protected:
	CSplashThreadUI();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplashThreadUI)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSplashThreadUI();

	// Generated message map functions
	//{{AFX_MSG(CSplashThreadUI)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	void SetTargetWnd(HWND hwnd);

private:
	CDlgSplash * m_pdlgSplash;
	static HWND s_hWndTarget;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASHTHREADUI_H__A949FC6E_227D_4AFC_B0D5_0BE25E9BFDEB__INCLUDED_)
