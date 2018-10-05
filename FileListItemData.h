// FileListItemData.h: interface for the CFileListItemData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILELISTITEMDATA_H__DE3B8A42_2F44_4109_B744_AD6510098A4D__INCLUDED_)
#define AFX_FILELISTITEMDATA_H__DE3B8A42_2F44_4109_B744_AD6510098A4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CompareHelp.h"

class CFileListItemData  
:	public CCompareHelp
{
public:
	CFileListItemData(CListCtrl & rList, const DWORD dwItem);
	virtual ~CFileListItemData();

public:
	CString GetTextAt(const int iColumn) const;

	int Compare(
				const CFileListItemData & that
				, const int iColumn
				, const int iColFmt
			) const;

private:
	CStringArray m_straryFieldTexts;
};

#endif // !defined(AFX_FILELISTITEMDATA_H__DE3B8A42_2F44_4109_B744_AD6510098A4D__INCLUDED_)
