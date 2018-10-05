// BrushHolder.h: interface for the CBrushHolder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BRUSHHOLDER_H__B7DEC19F_246F_4C25_8C37_50209938240A__INCLUDED_)
#define AFX_BRUSHHOLDER_H__B7DEC19F_246F_4C25_8C37_50209938240A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBrushHolder  
{
public:
	CBrushHolder();
	CBrushHolder(const COLORREF cref);
	virtual ~CBrushHolder();

public:
	void SetBrushColour(const COLORREF cref);

	HBRUSH GetBrush(HBRUSH hbrOrig);

private:
	CBrush m_brush;
};

#endif // !defined(AFX_BRUSHHOLDER_H__B7DEC19F_246F_4C25_8C37_50209938240A__INCLUDED_)
