// FileCopyThread.h: interface for the CFileCopyThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILECOPYTHREAD_H__B1449E33_6297_4B24_8B40_8AB6D8449DC5__INCLUDED_)
#define AFX_FILECOPYTHREAD_H__B1449E33_6297_4B24_8B40_8AB6D8449DC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "basicthread3.h"
using namespace INCLUDE_SERVICES::BASE_THREAD3;

#include "FileCopyThreadParams.h"
#include "PfaDataListItem.h"

class CFileCopyThread 
:	public CBasicThread3
{
public:
	CFileCopyThread();
	virtual ~CFileCopyThread();

public:
	bool StartFileCopyThread(const CFileCopyThreadParams & rStart);
	void StopFileCopyThread(void);

public:
	//bool PostFileCopyOp		(WPARAM wParam, LPARAM lParam);
	bool PostTargetThread	(DWORD dwMsg, WPARAM wParam, LPARAM lParam);

private:
	static DWORD WINAPI TF_FileCopyWrapper(LPVOID lpThreadParam);
	static DWORD        TF_FileCopyMainLoop(CFileCopyThreadParams & rStart);

	static void TF_HandleSingleOp(
								const MSG & msg
								, CFileCopyThreadParams & rStart
							);

	static void TF_HandleSingleOp(
								CPfaDataListItem & rItem
								, const DWORD dwListItem
								, CFileCopyThreadParams & rStart
							);

	static void TF_CopySingleDir(
								CPfaDataListItem & rItem
								, const DWORD dwListItem
								, CFileCopyThreadParams & rStart
							);

	static void TF_CopyDirAndSubDirs(
								CPfaDataListItem & rItem
								, const DWORD dwListItem
								, CFileCopyThreadParams & rStart
							);

	static void TF_DelDestFile(
								CPfaDataListItem & rItem
								, const DWORD dwListItem
								, CFileCopyThreadParams & rStart
							);

	static void TF_CreateNewDir(
								CPfaDataListItem & rItem
								, const DWORD dwListItem
								, CFileCopyThreadParams & rStart
							);

	static void TF_CopyFile(
								CPfaDataListItem & rItem
								, const DWORD dwListItem
								, CFileCopyThreadParams & rStart
							);

	static void TF_HandleSingleValidation(
								const MSG & msg
								, CFileCopyThreadParams & rStart
							);

	static void TF_HandleSingleValidation(
								CPfaDataListItem & rItem
								, const DWORD dwListItem
								, CFileCopyThreadParams & rStart
							);

	static void TF_CopySingleDir_Validate(
								CPfaDataListItem & rItem
								, const DWORD dwListItem
								, CFileCopyThreadParams & rStart
							);

	static void TF_CopyDirAndSubDirs_Validate(
								CPfaDataListItem & rItem
								, const DWORD dwListItem
								, CFileCopyThreadParams & rStart
							);

	static void TF_DelDestFile_Validate(
								CPfaDataListItem & rItem
								, const DWORD dwListItem
								, CFileCopyThreadParams & rStart
							);

	static void TF_CreateNewDir_Validate(
								CPfaDataListItem & rItem
								, const DWORD dwListItem
								, CFileCopyThreadParams & rStart
							);

	static void TF_CopyFile_Validate(
								CPfaDataListItem & rItem
								, const DWORD dwListItem
								, CFileCopyThreadParams & rStart
							);

};

#endif // !defined(AFX_FILECOPYTHREAD_H__B1449E33_6297_4B24_8B40_8AB6D8449DC5__INCLUDED_)
