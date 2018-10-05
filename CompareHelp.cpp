// CompareHelp.cpp: implementation of the CCompareHelp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "CompareHelp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCompareHelp::CCompareHelp()
{

}

CCompareHelp::~CCompareHelp()
{

}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/05/2007 10:24:09
	DESCRIP:	
	IN:
	OUT:
*/
CString CCompareHelp::GetCurrencySymbol(void) const
{
	const DWORD dwBUFSIZE = 10L;

	static bool		bLookedUp					= false;
	static TCHAR	szCurSym[dwBUFSIZE + 5]		= {0};

	if(!bLookedUp){
		TRACE(_T("CCompareHelp::GetCurrencySymbol - Looking up currency symbol...\n"));
		int iRet = ::GetLocaleInfo(
								LOCALE_USER_DEFAULT
								, LOCALE_SCURRENCY
								, szCurSym
								, dwBUFSIZE
							);

		if(iRet)
			bLookedUp = true;
	}

	return szCurSym;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/05/2007 10:29:10
	DESCRIP:	
	IN:
	OUT:
	eNST_NotNumeric
	, eNST_HexString		//starts with 0x or 0X
	, eNST_Currency			//starts with local currency symbol
	, eNST_Numeric			//contains only 0-9 and '.'
*/
NUM_STRING_TYPE CCompareHelp::GetNumStringType(const CString & str) const
{
	NUM_STRING_TYPE eRet = eNST_NotNumeric;

	CString strCurSym = GetCurrencySymbol();

	const int iCURSYMLEN = strCurSym.GetLength();
	const int iLEN = str.GetLength();

	TCHAR chZero	= 0;
	TCHAR chOne		= 0;


	if(iLEN > 0){
		chZero = str.GetAt(0);	//GetAt will ASSERT if index is outside bounds
	
		if(iLEN > 1)
			chOne = str.GetAt(1);

		if((_T('0') == chZero) && (_T('x') == _tolower(chOne)))
			eRet = eNST_HexString;

		else if( 0 == _tcsicmp(strCurSym, str.Left(iCURSYMLEN)) )
			eRet = eNST_Currency;

		else
			eRet = eNST_Numeric;
	}

	return eRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/05/2007 09:35:45
	DESCRIP:	
	IN:
	OUT:
		a negative value if the first item should precede the second, 
		a positive value if the first item should follow the second, or 
		zero if the two items are equivalent.
*/
int CCompareHelp::CompareNumeric(const CString & strThis, const CString & strThat) const
{
	int iCmp = 0;

	double rlThis = 0;
	double rlThat = 0;

	bool bConvertThis = ConvertDouble(strThis, rlThis);
	bool bConvertThat = ConvertDouble(strThat, rlThat);

	if(bConvertThis && bConvertThat){
	
		if(rlThis < rlThat)
			iCmp = -1;

		else if(rlThis > rlThat)
			iCmp = 1;
	}

	return iCmp;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/05/2007 09:38:45
	DESCRIP:	
	IN:
	OUT:
*/
bool CCompareHelp::ConvertDouble(const CString & str, double & rlOut) const
{
	bool bConverted = false;
	rlOut = 0;

	NUM_STRING_TYPE eType = GetNumStringType(str);

	switch(eType){
		case eNST_HexString:	bConverted = ConvertHexString	(str, rlOut);	break;
		case eNST_Currency:		bConverted = ConvertCurrency	(str, rlOut);	break;
		case eNST_Numeric:		bConverted = ConvertNumeric		(str, rlOut);	break;

		case eNST_NotNumeric:	
		default:
			bConverted = false;
			break;
	}

	return bConverted;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/05/2007 11:00:35
	DESCRIP:	
	IN:
	OUT:
*/
bool CCompareHelp::ConvertHexString(const CString & str, double & rlOut) const
{
	bool bOK = true;

	rlOut = 0.0;

	int		iLeng			= str.GetLength();
	TCHAR	chDigit			= 0;
	DWORD	dwMultiplier	= 1L;
	double	rlHexByte		= 0.0;
	
	//may include the "0x" at the start - but they will return '0.0' from HexCharValue()
	for(int iLoop = iLeng - 1 ; iLoop >= 0 ; iLoop--){

		chDigit		= str.GetAt(iLoop);
		rlHexByte	= HexCharValue(chDigit);

		rlOut += (dwMultiplier * rlHexByte);
		
		dwMultiplier *= 16;
	}

	return bOK;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/05/2007 11:10:46
	DESCRIP:	
	IN:
	OUT:
*/
double CCompareHelp::HexCharValue(const TCHAR chHex) const
{
	double rlRet = 0.0;

	switch(chHex){
		//case _T('0'):
		case _T('1'):
		case _T('2'):
		case _T('3'):
		case _T('4'):
		case _T('5'):
		case _T('6'):
		case _T('7'):
		case _T('8'):
		case _T('9'):
			rlRet = chHex - _T('0');
			break;

		case _T('a'):	
		case _T('A'):	rlRet = 10.0;		break;
		case _T('b'):	
		case _T('B'):	rlRet = 11.0;		break;
		case _T('c'):	
		case _T('C'):	rlRet = 12.0;		break;
		case _T('d'):	
		case _T('D'):	rlRet = 13.0;		break;
		case _T('e'):	
		case _T('E'):	rlRet = 14.0;		break;
		case _T('f'):	
		case _T('F'):	rlRet = 15.0;		break;
	}

	return rlRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/05/2007 11:00:33
	DESCRIP:	
	IN:
	OUT:
*/
bool CCompareHelp::ConvertCurrency(const CString & str, double & rlOut) const
{
	CString strCurSym = GetCurrencySymbol();
	const int iCURSYMLEN = strCurSym.GetLength();
	const int iLEN = str.GetLength();

	CString strNumber = str.Right(iLEN - iCURSYMLEN);

	return ConvertNumeric(strNumber, rlOut);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/05/2007 11:00:30
	DESCRIP:	
	IN:
	OUT:
*/
bool CCompareHelp::ConvertNumeric(const CString & str, double & rlOut) const
{
	rlOut = _tcstod(str, 0);
	return true;
}
