#pragma once

#include ".\fileinfostrings.h"
#include ".\fixedfileinfo.h"
//#include ".\resourceupdater.h"

class CFileMetaData
{
public:
	CFileMetaData(void);
	~CFileMetaData(void);

public:
	bool GetFixedFileInfo(const CString & strFileNAP, CFixedFileInfo & ffinfo) const ;
	//bool SetFixedFileInfo(const CString & strFileNAP, const CFixedFileInfo & ffinfo) const;

	DWORD GetFileVersionInfoSize(const CString & strFileName) const;
	
	BOOL GetFileVersionInfo(
					  const CString & strFileName		// pointer to filename string
					  , DWORD dwLen						// size of buffer
					  , LPVOID lpData					// pointer to buffer to receive file-version info.
					) const;

public:
	bool GetFileInfoStrings(const CString & strFileNAP, CFileInfoStrings & infostrings) const ;

private:
	//bool GetFileInfoStrings001(const CString & strFileNAP, CFileInfoStrings & infostrings) const ;
	//bool GetFileInfoStrings002(const CString & strFileNAP, CFileInfoStrings & infostrings) const ;
};
