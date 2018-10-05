#include "StdAfx.h"
#include ".\fixedfileinfo.h"

CFixedFileInfo::CFixedFileInfo(void)
:	m_bDataValid(false)
{
	::ZeroMemory(&m_fixedfileinfo, sizeof(VS_FIXEDFILEINFO));
	ResetEnables(false);
}

CFixedFileInfo::~CFixedFileInfo(void)
{
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 15:09:05	
	DESC:		
	IN:
	OUT:
*/
//void CFixedFileInfo::SetFileVersion(const WORD wdHH, const WORD wdHL, const WORD wdLH, const WORD wdLL)
//{
//	m_fixedfileinfo.dwFileVersionMS = DWORD(MAKELONG(wdHL, wdHH));	//low, high
//	m_fixedfileinfo.dwFileVersionLS = DWORD(MAKELONG(wdLL, wdLH));	//low, high
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 15:09:08	
	DESC:		
	IN:
	OUT:
*/
//void CFixedFileInfo::SetProductVersion(const WORD wdHH, const WORD wdHL, const WORD wdLH, const WORD wdLL)
//{
//	m_fixedfileinfo.dwProductVersionMS = DWORD(MAKELONG(wdHL, wdHH));	//low, high
//	m_fixedfileinfo.dwProductVersionLS = DWORD(MAKELONG(wdLL, wdLH));	//low, high
//}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 14:49:00	
	DESC:		
	IN:
	OUT:
*/
CString CFixedFileInfo::GetFileMetaData(const eMETA_TYPE eType) const
{
	CString strRet(_T("Invalid eMETA_TYPE"));

	switch(eType){
		case eMeta_FileVersion:		strRet = GetFileVersion();		break;
		case eMeta_ProductVersion:	strRet = GetProductVersion();	break;
		case eMeta_Signature:		strRet = GetSignature();		break;
		case eMeta_StrucVersion:	strRet = GetStrucVersion();		break;		
		case eMeta_FileFlagsMask:	strRet = GetFileFlagsMask();	break;	
		case eMeta_FileFlags:		strRet = GetFileFlags();		break;		
		case eMeta_FileOS:			strRet = GetFileOS();			break;			
		case eMeta_FileType:		strRet = GetFileType();			break;			
		case eMeta_FileSubtype:		strRet = GetFileSubtype();		break;		
		case eMeta_FileDate:		strRet = GetFileDate();			break;			
	}

	return strRet;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   03 November 2006 19:47:22	
	DESC:		
	IN:
	OUT:
*/
void CFixedFileInfo::ResetEnables(const bool bEnable)
{
	for(DWORD dwLoop = 0L ; dwLoop < eMeta__LAST ; dwLoop++)
		m_bsEnableEditMetaData[dwLoop] = bEnable;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   03 November 2006 20:13:24	
	DESC:		
	IN:
	OUT:
*/
bool CFixedFileInfo::SetEditEnable(const DWORD dwMetaType, const bool bEnable)
{
	bool bOK = false;

	if(dwMetaType < eMeta__LAST){
		bOK = true;

		m_bsEnableEditMetaData[dwMetaType] = bEnable;
	}

	return bOK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 12:31:41	
	DESC:		
	IN:
	OUT:
*/
const CFixedFileInfo & CFixedFileInfo::operator = (const VS_FIXEDFILEINFO & ffinfo)
{
	memcpy(&m_fixedfileinfo, &ffinfo, sizeof(VS_FIXEDFILEINFO));
	m_bDataValid = true;

	return * this;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   30 October 2006 21:28:43	
	DESC:		
typedef struct tagVS_FIXEDFILEINFO
{
    DWORD   dwSignature;            // e.g. 0xfeef04bd 
    DWORD   dwStrucVersion;         // e.g. 0x00000042 = "0.42" 
    DWORD   dwFileVersionMS;        // e.g. 0x00030075 = "3.75" 
    DWORD   dwFileVersionLS;        // e.g. 0x00000031 = "0.31" 
    DWORD   dwProductVersionMS;     // e.g. 0x00030010 = "3.10" 
    DWORD   dwProductVersionLS;     // e.g. 0x00000031 = "0.31" 
    DWORD   dwFileFlagsMask;        // = 0x3F for version "0.42" 
    DWORD   dwFileFlags;            // e.g. VFF_DEBUG | VFF_PRERELEASE 
    DWORD   dwFileOS;               // e.g. VOS_DOS_WINDOWS16 
    DWORD   dwFileType;             // e.g. VFT_DRIVER 
    DWORD   dwFileSubtype;          // e.g. VFT2_DRV_KEYBOARD 
    DWORD   dwFileDateMS;           // e.g. 0 
    DWORD   dwFileDateLS;           // e.g. 0 
} VS_FIXEDFILEINFO;
	IN:
	OUT:
*/
//void CFixedFileInfo::operator >> (VS_FIXEDFILEINFO & ffinfo) const
//{
//	//memcpy(&ffinfo, &m_fixedfileinfo, sizeof(VS_FIXEDFILEINFO));
//	for(DWORD dwLoop = 0L ; dwLoop < eMeta__LAST ; dwLoop ++){
//		if(m_bsEnableEditMetaData[dwLoop])
//			SetFixedFileInfo(ffinfo, dwLoop);
//	}
//}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   03 November 2006 20:03:25	
	DESC:		
	IN:
	OUT:
*/
//void CFixedFileInfo::SetFixedFileInfo(VS_FIXEDFILEINFO & ffinfo, const DWORD dwMetaType) const
//{
//	switch(dwMetaType){
//		case eMeta_FileVersion:		
//			ffinfo.dwFileVersionLS = m_fixedfileinfo.dwFileVersionLS;	
//			ffinfo.dwFileVersionMS = m_fixedfileinfo.dwFileVersionMS;	
//			break;
//
//		case eMeta_ProductVersion:	
//			ffinfo.dwProductVersionLS = m_fixedfileinfo.dwProductVersionLS;	
//			ffinfo.dwProductVersionMS = m_fixedfileinfo.dwProductVersionMS;	
//			break;
//
//		case eMeta_FileDate:		
//			ffinfo.dwFileDateLS = m_fixedfileinfo.dwFileDateLS;		
//			ffinfo.dwFileDateMS = m_fixedfileinfo.dwFileDateMS;		
//			break;
//
//		case eMeta_Signature:		ffinfo.dwSignature		= m_fixedfileinfo.dwSignature;		break;
//		case eMeta_StrucVersion:	ffinfo.dwStrucVersion	= m_fixedfileinfo.dwStrucVersion;	break;
//		case eMeta_FileFlagsMask:	ffinfo.dwFileFlagsMask	= m_fixedfileinfo.dwFileFlagsMask;	break;
//		case eMeta_FileFlags:		ffinfo.dwFileFlags		= m_fixedfileinfo.dwFileFlags;		break;
//		case eMeta_FileOS:			ffinfo.dwFileOS			= m_fixedfileinfo.dwFileOS;			break;
//		case eMeta_FileType:		ffinfo.dwFileType		= m_fixedfileinfo.dwFileType;		break;
//		case eMeta_FileSubtype:		ffinfo.dwFileSubtype	= m_fixedfileinfo.dwFileSubtype;	break;
//		default:
//			ATLASSERT(false);
//	}
//}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/04/2007 07:56:03
	DESCRIP:	
	IN:
	OUT:
*/
eCMP_RSLT CFixedFileInfo::CompareFFInfo(const CFixedFileInfo & rCmp) const
{
	eCMP_RSLT eCmp = eCmpRslt_None;

	//both valid...
	if(m_bDataValid && rCmp.m_bDataValid){

		CString strThisVer = GetFileVersion();
		CString strThatVer = rCmp.GetFileVersion();

		//	< 0		string1 less than string2 
		//	0		string1 identical to string2 
		//	> 0		string1 greater than string2 
		// a greater string is a 'better' version
		int iCompare = _tcsicmp(strThisVer, strThatVer);

		if(iCompare < 0)
			eCmp = eCmpRslt_SecondBetter;

		else if (iCompare > 0)
			eCmp = eCmpRslt_FirstBetter;

		else
			eCmp = eCmpRslt_NoDifference;
	}
	

	//we're valid, they're not...
	else if(m_bDataValid)
		eCmp = eCmpRslt_FirstBetter;

	//they're valid, we're not...
	else if(rCmp.m_bDataValid)
		eCmp = eCmpRslt_SecondBetter;

	return eCmp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 14:33:45	
	DESC:		
	IN:
	OUT:
*/
CString CFixedFileInfo::GetFileVersion(void) const
{
	CString strRet(_T("<Invalid>"));
	
	if(m_bDataValid)
		strRet.Format(
					_T("%03i, %03i, %03i, %03i")
					, HIWORD(m_fixedfileinfo.dwFileVersionMS)
					, LOWORD(m_fixedfileinfo.dwFileVersionMS)
					, HIWORD(m_fixedfileinfo.dwFileVersionLS)
					, LOWORD(m_fixedfileinfo.dwFileVersionLS)
				);

	return strRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 14:33:48	
	DESC:		
	IN:
	OUT:
*/
CString CFixedFileInfo::GetProductVersion(void) const
{
	CString strRet(_T("<Invalid>"));
	
	if(m_bDataValid)
		strRet.Format(
					_T("%i, %i, %i, %i")
					, HIWORD(m_fixedfileinfo.dwProductVersionMS)
					, LOWORD(m_fixedfileinfo.dwProductVersionMS)
					, HIWORD(m_fixedfileinfo.dwProductVersionLS)
					, LOWORD(m_fixedfileinfo.dwProductVersionLS)
				);

	return strRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 14:33:51	
	DESC:		
	IN:
	OUT:
*/
CString CFixedFileInfo::GetSignature(void) const	/* e.g. 0xfeef04bd */
{
	CString strRet(_T("<Invalid>"));

	if(m_bDataValid)
		strRet.Format(_T("0x%X"), m_fixedfileinfo.dwSignature);

	return strRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 14:33:54	
	DESC:		
	IN:
	OUT:
*/
CString CFixedFileInfo::GetStrucVersion(void) const	/* e.g. 0x00000042 = "0.42" */
{
	CString strRet(_T("<Invalid>"));
	if(m_bDataValid)
		strRet.Format(_T("0x%X"), m_fixedfileinfo.dwStrucVersion);
	return strRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 14:33:58	
	DESC:		
	IN:
	OUT:
*/
CString CFixedFileInfo::GetFileFlagsMask(void) const	/* = 0x3F for version "0.42" */
{
	CString strRet(_T("<Invalid>"));
	if(m_bDataValid)
		strRet.Format(_T("0x%X"), m_fixedfileinfo.dwFileFlagsMask);
	return strRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 14:34:00	
	DESC:		
	IN:
	OUT:
*/
CString CFixedFileInfo::GetFileFlags(void) const	/* e.g. VFF_DEBUG | VFF_PRERELEASE */
{
	CString strRet(_T("<Invalid>"));
	if(m_bDataValid)
		strRet.Format(_T("0x%X"), m_fixedfileinfo.dwFileFlags);
	return strRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 14:34:03	
	DESC:		
	IN:
	OUT:
*/
CString CFixedFileInfo::GetFileOS(void) const	/* e.g. VOS_DOS_WINDOWS16 */
{
	CString strRet(_T("<Unknown>"));

	if(m_bDataValid)
		switch(m_fixedfileinfo.dwFileOS){
			case VOS_DOS:			strRet = _T("VOS_DOS");				break;
			case VOS_NT:			strRet = _T("VOS_NT");				break;
			case VOS__WINDOWS16:	strRet = _T("VOS__WINDOWS16");		break;
			case VOS__WINDOWS32:	strRet = _T("VOS__WINDOWS32");		break;
			case VOS_OS216:			strRet = _T("VOS_OS216");			break;
			case VOS_OS232:			strRet = _T("VOS_OS232");			break;
			case VOS__PM16:			strRet = _T("VOS__PM16");			break;
			case VOS__PM32:			strRet = _T("VOS__PM32");			break;
			case VOS_UNKNOWN:		strRet = _T("VOS_UNKNOWN");			break;
		}

	return strRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 14:34:07	
	DESC:		
	IN:
	OUT:
*/
CString CFixedFileInfo::GetFileType(void) const	/* e.g. VFT_DRIVER */
{
	CString strRet(_T("<Unknown>"));

	if(m_bDataValid)
		switch(m_fixedfileinfo.dwFileType){
			case VFT_APP:			strRet = _T("VFT_APP");			break;
			case VFT_DLL:			strRet = _T("VFT_DLL");			break;
			case VFT_DRV:			strRet = _T("VFT_DRV");			break;
			case VFT_FONT:			strRet = _T("VFT_FONT");		break;
			case VFT_VXD:			strRet = _T("VFT_VXD");			break;
			case VFT_STATIC_LIB:	strRet = _T("VFT_STATIC_LIB");	break;
			case VFT_UNKNOWN:		strRet = _T("VFT_UNKNOWN");		break;
		}

	return strRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 14:34:09	
	DESC:		
	IN:
	OUT:
*/
CString CFixedFileInfo::GetFileSubtype(void) const	/* e.g. VFT2_DRV_KEYBOARD */
{
	CString strRet(_T("<Unknown>"));

	if(m_bDataValid)
		strRet.Format(_T("0x%X"), m_fixedfileinfo.dwFileSubtype);

	return strRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   29 October 2006 14:34:12	
	DESC:		
		dwFileDateMS
		Specifies the most significant 32 bits of the file's 64-bit 
		binary creation date and time stamp. 
		
		dwFileDateLS
		Specifies the least significant 32 bits of the file's 64-bit 
		binary creation date and time stamp. 
	IN:
	OUT:
*/
CString CFixedFileInfo::GetFileDate(void) const	/* e.g. 0 */
{
	CString strRet(_T("<Invalid>"));
	
	if(m_bDataValid)
		strRet.Format(
					_T("%i, %i, %i, %i")
					, HIWORD(m_fixedfileinfo.dwFileDateMS)
					, LOWORD(m_fixedfileinfo.dwFileDateMS)
					, HIWORD(m_fixedfileinfo.dwFileDateLS)
					, LOWORD(m_fixedfileinfo.dwFileDateLS)
				);

	return strRet;
}
