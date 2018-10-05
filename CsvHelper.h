// CsvHelper.h: interface for the CCsvHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSVHELPER_H__A3DFCBF1_343F_41E1_A104_B9EAB93E4866__INCLUDED_)
#define AFX_CSVHELPER_H__A3DFCBF1_343F_41E1_A104_B9EAB93E4866__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCsvHelper  
{
public:
	CCsvHelper();
	virtual ~CCsvHelper();

public:
	void CsvToListCtrl(
					const CString & strCSVFile
					, CListCtrl & rList
				) const;
	
	void CsvToListCtrl(
					CStdioFile & csvfile
					, CListCtrl & rList
				) const;

	void CsvLineToListCtrl(
					const CString & strCSVLine
					, CListCtrl & rList
				) const;

	void CsvLineToStrings(
					const CString & strCSVLine
					, CStringArray & rArray
					, const DWORD dwMinItems
				) const;

	CString StringsToCsvLine(
					const CStringArray & rArray
					, const DWORD dwMinItems
				) const;
};

#endif // !defined(AFX_CSVHELPER_H__A3DFCBF1_343F_41E1_A104_B9EAB93E4866__INCLUDED_)
