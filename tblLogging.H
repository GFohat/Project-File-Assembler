// tblLogging.H : Declaration of the CtblLogging class

#ifndef __TBLLOGGING_H_
#define __TBLLOGGING_H_

#include "ConstSQL.h"
using namespace CONS_SQL;

namespace OLEDB{

class CtblLoggingAccessor
{
public:
	LONG			m_iRecID;
	DBTIMESTAMP		m_dtWhen;
	LONG			m_iType;
	TCHAR			m_szType	[51];
	TCHAR			m_szLogon	[51];
	TCHAR			m_szMachine	[51];
	TCHAR			m_szSource	[101];
	TCHAR			m_szText	[1024];
	TCHAR			m_szSQL		[1024];

BEGIN_COLUMN_MAP(CtblLoggingAccessor)
	COLUMN_ENTRY(1, m_iRecID)
	COLUMN_ENTRY(2, m_dtWhen)
	COLUMN_ENTRY(3, m_iType)
	COLUMN_ENTRY(4, m_szType)
	COLUMN_ENTRY(5, m_szLogon)
	COLUMN_ENTRY(6, m_szMachine)
	COLUMN_ENTRY(7, m_szSource)
	COLUMN_ENTRY(8, m_szText)
	COLUMN_ENTRY(9, m_szSQL)
END_COLUMN_MAP()

DEFINE_COMMAND(CtblLoggingAccessor, _T(" \
	SELECT \
		iRecID, \
		dtWhen, \
		iType, \
		szType, \
		szLogon, \
		szMachine, \
		szSource, \
		szText, \
		szSQL  \
		FROM dbo.tblLogging"))

	// You may wish to call this function if you are inserting a record and wish to
	// initialize all the fields, if you are not going to explicitly set all of them.
	void ClearRecord()
	{
		memset(this, 0, sizeof(*this));
	}
};

class CtblLogging : public CCommand<CAccessor<CtblLoggingAccessor> >
{
public:
	HRESULT OpenSession(const CString & strUDL, CSession & session)
	{
		HRESULT hr = S_OK;

		CDataSource db;
		hr = db.OpenFromFileName(strUDL.AllocSysString());
		if (FAILED(hr))
			return hr;

		hr = session.Open(db);
		if (FAILED(hr))
			return hr;

		return hr;
	}

	//void CloseSession(CSession & session)
	//{
	//	session.Close();
	//}

	HRESULT Open(const CString & strSQL, const CSession & session)
	{
		HRESULT	hr = S_OK;

		//hr = OpenDataSource();
		//if (FAILED(hr))
		//	return hr;

		hr = OpenRowset(strSQL, session);
		ATLASSERT(SUCCEEDED(hr));
		if (FAILED(hr))
			return hr;

		hr = MoveFirst();
		if (FAILED(hr))
			return hr;

		//m_iCurPosition = 0;

		return hr;
	}

	//HRESULT OpenDataSource(CSession & session)
	//{
	//	HRESULT		hr;
	//	CDataSource db;
	//	CDBPropSet	dbinit(DBPROPSET_DBINIT);
	//
	//	dbinit.AddProperty	(DBPROP_AUTH_INTEGRATED,	OLESTR("SSPI"));
	//	dbinit.AddProperty	(DBPROP_INIT_CATALOG,		OLESTR("ProjectFileAssembler"));
	//	dbinit.AddProperty	(DBPROP_INIT_DATASOURCE,	OLESTR("POWERPC\\SQLEXPRESS"));
	//	dbinit.AddProperty	(DBPROP_INIT_LCID,			(long)2057);
	//	dbinit.AddProperty	(DBPROP_INIT_PROMPT,		(short)4);
	//
	//	hr = db.Open(_T("SQLOLEDB.1"), &dbinit);
	//
	//	if (FAILED(hr))
	//		return hr;
	//
	//	return session.Open(db);
	//}

	HRESULT OpenRowset(LPCTSTR szCommand, const CSession & session)
	{
		CDBPropSet propset(DBPROPSET_ROWSET);

		//Prevent DB_E_CANTFETCHBACKWARDS;
		VERIFY( propset.AddProperty(DBPROP_CANSCROLLBACKWARDS,	true) );
		VERIFY( propset.AddProperty(DBPROP_CANFETCHBACKWARDS,	true) );
		VERIFY( propset.AddProperty(DBPROP_IRowsetLocate,		true) );
		VERIFY( propset.AddProperty(DBPROP_IRowsetScroll,		true) );
		VERIFY( propset.AddProperty(DBPROP_BOOKMARKS,			true) );
		
		return CCommand<CAccessor<CtblLoggingAccessor> >::Open(session, szCommand, &propset);
	}
	
//private:
//	CSession	m_session;


	HRESULT MoveToPosition(const DWORD dwPosition)
	{
		HRESULT hr = S_OK;

		//dwPosition is a zero-based list item index
		//but a bookmark is one-based
		DWORD dwBookMark = dwPosition + 1L;

		try{
			ClearRecord();
			
			CBookmark<0> bkmark;

			BYTE * pBytes = reinterpret_cast<BYTE *>(&dwBookMark);
			
			THR( hr = bkmark.SetBookmark(sizeof(DWORD), pBytes) );
			THR( hr = MoveToBookmark(bkmark) );
		}
		//----------------------------------------------------------
		catch(_com_error & e){
			hr = e.Error();
			ASSERT(false);
		}

		return hr;
	}

	CString GetLimitedText(const int iSubItem, const DWORD dwMax) const
	{
		CString strRet;

		CString strTemp(_T("!!Unknown Column!!"));
		CSystemTime2 dtsys;
		
		switch(iSubItem){
			case eLogCol_RecID:	
				strTemp.Format(_T("%i"), m_iRecID);
				break;
				
			case eLogCol_When:		
				dtsys = m_dtWhen;
				strTemp = dtsys.GetCurDateTime();
				break;
				
			case eLogCol_iType:		
				strTemp.Format(_T("%i"), m_iType);
				break;
				
			case eLogCol_strType:	strTemp = m_szType;		break;						
			case eLogCol_Logon:		strTemp = m_szLogon;	break;
			case eLogCol_Machine:	strTemp = m_szMachine;	break;
			case eLogCol_Source:	strTemp = m_szSource;	break;
			case eLogCol_Text:		strTemp = m_szText;		break;
			case eLogCol_SQL:		strTemp = m_szSQL;		break;
		}

		if(DWORD(strTemp.GetLength()) >= dwMax)			
			strRet = strTemp.Left(dwMax - 4) + _T("...");
		else
			strRet = strTemp;

		return strRet;
	}
};


}	//namespace OLEDB


#endif // __TBLLOGGING_H_
