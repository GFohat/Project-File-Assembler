// DlgAddFiles.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "DlgAddFiles.h"

#include "ConstLists.h"
using namespace CONS_LISTS;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddFiles dialog


CDlgAddFiles::CDlgAddFiles(CWnd* pParent /*=NULL*/)
:	CDialog				(CDlgAddFiles::IDD, pParent)
	, m_pStepHolder		(0)
	, m_dwProjID		(0L)
	, m_iStartStepNum	(-1L)
{
	//{{AFX_DATA_INIT(CDlgAddFiles)
	m_strCurDir = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAddFiles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddFiles)
	DDX_Control(pDX, IDC_LIST_CUR_FILES, m_listCurFiles);
	DDX_Control(pDX, IDC_ED_CUR_DIR, m_edCurDir);
	DDX_Text(pDX, IDC_ED_CUR_DIR, m_strCurDir);
	DDV_MaxChars(pDX, m_strCurDir, 256);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddFiles, CDialog)
	//{{AFX_MSG_MAP(CDlgAddFiles)
	ON_BN_CLICKED(IDC_BN_BROWSE, OnBnBrowse)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CUR_FILES, OnClickListCurFiles)
	ON_BN_CLICKED(IDC_BN_SEL_ALL, OnBnSelAll)
	ON_BN_CLICKED(IDC_BN_SEL_NONE, OnBnSelNone)
	ON_BN_CLICKED(IDC_BN_SEL_INVERT, OnBnSelInvert)
	ON_BN_CLICKED(IDC_BN_SEL_HIGHLIGHTED, OnBnSelHighlighted)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_CUR_FILES, OnColumnclickListCurFiles)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST_CUR_FILES, OnDeleteitemListCurFiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddFiles message handlers

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 08:04:27
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CDlgAddFiles::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CDC * pdc = GetDC();
	CPropSheetCommon::InitFonts(pdc);
	ReleaseDC(pdc);

	InitList();
	InitEdBox();

	GetDlgItem(IDC_BN_SEL_ALL)			->SetFont(CPropSheetCommon::GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_BN_SEL_NONE)			->SetFont(CPropSheetCommon::GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_BN_SEL_INVERT)		->SetFont(CPropSheetCommon::GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_BN_SEL_HIGHLIGHTED)	->SetFont(CPropSheetCommon::GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_BN_BROWSE)			->SetFont(CPropSheetCommon::GetTheFont(eFont_Buttons));
	
	GetDlgItem(IDOK)					->SetFont(CPropSheetCommon::GetTheFont(eFont_Buttons));
	GetDlgItem(IDCANCEL)				->SetFont(CPropSheetCommon::GetTheFont(eFont_Buttons));

	RefreshFileList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 08:05:37
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::InitList(void)
{
	DWORD dwExStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP | LVS_EX_CHECKBOXES;

	m_listCurFiles.SetExtendedStyle(dwExStyle);
	m_listCurFiles.SetFont(CPropSheetCommon::GetTheFont(eFont_List));

	for(DWORD dwLoop = 0L ; dwLoop < eAFCol__LAST ; dwLoop++){
		m_listCurFiles.InsertColumn(
									dwLoop
									, szsCOL_NAMES_ADDFILES_DATA		[dwLoop]
									, isCOL_FMTS_ADDFILES_DATA		[dwLoop]
								);
	}

	CHeaderCtrl * pHdr = m_listCurFiles.GetHeaderCtrl();

	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		pHdr->SetFont(CPropSheetCommon::GetTheFont(eFont_ListHeader));
	}

	SetListColWidths();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 08:05:33
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::InitEdBox(void)
{
	m_edCurDir.SetFont(CPropSheetCommon::GetTheFont(eFont_EdBoxes));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/03/2007 07:57:28
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::SetListColWidths(void)
{
	CHeaderCtrl * pHdr = m_listCurFiles.GetHeaderCtrl();

	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		for(DWORD dwLoop = 0L ; dwLoop < DWORD(pHdr->GetItemCount()) ; dwLoop++){
			m_listCurFiles.SetColumnWidth(dwLoop, LVSCW_AUTOSIZE_USEHEADER);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 08:04:25
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::OnBnBrowse() 
{
	CString strBrowsed = m_strCurDir;

	bool bOK = CPropSheetCommon::BrowseForDirectory(_T("Choose a directory"), strBrowsed);

	if(bOK){
		m_strCurDir = strBrowsed;
		UpdateData(FALSE);
		RefreshFileList();
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 08:42:34
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::RefreshFileList(void)
{
	CWaitCursor wait;

	m_listCurFiles.SendMessage(WM_SETREDRAW, FALSE, 0);
	m_listCurFiles.DeleteAllItems();

	EnumFiles(m_strCurDir);

	m_listCurFiles.SendMessage(WM_SETREDRAW, TRUE, 0);
	m_listCurFiles.Invalidate();

	SetListColWidths();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 15:09:59
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::EnumFiles(const CString & strRootDir)
{
	CString strWild;
	strWild.Format(_T("%s\\*.*"), strRootDir);

	WIN32_FIND_DATA data;
	CString strFound;

	HANDLE hFind = ::FindFirstFile(strWild, &data);

	//If the function fails, the return value is INVALID_HANDLE_VALUE
	if(INVALID_HANDLE_VALUE != hFind){
		
		do{
			strFound.Format(_T("%s\\%s"), strRootDir, data.cFileName);

			if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){

				if(strFound.Right(3) != _T("\\.."))
					if(strFound.Right(2) != _T("\\."))
						EnumFiles(strFound);

			}
			else{
				AddFileListItem(strFound);
			}

		}while(::FindNextFile(hFind, &data));

		::FindClose(hFind);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 08:53:02
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::AddFileListItem(const CString & strFile)
{
	TCHAR szDrive	[_MAX_DRIVE]	= {0};
	TCHAR szDir		[_MAX_DIR]		= {0};
	TCHAR szFName	[_MAX_FNAME]	= {0};
	TCHAR szFExt	[_MAX_EXT]		= {0};

	_tsplitpath(strFile, szDrive, szDir, szFName, szFExt);

	CString strFileName;
	CString strDirectory;
	CString strExtension(szFExt);

	strFileName.Format(_T("%s%s"), szFName, szFExt);
	strDirectory.Format(_T("%s%s"), szDrive, szDir);
	strDirectory.TrimRight(_T("\\"));

	int iCur = m_listCurFiles.GetItemCount();
	int iNew = m_listCurFiles.InsertItem(iCur, _T(""));

	m_listCurFiles.SetItemText(iNew, eAFCol_FileName,	strFileName);
	m_listCurFiles.SetItemText(iNew, eAFCol_FileExt,	strExtension);
	m_listCurFiles.SetItemText(iNew, eAFCol_Directory,	strDirectory);

	CFileListItemData * pData = new CFileListItemData(m_listCurFiles, iNew);

	m_listCurFiles.SetItemData(iNew, reinterpret_cast<DWORD>(pData));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/05/2007 10:34:23
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::OnDeleteitemListCurFiles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLISTVIEW* pNMListView = reinterpret_cast<NMLISTVIEW*>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(pNMListView){
	
		CFileListItemData * pData = reinterpret_cast<CFileListItemData *>(pNMListView->lParam);
		ATLASSERT(pData);

		if(pData){
			delete pData;
			pData = 0;
		}

	}
	
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 08:34:12
	DESCRIP:	
	IN:
	OUT:
*/
INT_PTR CDlgAddFiles::DoModal(
							const CString & strStartDir
							, const long iStartStep
							, const DWORD dwProjID
							, CPfaStepHolder & stepholder
						)
{
	m_strCurDir		= strStartDir;
	m_pStepHolder	= &(stepholder);
	m_iStartStepNum	= iStartStep;
	m_dwProjID		= dwProjID;

	m_pStepHolder->DeleteAll();

	INT_PTR iReply = CDialog::DoModal();

	//if(m_straryFileList.GetSize() < 1)
	//	iReply = IDCANCEL;

	if( ! m_pStepHolder->GetStepList().size())
		iReply = IDCANCEL;

	return iReply;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 09:06:25
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::OnClickListCurFiles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

// 	NMLISTVIEW * pNmLv = reinterpret_cast<NMLISTVIEW *>(pNMHDR);
// 
// 	BOOL bChecked = m_listCurFiles.GetCheck(pNmLv->iItem);
// 
// 	UINT uHitFlags = 0L;
// 	int iHit = m_listCurFiles.HitTest(pNmLv->ptAction, &uHitFlags);
// 	
// 	if((LVHT_ONITEMICON & uHitFlags) || (LVHT_ONITEMLABEL & uHitFlags)){
// 		bChecked = ! bChecked;
// 		m_listCurFiles.SetCheck(pNmLv->iItem, bChecked);
// 	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 09:43:49
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::OnOK() 
{
	const long iMAXLIST = m_listCurFiles.GetItemCount();

	BOOL bChecked = FALSE;
	CPfaStep stepadd;
	bool bAddOK = false;

	for(long iItem = 0L ; iItem < iMAXLIST ; iItem ++){

		bChecked = m_listCurFiles.GetCheck(iItem);

		if(bChecked){

			//the caller is responsible for destination directory
			stepadd.SetSrcDir			(m_listCurFiles.GetItemText(iItem, eAFCol_Directory));
			stepadd.SetSrcFile			(m_listCurFiles.GetItemText(iItem, eAFCol_FileName));
			stepadd.SetDestFile			(m_listCurFiles.GetItemText(iItem, eAFCol_FileName));
			stepadd.SetStepType			(ePST_CopyFile);
			stepadd.SetProjectID		(m_dwProjID);
			stepadd.SetProjectStep		(m_iStartStepNum + iItem);

			bAddOK = m_pStepHolder->AddPfaStep(stepadd);
			ATLASSERT(bAddOK);
		}
	}

	
	CDialog::OnOK();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 10:41:53
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::OnBnSelAll() 
{
	CListTickSetter::SetTicksAll(m_listCurFiles);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 10:41:50
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::OnBnSelNone() 
{
	CListTickSetter::SetTicksNone(m_listCurFiles);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 10:41:48
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::OnBnSelInvert() 
{
	CListTickSetter::SetTicksInvert(m_listCurFiles);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 09:13:28
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::OnBnSelHighlighted() 
{
	CListTickSetter::SetTicksHighlighted(m_listCurFiles);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/05/2007 09:58:53
	DESCRIP:	
	IN:
	OUT:
*/
void CDlgAddFiles::OnColumnclickListCurFiles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	static bool bAscending = false;
	bAscending = ! bAscending;

	NMLISTVIEW* pNMListView = reinterpret_cast<NMLISTVIEW*>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	if(pNMListView){
		LVCOLUMN lvcolumn;
		::ZeroMemory(&lvcolumn, sizeof(LVCOLUMN));

		lvcolumn.mask = LVCF_FMT;
		m_listCurFiles.GetColumn(pNMListView->iSubItem, &lvcolumn);

		
		CFileListSortParams params(*pNMListView, bAscending, (lvcolumn.fmt & LVCFMT_JUSTIFYMASK));

		DWORD dwData = reinterpret_cast<DWORD>(&params);
		m_listCurFiles.SortItems(FileListCompareFunc001, dwData);
	}
	
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/05/2007 10:02:29
	DESCRIP:	
	
	IN:
		The lParam1 and lParam2 parameters specify the item data for the two items being compared. 
		The lParamSort parameter is the same as the application-passed dwData value.

	OUT:
		The comparison function must return:
		a negative value if the first item should precede the second, 
		a positive value if the first item should follow the second, or 
		zero if the two items are equivalent.
*/
int CALLBACK CDlgAddFiles::FileListCompareFunc001(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int iCmp = 0;

	CFileListSortParams *	pSortParams		= reinterpret_cast<CFileListSortParams *>	(lParamSort);
	CFileListItemData *		pData1			= reinterpret_cast<CFileListItemData *>		(lParam1);
	CFileListItemData *		pData2			= reinterpret_cast<CFileListItemData *>		(lParam2);
	ATLASSERT(pSortParams && pData1 && pData2);

	if(pSortParams && pData1 && pData2){

		iCmp = pData1->Compare(
							*pData2
							, pSortParams->GetSortColumn()
							, pSortParams->GetColumnFmt()
						);

		if( ! pSortParams->GetAscending())
			iCmp *= -1;
	}

	return iCmp;
}
