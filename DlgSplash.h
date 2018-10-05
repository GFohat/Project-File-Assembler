#if !defined(AFX_DLGSPLASH_H__C811CDFF_D15A_4BD9_8D1C_8DE68BFDB6F3__INCLUDED_)
#define AFX_DLGSPLASH_H__C811CDFF_D15A_4BD9_8D1C_8DE68BFDB6F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSplash.h : header file
//
#include "ButtonIcon.h"
#include ".\picturehelper.h"
using namespace PIC_HELP;

/////////////////////////////////////////////////////////////////////////////
// CDlgSplash dialog

class CDlgSplash 
:	public CDialog
	, public CPictureHelper
{
// Construction
public:
	CDlgSplash(HWND hwndTarget, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSplash)
	enum { IDD = IDD_DLG_SPLASH };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSplash)
public:
	virtual BOOL DestroyWindow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSplash)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	//	, eWM_SPLASH_START_PIC_INIT
	//	, eWM_SPLASH_PIC_INIT_DONE
	LRESULT OnWMSplashStartPicInit	(WPARAM wParam, LPARAM lParam);
	LRESULT OnWMSplashPicInitDone	(WPARAM wParam, LPARAM lParam);


	DECLARE_MESSAGE_MAP()

public:
	void SetText(const CString & strText);

private:
	CFontHandler m_fontSplash;

	CRichEditCtrl m_redText;
	HWND m_hWndTarget;
	CString m_strText;
		
	CRect m_rcText;
	CRect m_rcPicture;


	CBitmap m_bitmap;
	void InitText(const CRect & rcMove);
	void ExitText(void);
	void InitPicture(const CRect & rcMove);
	void ExitPicture(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSPLASH_H__C811CDFF_D15A_4BD9_8D1C_8DE68BFDB6F3__INCLUDED_)
