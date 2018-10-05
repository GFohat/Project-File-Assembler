// BuildListing.cpp : implementation file
//

#include "stdafx.h"
#include "Project File Assembler.h"
#include "BuildListing.h"

#include "ConstLists.h"
#include <fstream>
using namespace CONS_LISTS;

#include "dirbrowser.h"
using namespace DIR_BROWSER;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuildListing dialog


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	
	DESCRIP:	
	IN:
	OUT:
*/
CBuildListing::CBuildListing(CWnd* pParent /*=NULL*/)
	: CDialog(CBuildListing::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuildListing)
	m_EditDestDir = _T("");
	//}}AFX_DATA_INIT
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	
	DESCRIP:	
	IN:
	OUT:
*/
void CBuildListing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuildListing)
	DDX_Control(pDX, IDC_EDIT_DEST_DIR, m_EditDestinationDir);
	DDX_Control(pDX, IDC_EDIT_SOURCEDIR, m_EditSourceDir);
	DDX_Control(pDX, IDC_LBL_FILE_NAME, m_LblFileName);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
	DDX_Text(pDX, IDC_EDIT_DEST_DIR, m_EditDestDir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBuildListing, CDialog)
	//{{AFX_MSG_MAP(CBuildListing)
	ON_BN_CLICKED(IDC_BTN_FILE_NAME, OnBtnFileName)
	ON_BN_CLICKED(IDC_BTN_SOURCE, OnBtnSource)
	ON_BN_CLICKED(IDC_BTN_DEST_DIR, OnBtnDestDir)
	ON_BN_CLICKED(IDC_BTN_BUILD_LIST, OnBtnBuildList)
	ON_BN_CLICKED(IDC_BTN_SCAN_DIR, OnBtnScanDir)
	ON_BN_CLICKED(IDC_BTN_CHECK_ALL, OnBtnCheckAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuildListing message handlers

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	
	DESCRIP:	
	IN:
	OUT:
*/
void CBuildListing::OnBtnFileName() 
{
	const TCHAR szFILTER[] = _T("Comma Separated Values (*.csv)|*.csv|");
	m_listctrl.DeleteAllItems();
	
	CFileDialog fd( 
				false 
				, _T("csv")
				, _T("FileMove") 
				, OFN_HIDEREADONLY  | OFN_PATHMUSTEXIST
				, szFILTER 
				, this 
			);
	
	fd.m_ofn.lpstrInitialDir = _T("C:\\WINLINK\\Installation\\InstallShield 12");

	if( fd.DoModal() == IDOK )
	{
	
		m_strFilePath = fd.GetPathName();
		m_LblFileName.SetWindowText(m_strFilePath);

		CFileFind find;

		if(find.FindFile(m_strFilePath))
			::AfxMessageBox(
							m_strFilePath 
							+ _T(" already exists.\n")
							_T("This listing will be appended to the file.\n")
							_T("If this is not what you intended please select another file name.")
						);
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	
	DESCRIP:	
	IN:
	OUT:
*/
//void CBuildListing::OnBtnSource() 
//{
//	
//	CString		sFolder;
//	LPMALLOC	pMalloc;
//
//    // Gets the Shell's default allocator
//    if (::SHGetMalloc(&pMalloc) == NOERROR)
//    {
//        BROWSEINFO bi;
//        char pszBuffer[MAX_PATH];
//        LPITEMIDLIST pidl;
//
//        bi.hwndOwner = GetSafeHwnd();
//        bi.pidlRoot = ConvertPathToLpItemIdList("J:\\Winlink");
//        bi.pszDisplayName = pszBuffer;
//        bi.lpszTitle = _T("Select a directory...");
//        bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
//        bi.lpfn = NULL;
//        bi.lParam = 0;
//
//        // This next call issues the dialog box.
//        if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)
//        {
//            if (::SHGetPathFromIDList(pidl, pszBuffer))
//            { 
//	            // At this point pszBuffer contains the selected path
//				sFolder = pszBuffer;
//            }
//
//            // Free the PIDL allocated by SHBrowseForFolder.
//            pMalloc->Free(pidl);
//        }
//        // Release the shell's allocator.
//        pMalloc->Release();
//    }
//
//	m_EditSourceDir.SetWindowText(sFolder);
//	m_strSourcePath = sFolder;
//	
//	
//	
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10/03/2007 09:04:29
	DESCRIP:	
	IN:
	OUT:
*/
void CBuildListing::OnBtnSource() 
{
	
	CString		strFolder(_T("J:\\Winlink"));

//	LPMALLOC	pMalloc;
//
//    // Gets the Shell's default allocator
//    if (::SHGetMalloc(&pMalloc) == NOERROR)
//    {
//        BROWSEINFO bi;
//        char pszBuffer[MAX_PATH];
//        LPITEMIDLIST pidl;
//
//        bi.hwndOwner = GetSafeHwnd();
//        bi.pidlRoot = ConvertPathToLpItemIdList("J:\\Winlink");
//        bi.pszDisplayName = pszBuffer;
//        bi.lpszTitle = _T("Select a directory...");
//        bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
//        bi.lpfn = NULL;
//        bi.lParam = 0;
//
//        // This next call issues the dialog box.
//        if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)
//        {
//            if (::SHGetPathFromIDList(pidl, pszBuffer))
//            { 
//	            // At this point pszBuffer contains the selected path
//				sFolder = pszBuffer;
//            }
//
//            // Free the PIDL allocated by SHBrowseForFolder.
//            pMalloc->Free(pidl);
//        }
//        // Release the shell's allocator.
//        pMalloc->Release();
//    }

	CDirBrowser browser;
	browser.BrowseForDirectory(_T("Select a directory"), strFolder);

	m_EditSourceDir.SetWindowText(strFolder);
	m_strSourcePath = strFolder;
	
	
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	
	DESCRIP:	
	IN:
	OUT:
*/
void CBuildListing::OnBtnDestDir() 
{
	CString		strFolder(_T("C:\\WinLink\\Installation\\InstallShield 12"));

//	LPMALLOC	pMalloc;
//
//    // Gets the Shell's default allocator
//    if (::SHGetMalloc(&pMalloc) == NOERROR)
//    {
//        BROWSEINFO bi;
//        char pszBuffer[MAX_PATH];
//        LPITEMIDLIST pidl;
//
//        bi.hwndOwner = GetSafeHwnd();
//        bi.pidlRoot = ConvertPathToLpItemIdList("C:\\WINLINK\\Installation\\INSTALLSHIELD 10");
//        bi.pszDisplayName = pszBuffer;
//        bi.lpszTitle = _T("Select a directory...");
//        bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
//        bi.lpfn = NULL;
//        bi.lParam = 0;
//
//        // This next call issues the dialog box.
//        if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)
//        {
//            if (::SHGetPathFromIDList(pidl, pszBuffer))
//            { 
//	            // At this point pszBuffer contains the selected path
//				sFolder = pszBuffer;
//            }
//
//            // Free the PIDL allocated by SHBrowseForFolder.
//            pMalloc->Free(pidl);
//        }
//        // Release the shell's allocator.
//        pMalloc->Release();
//    }

	CDirBrowser browser;
	browser.BrowseForDirectory(_T("Select a directory"), strFolder);

	m_EditDestinationDir.SetWindowText(strFolder);
	m_strDestPath = strFolder;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	
	DESCRIP:	
	IN:
	OUT:
*/
void CBuildListing::OnBtnBuildList() 
{
	
	if(m_strFilePath.GetLength() == 0 || m_strSourcePath.GetLength() == 0 || m_strDestPath.GetLength() == 0)
	{
		AfxMessageBox(L"One or more values has not been set");
		return;
	}
	std::ofstream f1(m_strFilePath, std::ios::app);

	if(!f1)
	{
		AfxMessageBox("Could not open " + m_strFilePath + " for writing");
		return;
	}

	f1<<"# FILE,SOURCE,DESTINATION,COPIED NAME\n";
	f1<<"#\n";
	int nItem = 0; //Represents the row number inside CListCtrl
	  for(nItem =0 ; nItem <  m_listctrl.GetItemCount(); nItem++)
	  {
		 
		 BOOL bChecked =  m_listctrl.GetCheck(nItem);
		 if( bChecked != 0 )
		 {
			 CString strLine =  m_listctrl.GetItemText(nItem, 0);
			 CString str = strLine + ","+ m_strSourcePath + "," + m_strDestPath + "," + strLine + "\n";
			
			f1<<(char *) (LPCTSTR) str;
		
		

		 }
		 
	  }

	  f1.close();
	  AfxMessageBox(L"List Built");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CBuildListing::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitList();

	return true;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10/03/2007 07:10:15
	DESCRIP:	
	IN:
	OUT:
*/
void CBuildListing::InitList(void)
{
	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_listctrl);
	ListView_SetExtendedListViewStyle(m_listctrl, dwStyle | LVS_EX_CHECKBOXES);

	//m_listctrl.InsertColumn(0,"File");
	//m_listctrl.InsertColumn(1,"Source");
	//m_listctrl.InsertColumn(2,"Destination");

	for(DWORD dwCol = 0L ; dwCol < eBLC__LAST ; dwCol++){
		m_listctrl.InsertColumn(
							dwCol
							, szsCOL_NAMES_BUILDLIST	[dwCol]
							, isCOL_FMTS_BUILDLIST		[dwCol]
						);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	
	DESCRIP:	
	IN:
	OUT:
*/
void CBuildListing::OnBtnScanDir() 
{
	m_listctrl.DeleteAllItems();
	CFileFind finder;
	int row = 0;
	BOOL bWorking = finder.FindFile(m_strSourcePath+ "\\*.*");
	while(bWorking)
	{
		bWorking = finder.FindNextFile();
		CString str =  finder.GetFileName();

		if(finder.IsDots()||finder.IsDirectory())
			continue;
		
		m_listctrl.InsertItem(row + 1,str);
		m_listctrl.SetItemText(row,1,m_strSourcePath);
		m_listctrl.SetItemText(row,2,m_strDestPath);

		row++;
		
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	
	DESCRIP:	
	IN:
	OUT:
*/
void CBuildListing::OnBtnCheckAll() 
{
	int nItem = 0; //Represents the row number inside CListCtrl
      for(nItem =0 ; nItem <  m_listctrl.GetItemCount(); nItem++)
      {
         m_listctrl.SetCheck(nItem);
      }	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	
	DESCRIP:	
	IN:
	OUT:
*/
LPITEMIDLIST CBuildListing::ConvertPathToLpItemIdList(const char *pszPath)
{
	LPITEMIDLIST  pidl;
    LPSHELLFOLDER pDesktopFolder;
    OLECHAR       olePath[MAX_PATH];
    ULONG         chEaten;
    ULONG         dwAttributes;
    HRESULT       hr;

    if (SUCCEEDED(SHGetDesktopFolder(&pDesktopFolder)))
    {
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszPath, -1, olePath, 
                            MAX_PATH);
        hr = pDesktopFolder->ParseDisplayName(NULL,NULL,olePath,&chEaten,
                                              &pidl,&dwAttributes);
        pDesktopFolder->Release();
    }
    return pidl;
}
