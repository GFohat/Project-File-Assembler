// PageInstallShield.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "PageInstallShield.h"

#include "ConstInstallShield.h"
using namespace CONS_INSTALLSHIELD;

#include "PfaMainSheet.h"

#include "ConstLists.h"
using namespace CONS_LISTS;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageInstallShield property page

IMPLEMENT_DYNCREATE(CPageInstallShield, CPropertyPage)

CPageInstallShield::CPageInstallShield() 
:	CPropertyPage			(CPageInstallShield::IDD)
	, CBrushHolder			(CONS_COLOURS::crefPAGE_BACK)
{
	//{{AFX_DATA_INIT(CPageInstallShield)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageInstallShield::~CPageInstallShield()
{
}

void CPageInstallShield::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageInstallShield)
	DDX_Control	(pDX,	IDC_LCTRL_IS_MEDIA,		m_lctrlISMedia);
	DDX_Control	(pDX,	IDC_LCTRL_IS_PROJECTS,	m_lctrlISProjects);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageInstallShield, CPropertyPage)
	//{{AFX_MSG_MAP(CPageInstallShield)
	ON_BN_CLICKED	(IDC_RDO_IS_10,		OnRdoIs10)
	ON_BN_CLICKED	(IDC_RDO_IS_12,		OnRdoIs12)
	ON_BN_CLICKED	(IDC_BN_LAUNCH_IS,	OnBnLaunchIs)
	ON_BN_CLICKED	(IDC_BN_EXPLORE,	OnBnExplore)
	ON_WM_CTLCOLOR	()
	//}}AFX_MSG_MAP

	ON_MESSAGE	(eWM_SET_APPEARANCE,			OnWMSetAppearance)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageInstallShield message handlers

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 07:32:30
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageInstallShield::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	InitLists();

	PopulateProjectList(szsIS_ROOT_DIR[eISVer_Twelve]);

	CButton * pBtn = reinterpret_cast<CButton *>(GetDlgItem(IDC_RDO_IS_12));
	if(pBtn && ::IsWindow(pBtn->m_hWnd))
		pBtn->SetCheck(BST_CHECKED);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 11:06:33
	DESCRIP:	
	IN:
	OUT:
*/
LPARAM CPageInstallShield::OnWMSetAppearance(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_RDO_IS_10)		->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_RDO_IS_12)		->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_BN_LAUNCH_IS)	->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));
	GetDlgItem(IDC_BN_EXPLORE)		->SetFont(GetMainSheet()->GetTheFont(eFont_Buttons));

	return TRUE;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 12:18:01
	DESCRIP:	
	IN:
	OUT:
