// ListGeneralFiles.cpp: implementation of the CListGeneralFiles class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "ListGeneralFiles.h"

#include "ConstLists.h"
using namespace CONS_LISTS;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListGeneralFiles::CListGeneralFiles()
{

}

CListGeneralFiles::~CListGeneralFiles()
{

}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/04/2007 13:55:02
	DESCRIP:	
	IN:
	OUT:
*/
void CListGeneralFiles::InitGenFileList(CListCtrl & rList, CFont * pFont)
{
	DWORD dwExStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP;

	rList.SetExtendedStyle	(dwExStyle);
	rList.SetFont			(pFont);
	rList.DeleteAllItems	();

	//int nCol, LPCTSTR lpszColumnHeading, int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1 
	for(DWORD dwCol = 0L ; dwCol < eGFC__LAST ; dwCol ++){
		rList.InsertColumn(
						dwCol
						, szsCOL_NAMES_GENERAL_FILES	[dwCol]
						, isCOL_FMTS_GENERAL_FILES		[dwCol]
					);
	}

	SetListWids(rList);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/04/2007 14:02:16
	DESCRIP:	
	IN:
	OUT:
*/
void CListGeneralFiles::SetListWids(CListCtrl & rList)
{
	for(DWORD dwCol = 0L ; dwCol < eGFC__LAST ; dwCol ++){
		rList.SetColumnWidth(dwCol, LVSCW_AUTOSIZE_USEHEADER);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/04/2007 14:05:54
	DESCRIP:	
	IN:
	OUT:
*/
void CListGeneralFiles::AddGenFileListItem(
										CListCtrl & rList
										, const WIN32_FIND_DATA & data
										, const CString & strName
									)
{
	int iCur = rList.GetItemCount();
	int iNew = rList.InsertItem(iCur, _T(""));

	CString strMod;
	CString strSize;

	//	eGFC_NamePath		= 0
	//	, eGFC_LastMod
	//	, eGFC_Size
	SYSTEMTIME dtsys;
	::FileTimeToSystemTime(&(data.ftLastWriteTime), &dtsys);

	strMod.Format(
				_T("%04i-%02i-%02i %02i:%02i:%02i")
				, dtsys.wYear, dtsys.wMonth, dtsys.wDay
				, dtsys.wHour, dtsys.wMinute, dtsys.wSecond
			);

	LARGE_INTEGER liFileSize;
	liFileSize.LowPart = data.nFileSizeLow;
	liFileSize.HighPart = data.nFileSizeHigh;

	strSize.Format(_T("%I64i"), liFileSize.QuadPart);
	
	rList.SetItemText(iNew, eGFC_NamePath,	strName);
	rList.SetItemText(iNew, eGFC_LastMod,	strMod);
	rList.SetItemText(iNew, eGFC_Size,		strSize);

	rList.SetItemData(iNew, iNew);
}

