// ListSorter.h: interface for the CListSorter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTSORTER_H__FF8FD687_88FF_4EFD_942B_A40E8F654523__INCLUDED_)
#define AFX_LISTSORTER_H__FF8FD687_88FF_4EFD_942B_A40E8F654523__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ListSortParams.h"

class CListSorter  
{
public:
	CListSorter();
	virtual ~CListSorter();

protected:
	void SortTheList(
					CListCtrl & rListCtrl
					, const int iColumn
					, const bool bAscending
				);

	void SortTheList(
					CListCtrl & rListCtrl
					, const int iColumn
					, const int iColumnFormat
					, const bool bAscending
				);

	void ReSortTheList(CListCtrl & rListCtrl);

private:
	bool	m_bLastSortOrder;
	int		m_iLastSortCol;
	int		m_iLastSortColFmt;

private:
	//static int CALLBACK		ListItemCompareFunc001		(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	//static void GetIndicesForListItemDatas(int & iIndex1, int & iIndex2, const CListCtrl & rListCtrl, const DWORD_PTR dwItemData1, const DWORD_PTR dwItemData2);

	static int CALLBACK	ListItemCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	static long StringToLong	(const CString & strLong);
	static long HexStringToLong	(const CString & strHex);
	static long HexCharToLong	(const TCHAR chHex);
};

#endif // !defined(AFX_LISTSORTER_H__FF8FD687_88FF_4EFD_942B_A40E8F654523__INCLUDED_)
