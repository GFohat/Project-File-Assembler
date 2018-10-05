// FileCopyReport.cpp: implementation of the CFileCopyReport class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "FileCopyReport.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileCopyReport::CFileCopyReport(	
						const eRPT_LINETYPE		eLineType
						, const CString &		strFile
						, const CString &		strSource
						, const CString &		strDestination
						, const CString &		strCopiedName
						, const DWORD			dwOpNumber
						, const DWORD			dwStepNumber
						, const DWORD			dwStatus
					)
:	m_eLineType			(eLineType)
	, m_strFile			(strFile)
	, m_strSource		(strSource)
	, m_strDestination	(strDestination)
	, m_strCopiedName	(strCopiedName)
	, m_dwOpNumber		(dwOpNumber)
	, m_dwStatus		(dwStatus)
	, m_dwStepNumber	(dwStepNumber)
{
	m_dwSubStep = CalcSubStep(dwOpNumber);
}

CFileCopyReport::~CFileCopyReport()
{

}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 07:57:07
	DESCRIP:	
	IN:
	OUT:
*/
const CFileCopyReport & CFileCopyReport::operator = (const CFileCopyReport & src)
{
#pragma message ("CFileCopyReport::operator =")

	m_eLineType			= src.m_eLineType;
	m_strFile			= src.m_strFile;
	m_strSource			= src.m_strSource;
	m_strDestination	= src.m_strDestination;
	m_strCopiedName		= src.m_strCopiedName;
	m_dwOpNumber		= src.m_dwOpNumber;
	m_dwStatus			= src.m_dwStatus;
	m_dwSubStep			= src.m_dwSubStep;
	m_dwStepNumber		= src.m_dwStepNumber;

	return * this;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/04/2007 08:08:52
	DESCRIP:	

		If we pass in the same op number as last time,
			increment substep and return.

		If we pass in a new op number,
			reset substep to '1' and return.

	IN:
	OUT:
*/
DWORD CFileCopyReport::CalcSubStep(const DWORD dwOpNumber) const
{
	static DWORD dwSubStep = 1L;
	static DWORD dwLastOpNum = DWORD(-1L);

	if(dwOpNumber == dwLastOpNum){
		dwSubStep ++;
	}
	else{
		dwSubStep = 1L;
	}

	dwLastOpNum = dwOpNumber;

	return dwSubStep;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	15/05/2007 07:21:08
	DESCRIP:	
	IN:
	OUT:
*/
bool CFileCopyReport::Succeeded(void) const
{
	bool bSuccess = false;

	switch(m_dwStatus){
		case ePStatus_None:
		case ePStatus_Copying:
		case ePStatus_IncompleteLine:
		case ePStatus_DirCreationOnly:
		case ePStatus_SourceNonExistent:
		case ePStatus_DirCreationFailed:
		case ePStatus_DirBeingEmptied:
		case ePStatus_DirEmptiedFail:
		case ePStatus_FileDeleteFailed:
		case ePStatus_CopyFileFailed:
		case ePStatus_UserCancelled:
		case ePStatus_CopyFile:
		case ePStatus_DirIncSubDirs:
		case ePStatus_Validation:
		case ePStatus_Validating:
		case ePStatus_ValidatedBad:
			bSuccess = false;
			break;

		case ePStatus_DirEmptyCancelled:	//<-- success, since we always do this
		case ePStatus_DirCreationOK:
		case ePStatus_DirCopyOK:
		case ePStatus_DirEmptiedOK:
		case ePStatus_IgnoredLine:
		case ePStatus_FileDeleteOK:
		case ePStatus_CopyFileOK:
		case ePStatus_ValidatedOK:
			bSuccess = true;
			break;

		default:
			ATLASSERT(false);
			ATLTRACE(_T("New unhandled status enum\n"));
			break;
	}

	return bSuccess;
}
