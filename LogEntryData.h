// LogEntryData.h: interface for the CLogEntryData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGENTRYDATA_H__8E3C95E3_D51B_4F2E_8AFC_FF41396192FB__INCLUDED_)
#define AFX_LOGENTRYDATA_H__8E3C95E3_D51B_4F2E_8AFC_FF41396192FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tblLogging.H"
using namespace OLEDB;

class CLogEntryData  
{
public:
	CLogEntryData();
	CLogEntryData(const CLogEntryData & src) { *this = src; }
	virtual ~CLogEntryData();

public:
	const CLogEntryData & operator = (const CLogEntryData & src);

public:
	inline long				GetRecID	(void) const { return m_iRecID; }
	inline const CString &	GetWhen		(void) const { return m_strWhen; }
	inline long				GetTypeNum	(void) const { return m_iType; }
	inline const CString &	GetTypeStr	(void) const { return m_strType; }
	inline const CString &	GetLogon	(void) const { return m_strLogon; }
	inline const CString &	GetMachine	(void) const { return m_strMachine; }
	inline const CString &	GetSource	(void) const { return m_strSource; }
	inline const CString &	GetText		(void) const { return m_strText; }
	inline const CString &	GetSQL		(void) const { return m_strSQL; }

public:
//	inline void	SetRecID	(const long			iRecID)		{ m_iRecID		= iRecID; }
//	inline void	SetWhen		(const CString &	strWhen)	{ m_strWhen		= strWhen; }
//	inline void	SetType		(const long			iType)		{ m_iType		= iType; }
//	inline void	SetType		(const CString &	strType)	{ m_strType		= strType; }
//	inline void	SetLogon	(const CString &	strLogon)	{ m_strLogon	= strLogon; }
//	inline void	SetMachine	(const CString &	strMachine) { m_strMachine	= strMachine; }
//	inline void	SetSource	(const CString &	strSource)	{ m_strSource	= strSource; }
//	inline void	SetText		(const CString &	strText)	{ m_strText		= strText; }
//	inline void	SetSQL		(const CString &	strSQL)		{ m_strSQL		= strSQL; }

public:
	void SetData(const CtblLogging & table);

private:
	long		m_iRecID;
	long		m_iType;
	CString		m_strWhen;
	CString		m_strType;
	CString		m_strLogon;
	CString		m_strMachine;
	CString		m_strSource;
	CString		m_strText;
	CString		m_strSQL;
};

#endif // !defined(AFX_LOGENTRYDATA_H__8E3C95E3_D51B_4F2E_8AFC_FF41396192FB__INCLUDED_)
/*

	const TCHAR szSQL_LOG_LIST_ALL[] = 
							_T(" SELECT ")
							_T("     [iRecID] ")
							_T("     , [dtWhen] ")
							//_T("     , [iType] ")
							_T("     , [szType] ")
							_T("     , [szLogon] ")
							_T("     , [szMachine] ")
							_T("     , [szSource] ")
							_T("     , [szText] ")
							_T("     , [szSQL] ")
							_T(" FROM tblLogging ")
						;
*/