// CopyHelper.cpp: implementation of the CCopyHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "CopyHelper.h"

#include ".\paramscopyprogress.h"
#include ".\paramsshowfilepcposition.h"

#include <io.h>
#include <errno.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCopyHelper::CCopyHelper()
{

}

CCopyHelper::~CCopyHelper()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10/04/2007 07:46:47
	DESCRIP:	
	IN:
	OUT:
*/
void CCopyHelper::SetReason(bool bCan, const int iErrNo, CString & strReason) const
{
//	if(bCan)
//		strReason.Empty();
//
//	else{
		switch(iErrNo){
			case EACCES:	strReason = _T("Access denied");	break;
			case ENOENT:	strReason = _T("Not found");		break;

			default:
				strReason.Format(_T("Reason 0x%X"), iErrNo);
				break;
		}
//	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02/04/2007 10:14:47
	DESCRIP:	
	IN:
	OUT:
*/
bool CCopyHelper::ItemExists(const CString & strItem, CString & strReason) const
{
	bool bExists = false;

	//mode Value	Checks File For 
	//00			Existence only 
	//02			Write permission 
	//04			Read permission 
	//06			Read and write permission 

	int iMode = 0;

	//returns 0 if the file has the given mode. 
	//The function returns -1 if the named file does not exist 
	//or is not accessible in the given mode; in this case, 
	//errno is set as follows
	//EACCES	Access denied: file’s permission setting does not allow specified access.
	//ENOENT	Filename or path not found.

	int iRslt = _taccess(strItem, iMode);

	bExists = (0 == iRslt);

	SetReason(bExists, errno, strReason);

	return bExists;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02/04/2007 10:38:55
	DESCRIP:	
	IN:
	OUT:
*/
bool CCopyHelper::CanReadItem(const CString & strItem, CString & strReason) const
{
	bool bCan = false;

	//mode Value	Checks File For 
	//00			Existence only 
	//02			Write permission 
	//04			Read permission 
	//06			Read and write permission 

	int iMode = 4;

	//returns 0 if the file has the given mode. 
	//The function returns -1 if the named file does not exist 
	//or is not accessible in the given mode; in this case, 
	//errno is set as follows
	//EACCES	Access denied: file’s permission setting does not allow specified access.
	//ENOENT	Filename or path not found.

	int iRslt = _taccess(strItem, iMode);

	bCan = (0 == iRslt);

	SetReason(bCan, errno, strReason);

	return bCan;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02/04/2007 10:38:52
	DESCRIP:	
	IN:
	OUT:
*/
bool CCopyHelper::CanWriteItem(const CString & strItem, CString & strReason) const
{
	bool bCan = false;

	//mode Value	Checks File For 
	//00			Existence only 
	//02			Write permission 
	//04			Read permission 
	//06			Read and write permission 

	int iMode = 2;

	//returns 0 if the file has the given mode. 
	//The function returns -1 if the named file does not exist 
	//or is not accessible in the given mode; in this case, 
	//errno is set as follows
	//EACCES	Access denied: file’s permission setting does not allow specified access.
	//ENOENT	Filename or path not found.

	int iRslt = _taccess(strItem, iMode);

	bCan = (0 == iRslt);

	SetReason(bCan, errno, strReason);

	return bCan;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02/04/2007 10:53:52
	DESCRIP:	
	IN:
	OUT:
*/
bool CCopyHelper::CanWriteItemRoot(const CString & strItem, CString & strReason) const
{
	bool bCan = false;

	CString strRoot(strItem);
	int iLastSlash = 0;
	int iCurLeng = 0;
	
	errno = ENOENT;

	while(!strRoot.IsEmpty() && !bCan && (ENOENT == errno)){
		
		bCan = CanWriteItem(strRoot, strReason);

		//the item 'strRoot' may not have existed, check its parent...
		//(if it doesn't exist, then to create it we would need write access to its parent)
		if(!bCan && (ENOENT == errno)){
			iLastSlash = strRoot.ReverseFind(_T('\\'));

			if(iLastSlash >= 0)
				strRoot = strRoot.Left(iLastSlash);
			else
				strRoot.Empty();
		}
	}

	SetReason(bCan, errno, strReason);

	return bCan;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02/04/2007 10:38:50
	DESCRIP:	
	IN:
	OUT:
*/
bool CCopyHelper::CanReadWriteItem(const CString & strItem, CString & strReason) const
{
	bool bCan = false;

	//mode Value	Checks File For 
	//00			Existence only 
	//02			Write permission 
	//04			Read permission 
	//06			Read and write permission 

	int iMode = 6;

	//returns 0 if the file has the given mode. 
	//The function returns -1 if the named file does not exist 
	//or is not accessible in the given mode; in this case, 
	//errno is set as follows
	//EACCES	Access denied: file’s permission setting does not allow specified access.
	//ENOENT	Filename or path not found.

	int iRslt = _taccess(strItem, iMode);

	bCan = (0 == iRslt);

	SetReason(bCan, errno, strReason);

	return bCan;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 12:13:22
	DESCRIP:	
	IN:
	OUT:
*/
eSTEP_STATUS CCopyHelper::CopySingleFile(
										HWND hwndTarget
										, const CString & strSrcFile
										, const CString & strDestFile
										, const DWORD dwOPNumber
										, const DWORD dwStepNumber
										, const bool bReport		//report every operation, not just failures
									)
{
	static DWORD dwCalls = 0L;
	dwCalls ++;

	if(!(dwCalls % 10)){
		ATLTRACE(_T("%3i files copied\n"), dwCalls);
	}

	using namespace PARAMS;

	eSTEP_STATUS eRet = ePStatus_Copying;

	CompareFileVersions(strSrcFile, strDestFile);

	DWORD dwCopyFlags = 0L;

	CParamsCopyProgress prgrsparams(hwndTarget);
	BOOL bCancel = FALSE;

	BOOL bOK = ::CopyFileEx(
							strSrcFile
							, strDestFile
							, CopyProgressRoutine
							, LPVOID(&prgrsparams)
							, &bCancel
							, dwCopyFlags
						);

	if(bOK)
		eRet = ePStatus_CopyFileOK;
	
	else
		eRet = ePStatus_CopyFileFailed;		

	if(bReport || (ePStatus_CopyFileOK != eRet)){
		CFileCopyReport report(
							eRLT_CopyFile
							, _T("FROM ->")
							, strSrcFile
							, strDestFile
							, _T("<- TO")
							, dwOPNumber
							, dwStepNumber
							, eRet
						);

		ReportFCEvent(report);
	}
	


	return eRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/04/2007 07:14:24
	DESCRIP:	
	IN:
	OUT:
*/
eCMP_RSLT CCopyHelper::CompareFiles(const CString & strSrcFile, const CString & strDestFile)
{
	eCMP_RSLT eResult = CompareFileVersions(strSrcFile, strDestFile);
	return eResult;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 21:31:20
	DESCRIP:

		BOOL VerQueryValue(
		  const LPVOID pBlock, // address of buffer for version resource
		  LPTSTR lpSubBlock,   // address of value to retrieve
		  LPVOID *lplpBuffer,  // address of buffer for version value pointer
		  PUINT puLen          // address of length buffer
		);
	
	IN:
	OUT:
*/
//eCMP_RSLT CCopyHelper::CompareFileVersions(const CString & strSrcFile, const CString & strDestFile)
//{
//	eCMP_RSLT eResult = eCmpRslt_None;
//
//	BOOL bOK = TRUE;
//	DWORD dwHandle		= 0L;
//	DWORD dwSizeSrc		= GetFileVersionInfoSize(strSrcFile);
//	DWORD dwSizeDest	= GetFileVersionInfoSize(strDestFile);
//	//ATLASSERT(dwSizeSrc && dwSizeDest);
//
//	if(dwSizeSrc && dwSizeDest){
//		BYTE * pByteInfoSrc		= new BYTE[dwSizeSrc];
//		BYTE * pByteInfoDest	= new BYTE[dwSizeDest];
//
//		bOK = GetFileVersionInfo(strSrcFile, dwSizeSrc, pByteInfoSrc);
//		ATLASSERT(bOK);
//		
//		if(bOK){
//			bOK = GetFileVersionInfo(strDestFile, dwSizeDest, pByteInfoDest);
//			ATLASSERT(bOK);
//
//			if(bOK){
//				
//			}
//		}
//
//
//
//		delete [] pByteInfoDest;
//		delete [] pByteInfoSrc;
//	}
//
//	return eResult;
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/04/2007 07:37:44
	DESCRIP:	
	IN:
	OUT:
*/
eCMP_RSLT CCopyHelper::CompareFileVersions(const CString & strSrcFile, const CString & strDestFile)
{
	eCMP_RSLT eResult = eCmpRslt_None;

	CFixedFileInfo filinfoSrc;
	CFixedFileInfo filinfoDest;

	bool bSrcOK		= CFileMetaData::GetFixedFileInfo(strSrcFile, filinfoSrc);
	bool bDestOK	= CFileMetaData::GetFixedFileInfo(strDestFile, filinfoDest);

	if(bSrcOK && bDestOK){
		
	}

	return eResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 12:16:00
	DESCRIP:	
	IN:
	OUT:
*/
/*static*/
DWORD CALLBACK CCopyHelper::CopyProgressRoutine(
							LARGE_INTEGER		liTotalFileSize          // file size
							, LARGE_INTEGER		liTotalBytesTransferred  // bytes transferred
							, LARGE_INTEGER		liStreamSize             // bytes in stream
							, LARGE_INTEGER		liStreamBytesTransferred // bytes transferred for stream
							, DWORD				dwStreamNumber           // current stream
							, DWORD				dwCallbackReason         // callback reason
							, HANDLE			hSourceFile              // handle to source file
							, HANDLE			hDestinationFile         // handle to destination file
							, LPVOID			lpData                   // from CopyFileEx
						)
{
	using namespace PARAMS;

	DWORD dwRet = PROGRESS_CONTINUE;

	CParamsCopyProgress * pParams 
			= reinterpret_cast<CParamsCopyProgress *>(lpData);

	if(pParams){
		double rlPercent = double(liTotalBytesTransferred.QuadPart) / double(liTotalFileSize.QuadPart);
		rlPercent *= 100.0f;

		DWORD dwTimesSeen = pParams->SeenInCPR();

		//ShowCopyProgress(rlPercent, hSourceFile, hDestinationFile, *pParams);

		DWORD dwInstance = 0L;
		CParamsShowFilePCPosition * pSFPP 
				= new CParamsShowFilePCPosition(
										liTotalFileSize
										, liTotalBytesTransferred
										, dwStreamNumber
										, dwCallbackReason
									);

		_ASSERTE(pSFPP);
		
		BOOL bTX = pParams->SendMsg(
								eWM_SINGLEFILE_PC_POS
								, 0
								, LPARAM(pSFPP)
							);
		_ASSERTE(bTX);

		if(!bTX){
			delete pSFPP;
			pSFPP = 0;
		}
	}

	return dwRet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 14:25:56
	DESCRIP:	
	IN:
	OUT:
*/
eSTEP_STATUS CCopyHelper::CopySingleDirectory(
											HWND hwndTarget
											, const CString & strSrcDir
											, const CString & strDestDir
											, const DWORD dwOPNumber
											, const DWORD dwStepNumber
										)
{
	OnNewDirectory(strDestDir, dwOPNumber, dwStepNumber);

	eSTEP_STATUS eRet	= ePStatus_CopyFileOK;
	eSTEP_STATUS eTemp	= ePStatus_CopyFileFailed;

	CString strWild = strSrcDir + _T("\\*.*");

	CString strSrcFile;
	CString strDestFile;

	WIN32_FIND_DATA data;
	HANDLE hFind = ::FindFirstFile(strWild, &data);

	if(hFind && INVALID_HANDLE_VALUE != hFind){

		do{
		
			if(!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){

				strSrcFile.Format(_T("%s\\%s"), strSrcDir, data.cFileName);
				strDestFile.Format(_T("%s\\%s"), strDestDir, data.cFileName);

				eTemp = CopySingleFile(hwndTarget, strSrcFile, strDestFile, dwOPNumber, dwStepNumber, true);

				//a single failure shows up as a complete failure...
				if(ePStatus_CopyFileOK != eTemp)
					eRet = eTemp;
			}

		} while(::FindNextFile(hFind, &data));

		::FindClose(hFind);
	}

	CFileCopyReport report(
						eRLT_CopySingleDirectory
						, _T("")
						, strSrcDir
						, strDestDir
						, _T("")
						, dwOPNumber
						, dwStepNumber
						, eRet
					);

	ReportFCEvent(report);

	return eRet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 14:48:31
	DESCRIP:	
	IN:
	OUT:
*/
eSTEP_STATUS CCopyHelper::CopyDirAndSubDirs(
										HWND hwndTarget
										, const CString & strSrcDir
										, const CString & strDestDir
										, const DWORD dwOPNumber
										, const DWORD dwStepNumber
									)
{
	OnNewDirectory(strDestDir, dwOPNumber, dwStepNumber);

	CString strWild = strSrcDir + _T("\\*.*");

	CString strFound;
	CString strNewFrom;
	CString strNewTo;

	WIN32_FIND_DATA data;

	HANDLE hFind = ::FindFirstFile(strWild, &data);

	if(hFind && (INVALID_HANDLE_VALUE != hFind)){

		do{

			strFound	= data.cFileName;

			strNewFrom	= strSrcDir + _T("\\") + strFound;
			strNewTo	= strDestDir + _T("\\") + strFound;
			
			if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
				if(strFound != _T(".")){
					if(strFound != _T("..")){

						CopyDirAndSubDirs(hwndTarget, strNewFrom, strNewTo, dwOPNumber, dwStepNumber);
					}
				}
			}
			else{
				CopySingleFile(hwndTarget, strNewFrom, strNewTo, dwOPNumber, dwStepNumber, true);
			}

		} while(::FindNextFile(hFind, &data));

		::FindClose(hFind);
	}

	CFileCopyReport report(
						eRLT_CopyDirSubDirs
						, _T("")
						, strSrcDir
						, strDestDir
						, _T("")
						, dwOPNumber
						, dwStepNumber
						, ePStatus_DirCopyOK
					);

	ReportFCEvent(report);

	return ePStatus_DirCreationOK;
}
