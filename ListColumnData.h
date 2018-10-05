// ListColumnData.h: interface for the CListColumnData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTCOLUMNDATA_H__00140F7F_E40B_43E8_865D_D5146BC265C6__INCLUDED_)
#define AFX_LISTCOLUMNDATA_H__00140F7F_E40B_43E8_865D_D5146BC265C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CListColumnData  
{
public:
	CListColumnData();
	virtual ~CListColumnData();

public:
	const CString &		GetCellText	(void) const { return m_strCellText; }

private:
	CString m_strCellText;
};

#endif // !defined(AFX_LISTCOLUMNDATA_H__00140F7F_E40B_43E8_865D_D5146BC265C6__INCLUDED_)
