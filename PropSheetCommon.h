// PropSheetCommon.h: interface for the CPropSheetCommon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPSHEETCOMMON_H__DF081A2A_874B_4C9C_88F6_B92A6CB4B4BA__INCLUDED_)
#define AFX_PROPSHEETCOMMON_H__DF081A2A_874B_4C9C_88F6_B92A6CB4B4BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dirbrowser.h"
using namespace DIR_BROWSER;

class CPropSheetCommon  
:	public CDirBrowser
{
public:
	CPropSheetCommon();
	virtual ~CPropSheetCommon();

protected:
	CFontHandler m_fonts[eFont__LAST];
	void InitFonts(CDC * pdc);
	void InitTabCtrl(CTabCtrl * pTab);

public:
	CFont * GetTheFont(const eFont eWhichFont);
	void SetDlgItemFont(CWnd * pParent, const DWORD dwCtlID, const eFont eWhichFont);

public:
	void ExploreDirectory(HWND hWnd, const CString & strDir);
};

#endif // !defined(AFX_PROPSHEETCOMMON_H__DF081A2A_874B_4C9C_88F6_B92A6CB4B4BA__INCLUDED_)
