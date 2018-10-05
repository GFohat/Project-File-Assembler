// ListTickSetter.h: interface for the CListTickSetter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTTICKSETTER_H__AFBCF182_FBB9_48BD_9DC1_F2D7D58656B1__INCLUDED_)
#define AFX_LISTTICKSETTER_H__AFBCF182_FBB9_48BD_9DC1_F2D7D58656B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CListTickSetter  
{
public:
	CListTickSetter();
	virtual ~CListTickSetter();

protected:
	void SetTicksAll			(CListCtrl & rList);
	void SetTicksNone			(CListCtrl & rList);
	void SetTicksInvert			(CListCtrl & rList);
	void SetTicksHighlighted	(CListCtrl & rList);
};

#endif // !defined(AFX_LISTTICKSETTER_H__AFBCF182_FBB9_48BD_9DC1_F2D7D58656B1__INCLUDED_)
