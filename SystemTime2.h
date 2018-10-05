#pragma once

#include <oledb.h>
//#include <stdstring.h>
//#include <atlstr.h>

//using namespace ATL;
//using namespace INCLUDE_SERVICES::STD_STR;


namespace INCLUDE_SERVICES{



namespace SYS_TIME2{

	//The FILETIME structure is a 64-bit value representing the number of 
	//100-nanosecond intervals since January 1, 1601 (UTC).
	const ULONGLONG ullSECS_PER_MIN		= 60;
	const ULONGLONG ullSECS_PER_HOUR	= ullSECS_PER_MIN * 60;
	const ULONGLONG ullSECS_PER_DAY		= ullSECS_PER_HOUR * 24;
	const ULONGLONG ullSECS_PER_MONTH	= ullSECS_PER_DAY * 30;		//arbitrary!
	const ULONGLONG ullSECS_PER_YEAR	= ullSECS_PER_DAY * 365;


	const ULONGLONG ullBASE_SECONDS = 1601 * ullSECS_PER_YEAR;

	namespace INVALID{
		const WORD wInvalidYear				= WORD(-1);
		const WORD wInvalidMonth			= WORD(-1);
		const WORD wInvalidDayOfWeek		= WORD(-1);
		const WORD wInvalidDay				= WORD(-1);
		const WORD wInvalidHour				= WORD(-1);
		const WORD wInvalidMinute			= WORD(-1);
		const WORD wInvalidSecond			= WORD(-1);
		const WORD wInvalidMilliseconds		= WORD(-1);
	}

	namespace MIN_MAX{
		const WORD wMinYear				= 1;
		const WORD wMinMonth			= 1;
		const WORD wMinDayOfWeek		= 0;
		const WORD wMinDay				= 1;
		const WORD wMinHour				= 0;
		const WORD wMinMinute			= 0;
		const WORD wMinSecond			= 0;
		const WORD wMinMilliseconds		= 0;
		const WORD wMaxYear				= 30827;	//ms-help://MS.VSCC.2003/MS.MSDNQTR.2004JUL.1033/sysinfo/base/systemtime_str.htm
		const WORD wMaxMonth			= 12;
		const WORD wMaxDayOfWeek		= 6;
		const WORD wMaxDay				= 31;
		const WORD wMaxHour				= 23;
		const WORD wMaxMinute			= 59;
		const WORD wMaxSecond			= 59;
		const WORD wMaxMilliseconds		= 999;
	}

/*
	wYear 
		Specifies the current year. 
	wMonth 
		Specifies the current month; January = 1, February = 2, and so on. 
	wDayOfWeek 
		Specifies the current day of the week; Sunday = 0, Monday = 1, and so on. 
	wDay 
		Specifies the current day of the month. 
	wHour 
		Specifies the current hour. 
	wMinute 
		Specifies the current minute. 
	wSecond 
		Specifies the current second. 
	wMilliseconds 
		Specifies the current millisecond. 
*/

	const static ULONGLONG ullFTBLIPSPERSEC = 10000000L;


//#include <systemtime2.h>
//using namespace INCLUDE_SERVICES::SYS_TIME2;

class CSystemTime2
:	public _SYSTEMTIME
{
public:
	CSystemTime2(void);
	CSystemTime2(const DATE date);
	CSystemTime2(const CSystemTime2 & src);
	~CSystemTime2(void);

public:
	const CSystemTime2 & operator = (const CSystemTime2 & src);
	const CSystemTime2 & operator = (const FILETIME & filtim);
	const CSystemTime2 & operator = (const DATE date);
	const CSystemTime2 & operator = (const DBTIMESTAMP & dbts);

	bool operator	==	(const CSystemTime2 & src) const;
	bool operator	>	(const CSystemTime2 & src) const;
	bool operator	<	(const CSystemTime2 & src) const;
	bool operator	>=	(const CSystemTime2 & src) const;
	bool operator	<=	(const CSystemTime2 & src) const;

public:
	ULARGE_INTEGER	GetUlInt	(void) const;
	ULONGLONG		GetSeconds	(void) const;
	void			SetUlInt	(const ULARGE_INTEGER & uli);

	void SetNow		(void);
	void SetNowUTC	(void);
	void SetInvalid	(void);

	bool IsCloseTime(const DWORD dwSecs, const CSystemTime2 & src) const;

	bool ParseSQLSrvDateTime(const CString & strData);
	bool GetAsDBTIMESTAMP(DBTIMESTAMP & dbts) const;

public:
	const CString GetDateStr			(LPCTSTR szInvalid = 0) const;
	const CString GetTimeStr			(LPCTSTR szInvalid = 0) const;
	const CString GetDateStrFileName	(LPCTSTR szInvalid = 0) const;
	const CString GetTimeStrFileName	(LPCTSTR szInvalid = 0) const;

	const CString GetDayOfWeekStr		(LPCTSTR szInvalid = 0) const;
	const CString GetMonthStr			(LPCTSTR szInvalid = 0) const;

	const CString GetCurDateTime		(LPCTSTR szInvalid = 0) const;
	const CString GetCurDateTimeShort	(LPCTSTR szInvalid = 0) const;
	const CString GetCurDateTimeHTML	(LPCTSTR szInvalid = 0) const;
	const CString GetCurDateTimeADO		(LPCTSTR szInvalid = 0) const;

	const CString GetTimeZoneStr		(void) const;

public:
	bool IsValid		(void) const;
	bool IsValidDate	(void) const;
	bool IsValidTime	(void) const;

public:
	long GetTimeZoneAdjustMins	(void) const;

public:
	void AssertValid		(void) const;
	void AssertValidDate	(void) const;
	void AssertValidTime	(void) const;
	void DebugDump			(void) const;

public:
	bool SetDateTime(const DATE dt);
	void AddSeconds(const LONGLONG llNumSecs);

public:
	typedef enum _FILETIMETYPE{
		eFT_Create
		, eFT_Write
		, eFT_Access
	} FILETIMETYPE;

	bool SetFromFileTime	(const CString & strFileName, const FILETIMETYPE eType);
	bool SetFileTimeToThis	(const CString & strFileName, const FILETIMETYPE eType) const;

private:
	bool IsInLimits(const WORD wdCheck, const WORD wdMax, const WORD wdMin) const;
};



}	//end of namespace SYS_TIME2



}	//end of namespace INCLUDE_SERVICES
