#include "StdAfx.h"
#include "datasourceinfoholder.h"
#include <OleDBErr.h>

CDataSourceInfoHolder::CDataSourceInfoHolder(void)
:	m_bJetDataSource	(false)
{
}

CDataSourceInfoHolder::~CDataSourceInfoHolder(void)
{
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	PGC Created: (vsn) 15/11/2003 20:22:09
	DESC:
	IN:
	OUT:
*/
void CDataSourceInfoHolder::ClearPropertyValues(const CComVariant & varClear)
{
	using namespace CONS_DS_PROPS::PROPERTY_ORDINALS;

	for (DWORD dwLoop = 0L ; dwLoop < iPO__LAST ; dwLoop ++)
		m_varProps[dwLoop] = varClear;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10-May-2005 10:03:10
	DESC:	
	IN:		
	OUT:	
*/
void CDataSourceInfoHolder::ClearPropertyValues(const HRESULT hr)
{
	using namespace CONS_DS_PROPS::PROPERTY_ORDINALS;

	CComVariant varClear;
	varClear.vt = VT_ERROR;
	varClear.scode = hr;

	ClearPropertyValues(varClear);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	PGC Created: (vsn) 14/11/2003 21:29:30
	DESC:
	IN:
	OUT:
*/
CString CDataSourceInfoHolder::GetPropertyValue(const int iPropOrdinal) const
{
	using namespace CONS_DS_PROPS::PROPERTY_ORDINALS;

	if(iPropOrdinal < 0 || iPropOrdinal >= iPO__LAST)
		return _T("Invalid Property Ordinal");

	return GetStringFromVariant(m_varProps[iPropOrdinal]);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	PGC Created: (vsn) 14/11/2003 22:20:40
	DESC:
	IN:
	OUT:
*/
CString CDataSourceInfoHolder::GetPropertyName(const int iPropOrdinal) const
{
	using namespace CONS_DS_PROPS::PROPERTY_ORDINALS;
	if(iPropOrdinal < 0 || iPropOrdinal >= iPO__LAST)
		return _T("Invalid Property Ordinal");

	return szPROPERTY_NAMES[ iPropOrdinal ];
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	PGC Created: (vsn) 14/11/2003 21:29:33
	DESC:
	IN:
	OUT:
*/
CString CDataSourceInfoHolder::GetStringFromVariant(const CComVariant & vt) const
{
	USES_CONVERSION;

	CString strRet;

	switch(vt.vt & VT_TYPEMASK){
		case VT_BOOL:				strRet = (vt.boolVal == VARIANT_FALSE) ? _T("False") : _T("True");	break;

		case VT_INT:				strRet.Format(_T("%i"), vt.intVal);		break;
		case VT_I1:						
		case VT_I2:					strRet.Format(_T("%i"), vt.iVal);		break;
		case VT_I4:					strRet.Format(_T("%i"), vt.lVal);		break;
		//case VT_I8:					strRet.Format(_T("%i"), vt.llVal);		break;
		case VT_R4:					strRet.Format(_T("%f"), vt.fltVal);		break;
		case VT_R8:					strRet.Format(_T("%f"), vt.dblVal);		break;
		case VT_BSTR:				strRet.Format(_T("%s"), OLE2T(vt.bstrVal));		break;
		case VT_UINT:				strRet.Format(_T("%u"), vt.uintVal);		break;
		case VT_UI1:
		case VT_UI2:				strRet.Format(_T("%u"), vt.uiVal);		break;
		case VT_UI4:				strRet.Format(_T("0x%08X"), vt.ulVal);	break;

		case VT_ERROR:				strRet = GetStringFromError(vt);		break;

		//case VT_UI8:				strRet.Format(_T("%u"), vt.ullVal);		break;
		case VT_EMPTY:				strRet = _T("VT_EMPTY:			");	break;
		case VT_NULL:				strRet = _T("VT_NULL:			");	break;
		case VT_CY:					strRet = _T("VT_CY:				");	break;
		case VT_DATE:				strRet = _T("VT_DATE:			");	break;
		case VT_DISPATCH:			strRet = _T("VT_DISPATCH:		");	break;
		case VT_RECORD:				strRet = _T("VT_RECORD:			");	break;
		case VT_VARIANT:			strRet = _T("VT_VARIANT:		");	break;
		case VT_UNKNOWN:			strRet = _T("VT_UNKNOWN:		");	break;
		case VT_DECIMAL:			strRet = _T("VT_DECIMAL:		");	break;
		case VT_VOID:				strRet = _T("VT_VOID:			");	break;
		case VT_PTR:				strRet = _T("VT_PTR:			");	break;
		case VT_SAFEARRAY:			strRet = _T("VT_SAFEARRAY:		");	break;
		case VT_CARRAY:				strRet = _T("VT_CARRAY:			");	break;
		case VT_USERDEFINED:		strRet = _T("VT_USERDEFINED:	");	break;
		case VT_FILETIME:			strRet = _T("VT_FILETIME:		");	break;
		case VT_BLOB:				strRet = _T("VT_BLOB:			");	break;
		case VT_STREAM:				strRet = _T("VT_STREAM:			");	break;
		case VT_STORAGE:			strRet = _T("VT_STORAGE:		");	break;
		case VT_STREAMED_OBJECT:	strRet = _T("VT_STREAMED_OBJECT:");	break;
		case VT_STORED_OBJECT:		strRet = _T("VT_STORED_OBJECT:	");	break;
		case VT_BLOB_OBJECT:		strRet = _T("VT_BLOB_OBJECT:	");	break;
		case VT_CF:					strRet = _T("VT_CF:				");	break;
		case VT_CLSID:				strRet = _T("VT_CLSID:			");	break;
		//case VT_VERSIONED_STREAM:	strRet = _T("VT_VERSIONED_STREAM");	break;
		//case VT_BSTR_BLOB	= 0xfff,
		//case VT_VECTOR	= 0x1000,
		//case VT_ARRAY	= 0x2000,
		//case VT_BYREF	= 0x4000,
		//case VT_RESERVED	= 0x8000,
		//case VT_ILLEGAL	= 0xffff,
		//case VT_ILLEGALMASKED	= 0xfff,
		//case VT_TYPEMASK	= 0xfff
   	}

	return strRet;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10-May-2005 10:04:56
	DESC:	
	IN:		
	OUT:	
*/
CString CDataSourceInfoHolder::GetStringFromError(const CComVariant & vt) const
{
	CString strRet;

	switch(vt.scode){
		case NOERROR:					strRet = _T("NOERROR");						break;	
		case E_FAIL:					strRet = _T("E_FAIL");						break;
		case E_UNEXPECTED:				strRet = _T("E_UNEXPECTED");				break;		  
		case E_NOTIMPL:					strRet = _T("E_NOTIMPL");					break;		      
		case E_OUTOFMEMORY:				strRet = _T("E_OUTOFMEMORY");				break;		  
		case E_INVALIDARG:				strRet = _T("E_INVALIDARG");				break;			   
		case E_NOINTERFACE:				strRet = _T("E_NOINTERFACE");				break;			
		case E_POINTER:					strRet = _T("E_POINTER");					break;		      
		case E_HANDLE:					strRet = _T("E_HANDLE");					break;		       
		case E_ABORT:					strRet = _T("E_ABORT");						break;			        
		case DB_E_ERRORSOCCURRED:		strRet = _T("DB_E_ERRORSOCCURRED");			break;
		case DB_E_CANCELED: 			strRet = _T("DB_E_CANCELED");				break;
		case DB_SEC_E_AUTH_FAILED:		strRet = _T("DB_SEC_E_AUTH_FAILED");		break;
		case DB_SEC_E_PERMISSIONDENIED:	strRet = _T("DB_SEC_E_PERMISSIONDENIED");	break;
		//case DB_SEC_E_SAFEMODE_DENIED:	strRet = _T("DB_SEC_E_SAFEMODE_DENIED");	break;

		default:
			strRet.Format(_T("VT_ERROR 0x%X"), vt.scode);	
	}

	return strRet;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13-May-2005 08:09:38
	DESC:	
	IN:		
	OUT:	
*/
CString CDataSourceInfoHolder::GetCurrentCatalog(const CDataSource & ds) const
{
	USES_CONVERSION;

	CString strRet(_T("<NO CATALOG>"));

	if(ds.m_spInit){
		CComVariant varProp;

		HRESULT hr = ds.GetProperty(
								DBPROPSET_DATASOURCE
								, DBPROP_CURRENTCATALOG
								, &varProp
							);

		if(SUCCEEDED(hr)){
			if(VT_BSTR == varProp.vt)
				strRet = OLE2T(varProp.bstrVal);

			else if(VT_NULL == varProp.vt)
				strRet = _T("VT_NULL");

			else if(VT_EMPTY == varProp.vt)
				strRet = _T("VT_EMPTY");
		}
		else{
			varProp.vt = VT_ERROR;
			varProp.scode = hr;
			strRet = GetStringFromError(varProp);
		}
	}

	return strRet;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13-May-2005 09:48:43
	DESC:	
	IN:		
	OUT:	
*/
CString CDataSourceInfoHolder::GetCurrentServer(const CDataSource & ds) const
{
	USES_CONVERSION;

	CString strRet(_T("<NO SERVER>"));

	if(ds.m_spInit){
		CComVariant varProp;

		HRESULT hr = ds.GetProperty(
								DBPROPSET_DATASOURCEINFO
								, DBPROP_SERVERNAME
								, &varProp
							);

		if(SUCCEEDED(hr)){
			strRet = OLE2T(varProp.bstrVal);
		}
		else{
			varProp.vt = VT_ERROR;
			varProp.scode = hr;
			strRet = GetStringFromError(varProp);
		}
	}

	return strRet;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	PGC Created: (vsn) 14/11/2003 21:26:10
	DESC:
	IN:
	OUT:
*/
HRESULT CDataSourceInfoHolder::SetPropertyValues(const CDataSource & ds)
{
	const CComVariant varmsjet(L"MS Jet");
	HRESULT hrRet = S_FALSE;

	ClearPropertyValues(L"Uninitialized");

	if(ds.m_spInit){
		using namespace CONS_DS_PROPS::PROPERTY_ORDINALS;

		HRESULT hr = S_OK;

		for (DWORD dwLoop = 0L ; dwLoop < iPO__LAST ; dwLoop ++){
			
			hr = ds.GetProperty(
						DBPROPSET_DATASOURCEINFO
						, dwPROPERTY_IDS[dwLoop]
						, &(m_varProps[dwLoop])
					);

			if(FAILED(hr)){
				m_varProps[dwLoop].vt		= VT_ERROR;
				m_varProps[dwLoop].scode	= (SCODE) hr;
				hrRet = hr;
			}
			else if(S_FALSE == hr){
				m_varProps[dwLoop] = _T("S_FALSE");
			}

			//test for Jet database...
			if(dwPROPERTY_IDS[dwLoop] == DBPROP_DBMSNAME){
				if(SUCCEEDED(hr)){
					if(m_varProps[dwLoop] == varmsjet){
						ATLTRACE("<<<< MS Jet Data Source Detected >>>>\n");
						m_bJetDataSource = true;
					}
					else
						m_bJetDataSource = false;
				}
			}

			//special translations...
			switch(dwPROPERTY_IDS[dwLoop]){
				case DBPROP_CATALOGLOCATION:	Translate_DBPROP_CATALOGLOCATION	(m_varProps[dwLoop]);	break;
				case DBPROP_DSOTHREADMODEL:		Translate_DBPROP_DSOTHREADMODEL		(m_varProps[dwLoop]);	break;
				case DBPROP_GROUPBY:			Translate_DBPROP_GROUPBY			(m_varProps[dwLoop]);	break;	
				case DBPROP_COLUMNDEFINITION:	Translate_DBPROP_COLUMNDEFINITION	(m_varProps[dwLoop]);	break;
				case DBPROP_CONCATNULLBEHAVIOR:	Translate_DBPROP_CONCATNULLBEHAVIOR	(m_varProps[dwLoop]);	break;
			}

		}
	}

	return hrRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 08:39:22
	DESCRIP:	
		DBPROP_COLUMNDEFINITION Property group: Data Source Information
		Property set: DBPROPSET_DATASOURCEINFO
		Type: VT_I4
		Typical R/W: R
		Description: Column Definition
		A bitmask defining the valid clauses for the definition of a column. 
		A combination of zero or more of the following:

		DBPROPVAL_CD_NOTNULL	Columns can be created non-nullable.
 	IN:
	OUT:
*/
void CDataSourceInfoHolder::Translate_DBPROP_COLUMNDEFINITION(CComVariant & var)
{
	CComVariant varRet = var;

	//switch(var.lVal){
		//case DBPROPVAL_CL_START:	varRet = _T("DBPROPVAL_CL_START");	break;
		//case DBPROPVAL_CL_END:		varRet = _T("DBPROPVAL_CL_END");	break;
	//}	

	if(var.lVal & DBPROPVAL_CD_NOTNULL){
		varRet = _T("DBPROPVAL_CD_NOTNULL");
	}

	var = varRet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 08:44:02
	DESCRIP:	
		DBPROP_CONCATNULLBEHAVIOR Property group: Data Source Information
		Property set: DBPROPSET_DATASOURCEINFO
		Type: VT_I4
		Typical R/W: R
		Description: NULL Concatenation Behavior
		How the data source handles the concatenation of NULL-valued character data 
		type columns with non NULL-valued character data type columns. 
		
		One of the following:

		DBPROPVAL_CB_NULL		The result is NULL valued.

		DBPROPVAL_CB_NON_NULL	The result is the concatenation of the non–NULL-valued column or columns.
 	IN:
	OUT:
*/
void CDataSourceInfoHolder::Translate_DBPROP_CONCATNULLBEHAVIOR(CComVariant & var)
{
	CComVariant varRet;

	switch(var.lVal){
		case DBPROPVAL_CB_NULL:			varRet = _T("DBPROPVAL_CB_NULL");		break;
		case DBPROPVAL_CB_NON_NULL:		varRet = _T("DBPROPVAL_CB_NON_NULL");	break;
	}	

	var = varRet;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   09 May 2005 21:04:33	
	DESC:		
		Type: VT_I4 
		Typical R/W: R only

		Description: Catalog Location

		Specifies the position in a text command of a catalog name in a qualified table name, that is: 

		DBPROPVAL_CL_START, which indicates the catalog name, is at the start of the fully qualified table name. 
		DBPROPVAL_CL_END—The catalog name is at the end of the fully qualified name. 	IN:
	OUT:
*/
void CDataSourceInfoHolder::Translate_DBPROP_CATALOGLOCATION(CComVariant & var)
{
	CComVariant varRet;

	switch(var.lVal){
		case DBPROPVAL_CL_START:	varRet = _T("DBPROPVAL_CL_START");	break;
		case DBPROPVAL_CL_END:		varRet = _T("DBPROPVAL_CL_END");	break;
	}	

	var = varRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   09 May 2005 22:02:15	
	DESC:		
	IN:
	OUT:
*/
void CDataSourceInfoHolder::Translate_DBPROP_DSOTHREADMODEL(CComVariant & var)
{
	CComVariant varRet;

	switch(var.lVal){
		case DBPROPVAL_RT_APTMTTHREAD:		varRet = _T("DBPROPVAL_RT_APTMTTHREAD");	break;
		case DBPROPVAL_RT_FREETHREAD:		varRet = _T("DBPROPVAL_RT_FREETHREAD");		break;
		case DBPROPVAL_RT_SINGLETHREAD:		varRet = _T("DBPROPVAL_RT_SINGLETHREAD");	break;
	}	

	var = varRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   09 May 2005 22:02:12	
	DESC:		
	IN:
	OUT:
*/
void CDataSourceInfoHolder::Translate_DBPROP_GROUPBY(CComVariant & var)
{
	CComVariant varRet;

	switch(var.lVal){
		case DBPROPVAL_GB_COLLATE:			varRet = _T("DBPROPVAL_GB_COLLATE");			break;
		case DBPROPVAL_GB_CONTAINS_SELECT:	varRet = _T("DBPROPVAL_GB_CONTAINS_SELECT");	break;
		case DBPROPVAL_GB_EQUALS_SELECT:	varRet = _T("DBPROPVAL_GB_EQUALS_SELECT");		break;
		case DBPROPVAL_GB_NO_RELATION:		varRet = _T("DBPROPVAL_GB_NO_RELATION");		break;
		case DBPROPVAL_GB_NOT_SUPPORTED:	varRet = _T("DBPROPVAL_GB_NOT_SUPPORTED");		break;
	}	

	var = varRet;
}
