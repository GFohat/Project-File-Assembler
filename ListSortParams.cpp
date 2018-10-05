// ListSortParams.cpp: implementation of the CListSortParams class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "MFCFileCataloguer.h"
#include "ListSortParams.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListSortParams::CListSortParams(
								CListCtrl & rListCtrl
								, const int iColumn
								, const int iColumnFormat
								, const bool bAscending
							)
:	m_rListCtrl			(rListCtrl)
	, m_iColumn			(iColumn)
	, m_iColumnFormat	(iColumnFormat)
	, m_bAscending		(bAscending)
{
}

//CListSortParams::CListSortParams(
//								CListCtrl & rListCtrl
//								, const int iColumn
//								, const bool bAscending
//							)
//:	m_rListCtrl		(rListCtrl)
//	, m_iColumn		(iColumn)
//	, m_bAscending	(bAscending)
//{
//	LVCOLUMN lvcolumn;
//	lvcolumn.mask = LVCF_WIDTH | LVCF_FMT;
//
//	BOOL bOK = m_rListCtrl.GetColumn(m_iColumn, &lvcolumn);
//	_ASSERTE(bOK);
//
//	m_iColumnFormat = lvcolumn.fmt & LVCFMT_JUSTIFYMASK;
//}

CListSortParams::~CListSortParams()
{

}
