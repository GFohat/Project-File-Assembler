// FileListSortParams.h: interface for the CFileListSortParams class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILELISTSORTPARAMS_H__B2909F79_DC63_4741_8EEF_B0C3415A0BCC__INCLUDED_)
#define AFX_FILELISTSORTPARAMS_H__B2909F79_DC63_4741_8EEF_B0C3415A0BCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileListSortParams  
{
public:
	CFileListSortParams(
					const NMLISTVIEW & rNMLV
					, const bool bAscending
					, const int iColFmt
				);

	virtual ~CFileListSortParams();

public:
	inline int		GetSortColumn	(void) const { return m_iSortColumn; }
	inline int		GetColumnFmt	(void) const { return m_iColFormat; }
	inline bool		GetAscending	(void) const { return m_bAscending; }

private:
	int		m_iSortColumn;
	bool	m_bAscending;
	int		m_iColFormat;
};

#endif // !defined(AFX_FILELISTSORTPARAMS_H__B2909F79_DC63_4741_8EEF_B0C3415A0BCC__INCLUDED_)
