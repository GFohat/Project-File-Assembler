#include "StdAfx.h"
#include ".\filemetadata.h"

CFileMetaData::CFileMetaData(void)
{
}

CFileMetaData::~CFileMetaData(void)
{
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   30 October 2006 19:56:12	
	DESC:		
	IN:
	OUT:
*/
//bool CFileMetaData::SetFixedFileInfo(const CString & strFileNAP, const CFixedFileInfo & ffinfo) const
//{
//	bool bOK = false;
//
//	CResourceUpdater updater(strFileNAP);
//	bOK = updater.UpdateFileResources(strFileNAP, ffinfo);
//
//	return bOK;
//}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 13:47:29	
	DESC:		
	IN:
	OUT:
*/
bool CFileMetaData::GetFixedFileInfo(const CString & strFileNAP, CFixedFileInfo & ffinfo) const
{
#pragma message(__LOC__ "Function too long")

	bool bGotInfo = false;

	DWORD dwIgnored = 0L;
	DWORD dwBytes = GetFileVersionInfoSize(strFileNAP);

	if(dwBytes){
		BYTE * pBuffer = new BYTE[dwBytes];
		ATLASSERT(pBuffer);

		if(pBuffer){

			BOOL bOK = GetFileVersionInfo(strFileNAP, dwBytes, LPVOID(pBuffer));
			if(bOK){
				
				VS_FIXEDFILEINFO * pFFInfo = 0;
				UINT dwBytesRet = 0L;

				//The memory pointed to by *lplpBuffer is freed when 
				//the associated pBlock memory is freed. 
				bOK = ::VerQueryValue(
									LPVOID(pBuffer)
									, _T("\\")
									, reinterpret_cast<LPVOID *>(&pFFInfo)
									, &dwBytesRet
								);

				if(bOK && pFFInfo){
					ffinfo = *pFFInfo;
					bGotInfo = true;
				}
			}

			delete [] pBuffer;
		}
	}

	return bGotInfo;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 21:46:11
	DESCRIP:	
		Don't want to pass a non-const string to the function
		so wrap it up a bit;

		DWORD GetFileVersionInfoSize(
		  LPTSTR lptstrFilename,  // pointer to filename string
		  LPDWORD lpdwHandle      // pointer to variable to receive zero
		);

	IN:
	OUT:
*/
DWORD CFileMetaData::GetFileVersionInfoSize(const CString & strFileName) const
{
	DWORD dwHandle = 0L;
	DWORD dwRet = 0L;

	CString strNonConst(strFileName);
	
	dwRet = ::GetFileVersionInfoSize(strNonConst.GetBuffer(strNonConst.GetLength()), &dwHandle);
	strNonConst.ReleaseBuffer();

	//dwErr, hr	0x00000714 (1812) The specified image file did not contain a resource section. 
	//dwErr, hr	0x00000715 (1813) The specified resource type cannot be found in the image file. 
	if(!dwRet){
		DWORD dwErr = ::GetLastError();

		//is it an 'expected' error?
		switch(dwErr){
			case ERROR_RESOURCE_TYPE_NOT_FOUND:
			case ERROR_RESOURCE_DATA_NOT_FOUND:
			case ERROR_FILE_NOT_FOUND:
				break;

			default:
				ATLTRACE(_T("GetFileVersionInfoSize error %i\n"), dwErr);	//0x00000714
				ATLASSERT(false);
		}

	}

	return dwRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/04/2007 21:51:57
	DESCRIP:	
		Don't want to pass a non-const string to the function
		so wrap it up a bit;

		BOOL GetFileVersionInfo(
		  LPTSTR lptstrFilename,  // pointer to filename string
		  DWORD dwHandle,         // ignored
		  DWORD dwLen,            // size of buffer
		  LPVOID lpData           // pointer to buffer to receive 
		                          // file-version info.
		);
	IN:
	OUT:
*/
BOOL CFileMetaData::GetFileVersionInfo(
								  const CString & strFileName		// pointer to filename string
								  , DWORD dwLen						// size of buffer
								  , LPVOID lpData					// pointer to buffer to receive file-version info.
								) const
{
	DWORD dwHandle = 0L;
	BOOL bRet = FALSE;

	CString strNonConst(strFileName);
	
	bRet = ::GetFileVersionInfo(
							strNonConst.GetBuffer(strNonConst.GetLength())
							, dwHandle
							, dwLen
							, lpData
						);

	strNonConst.ReleaseBuffer();

	if(!bRet){
		DWORD dwErr = ::GetLastError();
		ATLTRACE(_T("GetFileVersionInfo error %i\n"), dwErr);
	}

	return bRet;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   30 October 2006 19:17:14	
	DESC:		
	IN:
	OUT:
*/
//bool CFileMetaData::GetFileInfoStrings(const CString & strFileNAP, CFileInfoStrings & infostrings) const 
//{
//	//return GetFileInfoStrings001(strFileNAP, infostrings);
//	return GetFileInfoStrings002(strFileNAP, infostrings);
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   30 October 2006 19:42:04	
	DESC:		
	IN:
	OUT:
*/
bool CFileMetaData::GetFileInfoStrings(const CString & strFileNAP, CFileInfoStrings & infostrings) const
{
#pragma message(__LOC__ "Function too long")

	bool bGotInfo = false;

	DWORD dwIgnored = 0L;
	DWORD dwBytes = GetFileVersionInfoSize(strFileNAP);

	if(dwBytes){
		BYTE * pBuffer = new BYTE[dwBytes];
		ATLASSERT(pBuffer);

		if(pBuffer){

			BOOL bOK = GetFileVersionInfo(strFileNAP, dwBytes, LPVOID(pBuffer));

			if(bOK){
				CString		strSubBlock;
				UINT		dwQryBytes		= 0L;
				UINT		dwTranslated	= 0L;
				TCHAR *		pszFileInfo		= 0;
			
				for(DWORD dwWhichInfo = 0L ; dwWhichInfo < eFIStr__LAST ; dwWhichInfo++ ){

					strSubBlock.Format(
							_T("\\StringFileInfo\\%04x%04x\\%s")
							, infostrings.GetLanguage()
							, infostrings.GetCodePage()
							, szsFILEINFO_IDENTS[dwWhichInfo]
						);

					pszFileInfo = 0;
					
					// Retrieve info for language and code page 
					bOK = ::VerQueryValue(
								pBuffer
								, strSubBlock.GetBuffer(strSubBlock.GetLength())		//.AllocSysString() 
								, reinterpret_cast<LPVOID *>(&pszFileInfo)
								, &dwQryBytes
							); 

					//if(pszFileInfo && bOK){
						infostrings.SetFileInfoString(
												eFILEINFO_STRING(dwWhichInfo)
												, pszFileInfo
											);
					//}
				}
			}

			delete [] pBuffer;
		}
	}

	return bGotInfo;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 19:05:01	
	DESC:		
	IN:
	OUT:

	The following are predefined version information Unicode strings: 

	Comments			InternalName		ProductName 
	CompanyName			LegalCopyright		ProductVersion 
	FileDescription		LegalTrademarks		PrivateBuild 
	FileVersion			OriginalFilename	SpecialBuild 
*/
//bool CFileMetaData::GetFileInfoStrings001(const CString & strFileNAP, CFileInfoStrings & infostrings) const
//{
//#pragma message(__LOC__ "Function too long")
//
//	bool bGotInfo = false;
//
//	DWORD dwIgnored = 0L;
//	DWORD dwBytes = GetFileVersionInfoSize(strFileNAP);
//
//	if(dwBytes){
//		BYTE * pBuffer = new BYTE[dwBytes];
//		ATLASSERT(pBuffer);
//
//		if(pBuffer){
//
//			BOOL bOK = GetFileVersionInfo(strFileNAP, dwBytes, LPVOID(pBuffer));
//
//			if(bOK){
//				CString		strSubBlock;
//				UINT		dwQryBytes		= 0L;
//				UINT		dwTranslated	= 0L;
//				TCHAR *		pszFileInfo		= 0;
//
//				//struct LANGANDCODEPAGE {
//				//	WORD wLanguage;
//				//	WORD wCodePage;
//				//} *lpTranslate;
//
//				// Read the list of languages and code pages.
//
//				//bOK = ::VerQueryValue(
//				//			pBuffer
//				//			, _T("\\VarFileInfo\\Translation")
//				//			, reinterpret_cast<LPVOID *>(&lpTranslate)
//				//			, &dwTranslated
//				//		);
//				
//				if(!bOK)
//					infostrings.Reset(_T("<No Translation code pages>"));
//
//				else{
//					for(DWORD dwWhichInfo = 0L ; dwWhichInfo < eFIStr__LAST ; dwWhichInfo++ ){
//
//						//strSubBlock.Format(
//						//		_T("\\StringFileInfo\\%04x%04x\\%s")
//						//		, lpTranslate[0L].wLanguage
//						//		, lpTranslate[0L].wCodePage
//						//		, szsFILEINFO_IDENTS[dwWhichInfo]
//						//	);
//
//						strSubBlock.Format(
//								_T("\\StringFileInfo\\%04x%04x\\%s")
//								, infostrings.GetLanguage()		//lpTranslate[0L].wLanguage
//								, infostrings.GetCodePage()		//lpTranslate[0L].wCodePage
//								, szsFILEINFO_IDENTS[dwWhichInfo]
//							);
//
//						// Retrieve info for language and code page 
//						bOK = ::VerQueryValue(
//									pBuffer
//									, strSubBlock.GetBuffer(strSubBlock.GetLength())		//.AllocSysString() 
//									, reinterpret_cast<LPVOID *>(&pszFileInfo)
//									, &dwQryBytes
//								); 
//
//						if(pszFileInfo && bOK){
//							infostrings.SetFileInfoString(
//													eFILEINFO_STRING(dwWhichInfo)
//													, pszFileInfo
//												);
//						}
//					}
//				}
//			}
//
//			delete [] pBuffer;
//		}
//	}
//
//	return bGotInfo;
//}
