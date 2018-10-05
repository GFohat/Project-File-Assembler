// ListSorter.cpp: implementation of the CListSorter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "ListSorter.h"

#include "PfaDataListItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListSorter::CListSorter()
:	m_bLastSortOrder		(true)
	, m_iLastSortCol		(-1)
	, m_iLastSortColFmt		(-1)
{

}

CListSorter::~CListSorter()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:		
	DESC:	
	IN:		
	OUT:	
*/
void CListSorter::SortTheList(
							CListCtrl & rListCtrl
							, const int iColumn
							, const bool bAscending
						)
{
	LVCOLUMN lvcolumn;
	lvcolumn.mask = LVCF_WIDTH | LVCF_FMT;

	BOOL bOK = rListCtrl.GetColumn(iColumn, &lvcolumn);
	_ASSERTE(bOK);

	int iColumnFormat = lvcolumn.fmt & LVCFMT_JUSTIFYMASK;

	SortTheList(rListCtrl, iColumn, iColumnFormat, bAscending);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/05/2007 07:36:15
	DESCRIP:	
	IN:
	OUT:
*/
void CListSorter::ReSortTheList(CListCtrl & rListCtrl)
{
	if(m_iLastSortCol < 0)
		m_iLastSortCol = 0;

	if(m_iLastSortColFmt < 0)
		m_iLastSortColFmt = LVCFMT_LEFT;

	SortTheList(rListCtrl, m_iLastSortCol, m_iLastSortColFmt, m_bLastSortOrder);
}
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:		
	DESC:	
	IN:		
	OUT:	
*/
void CListSorter::SortTheList(
							CListCtrl & rListCtrl
							, const int iColumn
							, const int iColumnFormat
							, const bool bAscending
						)
{
	CWaitCursor wait;

	m_bLastSortOrder	= bAscending;
	m_iLastSortCol		= iColumn;
	m_iLastSortColFmt	= iColumnFormat;

	rListCtrl.SendMessage(WM_SETREDRAW, FALSE, 0);
	CListSortParams * plistsort = new CListSortParams(rListCtrl, iColumn, iColumnFormat, bAscending);

	//ListView_SortItemsEx(pListCtrl->m_hWnd, ListItemCompareFuncEx, LPARAM(plistsort));
	rListCtrl.SortItems(ListItemCompareFunc, DWORD(plistsort));
	
	//MarkColumnSortOrder(pListCtrl, iColumn, bAscending);

	delete plistsort;
	rListCtrl.SendMessage(WM_SETREDRAW, TRUE, 0);
	//rListCtrl.UnlockWindowUpdate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:		
	DESC:	
	IN:		
	OUT:	
*/
/*static*/ 
//int CALLBACK CListSorter::ListItemCompareFunc001(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
//{
//	static BOOL bFirstTime = true;
//	static TCHAR szCurrencySymbol[10];
//
//	if(bFirstTime){
//		TRACE(_T("Looking up currency symbol...\n"));
//		int iRet = ::GetLocaleInfo(
//								LOCALE_USER_DEFAULT
//								, LOCALE_SCURRENCY
//								, szCurrencySymbol
//								, 9
//							);
//
//		if(iRet)
//			bFirstTime = false;
//	}
//
//	CListSortParams * pListSortParams = reinterpret_cast<CListSortParams *>(lParamSort);
//	
//	int iIndex1 = 0;
//	int iIndex2 = 0;
//
//	GetIndicesForListItemDatas(iIndex1, iIndex2, pListSortParams->GetListCtrl(), lParam1, lParam2);
//
//	CString str1 = pListSortParams->GetListCtrl().GetItemText(iIndex1, pListSortParams->GetColumn());
//	CString str2 = pListSortParams->GetListCtrl().GetItemText(iIndex2, pListSortParams->GetColumn());
//	
//	int iCompare = 0;
//	
//	//LVCFMT_LEFT LVCFMT_CENTER LVCFMT_RIGHT	
//	switch(pListSortParams->GetColumnFmt()){	//left / centre / right = string / date / number
//		case LVCFMT_LEFT:	//string
//		case LVCFMT_CENTER:	//date (as string)
//			//if(bAlphaSort_CaseSensitive)
//			//	iCompare = _tcscmp(str1, str2);
//			//else
//			iCompare = _tcsicmp(str1, str2);
//			break;
//
//		case LVCFMT_RIGHT:	//number
//			{
//				//in case it's currency, we need to strip off the '£' or whatever
//				str1.TrimLeft(szCurrencySymbol);
//				str2.TrimLeft(szCurrencySymbol);
//
//				long i1 = StringToLong(str1);
//				long i2 = StringToLong(str2);
//
//				if(i1 > i2)
//					iCompare = 1;
//				
//				else if(i1 == i2)
//					iCompare = 0;
//				
//				else if(i1 < i2)
//					iCompare = -1;
//			}
//			break;
//	}
//
//	if(!pListSortParams->GetAscending())
//		iCompare *= -1;
//
//	return iCompare;
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	17/04/2007 14:24:15
	DESCRIP:	

		The lParam1 and lParam2 parameters specify the item data for the two items being 
		compared. 
		
		The lParamSort parameter is the same as the dwData value.	
	IN:
	OUT:
*/
/*static*/ 
int CALLBACK CListSorter::ListItemCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	static bool bFirstTime = true;
	static TCHAR szCurrencySymbol[10];

	if(bFirstTime){
		int iRet = ::GetLocaleInfo(
								LOCALE_USER_DEFAULT
								, LOCALE_SCURRENCY
								, szCurrencySymbol
								, 9
							);

		if(iRet)
			bFirstTime = false;
	}

	CListSortParams *	pSortParams	= reinterpret_cast<CListSortParams *>	(lParamSort);
	CPfaDataListItem *	pData1		= reinterpret_cast<CPfaDataListItem *>	(lParam1);
	CPfaDataListItem *	pData2		= reinterpret_cast<CPfaDataListItem *>	(lParam2);

	int iCompare = pData1->Compare(*pData2, pSortParams->GetColumn(), pSortParams->GetColumnFmt());

//	CString str1 = pData1->GetItemText(pSortParams->GetColumn());
//	CString str2 = pData2->GetItemText(pSortParams->GetColumn());
//
//	int iCompare = 0;
//	
//	//LVCFMT_LEFT LVCFMT_CENTER LVCFMT_RIGHT	
//	switch(pSortParams->GetColumnFmt()){	//left / centre / right = string / date / number
//
//		case LVCFMT_LEFT:	//string
//		case LVCFMT_CENTER:	//date (as string - eg "2007-04-17 14:33")
//			iCompare = _tcsicmp(str1, str2);
//			break;
//
//		case LVCFMT_RIGHT:	//number
//			{
//				//in case it's currency, we need to strip off the '£' or whatever
//				str1.TrimLeft(szCurrencySymbol);
//				str2.TrimLeft(szCurrencySymbol);
//
//				long i1 = StringToLong(str1);
//				long i2 = StringToLong(str2);
//
//				if(i1 > i2)
//					iCompare = 1;
//				
//				else if(i1 == i2)
//					iCompare = 0;
//				
//				else if(i1 < i2)
//					iCompare = -1;
//			}
//			break;
//	}

	if(!pSortParams->GetAscending())
		iCompare *= -1;

	return iCompare;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:		
	DESC:	
	IN:		
	OUT:	
*/
/*static*/ 
//void CListSorter::GetIndicesForListItemDatas(
//											int & iIndex1
//											, int & iIndex2
//											, const CListCtrl & rListCtrl
//											, const DWORD_PTR dwItemData1
//											, const DWORD_PTR dwItemData2
//										)
//{
//
//	// D O   N O T  U S E  -  W A Y   T O O   S L O W
//
//	iIndex1 = -1;
//	iIndex2 = -1;
//
//	int iCount = rListCtrl.GetItemCount();
//	int iLoop = 0;
//	DWORD_PTR dwProbeData = 0L;
//
//	for(iLoop = 0 ; (iLoop < iCount) && ((iIndex1 < 0) || (iIndex2 < 0)) ; iLoop ++){
//
//		dwProbeData = rListCtrl.GetItemData(iLoop);
//		
//		if(dwProbeData == dwItemData1 && iIndex1 < 0){
//			iIndex1 = iLoop;
//		}
//		
//		if(dwProbeData == dwItemData2 && iIndex2 < 0){
//			iIndex2 = iLoop;
//		}
//	}
//
//	//_ASSERTE(iIndex1 >= 0);
//	//_ASSERTE(iIndex2 >= 0);
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:		
	DESC:	
	IN:		
	OUT:	
*/
/*static*/ 
long CListSorter::StringToLong(const CString & strLong)
{
	const static int iCOMPARE_EQUAL = 0L;
	long iRet = 0L;

	bool bIsHex = false;

	if(strLong.GetLength() > 2)
		if(strLong.Left(2).CompareNoCase(_T("0x")) == iCOMPARE_EQUAL)
			bIsHex = true;

	if(bIsHex){
		iRet = HexStringToLong(strLong);
	}
	else{
		iRet = _ttol(strLong);
	}

	return iRet;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	PGC Created: (vsn) 02/05/2003 20:42:22

	DESC:
	IN:
	OUT:
*/
/*static*/ 
long CListSorter::HexStringToLong(const CString & strHex)
{
	long iRet = 0L;
	int iLeng = strHex.GetLength();
	TCHAR chDigit = 0;
	DWORD dwMultiplier = 1L;
	long iHexByte = 0L;
	

	//don't include the "0x" at the start
	for(int iLoop = iLeng - 1 ; iLoop >= 0 ; iLoop--){

		chDigit		= strHex.GetAt(iLoop);
		iHexByte	= HexCharToLong(chDigit);

		iRet += (dwMultiplier * iHexByte);
		
		dwMultiplier *= 16;
	}

	return iRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	PGC Created: (vsn) 02/05/2003 20:42:19

	DESC:
	IN:
	OUT:
*/
/*static*/ 
long CListSorter::HexCharToLong(const TCHAR chHex)
{
	long iRet = 0L;

	switch(chHex){
		//case _T('0'):
		case _T('1'):
		case _T('2'):
		case _T('3'):
		case _T('4'):
		case _T('5'):
		case _T('6'):
		case _T('7'):
		case _T('8'):
		case _T('9'):
			iRet = chHex - _T('0');
			break;

		case _T('a'):	
		case _T('A'):	iRet = 10L;		break;
		case _T('b'):	
		case _T('B'):	iRet = 11L;		break;
		case _T('c'):	
		case _T('C'):	iRet = 12L;		break;
		case _T('d'):	
		case _T('D'):	iRet = 13L;		break;
		case _T('e'):	
		case _T('E'):	iRet = 14L;		break;
		case _T('f'):	
		case _T('F'):	iRet = 15L;		break;
	}

	return iRet;
}
