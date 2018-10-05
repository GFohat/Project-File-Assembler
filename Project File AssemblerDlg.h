// Project File AssemblerDlg.h : header file
//

#if !defined(AFX_PROJECTFILEASSEMBLERDLG_H__E3A21396_C4B8_4E2C_8410_E04523C39293__INCLUDED_)
#define AFX_PROJECTFILEASSEMBLERDLG_H__E3A21396_C4B8_4E2C_8410_E04523C39293__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
/////////////////////////////////////////////////////////////////////////////
// CProjectFileAssemblerDlg dialog

#include ".\paramscopyprogress.h"
#include ".\paramsshowfilepcposition.h"

#include "CopyHelper.h"
#include "DirInitHandler.h"
#include "ReportHelper.h"

#include "ConstCsvSetup.h"
using namespace CONS_CSV_SETUP;

class CPfaMainSheet;

class CProjectFileAssemblerDlg 
:	public		CPropertyPage
	, public	CCopyHelper
	, public	CDirInitHandler
	, public	CReportHelper
	, public	CBrushHolder
{
// Construction
public:
	bool m_bFromCmdLine;
	CString m_strCmdLine;
	CProjectFileAssemblerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProjectFileAssemblerDlg)
	enum { IDD = IDD_PROJECTFILEASSEMBLER_DIALOG };
	CButton	m_btnBuildListing;
	CButton	m_btn1;
	CButton	m_btn3;
	//CButton	m_btnOK;
	CButton	m_btnCancel;
	CButton	m_ChkClearDir;
	CStatic	m_lblFilePath;
	CButton	m_ChkCreateDir;
	//CAutoListCtrl	m_listctrl;
	CListCtrl	m_listctrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectFileAssemblerDlg)
	public:
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProjectFileAssemblerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnCopyFiles();
	afx_msg void OnBtnBrowse();
	afx_msg void OnBtnBuildListng();
	afx_msg void OnBnQuickHelp();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	afx_msg	LRESULT OnWMBeginImmediate		(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMSingleFilePCPos		(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMRearrangeControls	(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMSetAppearance		(WPARAM wParam, LPARAM lParam);

	//OnNMListCustomDraw
	afx_msg void OnNMListCustomDraw(NMHDR * pNotifyStruct, LRESULT * pResult);

	DECLARE_MESSAGE_MAP()

private:
	CStringArray m_lstFail;
	CStringArray m_dirlist;

	int CopyAllFilesInDirectory(const CString & sFrom, const CString & sTo);
	int row;
	CString m_strDirsProcessed;
	CString m_strFilePath;
	int CheckDestinationDir(CString Path,CString &Err);
	CFileFind m_finder;

private:
	void CopySingleFile001			(const CString & sFrom, const CString & sTo);

	static DWORD CALLBACK CopyProgressRoutine(
							LARGE_INTEGER		liTotalFileSize          // file size
							, LARGE_INTEGER		liTotalBytesTransferred  // bytes transferred
							, LARGE_INTEGER		liStreamSize             // bytes in stream
							, LARGE_INTEGER		liStreamBytesTransferred // bytes transferred for stream
							, DWORD				dwStreamNumber           // current stream
							, DWORD				dwCallbackReason         // callback reason
							, HANDLE			hSourceFile              // handle to source file
							, HANDLE			hDestinationFile         // handle to destination file
							, LPVOID			lpData                   // from CopyFileEx
						);

	void CopySingleFile002			(const CString & strSrcFile, const CString & strDestFile);
	bool HasDirBeenProcessed		(const CString & strDir) const;
	void InitList					(void);
	void ShowStatus					(const DWORD dwStatus);
	void ShowStatus					(const int iRow, const DWORD dwStatus);
	void OnCopyOperationDone_CMD	(void);
	void OnCopyOperationDone_GUI	(void);
	void WriteResultExit			(const CString & strResult);
	void DeleteDirContent			(const CString & strDir);

	int CreateNewDirectory001(const CString & strDir);
	int CreateNewDirectory002(const CString & strDir);
			
	void CopyDirectoryComplete(const CString & strFrom, const CString & strTo);

	void AddListRow(
				const CString & strFile
				, const CString & strSource
				, const CString & strDestination
				, const CString & strCopiedName
				, const DWORD dwStatus
			);

private:
	void DumpListReport(void);
	void CreateDumpFile(CStdioFile & iofile, CString & strFileName);
	CString GetListRowText(const int iRow);

private:
	long m_iNumCsvFileLines;
	void InitProgress(const CString & strCsvFile);
	void ShowProgress(const long iCurFileLine);

private:
	void SetListColWidths(void);

	void SetLineColouring(
						const CString & strText
						, const CString & strStatus
						, COLORREF & crefFg
						, COLORREF & crefBg
					) const;

private:
	void CopyFiles001(void);
	void CopyFiles002(void);
	BOOL ProcessCsvFile(void);
	BOOL ProcessCsvLine(const long iLineNum, const CString & strLine);
	BOOL ProcessCsvItems(const long iLineNum, const CStringArray & aryItems);

	BOOL Process_Comment			(const long iLineNum, const CStringArray & aryItems);
	BOOL Process_CopySingleFile		(const long iLineNum, const CStringArray & aryItems);
	BOOL Process_CopySingleDir		(const long iLineNum, const CStringArray & aryItems);
	BOOL Process_CopyDirAndSubDirs	(const long iLineNum, const CStringArray & aryItems);
	BOOL Process_CreateNewDir		(const long iLineNum, const CStringArray & aryItems);

	eCSV_LINE_TYPE XLateLineType(const CString & strCsvIndicator) const;

private:
	CPfaMainSheet * GetMainSheet(void);

private:
	virtual bool DoCreateDirectory	(void);
	virtual bool DoEmptyDirectory	(void);
	virtual void OnNewDirectory		(const CString & strDir, const DWORD dwOPNumber, const DWORD dwStepNumber);
	virtual void ReportDIEvent		(const CFileCopyReport & report);
	virtual void ReportFCEvent		(const CFileCopyReport & report);

public:
	//void SetAppearance(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTFILEASSEMBLERDLG_H__E3A21396_C4B8_4E2C_8410_E04523C39293__INCLUDED_)
