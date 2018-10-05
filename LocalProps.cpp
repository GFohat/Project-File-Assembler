#include "StdAfx.h"
#include "localprops.h"

#include <Lmcons.h>

CLocalProps::CLocalProps(void)
{
}

CLocalProps::~CLocalProps(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18-Jan-2006 14:40:20
	DESC:	
	IN:		
	OUT:	
*/
CString CLocalProps::GetMachineName(void) const
{
	TCHAR szComputerName[MAX_COMPUTERNAME_LENGTH + 5] = {0};

	DWORD dwBufSize = MAX_COMPUTERNAME_LENGTH + 1;
	::GetComputerName(szComputerName, &dwBufSize);

	szComputerName[dwBufSize] = 0;

	return szComputerName;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18-Jan-2006 14:41:43
	DESC:	
	IN:		
	OUT:	
*/
CString CLocalProps::GetUserName(void) const
{
	TCHAR szUserName[UNLEN + 5] = {0};

	DWORD dwBufSize = UNLEN + 1;
	::GetUserName(szUserName, &dwBufSize);

	szUserName[dwBufSize] = 0;

	return szUserName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 January 2006 12:57:08	
	DESC:		
	IN:
	OUT:
*/
CString CLocalProps::GetUserAtMachine(void) const
{
	CString strRet;

	strRet.Format(
				_T("%s@%s")
				, GetUserName()
				, GetMachineName()
			);

	return strRet;
}
