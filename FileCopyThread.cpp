// FileCopyThread.cpp: implementation of the CFileCopyThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "FileCopyThread.h"

#include "ConstStepTypes.h"
using namespace CONS_STEP_TYPES;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileCopyThread::CFileCopyThread()
{

}

CFileCopyThread::~CFileCopyThread()
{
	StopFileCopyThread();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 08:25:28
	DESCRIP:	
	IN:
	OUT:
*/
bool CFileCopyThread::StartFileCopyThread(const CFileCopyThreadParams & rStart)
{
	bool bOK = false;

	CFileCopyThreadParams * pNew = new CFileCopyThreadParams(rStart);
	ATLASSERT(pNew);

	if(pNew){
		bOK = CBasicThread3::StartBaseThread(
											_T("File Copy Thread")
											, TF_FileCopyWrapper
											, LPVOID(pNew)
										);

		if(!bOK)
			delete pNew;
	}

	return bOK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 08:25:26
	DESCRIP:	
	IN:
	OUT:
*/
void CFileCopyThread::StopFileCopyThread(void)
{
	CBasicThread3::StopBaseThread(5000L);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 08:51:51
	DESCRIP:	
	IN:
	OUT:
*/
//bool CFileCopyThread::PostFileCopyOp(WPARAM wParam, LPARAM lParam)
//{
//	DWORD dwTID = CBasicThread3::GetWrappedThreadID();
//
//	BOOL bTX = ::PostThreadMessage(dwTID, eWM_DO_SINGLE_OP, wParam, lParam);
//
//	return bTX ? true : false;
//}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 07:34:09
	DESCRIP:	
	IN:
	OUT:
*/
bool CFileCopyThread::PostTargetThread(DWORD dwMsg, WPARAM wParam, LPARAM lParam)
{
	DWORD dwTID = CBasicThread3::GetWrappedThreadID();

	BOOL bTX = ::PostThreadMessage(dwTID, dwMsg, wParam, lParam);
	ATLASSERT(bTX);

	return bTX ? true : false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 08:25:24
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
DWORD WINAPI CFileCopyThread::TF_FileCopyWrapper(LPVOID lpThreadParam)
{
	DWORD dwRet = DWORD(-1L);

	CFileCopyThreadParams * pParams = reinterpret_cast<CFileCopyThreadParams *>(lpThreadParam);
	ATLASSERT(pParams);

	if(pParams){

		dwRet = TF_FileCopyMainLoop(*pParams);

		delete pParams;
		pParams = 0;
	}

	return dwRet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 08:25:22
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
DWORD CFileCopyThread::TF_FileCopyMainLoop(CFileCopyThreadParams & rStart)
{
	DWORD dwRet = NOERROR;

	MSG msg;

	while(::GetMessage(&msg, 0, 0, 0) > 0){
		
		switch(msg.message){

			case eWM_DO_SINGLE_OP:
				TF_HandleSingleOp(msg, rStart);
				break;

			case eWM_VALIDATE_SINGLE_OP:
				TF_HandleSingleValidation(msg, rStart);
				break;

			case eWM_NO_MORE_ITEMS:
				rStart.ResetContent();
				break;

			default:
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
		}

	}

	return dwRet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 08:54:27
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
void CFileCopyThread::TF_HandleSingleOp(
									const MSG & msg
									, CFileCopyThreadParams & rStart
								)
{
	CPfaDataListItem * pItem = reinterpret_cast<CPfaDataListItem *>(msg.lParam);
	ATLASSERT(pItem);

	if(pItem){
		TF_HandleSingleOp(*pItem, msg.wParam, rStart);

		bool bTX = rStart.PostTargetMessage(eWM_SINGLE_OP_RESULT, msg.wParam, LPARAM(pItem));

		if(!bTX){
			delete pItem;
			pItem = 0;
		}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 08:54:29
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
void CFileCopyThread::TF_HandleSingleOp(
									CPfaDataListItem & rItem
									, const DWORD dwListItem
									, CFileCopyThreadParams & rStart
								)
{
	switch(rItem.GetStepType()){
		case ePST_Comment:
			rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_IgnoredLine);
			rItem.SetStepStatus(ePStatus_IgnoredLine);
			break;

		case ePST_CopySingleDir:
			TF_CopySingleDir(rItem, dwListItem, rStart);
			break;
		
		case ePST_CopyDirAndSubDirs:
			TF_CopyDirAndSubDirs(rItem, dwListItem, rStart);
			break;
		
		case ePST_DelDestFile:
			TF_DelDestFile(rItem, dwListItem, rStart);
			break;
		
		case ePST_CreateNewDir:
			TF_CreateNewDir(rItem, dwListItem, rStart);
			break;

		case ePST_CopyFile:
			TF_CopyFile(rItem, dwListItem, rStart);
			break;

		default:
			ATLASSERT(false);
			break;
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 09:34:31
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
void CFileCopyThread::TF_CopySingleDir(
									CPfaDataListItem & rItem
									, const DWORD dwListItem
									, CFileCopyThreadParams & rStart
								)
{
	rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_Copying);

	rStart.IsNewDestinationDir(rItem.GetDestDirectory(), dwListItem, rItem.GetStepNum());

	eSTEP_STATUS eStatus = rStart.CopySingleDirectory(
													rStart.GetTargetWnd()
													, rItem.GetSourceDir()
													, rItem.GetDestDirectory()
													, dwListItem
													, rItem.GetStepNum()
												);
	
	rItem.SetStepStatus(eStatus);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/04/2007 11:13:43
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
void CFileCopyThread::TF_CopySingleDir_Validate(
									CPfaDataListItem & rItem
									, const DWORD dwListItem
									, CFileCopyThreadParams & rStart
								)
{
	rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_Validating);

	CString strReason;
	
	bool bReadOK	= rStart.CanReadItem		(rItem.GetSourceDir(), strReason);
	bool bWriteOK	= rStart.CanWriteItemRoot	(rItem.GetDestDirectory(), strReason);

	rItem.SetValidationFail(strReason);

	bool bOK		= bReadOK && bWriteOK;

	eSTEP_STATUS eStatus = bOK ? ePStatus_ValidatedOK : ePStatus_ValidatedBad;

	rItem.SetStepStatus(eStatus);
}	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 09:34:33
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
void CFileCopyThread::TF_CopyDirAndSubDirs(
									CPfaDataListItem & rItem
									, const DWORD dwListItem
									, CFileCopyThreadParams & rStart
								)
{
	rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_Copying);
	
	rStart.IsNewDestinationDir(rItem.GetDestDirectory(), dwListItem, rItem.GetStepNum());

	eSTEP_STATUS eStatus = rStart.CopyDirAndSubDirs(
												rStart.GetTargetWnd()
												, rItem.GetSourceDir()
												, rItem.GetDestDirectory()
												, dwListItem
												, rItem.GetStepNum()
											);

	rItem.SetStepStatus(ePStatus_CopyFileOK);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/04/2007 11:14:10
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
void CFileCopyThread::TF_CopyDirAndSubDirs_Validate(
									CPfaDataListItem & rItem
									, const DWORD dwListItem
									, CFileCopyThreadParams & rStart
								)
{
	rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_Validating);
	
	CString strReason;
	
	bool bReadOK	= rStart.CanReadItem		(rItem.GetSourceDir(), strReason);
	bool bWriteOK	= rStart.CanWriteItemRoot	(rItem.GetDestDirectory(), strReason);

	rItem.SetValidationFail(strReason);

	bool bOK		= bReadOK && bWriteOK;

	eSTEP_STATUS eStatus = bOK ? ePStatus_ValidatedOK : ePStatus_ValidatedBad;

	rItem.SetStepStatus(eStatus);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 09:34:38
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
void CFileCopyThread::TF_DelDestFile(
									CPfaDataListItem & rItem
									, const DWORD dwListItem
									, CFileCopyThreadParams & rStart
								)
{
	rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_IgnoredLine);
	
	rItem.SetStepStatus(ePStatus_IgnoredLine);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/04/2007 11:15:59
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
void CFileCopyThread::TF_DelDestFile_Validate(
									CPfaDataListItem & rItem
									, const DWORD dwListItem
									, CFileCopyThreadParams & rStart
								)
{
	rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_IgnoredLine);
	
	rItem.SetStepStatus(ePStatus_IgnoredLine);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 09:34:41
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
void CFileCopyThread::TF_CreateNewDir(
									CPfaDataListItem & rItem
									, const DWORD dwListItem
									, CFileCopyThreadParams & rStart
								)
{
	rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_DirCreationOnly);
	
	rStart.IsNewDestinationDir(rItem.GetDestDirectory(), dwListItem, rItem.GetStepNum());

	rItem.SetStepStatus(ePStatus_DirCreationOK);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/04/2007 11:15:30
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
void CFileCopyThread::TF_CreateNewDir_Validate(
									CPfaDataListItem & rItem
									, const DWORD dwListItem
									, CFileCopyThreadParams & rStart
								)
{
	rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_Validating);
	
	CString strReason;
	
	bool bWriteOK	= rStart.CanWriteItemRoot	(rItem.GetDestDirectory(), strReason);

	rItem.SetValidationFail(strReason);

	eSTEP_STATUS eStatus = bWriteOK ? ePStatus_ValidatedOK : ePStatus_ValidatedBad;

	rItem.SetStepStatus(eStatus);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 09:34:43
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
void CFileCopyThread::TF_CopyFile(
									CPfaDataListItem & rItem
									, const DWORD dwListItem
									, CFileCopyThreadParams & rStart
								)
{
	rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_Copying);

	rStart.IsNewDestinationDir(rItem.GetDestDirectory(), dwListItem, rItem.GetStepNum());

	CString strSrcFile	(rItem.GetSourceDir() + _T("\\") + rItem.GetSourceFile());
	CString strDestFile (rItem.GetDestDirectory() + _T("\\") + rItem.GetDestFile());

	eSTEP_STATUS eStatus = rStart.CopySingleFile(
												rStart.GetTargetWnd()
												, strSrcFile
												, strDestFile
												, dwListItem
												, rItem.GetStepNum()
												, false			//don't report single file successes
											);

	rItem.SetStepStatus(eStatus);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/04/2007 11:14:39
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
void CFileCopyThread::TF_CopyFile_Validate(
									CPfaDataListItem & rItem
									, const DWORD dwListItem
									, CFileCopyThreadParams & rStart
								)
{
	rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_Validating);
	
	CString strReason;
	
	bool bReadOK	= rStart.CanReadItem		(rItem.GetSourceDir()		+ _T("\\")	+ rItem.GetSourceFile(), strReason);
	bool bWriteOK	= rStart.CanWriteItemRoot	(rItem.GetDestDirectory()	+ _T("\\")	+ rItem.GetDestFile(), strReason);

	rItem.SetValidationFail(strReason);

	bool bOK		= bReadOK && bWriteOK;

	eSTEP_STATUS eStatus = bOK ? ePStatus_ValidatedOK : ePStatus_ValidatedBad;

	rItem.SetStepStatus(eStatus);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/04/2007 09:20:49
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
void CFileCopyThread::TF_HandleSingleValidation(
									const MSG & msg
									, CFileCopyThreadParams & rStart
								)
{
	CPfaDataListItem * pItem = reinterpret_cast<CPfaDataListItem *>(msg.lParam);
	ATLASSERT(pItem);

	if(pItem){
		TF_HandleSingleValidation(*pItem, msg.wParam, rStart);

		bool bTX = rStart.PostTargetMessage(eWM_SINGLE_OP_VALIDATION, msg.wParam, LPARAM(pItem));

		if(!bTX){
			delete pItem;
			pItem = 0;
		}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 08:54:29
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
void CFileCopyThread::TF_HandleSingleValidation(
									CPfaDataListItem & rItem
									, const DWORD dwListItem
									, CFileCopyThreadParams & rStart
								)
{
	switch(rItem.GetStepType()){
		case ePST_Comment:
			rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_Validating);
			rItem.SetStepStatus(ePStatus_ValidatedOK);
			break;

		case ePST_CopySingleDir:
			rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_Validating);
			TF_CopySingleDir_Validate(rItem, dwListItem, rStart);
			break;
		
		case ePST_CopyDirAndSubDirs:
			rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_Validating);
			TF_CopyDirAndSubDirs_Validate(rItem, dwListItem, rStart);
			break;
		
		case ePST_DelDestFile:
			rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_Validating);
			TF_DelDestFile_Validate(rItem, dwListItem, rStart);
			break;
		
		case ePST_CreateNewDir:
			rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_Validating);
			TF_CreateNewDir_Validate(rItem, dwListItem, rStart);
			break;

		case ePST_CopyFile:
			rStart.PostTargetMessage(eWM_SINGLE_OP_STATUS, dwListItem, ePStatus_Validating);
			TF_CopyFile_Validate(rItem, dwListItem, rStart);
			break;

		default:
			ATLASSERT(false);
			break;
	}
}
