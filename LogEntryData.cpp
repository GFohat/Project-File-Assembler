// LogEntryData.cpp: implementation of the CLogEntryData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "LogEntryData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogEntryData::CLogEntryData()
:	m_iRecID	(-1L)
	, m_iType	(-1L)
{

}

CLogEntryData::~CLogEntryData()
{

}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/05/2007 13:16:28
	DESCRIP:	
	IN:
	OUT:
*/
const CLogEntryData & CLogEntryData::operator = (const CLogEntryData & src)
{
#pragma message ("CLogEntryData::operator =")

	m_iRecID		= src.m_iRecID;
	m_iType			= src.m_iType;
	m_strWhen		= src.m_strWhen;
	m_strType		= src.m_strType;
	m_strLogon		= src.m_strLogon;
	m_strMachine	= src.m_strMachine;
	m_strSource		= src.m_strSource;
	m_strText		= src.m_strText;
	m_strSQL		= src.m_strSQL;

	return * this;
}

void CLogEntryData::SetData(const CtblLogging & table)
{
	CSystemTime2 dtsys;
	dtsys = table.m_dtWhen;

	m_iRecID		= table.m_iRecID;
	m_iType			= table.m_iType;
	m_strWhen		= dtsys.GetCurDateTime();
	m_strType		= table.m_szType;
	m_strLogon		= table.m_szLogon;
	m_strMachine	= table.m_szMachine;
	m_strSource		= table.m_szSource;
	m_strText		= table.m_szText;
	m_strSQL		= table.m_szSQL;	
}
