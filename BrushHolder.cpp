// BrushHolder.cpp: implementation of the CBrushHolder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BrushHolder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBrushHolder::CBrushHolder()
{

}

CBrushHolder::CBrushHolder(const COLORREF cref)
{
	SetBrushColour(cref);
}

CBrushHolder::~CBrushHolder()
{
	if(m_brush.m_hObject)
		m_brush.DeleteObject();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	15/02/2007 21:14:07
	DESCRIP:	
	IN:
	OUT:
*/
void CBrushHolder::SetBrushColour(const COLORREF cref)
{
	if(m_brush.m_hObject)
		m_brush.DeleteObject();

	m_brush.CreateSolidBrush(cref);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/04/2007 12:37:03
	DESCRIP:	
	IN:
	OUT:
*/
HBRUSH CBrushHolder::GetBrush(HBRUSH hbrOrig)
{
	return m_brush;
	//return hbrOrig;
}
