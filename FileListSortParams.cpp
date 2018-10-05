// FileListSortParams.cpp: implementation of the CFileListSortParams class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "FileListSortParams.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileListSortParams::CFileListSortParams(
										const NMLISTVIEW & rNMLV
										, const bool bAscending
										, const int iColFmt
									)
:	m_iSortColumn	(rNMLV.iSubItem)
	, m_bAscending	(bAscending)
	, m_iColFormat	(iColFmt)
{
}

CFileListSortParams::~CFileListSortParams()
{

}
