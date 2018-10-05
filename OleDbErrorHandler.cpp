// OleDbErrorHandler.cpp: implementation of the COleDbErrorHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "OleDbErrorHandler.h"
#include <Oledberr.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COleDbErrorHandler::COleDbErrorHandler()
:	m_hrLastError	(S_OK)
	, m_dwLastTick	(::GetTickCount())
{

}

COleDbErrorHandler::~COleDbErrorHandler()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	15/02/2007 09:04:34
	DESCRIP:
		First cut: 
			1) don't report the same error twice in a row.
			2) don't report an S_OK / S_FALSE etc - (use to reset last error)
	IN:
	OUT:
*/
void COleDbErrorHandler::HandleHR(
								_com_error & e
								, const CString & strFunc
								, const CString & strExtra
								, const CString & strSQL
								, const bool bLog
							)
{
	HRESULT hr = e.Error();

	if(FAILED(hr)){

		if( ! strExtra.IsEmpty())
			ATLTRACE(_T("HandleHR: %s\n"), strExtra.Left(256L));

		if( ! IsRepetition(hr) ){
			
			CComPtr<IErrorInfo> spErrInfo = e.ErrorInfo();

			CString strWarn;
			CString strErrInfo;

			//HRESULT GetDescription (
			//   BSTR *   pbstrDescription);
			if(spErrInfo){
				BSTR bstr;
				
				spErrInfo->GetDescription(&bstr);
				strErrInfo = bstr;

				::SysFreeString(bstr);
			}
		
			strWarn.Format(_T("%s\n\nError 0x%X - %s\n"), strErrInfo, hr, XLateHR(hr));

			if( ! strExtra.IsEmpty())
				strWarn += strExtra;

			::MessageBox(0, strWarn, strFunc, MB_ICONERROR);

			if(bLog){
				LogDbError(strFunc, strWarn, strSQL);
			}
		}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	29/03/2007 15:26:55
	DESCRIP:	
	IN:
	OUT:
*/
bool COleDbErrorHandler::IsRepetition(const HRESULT hr)
{
	bool bRepeat = true;

	if(m_hrLastError != hr)
		bRepeat = false;

	DWORD dwTickLapse = ::GetTickCount() - m_dwLastTick;

	if(bRepeat)
		if(dwTickLapse > 500L)
			bRepeat = false;

	m_hrLastError = hr;
	m_dwLastTick = ::GetTickCount();

	return bRepeat;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	15/02/2007 09:22:15
	DESCRIP:	
		//
		//  Values are 32 bit values layed out as follows:
		//
		//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
		//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
		//  +-+-+-+-+-+---------------------+-------------------------------+
		//  |S|R|C|N|r|    Facility         |               Code            |
		//  +-+-+-+-+-+---------------------+-------------------------------+
		//
		//  where
		//
		//      S - Severity - indicates success/fail
		//
		//          0 - Success
		//          1 - Fail (COERROR)
		//
		//      R - reserved portion of the facility code, corresponds to NT's
		//              second severity bit.
		//
		//      C - reserved portion of the facility code, corresponds to NT's
		//              C field.
		//
		//      N - reserved portion of the facility code. Used to indicate a
		//              mapped NT status value.
		//
		//      r - reserved portion of the facility code. Reserved for internal
		//              use. Used to indicate HRESULT values that are not status
		//              values, but are instead message ids for display strings.
		//
		//      Facility - is the facility code
		//
		//      Code - is the facility's status code

	IN:
	OUT:
*/
CString COleDbErrorHandler::XLateHR(const HRESULT hr) const
{
	CString strRet;
	strRet.Format(_T("Unknown error: 0x%X"), hr);

	switch(hr){
		case E_FAIL:						strRet = _T("E_FAIL");							break;

		//2007-03-02
		case STG_E_INVALIDFUNCTION:			strRet = _T("STG_E_INVALIDFUNCTION");			break;			//_HRESULT_TYPEDEF_(0x80030001L)
		case STG_E_FILENOTFOUND:			strRet = _T("STG_E_FILENOTFOUND");				break;			//_HRESULT_TYPEDEF_(0x80030002L)
		case STG_E_PATHNOTFOUND:			strRet = _T("STG_E_PATHNOTFOUND");				break;			//_HRESULT_TYPEDEF_(0x80030003L)
		case STG_E_TOOMANYOPENFILES:		strRet = _T("STG_E_TOOMANYOPENFILES");			break;			//_HRESULT_TYPEDEF_(0x80030004L)
		case STG_E_ACCESSDENIED:			strRet = _T("STG_E_ACCESSDENIED");				break;			//_HRESULT_TYPEDEF_(0x80030005L)																							
		//(more...)

		//2007-05-15	
		case DISP_E_TYPEMISMATCH:			strRet = _T("DISP_E_TYPEMISMATCH");				break;
		//(more...)

		case DB_E_BADACCESSORHANDLE:		strRet = _T("DB_E_BADACCESSORHANDLE");			break;           //((HRESULT)0x80040E00L)
		case DB_E_ROWLIMITEXCEEDED:			strRet = _T("DB_E_ROWLIMITEXCEEDED");			break;           //((HRESULT)0x80040E01L)
		case DB_E_READONLYACCESSOR:			strRet = _T("DB_E_READONLYACCESSOR");			break;           //((HRESULT)0x80040E02L)
		case DB_E_SCHEMAVIOLATION:			strRet = _T("DB_E_SCHEMAVIOLATION");			break;           //((HRESULT)0x80040E03L)
		case DB_E_BADROWHANDLE:				strRet = _T("DB_E_BADROWHANDLE");				break;           //((HRESULT)0x80040E04L)
		case DB_E_OBJECTOPEN:				strRet = _T("DB_E_OBJECTOPEN");					break;           //((HRESULT)0x80040E05L)
																							
#if( OLEDBVER >= 0x0150 )																	
		case DB_E_BADCHAPTER:				strRet = _T("DB_E_BADCHAPTER");					break;           //((HRESULT)0x80040E06L)
#endif // OLEDBVER >= 0x0150

		case DB_E_CANTCONVERTVALUE:			strRet = _T("DB_E_CANTCONVERTVALUE");			break;           //((HRESULT)0x80040E07L)
		case DB_E_BADBINDINFO:				strRet = _T("DB_E_BADBINDINFO");				break;           //((HRESULT)0x80040E08L)
		case DB_SEC_E_PERMISSIONDENIED:		strRet = _T("DB_SEC_E_PERMISSIONDENIED");		break;           //((HRESULT)0x80040E09L)
		case DB_E_NOTAREFERENCECOLUMN:		strRet = _T("DB_E_NOTAREFERENCECOLUMN");		break;           //((HRESULT)0x80040E0AL)

#if( OLEDBVER >= 0x0250 )
		case DB_E_LIMITREJECTED:			strRet = _T("DB_E_LIMITREJECTED");				break;           //((HRESULT)0x80040E0BL)
#endif // OLEDBVER >= 0x0250

		case DB_E_NOCOMMAND:				strRet = _T("DB_E_NOCOMMAND");					break;           //((HRESULT)0x80040E0CL)

#if( OLEDBVER >= 0x0250 )
		case DB_E_COSTLIMIT:				strRet = _T("DB_E_COSTLIMIT");					break;           //((HRESULT)0x80040E0DL)
#endif // OLEDBVER >= 0x0250

		case DB_E_BADBOOKMARK:				strRet = _T("DB_E_BADBOOKMARK");				break;           //((HRESULT)0x80040E0EL)
		case DB_E_BADLOCKMODE:				strRet = _T("DB_E_BADLOCKMODE");				break;           //((HRESULT)0x80040E0FL)
		case DB_E_PARAMNOTOPTIONAL:			strRet = _T("DB_E_PARAMNOTOPTIONAL");			break;           //((HRESULT)0x80040E10L)
		case DB_E_BADCOLUMNID:				strRet = _T("DB_E_BADCOLUMNID");				break;           //((HRESULT)0x80040E11L)
		case DB_E_BADRATIO:					strRet = _T("DB_E_BADRATIO");					break;           //((HRESULT)0x80040E12L)

#if( OLEDBVER >= 0x0200 )
		case DB_E_BADVALUES:				strRet = _T("DB_E_BADVALUES");					break;           //((HRESULT)0x80040E13L)
#endif // OLEDBVER >= 0x0200

		case DB_E_ERRORSINCOMMAND:			strRet = _T("DB_E_ERRORSINCOMMAND");			break;           //((HRESULT)0x80040E14L)
		case DB_E_CANTCANCEL:				strRet = _T("DB_E_CANTCANCEL");					break;           //((HRESULT)0x80040E15L)
		case DB_E_DIALECTNOTSUPPORTED:		strRet = _T("DB_E_DIALECTNOTSUPPORTED");		break;           //((HRESULT)0x80040E16L)
		case DB_E_DUPLICATEDATASOURCE:		strRet = _T("DB_E_DUPLICATEDATASOURCE");		break;           //((HRESULT)0x80040E17L)
		case DB_E_CANNOTRESTART:			strRet = _T("DB_E_CANNOTRESTART");				break;           //((HRESULT)0x80040E18L)
		case DB_E_NOTFOUND:					strRet = _T("DB_E_NOTFOUND");					break;           //((HRESULT)0x80040E19L)
		case DB_E_NEWLYINSERTED:			strRet = _T("DB_E_NEWLYINSERTED");				break;           //((HRESULT)0x80040E1BL)

#if( OLEDBVER >= 0x0250 )
		case DB_E_CANNOTFREE:				strRet = _T("DB_E_CANNOTFREE");					break;           //((HRESULT)0x80040E1AL)
		case DB_E_GOALREJECTED:				strRet = _T("DB_E_GOALREJECTED");				break;           //((HRESULT)0x80040E1CL)
#endif // OLEDBVER >= 0x0250

		case DB_E_UNSUPPORTEDCONVERSION:	strRet = _T("DB_E_UNSUPPORTEDCONVERSION");		break;           //((HRESULT)0x80040E1DL)
		case DB_E_BADSTARTPOSITION:			strRet = _T("DB_E_BADSTARTPOSITION");			break;           //((HRESULT)0x80040E1EL)

#if( OLEDBVER >= 0x0200 )
		case DB_E_NOQUERY:					strRet = _T("DB_E_NOQUERY");					break;           //((HRESULT)0x80040E1FL)
#endif // OLEDBVER >= 0x0200

		case DB_E_NOTREENTRANT:				strRet = _T("DB_E_NOTREENTRANT");				break;           //((HRESULT)0x80040E20L)
		case DB_E_ERRORSOCCURRED:			strRet = _T("DB_E_ERRORSOCCURRED");				break;           //((HRESULT)0x80040E21L)
		case DB_E_NOAGGREGATION:			strRet = _T("DB_E_NOAGGREGATION");				break;           //((HRESULT)0x80040E22L)
		case DB_E_DELETEDROW:				strRet = _T("DB_E_DELETEDROW");					break;           //((HRESULT)0x80040E23L)
		case DB_E_CANTFETCHBACKWARDS:		strRet = _T("DB_E_CANTFETCHBACKWARDS");			break;           //((HRESULT)0x80040E24L)
		case DB_E_ROWSNOTRELEASED:			strRet = _T("DB_E_ROWSNOTRELEASED");			break;           //((HRESULT)0x80040E25L)
		case DB_E_BADSTORAGEFLAG:			strRet = _T("DB_E_BADSTORAGEFLAG");				break;           //((HRESULT)0x80040E26L)

#if( OLEDBVER >= 0x0150 )
		case DB_E_BADCOMPAREOP:				strRet = _T("DB_E_BADCOMPAREOP");				break;           //((HRESULT)0x80040E27L)
#endif // OLEDBVER >= 0x0150

		case DB_E_BADSTATUSVALUE:			strRet = _T("DB_E_BADSTATUSVALUE");				break;           //((HRESULT)0x80040E28L)
		case DB_E_CANTSCROLLBACKWARDS:		strRet = _T("DB_E_CANTSCROLLBACKWARDS");		break;           //((HRESULT)0x80040E29L)

#if( OLEDBVER >= 0x0250 )
		case DB_E_BADREGIONHANDLE:			strRet = _T("DB_E_BADREGIONHANDLE");			break;           //((HRESULT)0x80040E2AL)
		case DB_E_NONCONTIGUOUSRANGE:		strRet = _T("DB_E_NONCONTIGUOUSRANGE");			break;           //((HRESULT)0x80040E2BL)
		case DB_E_INVALIDTRANSITION:		strRet = _T("DB_E_INVALIDTRANSITION");			break;           //((HRESULT)0x80040E2CL)
		case DB_E_NOTASUBREGION:			strRet = _T("DB_E_NOTASUBREGION");				break;           //((HRESULT)0x80040E2DL)
#endif // OLEDBVER >= 0x0250

		case DB_E_MULTIPLESTATEMENTS:		strRet = _T("DB_E_MULTIPLESTATEMENTS");			break;           //((HRESULT)0x80040E2EL)
		case DB_E_INTEGRITYVIOLATION:		strRet = _T("DB_E_INTEGRITYVIOLATION");			break;           //((HRESULT)0x80040E2FL)
		case DB_E_BADTYPENAME:				strRet = _T("DB_E_BADTYPENAME");				break;           //((HRESULT)0x80040E30L)
		case DB_E_ABORTLIMITREACHED:		strRet = _T("DB_E_ABORTLIMITREACHED");			break;           //((HRESULT)0x80040E31L)

#if( OLEDBVER >= 0x0200 )
		case DB_E_ROWSETINCOMMAND:			strRet = _T("DB_E_ROWSETINCOMMAND");			break;           //((HRESULT)0x80040E32L)
		case DB_E_CANTTRANSLATE:			strRet = _T("DB_E_CANTTRANSLATE");				break;           //((HRESULT)0x80040E33L)
#endif // OLEDBVER >= 0x0200

		case DB_E_DUPLICATEINDEXID:			strRet = _T("DB_E_DUPLICATEINDEXID");			break;           //((HRESULT)0x80040E34L)
		case DB_E_NOINDEX:					strRet = _T("DB_E_NOINDEX");					break;           //((HRESULT)0x80040E35L)
		case DB_E_INDEXINUSE:				strRet = _T("DB_E_INDEXINUSE");					break;           //((HRESULT)0x80040E36L)
		case DB_E_NOTABLE:					strRet = _T("DB_E_NOTABLE");					break;           //((HRESULT)0x80040E37L)
		case DB_E_CONCURRENCYVIOLATION:		strRet = _T("DB_E_CONCURRENCYVIOLATION");		break;           //((HRESULT)0x80040E38L)
		case DB_E_BADCOPY:					strRet = _T("DB_E_BADCOPY");					break;           //((HRESULT)0x80040E39L)
		case DB_E_BADPRECISION:				strRet = _T("DB_E_BADPRECISION");				break;           //((HRESULT)0x80040E3AL)
		case DB_E_BADSCALE:					strRet = _T("DB_E_BADSCALE");					break;           //((HRESULT)0x80040E3BL)
		case DB_E_BADTABLEID:				strRet = _T("DB_E_BADTABLEID");					break;           //((HRESULT)0x80040E3CL)
		case DB_E_BADTYPE:					strRet = _T("DB_E_BADTYPE");					break;           //((HRESULT)0x80040E3DL)
		case DB_E_DUPLICATECOLUMNID:		strRet = _T("DB_E_DUPLICATECOLUMNID");			break;           //((HRESULT)0x80040E3EL)
		case DB_E_DUPLICATETABLEID:			strRet = _T("DB_E_DUPLICATETABLEID");			break;           //((HRESULT)0x80040E3FL)
		case DB_E_TABLEINUSE:				strRet = _T("DB_E_TABLEINUSE");					break;           //((HRESULT)0x80040E40L)
		case DB_E_NOLOCALE:					strRet = _T("DB_E_NOLOCALE");					break;           //((HRESULT)0x80040E41L)
		case DB_E_BADRECORDNUM:				strRet = _T("DB_E_BADRECORDNUM");				break;           //((HRESULT)0x80040E42L)
		case DB_E_BOOKMARKSKIPPED:			strRet = _T("DB_E_BOOKMARKSKIPPED");			break;           //((HRESULT)0x80040E43L)
		case DB_E_BADPROPERTYVALUE:			strRet = _T("DB_E_BADPROPERTYVALUE");			break;           //((HRESULT)0x80040E44L)
		case DB_E_INVALID:					strRet = _T("DB_E_INVALID");					break;           //((HRESULT)0x80040E45L)
		case DB_E_BADACCESSORFLAGS:			strRet = _T("DB_E_BADACCESSORFLAGS");			break;           //((HRESULT)0x80040E46L)
		case DB_E_BADSTORAGEFLAGS:			strRet = _T("DB_E_BADSTORAGEFLAGS");			break;           //((HRESULT)0x80040E47L)
		case DB_E_BYREFACCESSORNOTSUPPORTED:	strRet = _T("DB_E_BYREFACCESSORNOTSUPPORTED");	break;           //((HRESULT)0x80040E48L)
		case DB_E_NULLACCESSORNOTSUPPORTED:	strRet = _T("DB_E_NULLACCESSORNOTSUPPORTED");	break;           //((HRESULT)0x80040E49L)
		case DB_E_NOTPREPARED:				strRet = _T("DB_E_NOTPREPARED");				break;           //((HRESULT)0x80040E4AL)
		case DB_E_BADACCESSORTYPE:			strRet = _T("DB_E_BADACCESSORTYPE");			break;           //((HRESULT)0x80040E4BL)
		case DB_E_WRITEONLYACCESSOR:		strRet = _T("DB_E_WRITEONLYACCESSOR");			break;           //((HRESULT)0x80040E4CL)
		case DB_SEC_E_AUTH_FAILED:			strRet = _T("DB_SEC_E_AUTH_FAILED");			break;           //((HRESULT)0x80040E4DL)
		case DB_E_CANCELED:					strRet = _T("DB_E_CANCELED");					break;           //((HRESULT)0x80040E4EL)

#if( OLEDBVER >= 0x0200 )
		case DB_E_CHAPTERNOTRELEASED:		strRet = _T("DB_E_CHAPTERNOTRELEASED");			break;           //((HRESULT)0x80040E4FL)
#endif // OLEDBVER >= 0x0200

		case DB_E_BADSOURCEHANDLE:			strRet = _T("DB_E_BADSOURCEHANDLE");			break;           //((HRESULT)0x80040E50L)
		case DB_E_PARAMUNAVAILABLE:			strRet = _T("DB_E_PARAMUNAVAILABLE");			break;           //((HRESULT)0x80040E51L)
		case DB_E_ALREADYINITIALIZED:		strRet = _T("DB_E_ALREADYINITIALIZED");			break;           //((HRESULT)0x80040E52L)
		case DB_E_NOTSUPPORTED:				strRet = _T("DB_E_NOTSUPPORTED");				break;           //((HRESULT)0x80040E53L)
		case DB_E_MAXPENDCHANGESEXCEEDED:	strRet = _T("DB_E_MAXPENDCHANGESEXCEEDED");		break;           //((HRESULT)0x80040E54L)
		case DB_E_BADORDINAL:				strRet = _T("DB_E_BADORDINAL");					break;           //((HRESULT)0x80040E55L)
		case DB_E_PENDINGCHANGES:			strRet = _T("DB_E_PENDINGCHANGES");				break;           //((HRESULT)0x80040E56L)
		case DB_E_DATAOVERFLOW:				strRet = _T("DB_E_DATAOVERFLOW");				break;           //((HRESULT)0x80040E57L)
		case DB_E_BADHRESULT:				strRet = _T("DB_E_BADHRESULT");					break;           //((HRESULT)0x80040E58L)
		case DB_E_BADLOOKUPID:				strRet = _T("DB_E_BADLOOKUPID");				break;           //((HRESULT)0x80040E59L)
		case DB_E_BADDYNAMICERRORID:		strRet = _T("DB_E_BADDYNAMICERRORID");			break;           //((HRESULT)0x80040E5AL)
		case DB_E_PENDINGINSERT:			strRet = _T("DB_E_PENDINGINSERT");				break;           //((HRESULT)0x80040E5BL)
		case DB_E_BADCONVERTFLAG:			strRet = _T("DB_E_BADCONVERTFLAG");				break;           //((HRESULT)0x80040E5CL)
		case DB_E_BADPARAMETERNAME:			strRet = _T("DB_E_BADPARAMETERNAME");			break;           //((HRESULT)0x80040E5DL)
		case DB_E_MULTIPLESTORAGE:			strRet = _T("DB_E_MULTIPLESTORAGE");			break;           //((HRESULT)0x80040E5EL)
		case DB_E_CANTFILTER:				strRet = _T("DB_E_CANTFILTER");					break;           //((HRESULT)0x80040E5FL)
		case DB_E_CANTORDER:				strRet = _T("DB_E_CANTORDER");					break;           //((HRESULT)0x80040E60L)

#if( OLEDBVER >= 0x0200 )
		case MD_E_BADTUPLE:					strRet = _T("MD_E_BADTUPLE");					break;           //((HRESULT)0x80040E61L)
		case MD_E_BADCOORDINATE:			strRet = _T("MD_E_BADCOORDINATE");				break;           //((HRESULT)0x80040E62L)
		case MD_E_INVALIDAXIS:				strRet = _T("MD_E_INVALIDAXIS");				break;           //((HRESULT)0x80040E63L)
		case MD_E_INVALIDCELLRANGE:			strRet = _T("MD_E_INVALIDCELLRANGE");			break;           //((HRESULT)0x80040E64L)
		case DB_E_NOCOLUMN:					strRet = _T("DB_E_NOCOLUMN");					break;           //((HRESULT)0x80040E65L)
		case DB_E_COMMANDNOTPERSISTED:		strRet = _T("DB_E_COMMANDNOTPERSISTED");		break;           //((HRESULT)0x80040E67L)
		case DB_E_DUPLICATEID:				strRet = _T("DB_E_DUPLICATEID");				break;           //((HRESULT)0x80040E68L)
		case DB_E_OBJECTCREATIONLIMITREACHED:	strRet = _T("DB_E_OBJECTCREATIONLIMITREACHED");	break;           //((HRESULT)0x80040E69L)
		case DB_E_BADINDEXID:				strRet = _T("DB_E_BADINDEXID");					break;           //((HRESULT)0x80040E72L)
		case DB_E_BADINITSTRING:			strRet = _T("DB_E_BADINITSTRING");				break;           //((HRESULT)0x80040E73L)
		case DB_E_NOPROVIDERSREGISTERED:	strRet = _T("DB_E_NOPROVIDERSREGISTERED");		break;           //((HRESULT)0x80040E74L)
		case DB_E_MISMATCHEDPROVIDER:		strRet = _T("DB_E_MISMATCHEDPROVIDER");			break;           //((HRESULT)0x80040E75L)
#endif // OLEDBVER >= 0x0200

#if( OLEDBVER >= 0x0210 )
		//case SEC_E_PERMISSIONDENIED:
		//case DB_SEC_E_PERMISSIONDENIED:
		case SEC_E_BADTRUSTEEID:			strRet = _T("SEC_E_BADTRUSTEEID");				break;           //((HRESULT)0x80040E6AL)
		case SEC_E_NOTRUSTEEID:				strRet = _T("SEC_E_NOTRUSTEEID");				break;           //((HRESULT)0x80040E6BL)
		case SEC_E_NOMEMBERSHIPSUPPORT:		strRet = _T("SEC_E_NOMEMBERSHIPSUPPORT");		break;           //((HRESULT)0x80040E6CL)
		case SEC_E_INVALIDOBJECT:			strRet = _T("SEC_E_INVALIDOBJECT");				break;           //((HRESULT)0x80040E6DL)
		case SEC_E_NOOWNER:					strRet = _T("SEC_E_NOOWNER");					break;           //((HRESULT)0x80040E6EL)
		case SEC_E_INVALIDACCESSENTRYLIST:	strRet = _T("SEC_E_INVALIDACCESSENTRYLIST");	break;           //((HRESULT)0x80040E6FL)
		case SEC_E_INVALIDOWNER:			strRet = _T("SEC_E_INVALIDOWNER");				break;           //((HRESULT)0x80040E70L)
		case SEC_E_INVALIDACCESSENTRY:		strRet = _T("SEC_E_INVALIDACCESSENTRY");		break;           //((HRESULT)0x80040E71L)
		//case SEC_E_PERMISSIONDENIED DB_SEC_E_PERMISSIONDENIED
#endif // OLEDBVER >= 0x0210

		case DB_S_ROWLIMITEXCEEDED:			strRet = _T("DB_S_ROWLIMITEXCEEDED");			break;           //((HRESULT)0x00040EC0L)
		case DB_S_COLUMNTYPEMISMATCH:		strRet = _T("DB_S_COLUMNTYPEMISMATCH");			break;           //((HRESULT)0x00040EC1L)
		case DB_S_TYPEINFOOVERRIDDEN:		strRet = _T("DB_S_TYPEINFOOVERRIDDEN");			break;           //((HRESULT)0x00040EC2L)
		case DB_S_BOOKMARKSKIPPED:			strRet = _T("DB_S_BOOKMARKSKIPPED");			break;           //((HRESULT)0x00040EC3L)

#if( OLEDBVER >= 0x0200 )
		case DB_S_NONEXTROWSET:				strRet = _T("DB_S_NONEXTROWSET");				break;           //((HRESULT)0x00040EC5L)
#endif // OLEDBVER >= 0x0200

		case DB_S_ENDOFROWSET:				strRet = _T("DB_S_ENDOFROWSET");				break;           //((HRESULT)0x00040EC6L)
		case DB_S_COMMANDREEXECUTED:		strRet = _T("DB_S_COMMANDREEXECUTED");			break;           //((HRESULT)0x00040EC7L)
		case DB_S_BUFFERFULL:				strRet = _T("DB_S_BUFFERFULL");					break;           //((HRESULT)0x00040EC8L)
		case DB_S_NORESULT:					strRet = _T("DB_S_NORESULT");					break;           //((HRESULT)0x00040EC9L)
		case DB_S_CANTRELEASE:				strRet = _T("DB_S_CANTRELEASE");				break;           //((HRESULT)0x00040ECAL)
																							
#if( OLEDBVER >= 0x0250 )																	
		case DB_S_GOALCHANGED:				strRet = _T("DB_S_GOALCHANGED");				break;           //((HRESULT)0x00040ECBL)
#endif // OLEDBVER >= 0x0250

#if( OLEDBVER >= 0x0150 )
		case DB_S_UNWANTEDOPERATION:		strRet = _T("DB_S_UNWANTEDOPERATION");			break;           //((HRESULT)0x00040ECCL)
#endif // OLEDBVER >= 0x0150

		case DB_S_DIALECTIGNORED:			strRet = _T("DB_S_DIALECTIGNORED");				break;           //((HRESULT)0x00040ECDL)
		case DB_S_UNWANTEDPHASE:			strRet = _T("DB_S_UNWANTEDPHASE");				break;           //((HRESULT)0x00040ECEL)
		case DB_S_UNWANTEDREASON:			strRet = _T("DB_S_UNWANTEDREASON");				break;           //((HRESULT)0x00040ECFL)
																							
#if( OLEDBVER >= 0x0150 )																	
		case DB_S_ASYNCHRONOUS:				strRet = _T("DB_S_ASYNCHRONOUS");				break;           //((HRESULT)0x00040ED0L)
#endif // OLEDBVER >= 0x0150																
																							
		case DB_S_COLUMNSCHANGED:			strRet = _T("DB_S_COLUMNSCHANGED");				break;           //((HRESULT)0x00040ED1L)
		case DB_S_ERRORSRETURNED:			strRet = _T("DB_S_ERRORSRETURNED");				break;           //((HRESULT)0x00040ED2L)
		case DB_S_BADROWHANDLE:				strRet = _T("DB_S_BADROWHANDLE");				break;           //((HRESULT)0x00040ED3L)
		case DB_S_DELETEDROW:				strRet = _T("DB_S_DELETEDROW");					break;           //((HRESULT)0x00040ED4L)

#if( OLEDBVER >= 0x0250 )
		case DB_S_TOOMANYCHANGES:			strRet = _T("DB_S_TOOMANYCHANGES");				break;           //((HRESULT)0x00040ED5L)
#endif // OLEDBVER >= 0x0250																
																							
		case DB_S_STOPLIMITREACHED:			strRet = _T("DB_S_STOPLIMITREACHED");			break;           //((HRESULT)0x00040ED6L)
		case DB_S_LOCKUPGRADED:				strRet = _T("DB_S_LOCKUPGRADED");				break;           //((HRESULT)0x00040ED8L)
		case DB_S_PROPERTIESCHANGED:		strRet = _T("DB_S_PROPERTIESCHANGED");			break;           //((HRESULT)0x00040ED9L)
		case DB_S_ERRORSOCCURRED:			strRet = _T("DB_S_ERRORSOCCURRED");				break;           //((HRESULT)0x00040EDAL)
		case DB_S_PARAMUNAVAILABLE:			strRet = _T("DB_S_PARAMUNAVAILABLE");			break;           //((HRESULT)0x00040EDBL)
		case DB_S_MULTIPLECHANGES:			strRet = _T("DB_S_MULTIPLECHANGES");			break;           //((HRESULT)0x00040EDCL)
	}

	return strRet;
}
