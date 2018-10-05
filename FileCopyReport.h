// FileCopyReport.h: interface for the CFileCopyReport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILECOPYREPORT_H__78916D10_CE96_4ABB_B811_9E17D90D81AE__INCLUDED_)
#define AFX_FILECOPYREPORT_H__78916D10_CE96_4ABB_B811_9E17D90D81AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConstReport.h"
using namespace CONS_RPT;

class CFileCopyReport  
{
public:
	CFileCopyReport(	
					const eRPT_LINETYPE		eLineType
					, const CString &		strFile
					, const CString &		strSource
					, const CString &		strDestination
					, const CString &		strCopiedName
					, const DWORD			dwOpNumber
					, const DWORD			dwStepNumber
					, const DWORD			dwStatus
				);

	CFileCopyReport(const CFileCopyReport & src){ *this = src; }
	virtual ~CFileCopyReport();

public:
	const CFileCopyReport & operator = (const CFileCopyReport & src);

public:
	inline const CString &	GetFile			(void) const { return m_strFile; }
	inline const CString &	GetSource		(void) const { return m_strSource; }
	inline const CString &	GetDestination	(void) const { return m_strDestination; }
	inline const CString &	GetCopiedName	(void) const { return m_strCopiedName; }

	inline eRPT_LINETYPE	GetLineType		(void) const { return m_eLineType; }
	inline DWORD			GetOpNumber		(void) const { return m_dwOpNumber; }
	inline DWORD			GetStepNumber	(void) const { return m_dwStepNumber; }
	inline DWORD			GetSubStep		(void) const { return m_dwSubStep; }
	inline DWORD			GetStatus		(void) const { return m_dwStatus; }						

public:
	bool Succeeded(void) const;

private:
	eRPT_LINETYPE	m_eLineType;
	CString			m_strFile;
	CString			m_strSource;
	CString			m_strDestination;
	CString			m_strCopiedName;
	DWORD			m_dwOpNumber;
	DWORD			m_dwStepNumber;
	DWORD			m_dwStatus;	
	DWORD			m_dwSubStep;

private:
	DWORD CalcSubStep(const DWORD dwOpNumber) const;
};

#endif // !defined(AFX_FILECOPYREPORT_H__78916D10_CE96_4ABB_B811_9E17D90D81AE__INCLUDED_)
