// ListTickSetter.cpp: implementation of the CListTickSetter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "ListTickSetter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListTickSetter::CListTickSetter()
{

}

CListTickSetter::~CListTickSetter()
{

}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 10:37:08
	DESCRIP:	
	IN:
	OUT:
*/
void CListTickSetter::SetTicksAll(CListCtrl & rList)
{
	const long iMAX = rList.GetItemCount();

	for(long iItem = 0 ; iItem < iMAX ; iItem ++){
		rList.SetCheck(iItem, TRUE);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 09:06:19
	DESCRIP:	
	IN:
	OUT:
*/
void CListTickSetter::SetTicksHighlighted(CListCtrl & rList)
{
	const long iMAX = rList.GetItemCount();

	UINT uState = 0L;

	for(long iItem = 0 ; iItem < iMAX ; iItem ++){
		uState = rList.GetItemState(iItem, LVIS_SELECTED);

		if(LVIS_SELECTED & uState)
			rList.SetCheck(iItem, TRUE);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 10:37:13
	DESCRIP:	
	IN:
	OUT:
*/
void CListTickSetter::SetTicksNone(CListCtrl & rList)
{
	const long iMAX = rList.GetItemCount();

	for(long iItem = 0 ; iItem < iMAX ; iItem ++){
		rList.SetCheck(iItem, FALSE);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 10:37:17
	DESCRIP:	
	IN:
	OUT:
*/
void CListTickSetter::SetTicksInvert(CListCtrl & rList)
{
	const long iMAX = rList.GetItemCount();
	BOOL bCheck = FALSE;

	for(long iItem = 0 ; iItem < iMAX ; iItem ++){
		bCheck = rList.GetCheck(iItem);
		bCheck = ! bCheck;
		rList.SetCheck(iItem, bCheck);
	}
}
