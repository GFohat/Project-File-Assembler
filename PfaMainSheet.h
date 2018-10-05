#if !defined(AFX_PFAMAINSHEET_H__4D4044A1_EA55_41A9_B152_5EDF1F3FA197__INCLUDED_)
#define AFX_PFAMAINSHEET_H__4D4044A1_EA55_41A9_B152_5EDF1F3FA197__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PfaMainSheet.h : header file
//

#include "Project File AssemblerDlg.h"
#include "PagePfaData.h"
#include "PageBatFiles.h"
#include "PageInstallShield.h"
#include "PageOptions.h"
#include "PageDataProps.h"
#include "PageLogging.h"
#include "PageLoggingOwnerData.h"
#include "PageData.h"

#include "DlgSplash.h"
#include "SplashThreadUI.h"

#include "ControlPopulator.h"

#include "PropSheetCommon.h"
#include "PfaArchiveHandler.h"

/////////////////////////////////////////////////////////////////////////////
// CPfaMainSheet

typedef enum _ePROP_PAGES{
	ePage_PfaDlg				= 0
	, ePage_PfaData
	, ePage_InstallShield
	, ePage_BatFiles
	, ePage_Options
	, ePage_DataProps
	, ePage_Logging
	, ePage_LoggingOwnerData
	, ePage_Data
	, ePage__LAST
} ePROP_PAGES;

//which menu bar to show when a page is activated...
const DWORD dwMENU_IDS[ePage__LAST] = {
	IDR_MNU_MINIMAL				//ePage_PfaDlg		
	, IDR_MNU_PPAGE_DATA		//, ePage_PfaData
	, IDR_MNU_MINIMAL			//, ePage_InstallShield
	, IDR_MNU_MINIMAL			//, ePage_BatFiles
	, IDR_MNU_MINIMAL			//, ePage_Options
	, IDR_MNU_MINIMAL			//, ePage_DataProps
	, IDR_MNU_MINIMAL			//, ePage_Logging
	, IDR_MNU_MINIMAL			//, ePage_LoggingOwnerData
	, IDR_MNU_MINIMAL			//, ePage_Data
};

class CPfaMainSheet 
:	public		CPropertySheet
	, public	CPropSheetCommon
	, public	CDataHandler
	, public	CPfaArchiveHandler
{
	DECLARE_DYNAMIC(CPfaMainSheet)

// Construction
public:
	CPfaMainSheet(LPCTSTR pszCaption);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPfaMainSheet)
	public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPfaMainSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPfaMainSheet)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUpdateActionCopyprojectfiles(CCmdUI* pCmdUI);
	afx_msg void OnUpdateActionValidateproject(CCmdUI* pCmdUI);
	afx_msg void OnFileExit();
	//}}AFX_MSG

	void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu);

	//eWM_GET_FONT
	afx_msg LRESULT OnWMGetFont			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMPageActivated	(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMSplashInitDone	(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	void AddAllPages(void);

	CProjectFileAssemblerDlg	m_pageFileAssembler;
	CPagePfaData				m_pagePfaData;
	CPageBatFiles				m_pageBatFiles;
	CPageInstallShield			m_pageInstallShield;
	CPageOptions				m_pageOptions;
	CPageDataProps				m_pageDataProps;
	CPageLogging				m_pageLogging;
	CPageLoggingOwnerData		m_pageLoggingOD;
	CPageData					m_pageData;

	void InitSheet(void);

private:
	CDlgSplash * m_pdlgSplash;
	CSplashThreadUI * m_pSplashThread;

	void InitSplash(void);
	void ExitSplash(void);

private:
	void InitMenu(void);	//IDR_MNU_TEST_PPAGE_DATA
	CMenu m_mnuPropPage;

public:
	void EnableSheetMenuItem(const DWORD dwSubMenu, const DWORD dwItem, const bool bEnable);

public:
	HRESULT GetOption		(const eOPTION eOption, long & iValue);
	HRESULT GetOption		(const eOPTION eOption, CString & strValue);
	HRESULT GetOption		(const CString & strName, const CString & strDflt, CString & strValue);
	HRESULT SetOption		(const eOPTION eOption, const CString & strValue);
	HRESULT SetOption		(const CString & strName, const CString & strValue);
	HRESULT OptionExists	(const CString & strName, bool & bExists);

public:
	HRESULT ArchiveProject(
						const DWORD dwProjID
						, const CString & strProjectName
					);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PFAMAINSHEET_H__4D4044A1_EA55_41A9_B152_5EDF1F3FA197__INCLUDED_)
