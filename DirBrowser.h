#pragma once



#ifndef BFFM_VALIDATEFAILED
  #ifdef UNICODE
		const int BFFM_VALIDATEFAILED = 4;
  #else
		const int BFFM_VALIDATEFAILED = 3;
  #endif
#endif // !BFFM_VALIDATEFAILED

#ifndef BFFM_IUNKNOWN
		const int BFFM_IUNKNOWN = 5;
#endif // !BFFM_IUNKNOWN

#ifndef BIF_NEWDIALOGSTYLE
		//const UINT BIF_NEWDIALOGSTYLE = 0x0040;
		const UINT BIF_NEWDIALOGSTYLE = 0x0040;
#endif // !BIF_NEWDIALOGSTYLE

#ifndef BIF_EDITBOX
		const UINT BIF_EDITBOX	= 0x0010;   // Add an editbox to the dialog
#endif

#ifndef BIF_USENEWUI
		const UINT BIF_USENEWUI	= BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
		//const UINT BIF_USENEWUI	= 0L;
#endif

namespace DIR_BROWSER{

const DWORD dwINITSTR_BUFFSIZE = _MAX_PATH + 5;

//#include "dirbrowser.h"
//using namespace DIR_BROWSER;
class CDirBrowser
{
public:
	CDirBrowser(void);
	~CDirBrowser(void);

public:
	bool BrowseForDirectory(
						const CString & strTitle
						, CString & strBrowsedDir
					);

	bool BrowseForFile(
						const CString & strTitle
						, const CString & strInitDir
						, CString & strBrowsed
					);
	
	bool BrowseForComputer(
						const CString & strTitle
						, CString & strBrowsed
					);

	CString GetUNCPath(const CString & strPath) const;
	CString GetDirName(const CString & strUNCPath) const;

	CString GetCurComputerName(void) const;

private:
	void AdjustInitDir(const CString & strInit);

	void InitBrowseInfo(
						const CString & strTitle
						, const DWORD dwFlags
						, BROWSEINFO & brinfo
					);

private:
	static int CALLBACK BrowseCallbackProc(          
										HWND hwnd
										, UINT uMsg
										, LPARAM lParam
										, LPARAM lpData
									);

	static TCHAR m_szInitDirectory[dwINITSTR_BUFFSIZE + 1];
};



}	//end of namespace DIR_BROWSER
