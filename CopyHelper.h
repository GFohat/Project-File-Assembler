// CopyHelper.h: interface for the CCopyHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COPYHELPER_H__D5C8418B_A098_4307_B9CE_FB334E18A877__INCLUDED_)
#define AFX_COPYHELPER_H__D5C8418B_A098_4307_B9CE_FB334E18A877__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include ".\filemetadata.h"

#include "ConstStepStatus.h"
using namespace CONS_STEP_STATUS;


class CCopyHelper  
:	public CFileMetaData
{
public:
	CCopyHelper();
	virtual ~CCopyHelper();

public:
	virtual void ReportFCEvent(const CFileCopyReport & report) = 0;
	virtual void OnNewDirectory(const CString & strDir, const DWORD dwOPNumber, const DWORD dwStepNumber) = 0;

public:
	eCMP_RSLT CompareFiles			(const CString & strSrcFile, const CString & strDestFile);
	eCMP_RSLT CompareFileVersions	(const CString & strSrcFile, const CString & strDestFile);

public:
	eSTEP_STATUS CopySingleFile(
								HWND hwndTarget
								, const CString & strSrcFile
								, const CString & strDestFile
								, const DWORD dwOPNumber
								, const DWORD dwStepNumber
								, const bool bReport		//report every operation, not just failures
							);

	eSTEP_STATUS CopySingleDirectory(
								HWND hwndTarget
								, const CString & strSrcDir
								, const CString & strDestDir
								, const DWORD dwOPNumber
								, const DWORD dwStepNumber
							);

	eSTEP_STATUS CopyDirAndSubDirs(
								HWND hwndTarget
								, const CString & strSrcDir
								, const CString & strDestDir
								, const DWORD dwOPNumber
								, const DWORD dwStepNumber
							);

	//eSTEP_STATUS CreateNewDirectory	(HWND hwndTarget, const CString & strDir) const;
	bool ItemExists			(const CString & strItem, CString & strReason) const;
	bool CanReadItem		(const CString & strItem, CString & strReason) const;
	bool CanWriteItem		(const CString & strItem, CString & strReason) const;
	bool CanReadWriteItem	(const CString & strItem, CString & strReason) const;
	bool CanWriteItemRoot	(const CString & strItem, CString & strReason) const;
	void SetReason			(bool bCan, const int iErrNo, CString & strReason) const;

private:
	static DWORD CALLBACK CopyProgressRoutine(
								LARGE_INTEGER		liTotalFileSize          // file size
								, LARGE_INTEGER		liTotalBytesTransferred  // bytes transferred
								, LARGE_INTEGER		liStreamSize             // bytes in stream
								, LARGE_INTEGER		liStreamBytesTransferred // bytes transferred for stream
								, DWORD				dwStreamNumber           // current stream
								, DWORD				dwCallbackReason         // callback reason
								, HANDLE			hSourceFile              // handle to source file
								, HANDLE			hDestinationFile         // handle to destination file
								, LPVOID			lpData                   // from CopyFileEx
							);
};

#endif // !defined(AFX_COPYHELPER_H__D5C8418B_A098_4307_B9CE_FB334E18A877__INCLUDED_)
