// XLateFieldText.h: interface for the CXLateFieldText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XLATEFIELDTEXT_H__1F2967A1_D04A_4294_B628_F6C86CCAFB7F__INCLUDED_)
#define AFX_XLATEFIELDTEXT_H__1F2967A1_D04A_4294_B628_F6C86CCAFB7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConstSQL.h"
using namespace CONS_SQL;

class CXLateFieldText  
{
public:
	CXLateFieldText();
	virtual ~CXLateFieldText();

public:
	CComVariant ExtractFieldValue(const CComPtr<ADODB::Fields> & spFields, const eSTEP_FIELD eWhich) const;
	void ExtractFieldValue(const CComPtr<ADODB::Fields> & spFields, const eSTEP_FIELD eWhich, long & iValue) const;
	void ExtractFieldValue(const CComPtr<ADODB::Fields> & spFields, const eSTEP_FIELD eWhich, CString & strValue) const;

public:
	void	XLateComVariant		(const CComVariant & var, long & iValue) const;
	void	XLateComVariant		(const CComVariant & var, CString & strValue) const;
	
	CString XLateFieldText(
						const CComVariant & var
						, const DWORD dwMaxLeng
						, const CString & strOverFlow
					) const;

	long	XLateFieldNumber	(const CComVariant & var) const;

	CString XLateFieldText(
						const CComPtr<ADODB::_Recordset> spRst
						, const CString & strFieldName
					);

	long	XLateFieldNumber(
						const CComPtr<ADODB::_Recordset> spRst
						, const CString & strFieldName
					);
};

#endif // !defined(AFX_XLATEFIELDTEXT_H__1F2967A1_D04A_4294_B628_F6C86CCAFB7F__INCLUDED_)
