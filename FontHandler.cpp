#include "StdAfx.h"
#include "fonthandler.h"

CFontHandler::CFontHandler(void)
{
}

CFontHandler::~CFontHandler(void)
{
	ExitFont();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30-Jun-2006 11:00:41
	DESC:	
	IN:		
	OUT:	
*/
void CFontHandler::InitFont(
						CDC * pdc
						, const int iPoints
						, const int iWeight
						, const CString & strFace
					)
{
	ExitFont();

	ATLASSERT(pdc);

	if(pdc){
		int iLogPixelsY = pdc->GetDeviceCaps(LOGPIXELSY);
		int iFontSize = - MulDiv(iPoints, iLogPixelsY, 72);

		m_font.CreateFont(
						iFontSize, 0, 0, 0, iWeight, 0, 0
						, 0, 0, 0, 0, 0, 0
						, strFace
					);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30-Jun-2006 11:00:45
	DESC:	
	IN:		
	OUT:	
*/
void CFontHandler::ExitFont(void)
{
	if(m_font.m_hObject)
		m_font.DeleteObject();
}
