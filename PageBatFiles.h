#if !defined(AFX_PAGEBATFILES_H__B2C0A09B_0282_4757_85D0_8098F85098F9__INCLUDED_)
#define AFX_PAGEBATFILES_H__B2C0A09B_0282_4757_85D0_8098F85098F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageBatFiles.h : header file
//

#include "ConsBatFiles.h"
using namespace CONS_BAT_FILES;

#include "ConstAppearance.h"
using namespace CONS_APPEAR;

#include "BuildReporter.h"

/////////////////////////////////////////////////////////////////////////////
// CPageBatFiles dialog
class CPfaMainSheet;

class CPageBatFiles 
:	public		CPropertyPage
	, public	CPipeServerThread
	, public	CBuildReporter
	, public	CBrushHolder
{
	DECLARE_DYNCREATE(CPageBatFiles)

// Construction
public:
	CPageBatFiles();
	~CPageBatFiles();

// Dialog Data
	//{{AFX_DATA(CPageBatFiles)
	enum { IDD = IDD_PAGE_BATCH_FILES };
	CRichEditCtrl	m_redBatchContents;
	CListCtrl		m_lctrlBatFiles;
	CRichEditCtrl	m_redRecv;
	CString			m_strCurBatFile;
	CString			m_strCurRsltsFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageBatFiles)
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
	//{{AFX_MSG(CPageBatFiles)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListBatfiles();
	afx_msg void OnBnRunBatfile();
	afx_msg void OnBnOpenRslts();
	afx_msg void OnBnTestPipe();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickLctrlBatfiles(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	afx_msg LRESULT OnWMPipeDataReceived		(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMPipeInstanceStartup		(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMPipeInstanceShutdown	(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMRearrangeControls		(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMSetAppearance			(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	void InitListBox(void);
	void InitRichEdBox(void);
	void EnableCmdBtns(void);

private:
	CString m_strCurRunDir;
	CString m_strFullPipeName;
	
	bool m_bRunBatWaitRqrd;

	void RunBatAndWait		(const DWORD dwTimeOutMSecs);
	void RunBatAndDontWait	(void);

private:
	CPfaMainSheet * GetMainSheet(void);

private:
	void ClearRecvText			(void);
	void OnWMPipeDataReceived	(const CString & strMsg);
	void AddRcvTextLine			(const CString & strLine);

private:
	CHARFORMAT2 m_charformats[eRlt__LAST];

	void InitCharFormats(void);

	DWORD	GetCFMask		(const eRCV_LINE_TYPE eType) const;
	DWORD	GetCFEffects	(const eRCV_LINE_TYPE eType) const;

	eRCV_LINE_TYPE	GetLineType	(const CString & strLine) const;
	bool IsInString(const CString & strSearchBody, const CString & strPhrase) const;

private:
	void LoadBatchContents(const CString & strBatFile);


public:
	//void SetAppearance(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEBATFILES_H__B2C0A09B_0282_4757_85D0_8098F85098F9__INCLUDED_)
