// ReportHelper.h: interface for the CReportHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTHELPER_H__ECF62408_83C0_4C97_A276_13A61CED1948__INCLUDED_)
#define AFX_REPORTHELPER_H__ECF62408_83C0_4C97_A276_13A61CED1948__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConstReport.h"
using namespace CONS_RPT;

#include "CsvHelper.h"

class CReportHelper  
:	public	CCsvHelper
{
public:
	CReportHelper();
	virtual ~CReportHelper();

protected:
	void InitReport(const CString & strCsvFile);
	void ExitReport(const bool bShowSummary);

protected:
	void AddReportLine(const CStringArray & rArray);
	
protected:
	void RptDirCreated(const CString & strDirName);
	void RptFileCopied(const CString & strFileSrc, const CString & strFileDest);

private:
	bool			IsTimeImportant	(const CString & strFileNAP) const;
	COleDateTime	GetModTime		(const CString & strFileNAP) const;

private:
	CStdioFile		m_filReport;
	CString			m_strFileName;
	COleDateTime	m_dtLatestFile;
	COleDateTime	m_dtEarliestFile;
};

#endif // !defined(AFX_REPORTHELPER_H__ECF62408_83C0_4C97_A276_13A61CED1948__INCLUDED_)
