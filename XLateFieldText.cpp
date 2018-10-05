// XLateFieldText.cpp: implementation of the CXLateFieldText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "XLateFieldText.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXLateFieldText::CXLateFieldText()
{

}

CXLateFieldText::~CXLateFieldText()
{

}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/03/2007 15:03:52
	DESCRIP:	
	IN:
	OUT:
*/
CComVariant CXLateFieldText::ExtractFieldValue(
											const CComPtr<ADODB::Fields> & spFields
											, const eSTEP_FIELD eWhich
										) const
{
	HRESULT hr = S_OK;

	CComVariant varRet;

	try{
		varRet = spFields->Item[bstrsSTEP_FIELDS[eWhich]]->Value;
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
	}

	return varRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/03/2007 15:07:44
	DESCRIP:	
	IN:
	OUT:
*/
void CXLateFieldText::ExtractFieldValue(
									const CComPtr<ADODB::Fields> & spFields
									, const eSTEP_FIELD eWhich
									, long & iValue
								) const
{
	CComVariant var = ExtractFieldValue(spFields, eWhich);
	XLateComVariant(var, iValue);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/03/2007 15:07:49
	DESCRIP:	
	IN:
	OUT:
*/
void CXLateFieldText::ExtractFieldValue(
									const CComPtr<ADODB::Fields> & spFields
									, const eSTEP_FIELD eWhich
									, CString & strValue
								) const
{
	CComVariant var = ExtractFieldValue(spFields, eWhich);
	XLateComVariant(var, strValue);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/03/2007 14:08:23
	DESCRIP:	
	IN:
	OUT:
*/
void CXLateFieldText::XLateComVariant(const CComVariant & var, long & iValue) const
{
	iValue = XLateFieldNumber(var);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/03/2007 14:08:20
	DESCRIP:	
	IN:
	OUT:
*/
void CXLateFieldText::XLateComVariant(const CComVariant & var, CString & strValue) const
{
	strValue = XLateFieldText(var, 0, _T(""));
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/03/2007 07:42:18
	DESCRIP:	
	IN:
	OUT:
*/
long CXLateFieldText::XLateFieldNumber(const CComVariant & var) const
{
	CString strText = XLateFieldText(var, 0, _T(""));
	return _ttol(strText);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/02/2007 08:04:48
	DESCRIP:

empirically found max length of a clistctrl cell

         1         2         3         4         5         6         7         8         9         0         1         2         3         4         5         6         7         8         9         0         1         2         3         4         5         6         7         8         9         0 
123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
16 msecs   SELECT      szProjectName      , iProjectID      , iStep      , iStepType      , szStepType      , szSourceFile      , szSourceDir      , szDestDirectory      , szDestFile      , szCreated      , szModified  FROM vwProjectAssemblySteps  WHERE iProj<<<  ectID	
	IN:
	OUT:
*/
CString CXLateFieldText::XLateFieldText(
									const CComVariant & var
									, const DWORD dwMaxLeng
									, const CString & strOverFlow
								) const
{
#pragma message ("Confirm this...")

	//const DWORD dwMAX_LIST_TEXT = 259L;		//to be confirmed

	USES_CONVERSION;

	CString strRet(_T("Not translated..."));

	switch(var.vt){
		case VT_NULL:		strRet = _T("<null>");							break;
		case VT_I1: 		strRet.Format(_T("%c"), var.cVal);				break;     	//CHAR                      
		case VT_I2: 		strRet.Format(_T("%i"), var.iVal);				break;     	//SHORT                     
		case VT_I4: 		strRet.Format(_T("%i"), var.lVal);				break;     	//LONG                      
		//case VT_I8: 		strRet.Format(_T("%i"), var.llVal);				break;    	//LONGLONG                  
		case VT_INT: 		strRet.Format(_T("%i"), var.intVal);			break;   	//INT                       
		
		case VT_R4: 		strRet.Format(_T("%f"), var.fltVal);			break;   	//FLOAT                     
		case VT_R8: 		strRet.Format(_T("%f"), var.dblVal);			break;   	//DOUBLE                    
		
		case VT_BOOL: 		strRet.Format(_T("%i"), var.boolVal);			break;  	//VARIANT_BOOL              
		case VT_ERROR: 		strRet.Format(_T("0x%X"), var.scode);			break;    	//SCODE                     
		case VT_CY: 		strRet.Format(_T("%f"), var.cyVal);				break;    	//CY                        
		
		
		case VT_UI1: 		strRet.Format(_T("%u"), var.bVal);				break;     	//BYTE                      
		case VT_UI2: 		strRet.Format(_T("%u"), var.uiVal);				break;    	//USHORT                    
		case VT_UI4: 		strRet.Format(_T("%u"), var.ulVal);				break;    	//ULONG                     
		//case VT_UI8: 		strRet.Format(_T("%u"), var.ullVal);			break;   	//ULONGLONG                 
		case VT_UINT: 		strRet.Format(_T("%u"), var.uintVal);			break;  	//UINT

		case VT_EMPTY:		strRet = _T("<VT_EMPTY>");	break;

		case VT_BSTR: 		
			//strRet.Format(_T("%s"), OLE2T(var.bstrVal));	
			strRet = var.bstrVal;
			break;  	//BSTR                      
			
		case VT_DATE:     		//DATE 	
			{
				CSystemTime2 dtsys = var.date;
				strRet = dtsys.GetCurDateTimeShort();; 
			}
			break;                      
	}

	if(DWORD(strRet.GetLength()) > dwMaxLeng){
		
		if(dwMaxLeng){
			DWORD dwTextLeng = dwMaxLeng - strOverFlow.GetLength();
			strRet = strRet.Left(dwTextLeng);
			strRet += strOverFlow;

			//ATLTRACE("Truncated string in CXLateFieldText::XLateFieldText !\n");
		}
	}

	return strRet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/05/2007 13:03:21
	DESCRIP:	
	IN:
	OUT:
*/
CString CXLateFieldText::XLateFieldText(
									const CComPtr<ADODB::_Recordset> spRst
									, const CString & strFieldName
								)
{
	CString strRet;
	HRESULT hr = S_OK;

	CComPtr<ADODB::Fields>	spFieldColl		= 0;
	CComPtr<ADODB::Field>	spField			= 0;

	try{
		spFieldColl = spRst->Fields;
		spField = spFieldColl->Item[strFieldName.AllocSysString()];

		strRet = XLateFieldText(spField->Value, 0, _T(""));
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
		strRet.Format(_T("<0x%08X>"), hr);
	}

	return strRet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/05/2007 13:03:23
	DESCRIP:	
	IN:
	OUT:
*/
long CXLateFieldText::XLateFieldNumber(
									const CComPtr<ADODB::_Recordset> spRst
									, const CString & strFieldName
								)
{
	long iRet;
	HRESULT hr = S_OK;

	CComPtr<ADODB::Fields>	spFieldColl		= 0;
	CComPtr<ADODB::Field>	spField			= 0;

	try{
		spFieldColl = spRst->Fields;
		spField = spFieldColl->Item[strFieldName.AllocSysString()];

		iRet = spField->Value.lVal;
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
		iRet = -1L;
	}

	return iRet;
}
