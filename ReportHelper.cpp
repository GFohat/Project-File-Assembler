// ReportHelper.cpp: implementation of the CReportHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "ReportHelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportHelper::CReportHelper()
:	m_dtEarliestFile	(COleDateTime::GetCurrentTime())
	, m_dtLatestFile	(COleDateTime::GetCurrentTime())
{

}

CReportHelper::~CReportHelper()
{
	ExitReport(false);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 18:44:57
	DESCRIP:	
	IN:
	OUT:
*/
void CReportHelper::InitReport(const CString & strCsvFile)
{
	ExitReport(false);

	SYSTEMTIME dtsys;
	::GetLocalTime(&dtsys);

	TCHAR szDrive	[_MAX_DRIVE]	= {0};
	TCHAR szDir		[_MAX_DIR]		= {0};
	TCHAR szFileName[_MAX_FNAME]	= {0};

	_tsplitpath(strCsvFile, szDrive, szDir, szFileName, 0);

	m_strFileName.Format(
						_T("%s%sPfa Reports\\%04i-%02i-%02i %02i%02i%02i %s Report.csv")
						, szDrive, szDir
						, dtsys.wYear, dtsys.wMonth, dtsys.wDay
						, dtsys.wHour, dtsys.wMinute, dtsys.wSecond
						, szFileName
					);

	UINT uFlags = 
				CFile::modeReadWrite
				| CFile::shareDenyNone
				| CFile::typeText
				| CFile::modeCreate
				| CFile::modeNoTruncate
			;

	BOOL bOK = m_filReport.Open(m_strFileName, uFlags);
	
	if(bOK)
		m_filReport.SeekToEnd();
	else
		::AfxMessageBox(_T("Error opening file:\n") + m_strFileName);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 07:49:08
	DESCRIP:	
	IN:
	OUT:
*/
void CReportHelper::ExitReport(const bool bShowSummary)
{
	if(m_filReport.m_pStream)
		m_filReport.Close();

	if(bShowSummary){
		CString strMsg;

		COleDateTimeSpan dtspan = m_dtLatestFile - m_dtEarliestFile;

		strMsg.Format(
					_T("Earliest file: %s\n")
					_T("Latest file:   %s\n")
					_T("Span:          %i days")
					, m_dtEarliestFile.Format(szTIME_FORMAT)
					, m_dtLatestFile.Format(szTIME_FORMAT)
					, dtspan.GetTotalDays()
				);

		::AfxMessageBox(strMsg, MB_ICONINFORMATION);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 07:53:13
	DESCRIP:	
	IN:
	OUT:
*/
void CReportHelper::AddReportLine(const CStringArray & rArray)
{
	CString strCsvLine = CCsvHelper::StringsToCsvLine(rArray, 4L);
	strCsvLine += _T("\n");

	m_filReport.WriteString(strCsvLine);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 07:41:40
	DESCRIP:	
	IN:
	OUT:
*/
void CReportHelper::RptDirCreated(const CString & strDirName)
{
	CStringArray array;

	array.Add(szsRPT_LINE_DESCRIPS[eRLT_CreateDir]);
	array.Add(strDirName);

	AddReportLine(array);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 07:41:42
	DESCRIP:	
	OUT:
*/
void CReportHelper::RptFileCopied(const CString & strFileSrc, const CString & strFileDest)
{
	CStringArray array;

	array.Add(szsRPT_LINE_DESCRIPS[eRLT_CopyFile]);
	array.Add(strFileSrc);
	array.Add(strFileDest);
		
	COleDateTime dtMod = GetModTime(strFileSrc);
	array.Add(_T("'") + dtMod.Format(szTIME_FORMAT));

	if(IsTimeImportant(strFileSrc)){
		if(dtMod > m_dtLatestFile)
			m_dtLatestFile = dtMod;

		if(dtMod < m_dtEarliestFile)
			m_dtEarliestFile = dtMod;
	}

	AddReportLine(array);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 07:42:46
	DESCRIP:	
	IN:
	OUT:
*/
bool CReportHelper::IsTimeImportant(const CString & strFileNAP) const
{
	bool bImportant = false;

	TCHAR szExt[_MAX_EXT] = {0};

	_tsplitpath(strFileNAP, 0, 0, 0, szExt);

	if(0 == _tcsicmp(szExt, _T(".EXE")))
		bImportant = true;

	else if(0 == _tcsicmp(szExt, _T(".DLL")))
		bImportant = true;

	return bImportant;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 07:59:22
	DESCRIP:	
	IN:
	OUT:
*/
COleDateTime CReportHelper::GetModTime(const CString & strFileNAP) const
{
	COleDateTime dtMod = COleDateTime::GetCurrentTime();

	HANDLE hFile = ::CreateFile(
						strFileNAP
						, GENERIC_READ				//access
						, FILE_SHARE_READ			//share
						, 0							//secattrib
						, OPEN_EXISTING				//creation disposition
						, FILE_ATTRIBUTE_NORMAL		//flags and attribs
						, 0							//hTemplate
					);	//GENERIC_READ

	if(INVALID_HANDLE_VALUE != hFile){
		
		FILETIME ftModified;

		::GetFileTime(hFile, 0, 0, &ftModified);

		dtMod = ftModified;

		::CloseHandle(hFile);
		hFile = 0;
	}

	return dtMod;
}
