// PropSheetCommon.cpp: implementation of the CPropSheetCommon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "PropSheetCommon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPropSheetCommon::CPropSheetCommon()
{

}

CPropSheetCommon::~CPropSheetCommon()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 10:28:42
	DESCRIP:	
	IN:
	OUT:
*/
void CPropSheetCommon::InitFonts(CDC * pdc)
{
	for(DWORD dwLoop = 0 ; dwLoop < eFont__LAST ; dwLoop ++){

		m_fonts[dwLoop].InitFont(
								pdc
								, isFONT_POINTS		[dwLoop]
								, isFONT_WEIGHTS	[dwLoop]
								, szsFONT_FACE		[dwLoop]
							);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/03/2007 10:28:40
	DESCRIP:	
	IN:
	OUT:
*/
CFont * CPropSheetCommon::GetTheFont(const eFont eWhichFont)
{
	return m_fonts[eWhichFont].GetFont();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	01/05/2007 10:10:13
	DESCRIP:	
	IN:
	OUT:
*/
void CPropSheetCommon::SetDlgItemFont(CWnd * pParent, const DWORD dwCtlID, const eFont eWhichFont)
{
	if(pParent && ::IsWindow(pParent->m_hWnd)){

		CWnd * pCtl = pParent->GetDlgItem(dwCtlID);

		if(pCtl && ::IsWindow(pCtl->m_hWnd)){
			pCtl->SetFont(GetTheFont(eWhichFont));
		}
		else{
			ATLTRACE(_T("!!!! CPropSheetCommon::SetDlgItemFont - invalid CWnd * pCtl\n"));
		}

	}
	else{
		ATLTRACE(_T("!!!! CPropSheetCommon::SetDlgItemFont - invalid CWnd * pParent\n"));
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 08:46:17
	DESCRIP:	
	IN:
	OUT:
*/
void CPropSheetCommon::InitTabCtrl(CTabCtrl * pTab)
{
	ASSERT(pTab && ::IsWindow(pTab->m_hWnd));

	if(pTab && ::IsWindow(pTab->m_hWnd)){
		pTab->SetFont(GetTheFont(eFont_Tab));
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	17/04/2007 10:55:37
	DESCRIP:	
	IN:
	OUT:
*/
void CPropSheetCommon::ExploreDirectory(HWND hWnd, const CString & strDir)
{
	HINSTANCE hInst = ::ShellExecute(
								hWnd				//HWND hwnd, 
								, _T("explore")		//LPCTSTR lpOperation,
								, strDir			//LPCTSTR lpFile, 
								, _T("")			//LPCTSTR lpParameters, 
								, strDir			//LPCTSTR lpDirectory,
								, SW_NORMAL			//INT nShowCmd
							);

	long iRet = long(hInst);

	if(iRet <= 32){

		CString strErr;
	
		//Returns a value greater than 32 if successful, or an error value that is less than 
		//or equal to 32 otherwise. The following table lists the error values. The return 
		//value is cast as an HINSTANCE for backward compatibility with 16-bit Windows 
		//applications. 
		switch(iRet){
			case 0:							strErr = _T("The operating system is out of memory or resources.");													break;
			//case SE_ERR_FNF:				strErr = _T("The specified file was not found.");																	break;
			case ERROR_FILE_NOT_FOUND:		strErr = _T("The specified file was not found.");																	break;
			//case SE_ERR_PNF:				strErr = _T("The specified path was not found.");																	break;
			case ERROR_PATH_NOT_FOUND:		strErr = _T("The specified path was not found.");																	break;
			case ERROR_BAD_FORMAT:			strErr = _T("The .exe file is invalid (non-Win32® .exe or error in .exe image).");									break;
			case SE_ERR_ACCESSDENIED:		strErr = _T("The operating system denied access to the specified file.");											break;
			case SE_ERR_ASSOCINCOMPLETE:	strErr = _T("The file name association is incomplete or invalid.");													break;
			case SE_ERR_DDEBUSY:			strErr = _T("The DDE transaction could not be completed because other DDE transactions were being processed.");		break;
			case SE_ERR_DDEFAIL:			strErr = _T("The DDE transaction failed.");																			break;
			case SE_ERR_DDETIMEOUT:			strErr = _T("The DDE transaction could not be completed because the request timed out.");							break;
			case SE_ERR_DLLNOTFOUND:		strErr = _T("The specified dynamic-link library was not found.");													break;
			case SE_ERR_NOASSOC:			strErr = _T("There is no application associated with the given file name extension.");								break;
			case SE_ERR_OOM:				strErr = _T("There was not enough memory to complete the operation.");												break;
			case SE_ERR_SHARE:				strErr = _T("A sharing violation occurred.");																		break;

			default:
				strErr.Format(_T("Unknown ::ShellExecute error %i (0x%X)"), iRet, iRet);
				break;
		}

		::AfxMessageBox(strErr, MB_ICONEXCLAMATION);
	}
}
