// ListSortParams.h: interface for the CListSortParams class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTSORTPARAMS_H__240256E7_8B8F_445F_B357_46FBD5171584__INCLUDED_)
#define AFX_LISTSORTPARAMS_H__240256E7_8B8F_445F_B357_46FBD5171584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CListSortParams  
{
public:
	//CListSortParams(
	//			CListCtrl & rListCtrl
	//			, const int iColumn
	//			, const bool bAscending
	//		);

	CListSortParams(
				CListCtrl & rListCtrl
				, const int iColumn
				, const int iColumnFormat
				, const bool bAscending
			);

	virtual ~CListSortParams();

	inline CListCtrl &	GetListCtrl		(void)			{ return m_rListCtrl; }

	inline int			GetColumn		(void) const	{ return m_iColumn; }
	inline int			GetColumnFmt	(void) const	{ return m_iColumnFormat; }
	inline bool			GetAscending	(void) const	{ return m_bAscending; }

private:
	CListCtrl &		m_rListCtrl;
	int				m_iColumn;
	bool			m_bAscending;
	int				m_iColumnFormat;	//left / centre / right = string / date / number
};

#endif // !defined(AFX_LISTSORTPARAMS_H__240256E7_8B8F_445F_B357_46FBD5171584__INCLUDED_)
