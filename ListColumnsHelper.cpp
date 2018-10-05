// ListColumnsHelper.cpp: implementation of the CListColumnsHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "ListColumnsHelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListColumnsHelper::CListColumnsHelper()
{

}

CListColumnsHelper::~CListColumnsHelper()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11/05/2007 22:00:59
	DESCRIP:	
	IN:
	OUT:
*/
void CListColumnsHelper::AutoSizeListColumns(CListCtrl & rList)
{
	//not sure if we will have a header, may just be icons?
	CHeaderCtrl * pHdr = rList.GetHeaderCtrl();
	//ATLASSERT(pHdr && ::IsWindow(pHdr->m_hWnd));
	
	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		for(DWORD dwLoop = 0L ; dwLoop < DWORD(pHdr->GetItemCount()) ; dwLoop ++){

			rList.SetColumnWidth(dwLoop, LVSCW_AUTOSIZE_USEHEADER);

		}
	}
}
