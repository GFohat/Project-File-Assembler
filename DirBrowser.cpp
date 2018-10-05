#include "StdAfx.h"
#include "dirbrowser.h"


namespace DIR_BROWSER{
	
/*static*/ TCHAR CDirBrowser::m_szInitDirectory[] = {0};


CDirBrowser::CDirBrowser(void)
{
	//HRESULT hr = ::CoInitialize(0);
	//ATLTRACE(_T("0x%X\n"), hr);
}

CDirBrowser::~CDirBrowser(void)
{
	//::CoUninitialize();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 07:53:58
	DESCRIP:	
	IN:
	OUT:
*/
void CDirBrowser::InitBrowseInfo(
								const CString & strTitle
								, const DWORD dwFlags
								, BROWSEINFO & brinfo
							)
{
	::ZeroMemory(&brinfo, sizeof(BROWSEINFO));

	brinfo.hwndOwner;
	brinfo.iImage;
	brinfo.lParam;
	brinfo.pidlRoot;

	brinfo.lpfn				= BrowseCallbackProc;
	brinfo.lpszTitle		= strTitle;
	brinfo.ulFlags			= dwFlags;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   24 September 2005 07:46:59	
	DESC:		
	IN:
	OUT:
*/
bool CDirBrowser::BrowseForDirectory(
								const CString & strTitle
								, CString & strBrowsedDir
							)
{
	const DWORD dwBUFSIZE = 1024L;
	TCHAR szItemPath[dwBUFSIZE + 5] = {0};

	AdjustInitDir(strBrowsedDir);

	ITEMIDLIST * pIdl = 0;

	DWORD dwFlags	=	0 
						//| BIF_USENEWUI
						| BIF_NEWDIALOGSTYLE 
						| BIF_EDITBOX
						| BIF_RETURNONLYFSDIRS
					;


	BROWSEINFO brinfo;

	InitBrowseInfo(strTitle, dwFlags, brinfo);

	pIdl = ::SHBrowseForFolder(&brinfo);

	bool bBrowsed = pIdl ? true : false;

	if(bBrowsed){
		BOOL bGotPath = ::SHGetPathFromIDList(pIdl, szItemPath);
		if(bGotPath)
			strBrowsedDir = szItemPath;
		else
			bBrowsed = false;

		//The calling application is responsible for freeing the 
		//returned PIDL by using the Shell allocator's IMalloc::Free method. 
		//To retrieve a handle to that IMalloc interface, call SHGetMalloc. 
		/*
			SHGetMalloc Function
			This function should no longer be used. Use the CoTaskMemFree 
			and CoTaskMemAlloc functions in its place.
		*/
		::CoTaskMemFree(pIdl);
	}

	//delete [] brinfo.pszDisplayName;

	return bBrowsed;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23-Jan-2006 11:45:24
	DESC:	
	IN:		
	OUT:	
*/
bool CDirBrowser::BrowseForFile(
								const CString & strTitle
								, const CString & strInitDir
								, CString & strBrowsed
							)
{
	const DWORD dwBUFSIZE = 1024L;
	TCHAR szItemPath[dwBUFSIZE + 5] = {0};

	AdjustInitDir(strInitDir);

	ITEMIDLIST * pIdl = 0;
	
	DWORD dwFlags =	0 
					| BIF_USENEWUI
					| BIF_RETURNONLYFSDIRS
					| BIF_BROWSEINCLUDEFILES
				;

	BROWSEINFO brinfo;

	InitBrowseInfo(strTitle, dwFlags, brinfo);

	pIdl = ::SHBrowseForFolder(&brinfo);

	bool bBrowsed = pIdl ? true : false;

	if(bBrowsed){
		BOOL bGotPath = ::SHGetPathFromIDList(pIdl, szItemPath);
		if(bGotPath)
			strBrowsed = szItemPath;
		else
			bBrowsed = false;

		//The calling application is responsible for freeing the 
		//returned PIDL by using the Shell allocator's IMalloc::Free method. 
		//To retrieve a handle to that IMalloc interface, call SHGetMalloc. 
		/*
			SHGetMalloc Function
			This function should no longer be used. Use the CoTaskMemFree 
			and CoTaskMemAlloc functions in its place.
		*/
		::CoTaskMemFree(pIdl);
	}

	return bBrowsed;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23-Jan-2006 11:45:24
	DESC:	
	IN:		
	OUT:	
*/
bool CDirBrowser::BrowseForComputer(
								const CString & strTitle
								, CString & strBrowsed
							)
{
	const DWORD dwBUFSIZE = 1024L;
	TCHAR szItemPath[dwBUFSIZE + 5] = {0};

	AdjustInitDir(strBrowsed);

	ITEMIDLIST * pIdl = 0;
	
	DWORD dwFlags =		0
						| BIF_BROWSEFORCOMPUTER
						| BIF_USENEWUI
					;

	BROWSEINFO brinfo;

	InitBrowseInfo(strTitle, dwFlags, brinfo);

	brinfo.pszDisplayName	= new TCHAR[MAX_PATH];

	pIdl = ::SHBrowseForFolder(&brinfo);

	bool bBrowsed = pIdl ? true : false;

	if(bBrowsed){
		/*
			The server can not be retrieved using this pidl in a call to 
			SHGetPathFromIDList because a server is not a valid file 
			system object.
		*/
		//BOOL bGotPath = ::SHGetPathFromIDList(pIdl, szItemPath);
		//if(bGotPath)
		//	strBrowsed = szItemPath;
		//else
		//	bBrowsed = false;
		strBrowsed.Format(_T("\\\\%s"), brinfo.pszDisplayName);

		//The calling application is responsible for freeing the 
		//returned PIDL by using the Shell allocator's IMalloc::Free method. 
		//To retrieve a handle to that IMalloc interface, call SHGetMalloc. 
		/*
			SHGetMalloc Function
			This function should no longer be used. Use the CoTaskMemFree 
			and CoTaskMemAlloc functions in its place.
		*/
		::CoTaskMemFree(pIdl);
	}

	if(brinfo.pszDisplayName)
		delete [] brinfo.pszDisplayName;

	return bBrowsed;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 07:48:10
	DESCRIP:	
	IN:
	OUT:
*/
void CDirBrowser::AdjustInitDir(const CString & strInit)
{
	if(!strInit.IsEmpty())
		_tcscpy(m_szInitDirectory, strInit.Left(dwINITSTR_BUFFSIZE));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	27-Sep-2005 10:18:56
	DESC:	
		hwnd
			Window handle of the browse dialog box.
		
		uMsg
			Dialog box event that generated the message. One of the following values:
			BFFM_INITIALIZED		The dialog box has finished initializing.
			BFFM_IUNKNOWN			An IUnknown interface is available to the dialog box.
			BFFM_SELCHANGED			The selection has changed in the dialog box.
			BFFM_VALIDATEFAILED		Version 4.71. The user typed an invalid name into 
									the dialog's edit box. A nonexistent folder is 
									considered an invalid name.
		
		lParam
			Value whose meaning depends on the event specified in uMsg as follows: 
			
			uMsg					lParam 
			
			BFFM_INITIALIZED		Not used, value is NULL. 
			
			BFFM_IUNKNOWN			Pointer to an IUnknown interface. 

			BFFM_SELCHANGED			Pointer to an item identifier list (PIDL) 
									identifying the newly selected item. 

			BFFM_VALIDATEFAILED		Pointer to a string containing the invalid name. 
									An application can use this data in an error dialog 
									informing the user that the name was not valid. 

		lpData
			Application-defined value that was specified in the lParam member of the 
			BROWSEINFO structure used in the call to SHBrowseForFolder.
	IN:		
	OUT:	
		Returns zero except in the case of BFFM_VALIDATEFAILED. For that flag, 
		returns zero to dismiss the dialog or nonzero to keep the dialog displayed.
*/
/*static*/ 
int CALLBACK CDirBrowser::BrowseCallbackProc(          
										HWND hwnd
										, UINT uMsg
										, LPARAM lParam
										, LPARAM lpData
									)
{
	switch(uMsg){
		case BFFM_INITIALIZED:		
			::SendMessage(hwnd, BFFM_SETSELECTION, 1, (LPARAM)m_szInitDirectory);
			break;

		case BFFM_IUNKNOWN:			
			{
				ATLTRACE(_T("BrowseCallbackProc BFFM_IUNKNOWN\n"));		
				//IUnknown * pUnk = reinterpret_cast<IUnknown *>();
				//CComPtr<IUnknown> spUnknown = reinterpret_cast<IUnknown *>(lParam);
			}
			break;
		
		//this sets the text of the status edit box...
		case BFFM_SELCHANGED:
			{
				TCHAR szText[MAX_PATH] = {0};

				::SHGetPathFromIDList(reinterpret_cast<LPITEMIDLIST>(lParam), szText);
				::SendMessage(hwnd, BFFM_SETSTATUSTEXT, 0, reinterpret_cast<LPARAM>(szText));
				
				//ATLTRACE(_T("BrowseCallbackProc BFFM_SELCHANGED \"%s\"\n"), szText);		
			}
			break;

		case BFFM_VALIDATEFAILED:	
			ATLTRACE(_T("BrowseCallbackProc BFFM_VALIDATEFAILED\n"));	
			break;

		default:
			ATLTRACE(_T("BrowseCallbackProc unknown message\n"));
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   24 September 2005 08:59:24	
	DESC:		
	IN:
	OUT:
*/
CString CDirBrowser::GetUNCPath(const CString & strPath) const
{
	CString strRet;

	if(_T("\\\\") == strPath.Left(2))
		strRet = strPath;

	else{
		TCHAR szDrive	[_MAX_DRIVE];
		TCHAR szDir		[_MAX_DIR];
		TCHAR szFName	[_MAX_FNAME];
		TCHAR szExt		[_MAX_EXT];

		_tsplitpath(strPath, szDrive, szDir, szFName, szExt);

		CString strComputerName = GetCurComputerName();

		strRet.Format(
						_T("\\\\%s\\%c$%s%s%s")
						, strComputerName
						, szDrive[0]
						, szDir
						, szFName
						, szExt
					);

		strRet.TrimRight(_T("\\"));
	}

	return strRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07-Nov-2005 09:26:35
	DESC:	
	IN:		
	OUT:	
*/
CString CDirBrowser::GetDirName(const CString & strUNCPath) const
{
	CString strDirName;

	//there should NOT be a '\' at the end of strUNCPath

	int iLastSlash = strUNCPath.ReverseFind(_T('\\'));
	if(iLastSlash < 0)
		strDirName = strUNCPath;

	else{
		int iRight = strUNCPath.GetLength() - iLastSlash - 1;
		strDirName = strUNCPath.Right(iRight);
	}

	return strDirName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   24 September 2005 09:03:25	
	DESC:		
	IN:
	OUT:
*/
CString CDirBrowser::GetCurComputerName(void) const
{
	static TCHAR szComputerName[MAX_COMPUTERNAME_LENGTH + 5];
	static bool bSet = false;

	if(!bSet){
		DWORD dwNameLength = MAX_COMPUTERNAME_LENGTH;
		::GetComputerName(szComputerName, &dwNameLength);
		bSet = true;
	}

	return szComputerName;
}




}	//end of namespace DIR_BROWSER
