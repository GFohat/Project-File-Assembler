// ListColumnsHelper.h: interface for the CListColumnsHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTCOLUMNSHELPER_H__670E8379_C90C_4724_8FC4_A48F9519AD67__INCLUDED_)
#define AFX_LISTCOLUMNSHELPER_H__670E8379_C90C_4724_8FC4_A48F9519AD67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CListColumnsHelper  
{
public:
	CListColumnsHelper();
	virtual ~CListColumnsHelper();

public:
	void AutoSizeListColumns(CListCtrl & rList);
};

#endif // !defined(AFX_LISTCOLUMNSHELPER_H__670E8379_C90C_4724_8FC4_A48F9519AD67__INCLUDED_)
