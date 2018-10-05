// DirInitHandler.cpp: implementation of the CDirInitHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "DirInitHandler.h"

#include "ConstLists.h"
using namespace CONS_LISTS;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirInitHandler::CDirInitHandler()
{

}

CDirInitHandler::~CDirInitHandler()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 09:13:53
	DESCRIP:	
	IN:
	OUT:
*/
void CDirInitHandler::ResetContent(void)
{
	m_strsProcessed.RemoveAll();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 09:13:56
	DESCRIP:	
	IN:
	OUT:
*/
bool CDirInitHandler::IsNewDestinationDir(
										const CString & strDir
										, const DWORD dwOpNumber
										, const DWORD dwStepNumber
									)
{
	bool bNewDir = false;

	//if it's not in our array, then process it
	//and add it to our array
	bool bIsPresent = false;

	const int iMAX = m_strsProcessed.GetSize();
	CString strProbe;

	for(int iLoop = 0 ; iLoop < iMAX && !bIsPresent; iLoop++){
		strProbe = m_strsProcessed.GetAt(iLoop);

		if(0 == strDir.CompareNoCase(strProbe))
			bIsPresent = true;
	}

	if(!bIsPresent){
		ProcessDestDir(strDir, dwOpNumber, dwStepNumber);
		m_strsProcessed.Add(strDir);
		bNewDir = true;
	}

	return bNewDir;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 09:17:53
	DESCRIP:	
	IN:
	OUT:
*/
void CDirInitHandler::ProcessDestDir(
								const CString & strDir
								, const DWORD dwOpNumber
								, const DWORD dwStepNumber
							)
{
	CheckDirIsEmpty(strDir, dwOpNumber, dwStepNumber);
	CheckDirExists(strDir, dwOpNumber, dwStepNumber);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 09:21:03
	DESCRIP:	
	IN:
	OUT:
*/
void CDirInitHandler::CheckDirExists(
								const CString & strDir
								, const DWORD dwOpNumber
								, const DWORD dwStepNumber
							)
{
	TRACE(_T("Checking existence of %s\n"), strDir);

	if(DoCreateDirectory()){

		const TCHAR chSLASH = _T('\\');
		const long iMAX = strDir.GetLength();

		TCHAR chProbe = 0;
		long iCharPos = 0;
		CString strDirCheck;
		DWORD dwErr = NOERROR;
		BOOL bCreated = FALSE;

		for(iCharPos = 0 ; iCharPos < iMAX ; iCharPos++){
			chProbe = strDir.GetAt(iCharPos);

			if(chSLASH == chProbe){
				strDirCheck = strDir.Left(iCharPos);
				
				if(strDirCheck.GetLength() > 2){
					bCreated = ::CreateDirectory(strDirCheck, 0);

					if(!bCreated){
						dwErr = ::GetLastError();
						
						if(ERROR_ALREADY_EXISTS != dwErr){
							//AddListRow(_T("Create new directory"), _T(""), strDirCheck, _T(""), ePStatus_DirCreationFailed);
							::AfxMessageBox(_T("Failed to create directory:\n") + strDirCheck);
						}
					}
				}
				else{
					ATLTRACE(_T("Skipped creation of dir \"%s\"\n"), strDirCheck);
				}
			}
		}

		//path to new directory should now be in place, so create it...
		::CreateDirectory(strDir, 0);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 09:21:03
	DESCRIP:	
	IN:
	OUT:
*/
void CDirInitHandler::CheckDirIsEmpty(
									const CString & strDir
									, const DWORD dwOpNumber
									, const DWORD dwStepNumber
								)
{
	if(DoEmptyDirectory()){
		DelDirContents(strDir, dwOpNumber, dwStepNumber);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 10:08:30
	DESCRIP:	
	IN:
	OUT:
*/
//void CDirInitHandler::DelDir(const CString & strDir, const DWORD dwOpNumber)
//{
//	DelDirContents(strDir, dwOpNumber);
//	//DeleteSingleDir(strDir, dwOpNumber);
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 10:08:33
	DESCRIP:	
	IN:
	OUT:
*/
void CDirInitHandler::DelDirContents(
									const CString & strDir
									, const DWORD dwOpNumber
									, const DWORD dwStepNumber
								)
{
	CString strConfirm;
	strConfirm.Format(
					_T("Delete Directory Contents\n\"%s\"?")
					, strDir
				);

	eSTEP_STATUS eStatus = ePStatus_DirEmptyCancelled;

//	INT_PTR iReply = ::AfxMessageBox(strConfirm, MB_YESNO | MB_ICONQUESTION);
//
//	if(IDYES == iReply){
//
//		CString strWild;
//		strWild.Format(_T("%s\\*.*"), strDir);
//
//		WIN32_FIND_DATA data;
//		CString strFound;
//
//		CFileCopyReport reportstart(eRLT_DeleteDir, _T(""), _T(""), strDir, _T(""), dwOpNumber, ePStatus_DirBeingEmptied);
//		ReportDIEvent(reportstart);
//
//		HANDLE hndlFind = ::FindFirstFile(strWild, &data);
//
//		if(hndlFind && (INVALID_HANDLE_VALUE != hndlFind)){
//
//			do{
//				strFound.Format(_T("%s\\%s"), strDir, data.cFileName);
//
//				//delete any child directories...
//				if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
//				//	if(0 != _tcsicmp(data.cFileName, _T(".."))){
//				//		if(0 != _tcsicmp(data.cFileName, _T("."))){
//				//			DelDirContents(strFound, dwOpNumber);
//				//		}
//				//	}
//				}
//
//				//17/04/2007 19:42:07
//				//only delete files...
//				else{
//					DeleteSingleFile(strFound, dwOpNumber);
//				}
//
//			}while(::FindNextFile(hndlFind, &data));
//
//			::FindClose(hndlFind);
//		}
//
//		eStatus = ePStatus_DirEmptiedOK;
//	}
		
	CFileCopyReport reportfinish(eRLT_DirEmptied, _T(""), _T(""), strDir, _T(""), dwOpNumber, dwStepNumber, eStatus);
	ReportDIEvent(reportfinish);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	27/03/2007 10:50:55
	DESCRIP:	
	IN:
	OUT:
*/
//void CDirInitHandler::DeleteSingleDir(const CString & strDir, const DWORD dwOpNumber)
//{
//	BOOL bOK = FALSE;
//
//	if(IsValidDeletion(strDir, dwOpNumber)){
//		bOK = ::RemoveDirectory(strDir);
//	}
//
//	CFileCopyReport report(
//						eRLT_DeleteDir
//						, _T("DELETE DIR")
//						, _T("")
//						, strDir
//						, _T("")
//						, dwOpNumber
//						, bOK ? ePStatus_FileDeleteOK : ePStatus_FileDeleteFailed
//					);
//
//	ReportDIEvent(report);
//}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	27/03/2007 10:52:31
	DESCRIP:	
	IN:
	OUT:
*/
bool CDirInitHandler::IsValidDeletion(const CString & strName, const DWORD dwOpNumber) const
{
	bool bValid = false;
	ATLASSERT(!strName.IsEmpty());

	if(!strName.IsEmpty()){

		if(IsValidDeletionAttribs(strName, dwOpNumber)){

			CString strTest = strName;
			strTest.MakeUpper();

			int iFind = strTest.Find(_T("SOURCE"));

			if(iFind >= 0){
				bValid = true;
			}
		}
	}

	return bValid;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	29/03/2007 07:25:56
	DESCRIP:	
	IN:
	OUT:
*/
bool CDirInitHandler::IsValidDeletionAttribs(const CString & strName, const DWORD dwOpNumber) const
{
	bool bValid = true;
		
	DWORD dwAttribs = ::GetFileAttributes(strName);

	if(dwAttribs & FILE_ATTRIBUTE_HIDDEN){
		bValid = AskOverrideInvalidDelete(strName, _T("Hidden File"));
	}

	if(dwAttribs & FILE_ATTRIBUTE_SYSTEM){
		bValid = AskOverrideInvalidDelete(strName, _T("System File"));
	}

	if(dwAttribs & FILE_ATTRIBUTE_READONLY){
		bValid = AskOverrideInvalidDelete(strName, _T("Read-Only File"));
	}

	return bValid;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	29/03/2007 07:36:15
	DESCRIP:	
	IN:
	OUT:
		true:	overrides the reason, and allows the deletion
		false:	confirms the disallowed deletion
*/
bool CDirInitHandler::AskOverrideInvalidDelete(
											const CString & strName
											, const CString & strReason
										) const
{
	bool bOverride = false;

	CString strQuestion;
	strQuestion.Format(
					_T("Do you really want to delete the file or folder\n")
					_T("[%s]?\n")
					_T("(%s)")
					, strName
					, strReason
				);

	DWORD dwMbType = MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION;

	INT_PTR iReply = ::AfxMessageBox(strQuestion, dwMbType);

	if(IDYES == iReply)
		bOverride = true;

	return bOverride;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	27/03/2007 10:10:06
	DESCRIP:	
	IN:
	OUT:
*/
//bool CDirInitHandler::IsValidFileDeletion(const CString & strNAP, const DWORD dwOpNumber) const
//{
//	bool bValid = false;
//	ATLASSERT(!strNAP.IsEmpty());
//
//	if(!strNAP.IsEmpty()){
//		
//		CString strTest = strNAP;
//		strTest.MakeUpper();
//
//		int iFind = strTest.Find(_T("SOURCE"));
//
//		if(iFind >= 0){
//			bValid = true;
//		}
//	}
//
//	return bValid;
//}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/03/2007 11:09:33
	DESCRIP:	
		, ePStatus_FileDeleteOK
		, ePStatus_FileDeleteFailed
	IN:
	OUT:
*/
void CDirInitHandler::DeleteSingleFile(
									const CString & strNAP
									, const DWORD dwOpNumber
									, const DWORD dwStepNumber
								)
{
	ATLTRACE(_T("DeleteSingleFile %s\n"), strNAP);
	BOOL bOK = FALSE;
	
	if(IsValidDeletion(strNAP, dwOpNumber)){

		//CString strConfirm;
		//strConfirm.Format(
		//				_T("Delete File\n\"%s\"?")
		//				, strNAP
		//			);

		//INT_PTR iReply = ::AfxMessageBox(strConfirm, MB_YESNO | MB_ICONQUESTION);

		//if(IDYES == iReply)
			
		//bOK = ::DeleteFile(strNAP);

//		if(!bOK){
//			DWORD dwErr = ::GetLastError();
//
//			//read-only file...
//			if(ERROR_ACCESS_DENIED == dwErr){
//				
//				//change file attributes
//				DWORD dwAttribs = ::GetFileAttributes(strNAP);
//				dwAttribs &= ~ FILE_ATTRIBUTE_READONLY;
//
//				::SetFileAttributes(strNAP, dwAttribs);
//				
//				bOK = ::DeleteFile(strNAP);
//			}
//		}
	}
	
	CFileCopyReport report(
						eRLT_DeleteFile
						, _T("DELETE FILE")
						, _T("")
						, strNAP
						, _T("")
						, dwOpNumber
						, dwStepNumber
						, bOK ? ePStatus_FileDeleteOK : ePStatus_FileDeleteFailed
					);

	ReportDIEvent(report);
}



