#if !defined(AFX_DLGADDFILES_H__759580A8_B2E2_4938_BA3F_898C482A55E0__INCLUDED_)
#define AFX_DLGADDFILES_H__759580A8_B2E2_4938_BA3F_898C482A55E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddFiles.h : header file
//

#include "PropSheetCommon.h"
#include "ListTickSetter.h"
#include "FileListSortParams.h"
#include "FileListItemData.h"
#include "PfaStepHolder.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgAddFiles dialog

class CDlgAddFiles 
:	public CDialog
	, public CPropSheetCommon
	, public CListTickSetter
{
// Construction
public:
	CDlgAddFiles(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddFiles)
	enum { IDD = IDD_DLG_ADD_FILES };
	CListCtrl	m_listCurFiles;
	CEdit	m_edCurDir;
	CString	m_strCurDir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddFiles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddFiles)
	afx_msg void OnBnBrowse();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListCurFiles(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnBnSelAll();
	afx_msg void OnBnSelNone();
	afx_msg void OnBnSelInvert();
	afx_msg void OnBnSelHighlighted();
	afx_msg void OnColumnclickListCurFiles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitemListCurFiles(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	INT_PTR DoModal(
					const CString & strStartDir
					, const long iStartStep
					, const DWORD dwProjID
					, CPfaStepHolder & stepholder
				);

	//inline const CStringArray & GetFileList	(void) const { return m_straryFileList; }
	//inline const CStringArray & GetDirList	(void) const { return m_straryDirList; }
	//inline const CPfaStepHolder & GetStepHolder(void) const;

private:
	void InitList(void);
	void InitEdBox(void);

	void RefreshFileList(void);
	void EnumFiles(const CString & strRootDir);
	void AddFileListItem(const CString & strFile);

	void SetListColWidths(void);

	//CStringArray m_straryFileList;
	//CStringArray m_straryDirList;
	CPfaStepHolder * m_pStepHolder;
	long	m_iStartStepNum;
	DWORD	m_dwProjID;

	static int CALLBACK FileListCompareFunc001(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDFILES_H__759580A8_B2E2_4938_BA3F_898C482A55E0__INCLUDED_)
