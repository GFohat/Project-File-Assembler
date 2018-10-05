// CompareHelp.h: interface for the CCompareHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPAREHELP_H__A4AC86D5_A842_43F9_99B2_986097B80DD9__INCLUDED_)
#define AFX_COMPAREHELP_H__A4AC86D5_A842_43F9_99B2_986097B80DD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum _NUM_STRING_TYPE{
	eNST_NotNumeric
	, eNST_HexString		//starts with 0x or 0X
	, eNST_Currency			//starts with local currency symbol
	, eNST_Numeric			//contains only 0-9 and '.'
} NUM_STRING_TYPE;

class CCompareHelp  
{
public:
	CCompareHelp();
	virtual ~CCompareHelp();

public:
	int CompareNumeric(const CString & strThis, const CString & strThat) const;
	bool ConvertDouble(const CString & str, double & rlOut) const;

	bool ConvertCurrency	(const CString & str, double & rlOut) const;
	bool ConvertNumeric		(const CString & str, double & rlOut) const;
	bool ConvertHexString	(const CString & str, double & rlOut) const;

	double HexCharValue	(const TCHAR chHex) const;

	NUM_STRING_TYPE GetNumStringType(const CString & str) const;
	CString GetCurrencySymbol(void) const;
};

#endif // !defined(AFX_COMPAREHELP_H__A4AC86D5_A842_43F9_99B2_986097B80DD9__INCLUDED_)
