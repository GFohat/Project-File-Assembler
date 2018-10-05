#include "StdAfx.h"
#include "systemtime2.h"
#include <math.h>

//#include <PragmaMessageDefines.h>
//#include <ATLComTime.h>

namespace INCLUDE_SERVICES{


namespace SYS_TIME2{


CSystemTime2::CSystemTime2(void)
{
	SetNow();
}

CSystemTime2::CSystemTime2(const CSystemTime2 & src)
{
	*this = src;
}
	
CSystemTime2::CSystemTime2(const DATE date)
{
	*this = date;
}

CSystemTime2::~CSystemTime2(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 March 2005 20:38:44	
	DESC:		
	IN:
	OUT:
*/
const CSystemTime2 & CSystemTime2::operator = (const CSystemTime2 & src)
{
	wYear			= src.wYear;
	wMonth			= src.wMonth;
	wDay			= src.wDay;
	wDayOfWeek		= src.wDayOfWeek;
	wHour			= src.wHour;
	wMinute			= src.wMinute;
	wSecond			= src.wSecond;
	wMilliseconds	= src.wMilliseconds;

	return * this;
}

const CSystemTime2 & CSystemTime2::operator = (const DBTIMESTAMP & dbts)
{
	wYear			= dbts.year;
	wMonth			= dbts.month;
	wDay			= dbts.day;
	//wDayOfWeek		= dbts;
	wHour			= dbts.hour;
	wMinute			= dbts.minute;
	wSecond			= dbts.second;
	wMilliseconds	= 0;				//dbts.wMilliseconds;

	return * this;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11-Oct-2005 10:10:43
	DESC:	
		The DATE type is implemented using an 8-byte floating-point number. 
		Days are represented by whole number increments starting with 
		30 December 1899, midnight as time zero. 

		Hour values are expressed as the absolute value of the fractional 
		part of the number. 
	IN:		
	OUT:	
*/
const CSystemTime2 & CSystemTime2::operator = (const DATE date)
{
	//this bit calculates the date accurately
	//but I don't think the 'wMilliseconds' works
	COleDateTime odt(date);
	SYSTEMTIME dtSysCheck;
	odt.GetAsSystemTime(dtSysCheck);

	//DATE starts at 30 December 1899, midnight as time zero.
	//FILETIME data structure is a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601
	//so we need to add 299 years (109205 days as calculated below)
	//COleDateTime dtBaseDATE		(1899, 12, 30, 0, 0, 0);
	//COleDateTime dtBaseFILETIME	(1601,  1,  1, 0, 0, 0);

	//COleDateTimeSpan dtDiff = dtBaseDATE - dtBaseFILETIME;

	ULARGE_INTEGER uliValue;

	//convert to file time ticks

	//calc the number of blips for the whole part of the date
	//(ie just the 'days')
	uliValue.QuadPart = (ULONGLONG(date) + 109205) * 24 * 60 * 60 * ullFTBLIPSPERSEC;

	//add the time
	double rlFracDay = date - LONGLONG(date);
	uliValue.QuadPart += ULONGLONG(rlFracDay * 24 * 60 * 60 * ullFTBLIPSPERSEC);

	//convert to file time ticks
	//double rlSeconds = (date + 10925) * 24 * 60 * 60;
	//uliValue.QuadPart = ULONGLONG(rlSeconds * double(ullFTBLIPSPERSEC));

	SetUlInt(uliValue);

	return * this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   14 August 2005 11:42:25	
	DESC:		
	IN:
	OUT:
*/
bool CSystemTime2::ParseSQLSrvDateTime(const CString & strData)
{
#pragma message(__LOC__ "Clean this up!!")

	const static DWORD_PTR dwLENG_W_MSECS	= _tcslen(_T("2005-01-01 01:01:01.999"));
	const static DWORD_PTR dwLENG_NO_MSECS	= _tcslen(_T("2005-01-01 01:01:01"));

	bool bMillisecs = false;

	if(dwLENG_NO_MSECS == DWORD_PTR(strData.GetLength()))
		bMillisecs = false;

	else if(dwLENG_W_MSECS == DWORD_PTR(strData.GetLength()))
		bMillisecs = true;

	else if(0 == strData.CompareNoCase(_T("<now>"))){
		SetNow();
		return true;
	}

	else if(0 == strData.CompareNoCase(_T("<null>"))){
		SetNow();
		return true;
	}

	else
		return false;

	//just because it's the right length does not mean it's a valid date time!
	CString strTemp;
	int iTest = 0;

	//Year								  012345678901234567890123
	strTemp = strData.Mid(0, 4);		//2005-01-01 01:01:01.999
	iTest = _ttoi(strTemp);

	if(iTest)
		_SYSTEMTIME::wYear = iTest;
	else{
		SetInvalid();
		return false;
	}

	//Month								  012345678901234567890123
	strTemp = strData.Mid(5, 2);		//2005-01-01 01:01:01.999
	iTest = _ttoi(strTemp);

	if(iTest > 0 && iTest < 13)
		_SYSTEMTIME::wMonth = iTest;
	else{
		SetInvalid();
		return false;
	}

	//day							  012345678901234567890123
	strTemp = strData.Mid(8, 2);	//2005-01-01 01:01:01.999
	iTest = _ttoi(strTemp);

	if(iTest > 0 && iTest < 32)
		_SYSTEMTIME::wDay = iTest;
	else{
		SetInvalid();
		return false;
	}

	//hour							  012345678901234567890123
	strTemp = strData.Mid(11, 2);	//2005-01-01 01:01:01.999
	iTest = _ttoi(strTemp);

	if(iTest >= 0 && iTest < 24)
		_SYSTEMTIME::wHour = iTest;
	else{
		SetInvalid();
		return false;
	}

	//minute						  012345678901234567890123
	strTemp = strData.Mid(14, 2);	//2005-01-01 01:01:01.999
	iTest = _ttoi(strTemp);

	if(iTest >= 0 && iTest < 60)
		_SYSTEMTIME::wMinute = iTest;
	else{
		SetInvalid();
		return false;
	}

	//second						  012345678901234567890123
	strTemp = strData.Mid(17, 2);	//2005-01-01 01:01:01.999
	iTest = _ttoi(strTemp);

	if(iTest >= 0  && iTest < 60)
		_SYSTEMTIME::wSecond = iTest;
	else{
		SetInvalid();
		return false;
	}

	//millisecs
	if(bMillisecs){						//012345678901234567890123
		strTemp = strData.Right(3);		//2005-01-01 01:01:01.999
		iTest = _ttoi(strTemp);

		if(iTest >= 0  && iTest < 1000)
			_SYSTEMTIME::wMilliseconds = iTest;
		else{
			SetInvalid();
			return false;
		}
	}
	else
		_SYSTEMTIME::wMilliseconds = 0;

	return true;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   14 August 2005 11:59:19	
	DESC:		
	IN:
	OUT:
*/
//bool CSystemTime2::GetAsDBTIMESTAMP(DBTIMESTAMP & dbts) const
//{
//	bool bValid = IsValid();
//
//	if(bValid){
//		dbts.year		= wYear;
//		dbts.month		= wMonth;
//		dbts.day		= wDay;
//		dbts.hour		= wHour;
//		dbts.minute		= wMinute;
//		dbts.second		= wSecond;
//		dbts.fraction	= wMilliseconds * 1000000L;
//		//ULONG uMSecs = dbts.fraction / 1000000L;
//	}
//
//	return bValid;
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20-May-2005 08:30:25
	DESC:
		SystemTimeToFileTime seems to fail when time is invalid,
		which makes the > and other operators fail.

		The FILETIME structure is a 64-bit value representing the number of 
		100-nanosecond intervals since January 1, 1601 (UTC).

		This value is a simple arbitrary value used for comparison operators.
		It is only guaranteed to be consistent, NOT accurate!
	IN:		
	OUT:	
*/
ULARGE_INTEGER CSystemTime2::GetUlInt(void) const
{
	ULARGE_INTEGER uli = {0, 0};

	uli.QuadPart = 0;

	//uli.QuadPart += wYear		* ullSECS_PER_YEAR;
	//uli.QuadPart += wMonth		* ullSECS_PER_MONTH;
	//uli.QuadPart += wDay		* ullSECS_PER_DAY;
	//uli.QuadPart += wHour		* ullSECS_PER_HOUR;
	//uli.QuadPart += wMinute		* ullSECS_PER_MIN;
	//uli.QuadPart += wSecond;

	FILETIME filetime = {0, 0};
	
	ATLASSERT(IsValid());

	BOOL bConverted = ::SystemTimeToFileTime(this, &filetime);
	ATLASSERT(bConverted);

	uli.HighPart	= filetime.dwHighDateTime;
	uli.LowPart		= filetime.dwLowDateTime;

	return uli;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   31 January 2006 14:47:30	
	DESC:		
	IN:
	OUT:
*/
void CSystemTime2::SetUlInt(const ULARGE_INTEGER & uli)
{
	FILETIME filetime;

	filetime.dwHighDateTime = uli.HighPart;
	filetime.dwLowDateTime = uli.LowPart;

	BOOL bConverted = ::FileTimeToSystemTime(&filetime, this);
	ATLASSERT(bConverted);

	FILETIME ftCheck;

	::SystemTimeToFileTime(this, &ftCheck);
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   31 January 2006 14:45:53	
	DESC:		
	IN:
	OUT:
*/
void CSystemTime2::AddSeconds(const LONGLONG llNumSecs)
{
	ULARGE_INTEGER uliBlips = GetUlInt();

	LONGLONG llNumBlips = llNumSecs * ullFTBLIPSPERSEC;
	uliBlips.QuadPart += llNumBlips;

	SetUlInt(uliBlips);
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   08 June 2005 09:56:11	
	DESC:		
	IN:
	OUT:
*/
ULONGLONG CSystemTime2::GetSeconds(void) const
{
	ULONGLONG ullRet = GetUlInt().QuadPart;
	ullRet /= ullFTBLIPSPERSEC;
	return ullRet;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20-May-2005 08:45:51
	DESC:	
		The FILETIME structure is a 64-bit value representing the number of 
		100-nanosecond intervals since January 1, 1601 (UTC).

		100 x 10^-9
		= 0.1 x 10^-6
		a 'ten millionth'
		10000000
	IN:		
	OUT:	
*/
bool CSystemTime2::IsCloseTime(const DWORD dwSecs, const CSystemTime2 & src) const
{
	ULONGLONG ullThis	= GetUlInt().QuadPart;
	ULONGLONG ullThat	= src.GetUlInt().QuadPart;
	ULONGLONG ullDiff	= dwSecs * ullFTBLIPSPERSEC;
	ULONGLONG ullHigh	= ullThat + ullDiff;
	ULONGLONG ullLow	= ullThat - ullDiff;

	return(ullThis < ullHigh && ullThis > ullLow);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20-May-2005 08:25:11
	DESC:	
		It is not recommended that you add and subtract values from the 
		SYSTEMTIME structure to obtain relative times. Instead, you should

			Convert the SYSTEMTIME structure to a FILETIME structure. 
			Copy the resulting FILETIME structure to a ULARGE_INTEGER structure. 
			Use normal 64-bit arithmetic on the ULARGE_INTEGER value. 
	IN:		
	OUT:	
*/
bool CSystemTime2::operator	==	(const CSystemTime2 & src) const
{
	ULARGE_INTEGER uliThis = GetUlInt();
	ULARGE_INTEGER uliThat = src.GetUlInt();

	return (uliThis.QuadPart == uliThat.QuadPart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20-May-2005 08:29:10
	DESC:	
	IN:		
	OUT:	
*/
bool CSystemTime2::operator	>	(const CSystemTime2 & src) const
{
	ULARGE_INTEGER uliThis = GetUlInt();
	ULARGE_INTEGER uliThat = src.GetUlInt();

	return (uliThis.QuadPart > uliThat.QuadPart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20-May-2005 08:29:14
	DESC:	
	IN:		
	OUT:	
*/
bool CSystemTime2::operator	<	(const CSystemTime2 & src) const
{
	ULARGE_INTEGER uliThis = GetUlInt();
	ULARGE_INTEGER uliThat = src.GetUlInt();

	return (uliThis.QuadPart < uliThat.QuadPart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20-May-2005 08:29:17
	DESC:	
	IN:		
	OUT:	
*/
bool CSystemTime2::operator	>=	(const CSystemTime2 & src) const
{
	ULARGE_INTEGER uliThis = GetUlInt();
	ULARGE_INTEGER uliThat = src.GetUlInt();

	return (uliThis.QuadPart >= uliThat.QuadPart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20-May-2005 08:29:20
	DESC:	
	IN:		
	OUT:	
*/
bool CSystemTime2::operator	<=	(const CSystemTime2 & src) const
{
	ULARGE_INTEGER uliThis = GetUlInt();
	ULARGE_INTEGER uliThat = src.GetUlInt();

	return (uliThis.QuadPart <= uliThat.QuadPart);
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 March 2005 20:47:46	
	DESC:		
	IN:
	OUT:
*/
void CSystemTime2::SetNow(void)
{
	::GetLocalTime(this);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	PGC Created: (vsn) 01-Apr-2005 07:15:23
	DESC:
	IN:
	OUT:
*/
void CSystemTime2::SetNowUTC(void)
{
	::GetSystemTime(this);
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   23 April 2005 09:16:41	
	DESC:		
		The DATE type is implemented using an 8-byte floating-point number. 
		Days are represented by whole number increments starting with 
		30 December 1899, midnight as time zero. Hour values are expressed 
		as the absolute value of the fractional part of the number. 
		The following table illustrates this.

			Date and time					Representation 
			30 December 1899, midnight		0.00 
			1 January 1900, midnight		2.00 
			4 January 1900, midnight		5.00 
			4 January 1900, 6 A.M.			5.25 
			4 January 1900, noon			5.50 
			4 January 1900, 9 P.M.			5.875 
	IN:
	OUT:
*/
bool CSystemTime2::SetDateTime(const DATE dt)
{
	BOOL bOK = ::VariantTimeToSystemTime(dt, this);
	
	//double rlDays = floor(dt);
	//double rlFrac = dt - rlDays;

	////rlFrac is now a fractional part of a day... convert to hours
	//double rlHours = rlFrac * 24;
	//while(rlHours >= 24)
	//	rlHours -= 24;

	////rlHours is now a fractional part of an hour... convert to mins
	//double rlMins = rlHours * 60;
	//while(rlMins >= 60)
	//	rlMins -= 60;

	////rlHours is now a fractional part of a minute... convert to secs
	//double rlSecs = rlMins * 60;
	//while(rlSecs >= 60)
	//	rlSecs -= 60;

	////rlHours is now a fractional part of a second... convert to millisecs
	//double rlMSecs = rlSecs * 1000;
	//while(rlMSecs >= 1000)
	//	rlMSecs -= 1000;

	//wMilliseconds = WORD(rlMSecs);

	return bOK ? true : false;
}
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20-May-2005 07:48:41
	DESC:	
	IN:		
	OUT:	
*/
bool CSystemTime2::SetFromFileTime(const CString & strFileName, const FILETIMETYPE eType)
{
	bool bOK = false;

	FILETIME filtime;
	ZeroMemory(&filtime, sizeof(FILETIME));

	FILETIME * pFTCreate	= 0;
	FILETIME * pFTAccess	= 0;
	FILETIME * pFTWrite		= 0;

	switch(eType){
		case eFT_Access:	pFTAccess = &filtime;	break;
		case eFT_Create:	pFTCreate = &filtime;	break;
		case eFT_Write:		pFTWrite = &filtime;	break;
	}

	HANDLE hndlFile = ::CreateFile(
									strFileName
									, GENERIC_READ				//dwAccess
									, FILE_SHARE_READ			//dwShare
									, 0							//lpSecAttribs0
									, OPEN_EXISTING				//dwCreateDisposition
									, FILE_ATTRIBUTE_NORMAL		//dwFlags
									, 0							//hndlTemplate
								);

	if(INVALID_HANDLE_VALUE != hndlFile){

		BOOL bGotFT = ::GetFileTime(hndlFile, pFTCreate, pFTAccess, pFTWrite);

		if(bGotFT){
			BOOL bConverted = ::FileTimeToSystemTime(&filtime, this);

			if(bConverted)
				bOK = true;
		}

		::CloseHandle(hndlFile);
	}

	return bOK;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	27-Sep-2005 15:23:05
	DESC:	
	IN:		
	OUT:	
*/
const CSystemTime2 & CSystemTime2::operator = (const FILETIME & filtim)
{
	BOOL bOK = ::FileTimeToSystemTime(&filtim, this);
	ATLASSERT(bOK);

	return * this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20-May-2005 07:48:46
	DESC:	
	IN:		
	OUT:	
*/
bool CSystemTime2::SetFileTimeToThis(const CString & strFileName, const FILETIMETYPE eType) const
{
	bool bOK = false;

	FILETIME filtime;
	ZeroMemory(&filtime, sizeof(FILETIME));
	BOOL bConverted = ::SystemTimeToFileTime(this, &filtime);

	if(bConverted){

		FILETIME * pFTCreate	= 0;
		FILETIME * pFTAccess	= 0;
		FILETIME * pFTWrite		= 0;

		switch(eType){
			case eFT_Access:	pFTAccess = &filtime;	break;
			case eFT_Create:	pFTCreate = &filtime;	break;
			case eFT_Write:		pFTWrite = &filtime;	break;
		}

		HANDLE hndlFile = ::CreateFile(
										strFileName
										, GENERIC_WRITE				//dwAccess
										, FILE_SHARE_READ			//dwShare
										, 0							//lpSecAttribs0
										, OPEN_EXISTING				//dwCreateDisposition
										, FILE_ATTRIBUTE_NORMAL		//dwFlags
										, 0							//hndlTemplate
									);

		if(INVALID_HANDLE_VALUE != hndlFile){

			BOOL bSet = ::SetFileTime(hndlFile, pFTCreate, pFTAccess, pFTWrite);

			if(bSet)
				bOK = true;

			::CloseHandle(hndlFile);
		}
	}

	return bOK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 March 2005 21:02:52	
	DESC:		
	IN:
	OUT:
*/
void CSystemTime2::SetInvalid(void)
{
	using namespace INVALID;

	wYear			= wInvalidYear;
	wMonth			= wInvalidMonth;
	wDay			= wInvalidDay;
	wDayOfWeek		= wInvalidDayOfWeek;
	wHour			= wInvalidHour;
	wMinute			= wInvalidMinute;
	wSecond			= wInvalidSecond;
	wMilliseconds	= wInvalidMilliseconds;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 March 2005 21:04:47	
	DESC:		
	IN:
	OUT:
*/
bool CSystemTime2::IsValid(void) const
{
	return IsValidDate() && IsValidTime();
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 March 2005 21:12:54	
	DESC:		
	IN:
	OUT:
*/
bool CSystemTime2::IsValidDate(void) const
{
	using namespace MIN_MAX;

	bool bYear	= IsInLimits(wYear,			wMaxYear,		wMinYear);
	bool bMonth = IsInLimits(wMonth,		wMaxMonth,		wMinMonth);
	bool bDay	= IsInLimits(wDay,			wMaxDay,		wMinDay);
	bool bDOY	= IsInLimits(wDayOfWeek,	wMaxDayOfWeek,	wMinDayOfWeek);


	bool bValid = bYear && bMonth && bDay && bDOY;

	return bValid;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 March 2005 21:12:52	
	DESC:		
	IN:
	OUT:
*/
bool CSystemTime2::IsValidTime(void) const
{
	using namespace MIN_MAX;

	bool bHour		= IsInLimits(wHour,				wMaxHour,			wMinHour);
	bool bMinute	= IsInLimits(wMinute,			wMaxMinute,			wMinMinute);
	bool bSecond	= IsInLimits(wSecond,			wMaxSecond,			wMinSecond);
	bool bMSecs		= IsInLimits(wMilliseconds,		wMaxMilliseconds,	wMinMilliseconds);

	return bHour && bMinute && bSecond && bMSecs;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 March 2005 21:12:49	
	DESC:		
	IN:
	OUT:
*/
bool CSystemTime2::IsInLimits(const WORD wdCheck, const WORD wdMax, const WORD wdMin) const
{
	if(wdCheck > wdMax)
		return false;
	if(wdCheck < wdMin)
		return false;

	return true;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 March 2005 21:22:05	
	DESC:		
	IN:
	OUT:
*/
void CSystemTime2::AssertValid(void) const
{
	AssertValidDate();
	AssertValidTime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 March 2005 21:22:10	
	DESC:		
	IN:
	OUT:
*/
void CSystemTime2::AssertValidDate(void) const
{
	bool bValid = IsValidDate();

	if(!bValid)
		DebugDump();

	ATLASSERT( bValid );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 March 2005 21:22:12	
	DESC:		
	IN:
	OUT:
*/
void CSystemTime2::AssertValidTime(void) const
{
	bool bValid = IsValidTime();

	if(!bValid)
		DebugDump();

	ATLASSERT(bValid);
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   31 March 2005 19:24:59	
	DESC:		
	wDayOfWeek 
		Specifies the current day of the week; Sunday = 0, Monday = 1, and so on. 
	IN:
	OUT:
*/
const CString CSystemTime2::GetDayOfWeekStr(LPCTSTR szInvalid /*= 0*/) const
{
	CString strRet;

	switch(wDayOfWeek){
		case 0:	strRet = _T("Sun");	break;
		case 1:	strRet = _T("Mon");	break;
		case 2:	strRet = _T("Tue");	break;
		case 3:	strRet = _T("Wed");	break;
		case 4:	strRet = _T("Thu");	break;
		case 5:	strRet = _T("Fri");	break;
		case 6:	strRet = _T("Sat");	break;
	}

	return strRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   31 March 2005 19:27:43	
	DESC:		
	IN:
	OUT:
*/
const CString CSystemTime2::GetMonthStr(LPCTSTR szInvalid /*= 0*/) const
{
	CString strRet;

	switch(wMonth){
		case 1:		strRet = _T("Jan");	break;
		case 2:		strRet = _T("Feb");	break;
		case 3:		strRet = _T("Mar");	break;
		case 4:		strRet = _T("Apr");	break;
		case 5:		strRet = _T("May");	break;
		case 6:		strRet = _T("Jun");	break;
		case 7:		strRet = _T("Jul");	break;
		case 8:		strRet = _T("Aug");	break;
		case 9:		strRet = _T("Sep");	break;
		case 10:	strRet = _T("Oct");	break;
		case 11:	strRet = _T("Nov");	break;
		case 12:	strRet = _T("Dec");	break;
	}

	return strRet;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   31 March 2005 19:35:49	
	DESC:		
		All translations between UTC time and local time are based on 
		the following formula:
			UTC = local time + bias

		The bias is the difference, in minutes, between UTC time 
		and local time.

	IN:
	OUT:
*/
long CSystemTime2::GetTimeZoneAdjustMins(void) const
{
#pragma message (__LOC__ "CHECK THIS")

	TIME_ZONE_INFORMATION tzinfo;
	memset(&tzinfo, 0, sizeof(TIME_ZONE_INFORMATION));

	DWORD dwErr = ::GetTimeZoneInformation(&tzinfo);

	long iRet = 0;

	switch(dwErr){
		case TIME_ZONE_ID_STANDARD:
			iRet = tzinfo.StandardBias + tzinfo.Bias;
			break;

		case TIME_ZONE_ID_DAYLIGHT:
			iRet = tzinfo.DaylightBias + tzinfo.Bias;
			break;
	}

	return iRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   31 March 2005 19:35:52	
	DESC:		
	IN:
	OUT:
*/
const CString CSystemTime2::GetTimeZoneStr(void) const
{
#pragma message (__LOC__ "CHECK THIS")

	TIME_ZONE_INFORMATION tzinfo;
	memset(&tzinfo, 0, sizeof(TIME_ZONE_INFORMATION));

	DWORD dwErr = ::GetTimeZoneInformation(&tzinfo);

	USES_CONVERSION;

	CString strRet = OLE2T(tzinfo.StandardName);

	return strRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   31 March 2005 19:19:00	
	DESC:	
	IN:
	OUT:
		Thu, 31 Mar 2005 17:20:20 GMT
*/
const CString CSystemTime2::GetCurDateTimeHTML(LPCTSTR szInvalid /*= 0*/) const
{
#pragma message (__LOC__ "CHECK THIS")

	const DWORD dwBUFSIZE = 64L;	//"Thu, 31 Mar 2005 17:20:20 GMT"
	TCHAR szDateTime[dwBUFSIZE + 5L];
	memset(szDateTime, 0, sizeof(szDateTime));

	_sntprintf(
			szDateTime
			, dwBUFSIZE
			, _T("%s, %i %s %04i %02i:%02i:%02i %s")
			, GetDayOfWeekStr()
			, wDay
			, GetMonthStr()
			, wYear
			, wHour
			, wMinute
			, wSecond
			, GetTimeZoneStr()
		);

	CString strDT(szDateTime);

	return strDT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   23 February 2005 21:35:09	
	DESC:		
	IN:
	OUT:
*/
const CString CSystemTime2::GetCurDateTime(LPCTSTR szInvalid /*= 0*/) const
{
	const DWORD dwBUFSIZE = 25L;	//"2005-02-23 21:36:11.012"
	TCHAR szDateTime[dwBUFSIZE + 5L];
	memset(szDateTime, 0, sizeof(szDateTime));

	_sntprintf(
			szDateTime
			, dwBUFSIZE
			, _T("%s %s")
			, GetDateStr(szInvalid)
			, GetTimeStr()
		);

	CString strDT(szDateTime);

	return strDT;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   06 February 2007 19:28:35	
	DESC:		
	IN:
	OUT:
*/
const CString CSystemTime2::GetCurDateTimeShort(LPCTSTR szInvalid /*= 0*/) const
{
	CString strRet;

	strRet.Format(
					_T("%04i-%02i-%02i %02i:%02i:%02i")
					, wYear, wMonth, wDay
					, wHour, wMinute, wSecond
				);

	return strRet;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   02 July 2006 12:20:44	
	DESC:		
	IN:
	OUT:
*/
const CString CSystemTime2::GetCurDateTimeADO(LPCTSTR szInvalid /*= 0*/) const
{
	CString strRet;
	strRet.Format(
				_T("%i/%i/%i %02i:%02i:%02i")
				, wDay
				, wMonth
				, wYear
				, wHour
				, wMinute
				, wSecond
			);

	return strRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 March 2005 21:33:51	
	DESC:		
	IN:
	OUT:
*/
const CString CSystemTime2::GetDateStr(LPCTSTR szInvalid /*= 0*/) const
{
	CString strOut;
	
	if(IsValidDate()){
		strOut.Format(_T("%04i-%02i-%02i"), wYear, wMonth, wDay);
	}
	else{
		if(szInvalid)
			strOut = szInvalid;
		else
			strOut = _T("<Invalid Date>");
	}

	return strOut;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 March 2005 21:33:54	
	DESC:		
	IN:
	OUT:
*/
const CString CSystemTime2::GetTimeStr(LPCTSTR szInvalid /*= 0*/) const
{
	CString strOut;
	
	if(IsValidTime()){
		strOut.Format(_T("%02i:%02i:%02i.%03i"), wHour, wMinute, wSecond, wMilliseconds);
	}
	else{
		if(szInvalid)
			strOut = szInvalid;
		else
			strOut = _T("<Invalid Time>");
	}

	return strOut;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	29-Sep-2005 08:30:59
	DESC:	
		Invalid characters removed for use in file names
	IN:		
	OUT:	
*/
const CString CSystemTime2::GetDateStrFileName(LPCTSTR szInvalid /*= 0*/) const
{
	return GetDateStr(szInvalid);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	29-Sep-2005 08:30:55
	DESC:	
		Invalid characters removed for use in file names
	IN:		
	OUT:	
*/
const CString CSystemTime2::GetTimeStrFileName(LPCTSTR szInvalid /*= 0*/) const
{
	CString strOut;
	
	if(IsValidTime()){
		strOut.Format(_T("%02i%02i%02i.%03i"), wHour, wMinute, wSecond, wMilliseconds);
	}
	else{
		if(szInvalid)
			strOut = szInvalid;
		else
			strOut = _T("<Invalid Time>");
	}

	return strOut;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 March 2005 21:22:16	
	DESC:		
	IN:
	OUT:
*/
void CSystemTime2::DebugDump(void) const
{
	ATLTRACE(
		_T("%s %s, Date: %i, Time: %i, Valid: %i\n")
			, GetDateStr()
			, GetTimeStr()
			, IsValidDate()
			, IsValidTime()
			, IsValid()
		);
}

}	//end of namespace SYS_TIME2



}	//end of namespace INCLUDE_SERVICES
