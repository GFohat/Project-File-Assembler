#if !defined(AFX_PAGEPFADATA_H__51AD38B7_B297_4290_B303_C2E5B9386CB1__INCLUDED_)
#define AFX_PAGEPFADATA_H__51AD38B7_B297_4290_B303_C2E5B9386CB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PagePfaData.h : header file
//

#include "PfaDataListItem.h"
#include "FileCopyThread.h"
#include "ListTickSetter.h"

#include "EditListItem.h"
#include "ComboListItem.h"
#include "ListSorter.h"

#include "PfaStepHolder.h"

#include "ConstMenus.h"
using namespace CONS_MENUS;

#include "ConstDynamicCtrlIDs.h" 
using namespace CONS_CTL_IDS;

/////////////////////////////////////////////////////////////////////////////
// CPagePfaData dialog
class CPfaMainSheet;


class CPagePfaData 
:	public		CPropertyPage
	, public	CFileCopyThread
	, public	CListTickSetter
	, public	CListSorter
	, public	CBrushHolder
{
	DECLARE_DYNCREATE(CPagePfaData)

// Construction
public:
	CPagePfaData();
	~CPagePfaData();

// Dialog Data
	//{{AFX_DATA(CPagePfaData)
	enum { IDD = IDD_PAGE_PFA_DATA };
	CProgressCtrl	m_prgrsFile;
	CProgressCtrl	m_prgrsBatch;
	CListCtrl		m_listProjectItems;
	BOOL			m_bLockEdits;
	DWORD	m_dwRowCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPagePfaData)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL DestroyWindow();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPagePfaData)
	virtual BOOL OnInitDialog					();
	afx_msg void OnDeleteitemLstProjectItems	(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnClickLstProjectItems			(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnDblclkLstProjectItems		(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnKeydownLstProjectItems		(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnRclickLstProjectItems		(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnColumnclickLstProjectItems	(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnNMProjListCustomDraw			(NMHDR * pNotifyStruct, LRESULT * pResult);
	afx_msg void OnCtxtAddastep					();
	afx_msg void OnCtxtDeleteastep				();
	afx_msg void OnCtxtEditastep				();
	afx_msg void OnCtxtReordinate				();
	afx_msg void OnBnBrowseDfltDestDir			();
	afx_msg void OnBnBrowseDfltSrcDir			();
	afx_msg void OnCtxtCopyastep				();
	afx_msg void OnCtxtExploresource			();
	afx_msg void OnCtxtExploredestination		();
	afx_msg void OnCtxtAddsinglefiles			();
	afx_msg void OnBnSelAll						();
	afx_msg void OnBnSelNone					();
	afx_msg void OnBnSelInvert					();
	afx_msg void OnChkLock						();
	afx_msg void OnBnSelHighlighted				();
	afx_msg HBRUSH OnCtlColor					(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMeasureItem					(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem						(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnActionCopyprojectfiles		();
	afx_msg void OnActionValidateproject		();
	afx_msg void OnBnSelect();
	afx_msg void OnBnFileList();
	afx_msg void OnProjectNew();
	afx_msg void OnProjectOpen();
	afx_msg void OnProjectSaveas();
	afx_msg void OnProjectDelete();
	afx_msg void OnUpdateActionCopyprojectfiles(CCmdUI* pCmdUI);
	afx_msg void OnUpdateActionValidateproject(CCmdUI* pCmdUI);
	afx_msg void OnUpdateProjectDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateProjectNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateProjectOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateProjectSaveas(CCmdUI* pCmdUI);
	afx_msg void OnBnExportCsvTicked();
	afx_msg void OnBnRefresh();
	afx_msg void OnProjectArchiveExport();
	afx_msg void OnProjectArchiveImport();
	//}}AFX_MSG

	//afx_msg void OnProjectDelete			();
	//afx_msg void OnProjectNew				();
	//afx_msg void OnProjectOpen			();
	//afx_msg void OnProjectSaveas			();

	afx_msg void OnKillFocusCmboStepType	();
	afx_msg void OnCloseupCmboStepType		();
	afx_msg void OnDropDownCmboStepType		();
	afx_msg void OnSelChangeCmboStepType	();
	afx_msg void OnKillFocusRedEdit			();
	afx_msg void OnChangeRedEdit			();
	afx_msg void OnMsgfilterRedEdit			(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg BOOL OnTTNeedText(UINT id, NMHDR * pNMHDR, LRESULT * pResult);

	afx_msg LRESULT OnWMSingleOpStatus				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMSingleOpResult				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMSingleOpValidation			(WPARAM wParam, LPARAM lParam);	//eWM_SINGLE_OP_VALIDATION
	afx_msg LRESULT OnWMSingleFilePCPos				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMEventReport					(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMSkippedSingleOp				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMSkippedSingleValidation		(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMRefreshList					(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMRearrangeControls			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMSetAppearance				(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	CPfaMainSheet * GetMainSheet(void);
	
	void OnWMEventReport(const CFileCopyReport & report);

private:
	void OnKeyUpCellEdit(const MSGFILTER & msgfilter, LRESULT & rResult);

public:
	//void SetAppearance(void);

private:
	void InitList				(void);
	void SetListColWidths		(void);
	void RefreshList			(const long iSetSelMark);
	void EnsureItemVisible		(const long iSetSelMark);
	void RefreshDfltDirs		(void);
	void RefreshLockState		(void);

private:
	void DoNewProject		(void);
	void DoDeleteProject	(void);
	void DoProjectSaveAs	(void);
	void DoProjectOpen		(void);

	void DoActionValidate	(void);
	void DoActionCopyFiles	(void);
	void DoExportCSV		(const bool bTickedOnly);

private:
	CString m_strCurProject;
	DWORD m_dwCurProjID;

private:
	bool GetCurProjectID(DWORD & dwProjID);

	HRESULT PopulateList	(const CString & strSQL);
	HRESULT AddListRow		(const CComPtr<ADODB::_Recordset> & spRst);
	CString GetShortDirStr	(const CString & strLong, const DWORD dwEditID) const;
	CString GetLongDirStr	(const CString & strShort, const DWORD dwEditID) const;

	CPfaDataListItem * GetDataAt(const long iItem);
	bool DataExistsAt(const long iItem);

private:
	void StartOperations	(const bool bValidate);
	void SendOpRequest		(const long iItem, const bool bValidate);
	void OnNoMoreItems		(void);

private:
	bool HasTickedItems		(CListCtrl & rList);
	long NumTickedItems		(CListCtrl & rList);
	bool HasDirectoryEntry	(const int iItem, const int iSubItem);

private:
	void DelTickedSteps		(void);
	void AddNewStep			(void);
	void EditCurrentStep	(void);

private:
	CComboListItem m_cmboStepType;
	void InitStepTypeCombo(void);

	CEditListItem m_redEditBox;
	void InitEditBox(void);

	CButton m_bnBrowse;
	void InitBrowseBn(void);

	bool GetCellRect			(const NMLISTVIEW & rNmlv, CListCtrl & rList, CRect & rcCell);

	//bool OnClickedStepNum		(const NMLISTVIEW & rNmlv);
	//bool OnClickedStatus		(const NMLISTVIEW & rNmlv);
	//bool OnClickedFile			(const NMLISTVIEW & rNmlv);
	//bool OnClickedSource		(const NMLISTVIEW & rNmlv);
	//bool OnClickedDestination	(const NMLISTVIEW & rNmlv);
	//bool OnClickedCopiedName	(const NMLISTVIEW & rNmlv);
	//bool OnClickedCreated		(const NMLISTVIEW & rNmlv);
	//bool OnClickedModified		(const NMLISTVIEW & rNmlv);

	bool OnClickedStepType		(const NMLISTVIEW & rNmlv);
	bool EditSingleCell			(const NMLISTVIEW & rNmlv, const bool bAddDirBrowse);

private:
	CString CalcBuiltDestDir(const CString & strRootSrc, const CString & strFullSrc, const CString & strRootDest) const;

	void AddSingleFiles(
						CPfaStepHolder & stepholder
						, const CString & strRootSrcDir
						, const CString & strRootDestDir
					);

	void AddSingleFiles(
						const CStringArray & straryFiles
						, const CStringArray & straryDirs
						, const CString & strRootSrcDir
						, const CString & strRootDestDir
					);

	void StartProgress(const long iMaxSteps, const long iCurStep);
	void ShowProgress(const long iCurStep);
	long m_iPrgrsMax;

private:
	DWORD m_dwCountOK_Items;
	DWORD m_dwCountOK_SubItems;

	DWORD m_dwCountFail_Items;
	DWORD m_dwCountFail_SubItems;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEPFADATA_H__51AD38B7_B297_4290_B303_C2E5B9386CB1__INCLUDED_)
