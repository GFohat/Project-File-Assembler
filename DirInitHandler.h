// DirInitHandler.h: interface for the CDirInitHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRINITHANDLER_H__9674331B_5041_46E7_B047_FA2001078D56__INCLUDED_)
#define AFX_DIRINITHANDLER_H__9674331B_5041_46E7_B047_FA2001078D56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileCopyReport.h"

class CDirInitHandler  
{
public:
	CDirInitHandler();
	virtual ~CDirInitHandler();

public:
	virtual bool DoCreateDirectory	(void) = 0;
	virtual bool DoEmptyDirectory	(void) = 0;
	virtual void ReportDIEvent(const CFileCopyReport & report) = 0;

public:
	bool IsNewDestinationDir(
						const CString & strDir
						, const DWORD dwOpNumber
						, const DWORD dwStepNumber
					);

	void ResetContent(void);

private:
	void ProcessDestDir(
						const CString & strDir
						, const DWORD dwOpNumber
						, const DWORD dwStepNumber
					);

	void CheckDirExists(
						const CString & strDir
						, const DWORD dwOpNumber
						, const DWORD dwStepNumber
					);
	
	void CheckDirIsEmpty(
						const CString & strDir
						, const DWORD dwOpNumber
						, const DWORD dwStepNumber
					);

	//void DelDir					(const CString & strDir, const DWORD dwOpNumber);
	void DelDirContents(
						const CString & strDir
						, const DWORD dwOpNumber
						, const DWORD dwStepNumber
					);

	void DeleteSingleFile(
						const CString & strNAP
						, const DWORD dwOpNumber
						, const DWORD dwStepNumber
					);

	//void DeleteSingleDir		(const CString & strDir, const DWORD dwOpNumber);
	bool IsValidDeletion		(const CString & strName, const DWORD dwOpNumber) const;
	bool IsValidDeletionAttribs	(const CString & strName, const DWORD dwOpNumber) const;
	
	bool AskOverrideInvalidDelete(
								const CString & strName
								, const CString & strReason
							) const;

	CStringArray m_strsProcessed;
};

#endif // !defined(AFX_DIRINITHANDLER_H__9674331B_5041_46E7_B047_FA2001078D56__INCLUDED_)
