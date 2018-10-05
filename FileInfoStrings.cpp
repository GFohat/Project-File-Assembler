#include "StdAfx.h"
#include ".\fileinfostrings.h"

CFileInfoStrings::CFileInfoStrings(const WORD wdLanguage, const WORD wdCodePage)
:	m_wdLanguage	(wdLanguage)
	, m_wdCodePage	(wdCodePage)
{
	m_saryFileInfoStrings.SetSize(eFIStr__LAST);
	m_strLangCode.Format(_T("%04x%04x"), wdLanguage, wdCodePage);
}

CFileInfoStrings::~CFileInfoStrings(void)
{
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 19:49:44	
	DESC:		
	IN:
	OUT:
*/
void CFileInfoStrings::SetFileInfoString(const eFILEINFO_STRING eWhich, const CString & strInfo)
{
	ATLASSERT(eWhich >= 0 && eWhich < eFIStr__LAST);

	m_saryFileInfoStrings.SetAt(eWhich, strInfo);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 19:49:46	
	DESC:		
	IN:
	OUT:
*/
const CString CFileInfoStrings::GetFileInfoString(const eFILEINFO_STRING eWhich) const
{
	ATLASSERT(eWhich >= 0 && eWhich < eFIStr__LAST);

	return m_saryFileInfoStrings.GetAt(eWhich);
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 20:02:57	
	DESC:		
	IN:
	OUT:
*/
void CFileInfoStrings::Dump(void) const
{
	for(DWORD dwWhichInfo = 0L ; dwWhichInfo < eFIStr__LAST ; dwWhichInfo++ ){
		ATLTRACE(
				_T("%s = %s\n")
				, szsFILEINFO_IDENTS[dwWhichInfo]
				, GetFileInfoString(eFILEINFO_STRING(dwWhichInfo))
			);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 21:01:27	
	DESC:		
	IN:
	OUT:
*/
void CFileInfoStrings::Reset(const CString & strFill)
{
	for(DWORD dwWhichInfo = 0L ; dwWhichInfo < eFIStr__LAST ; dwWhichInfo++ ){
		SetFileInfoString(eFILEINFO_STRING(dwWhichInfo), strFill);
	}
}
