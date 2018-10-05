// FileListItemData.cpp: implementation of the CFileListItemData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "FileListItemData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileListItemData::CFileListItemData(CListCtrl & rList, const DWORD dwItem)
{
	DWORD dwColumnCount = 0L;

	CHeaderCtrl * pHdr = rList.GetHeaderCtrl();
	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		dwColumnCount = pHdr->GetItemCount();
	}

	for(DWORD dwColumn = 0L ; dwColumn < dwColumnCount ; dwColumn++){
		m_straryFieldTexts.Add(rList.GetItemText(dwItem, dwColumn));
	}
}

CFileListItemData::~CFileListItemData()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/05/2007 14:43:49
	DESCRIP:	
	IN:
	OUT:
*/
CString CFileListItemData::GetTextAt(const int iColumn) const
{
	CString strRet(_T("<Invalid>"));
	ATLASSERT(iColumn < m_straryFieldTexts.GetSize());

	if(iColumn < m_straryFieldTexts.GetSize())
		strRet = m_straryFieldTexts.GetAt(iColumn);

	return strRet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/05/2007 09:25:25
	DESCRIP:	
	IN:
	OUT:
		a negative value if the first item should precede the second, 
		a positive value if the first item should follow the second, or 
		zero if the two items are equivalent.
*/
int CFileListItemData::Compare(
							const CFileListItemData & that
							, const int iColumn
							, const int iColFmt
						) const
{
	int iCmp = 0;

	CString strText1 = GetTextAt(iColumn);
	CString strText2 = that.GetTextAt(iColumn);

	switch(iColFmt){
		case LVCFMT_LEFT:
		case LVCFMT_CENTER:
			iCmp = strText1.CompareNoCase(strText2);
			break;

		case LVCFMT_RIGHT:
			iCmp = CCompareHelp::CompareNumeric(strText1, strText2);
			break;

		default:
			ATLASSERT(false);
			break;
	}

	return iCmp;
}

