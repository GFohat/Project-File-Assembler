// ListGeneralFiles.h: interface for the CListGeneralFiles class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTGENERALFILES_H__2EC8C936_56CA_41CF_A009_1D4E32B01EBF__INCLUDED_)
#define AFX_LISTGENERALFILES_H__2EC8C936_56CA_41CF_A009_1D4E32B01EBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CListGeneralFiles  
{
public:
	CListGeneralFiles();
	virtual ~CListGeneralFiles();

protected:
	void InitGenFileList	(CListCtrl & rList, CFont * pFont);
	void SetListWids		(CListCtrl & rList);
	
	void AddGenFileListItem(
						CListCtrl & rList
						, const WIN32_FIND_DATA & data
						, const CString & strName
					);
};

#endif // !defined(AFX_LISTGENERALFILES_H__2EC8C936_56CA_41CF_A009_1D4E32B01EBF__INCLUDED_)
