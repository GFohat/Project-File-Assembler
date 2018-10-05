// ButtonIcon.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "ButtonIcon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonIcon

CButtonIcon::CButtonIcon()
{
}

CButtonIcon::~CButtonIcon()
{
}


BEGIN_MESSAGE_MAP(CButtonIcon, CButton)
	//{{AFX_MSG_MAP(CButtonIcon)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonIcon message handlers

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 11:03:47
	DESCRIP:	
	IN:
	OUT:
*/
void CButtonIcon::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(rcClient);

	dc.SelectStockObject(BLACK_BRUSH);
	dc.Rectangle(rcClient);
}