*/
LRESULT CPageInstallShield::OnWMRearrangeControls(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 07:56:02
	DESCRIP:	
	IN:
	OUT:
*/
void CPageInstallShield::InitLists(void)
{
	CListGeneralFiles::InitGenFileList(m_lctrlISMedia, GetMainSheet()->GetTheFont(eFont_List));
	CListGeneralFiles::InitGenFileList(m_lctrlISProjects, GetMainSheet()->GetTheFont(eFont_List));

	CHeaderCtrl * pHdr = m_lctrlISMedia.GetHeaderCtrl();
	ATLASSERT(pHdr && ::IsWindow(pHdr->m_hWnd));

	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		pHdr->SetFont(GetMainSheet()->GetTheFont(eFont_ListHeader));
	}

	pHdr = m_lctrlISProjects.GetHeaderCtrl();
	ATLASSERT(pHdr && ::IsWindow(pHdr->m_hWnd));

	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		pHdr->SetFont(GetMainSheet()->GetTheFont(eFont_ListHeader));
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 07:32:27
	DESCRIP:	
	ePage_PfaDlg				= 0
	, ePage_PfaData
	, ePage_InstallShield
	, ePage_BatFiles
	IN:
	OUT:
*/
BOOL CPageInstallShield::OnSetActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_InstallShield, TRUE);
	return CPropertyPage::OnSetActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 07:32:25
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageInstallShield::OnKillActive() 
{
	GetParent()->PostMessage(eWM_PAGE_ACTIVATED, ePage_InstallShield, FALSE);
	
	return CPropertyPage::OnKillActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 07:32:40
	DESCRIP:	
	IN:
	OUT:
*/
void CPageInstallShield::OnRdoIs10() 
{
	m_lctrlISMedia.DeleteAllItems();
	m_lctrlISProjects.DeleteAllItems();

	PopulateProjectList(szsIS_ROOT_DIR[eISVer_Ten]);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 07:32:44
	DESCRIP:	
	IN:
	OUT:
*/
void CPageInstallShield::OnRdoIs12() 
{
	m_lctrlISMedia.DeleteAllItems();
	m_lctrlISProjects.DeleteAllItems();
	
	PopulateProjectList(szsIS_ROOT_DIR[eISVer_Twelve]);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 07:43:31
	DESCRIP:	
	IN:
	OUT:
*/
void CPageInstallShield::PopulateProjectList(const CString & strRootDir)
{
	CString strWild;
	strWild.Format(_T("%s\\*.*"), strRootDir);

	WIN32_FIND_DATA data;
	
	HANDLE hFind = ::FindFirstFile(strWild, &data);

	if(hFind && (INVALID_HANDLE_VALUE != hFind)){

		do{
			if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				HandleFoundDirectory(strRootDir, data.cFileName, data);

			else
				HandleFoundFile(strRootDir, data.cFileName, data);

		}while(::FindNextFile(hFind, &data));

		::FindClose(hFind);
	}

	SetListWids(m_lctrlISMedia);
	SetListWids(m_lctrlISProjects);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 07:49:38
	DESCRIP:	
	IN:
	OUT:
*/
void CPageInstallShield::HandleFoundDirectory(
											const CString & strRootDir
											, const CString & strFound
											, const WIN32_FIND_DATA & data
										)
{
	if(0 == _tcsicmp(strFound, _T(".")))
		return;

	if(0 == _tcsicmp(strFound, _T("..")))
		return;

	CString strNewRoot;
	strNewRoot.Format(_T("%s\\%s"), strRootDir, strFound);

	if(0 == strFound.CompareNoCase(_T("Media"))){
		CListGeneralFiles::AddGenFileListItem(m_lctrlISMedia, data, strNewRoot);
	}
	else{
		PopulateProjectList(strNewRoot);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 07:49:41
	DESCRIP:	
	IN:
	OUT:
*/
void CPageInstallShield::HandleFoundFile(
									const CString & strRootDir
									, const CString & strFound
									, const WIN32_FIND_DATA & data
								)
{
	CString strNAP;

	strNAP.Format(_T("%s\\%s"), strRootDir, strFound);

	TCHAR szExt[_MAX_EXT] = {0};

	_tsplitpath(strNAP, 0, 0, 0, szExt);

	if(0 == _tcsicmp(szExt, szISPROJ_EXT)){
		CListGeneralFiles::AddGenFileListItem(m_lctrlISProjects, data, strNAP);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 07:58:34
	DESCRIP:	
	IN:
	OUT:
*/
void CPageInstallShield::OnBnLaunchIs() 
{
	int iSel = m_lctrlISProjects.GetSelectionMark();

	if(iSel >= 0){
		CString strProject = m_lctrlISProjects.GetItemText(iSel, eGFC_NamePath);

		HINSTANCE hinst = ::ShellExecute(
										0
										, _T("open")
										, strProject
										, 0		//params
										, 0		//directory
										, SW_MAXIMIZE	//show cmd
									);

		//Returns a value greater than 32 if successful
		//The only thing that can be done with the returned HINSTANCE is 
		//to cast it to an int and compare it with the value 32 or one of the error codes

		int iRet = int(hinst);

		if(iRet <= 32){
			::AfxMessageBox(_T("Error opening file:\n") + strProject);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 08:40:33
	DESCRIP:	
	IN:
	OUT:
*/
void CPageInstallShield::OnBnExplore() 
{
	int iSel = m_lctrlISMedia.GetSelectionMark();

	if(iSel >= 0){
		CString strDir = m_lctrlISMedia.GetItemText(iSel, eGFC_NamePath);

		HINSTANCE hinst = ::ShellExecute(
										0
										, _T("explore")
										, strDir
										, 0		//params
										, 0		//directory
										, SW_RESTORE	//show cmd
									);

		//Returns a value greater than 32 if successful
		//The only thing that can be done with the returned HINSTANCE is 
		//to cast it to an int and compare it with the value 32 or one of the error codes

		int iRet = int(hinst);

		if(iRet <= 32){
			::AfxMessageBox(_T("Error opening file:\n") + strDir);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 09:18:20
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageInstallShield::DestroyWindow() 
{
	return CPropertyPage::DestroyWindow();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 10:50:00
	DESCRIP:	
	IN:
	OUT:
*/
CPfaMainSheet * CPageInstallShield::GetMainSheet(void)
{
	CPfaMainSheet * pSheet = reinterpret_cast<CPfaMainSheet *>(GetParent());
	ATLASSERT(pSheet && ::IsWindow(pSheet->m_hWnd));
	return pSheet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 08:00:27
	DESCRIP:	
	IN:
	OUT:
*/
void CPageInstallShield::OnOK() 
{
	ATLTRACE(_T("CPageInstallShield::OnOK\n"));	
	
	CPropertyPage::OnOK();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 08:00:25
	DESCRIP:	
	IN:
	OUT:
*/
void CPageInstallShield::OnCancel() 
{
	ATLTRACE(_T("CPageInstallShield::OnCancel\n"));	
	
	CPropertyPage::OnCancel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/04/2007 12:26:31
	DESCRIP:	
	IN:
	OUT:
*/
HBRUSH CPageInstallShield::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return CBrushHolder::GetBrush(hbr);
}
