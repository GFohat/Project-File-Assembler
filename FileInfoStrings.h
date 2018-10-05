#pragma once

/*
	The following are predefined version information Unicode strings: 

	Comments			
	InternalName		
	ProductName 
	CompanyName			
	LegalCopyright		
	ProductVersion 
	FileDescription		
	LegalTrademarks		
	PrivateBuild 
	FileVersion			
	OriginalFilename	
	SpecialBuild 
*/

typedef enum _FILEINFO_STRING{
	eFIStr_Comments				= 0
	, eFIStr_InternalName	
	, eFIStr_ProductName 
	, eFIStr_CompanyName		
	, eFIStr_LegalCopyright	
	, eFIStr_ProductVersion 
	, eFIStr_FileDescription	
	, eFIStr_LegalTrademarks	
	, eFIStr_PrivateBuild 
	, eFIStr_FileVersion		
	, eFIStr_OriginalFilename
	, eFIStr_SpecialBuild 
	, eFIStr__LAST
} eFILEINFO_STRING;

const TCHAR szsFILEINFO_IDENTS[eFIStr__LAST][40] = {
	_T("Comments")
	, _T("InternalName")
	, _T("ProductName")
	, _T("CompanyName")
	, _T("LegalCopyright")
	, _T("ProductVersion")
	, _T("FileDescription")
	, _T("LegalTrademarks")
	, _T("PrivateBuild")
	, _T("FileVersion")
	, _T("OriginalFilename")
	, _T("SpecialBuild")
};

class CFileInfoStrings
{
public:
	CFileInfoStrings(const WORD wdLanguage, const WORD wdCodePage);
	~CFileInfoStrings(void);

public:
	void SetFileInfoString(const eFILEINFO_STRING eWhich, const CString & strInfo);
	const CString GetFileInfoString(const eFILEINFO_STRING eWhich) const;

	void Dump(void) const;
	void Reset(const CString & strFill);

public:
	inline const CString &	GetLangCode	(void) const { return m_strLangCode; }
	inline const WORD		GetLanguage	(void) const { return m_wdLanguage; }
	inline const WORD		GetCodePage	(void) const { return m_wdCodePage; }

private:
	CStringArray m_saryFileInfoStrings;
	
	WORD m_wdLanguage;
	WORD m_wdCodePage;

	CString m_strLangCode;
};
