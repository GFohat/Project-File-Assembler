#include "StdAfx.h"
#include "listcacheitem.h"



namespace LIST_CACHE{


CListCacheItem::CListCacheItem(
						const ROWTYPE dwNumColumns
						, const bool bPreFetchCreated
						, const DWORD_PTR dwSerialNo
					)
:	m_dwNumStrings			(dwNumColumns)
	, m_ullItemData			(ULONGLONG(0))
	, m_iImageIndex			(0)
	, m_bPreFetchCreated	(bPreFetchCreated)
	, m_bDataWasFetched		(false)
	, m_dwSerialNo			(dwSerialNo)
{
	m_strsRowItems.SetSize(m_dwNumStrings);
	ResetData(_T("Initialized..."));
}

CListCacheItem::~CListCacheItem(void)
{
	//if(m_bPreFetchCreated && !m_bDataWasFetched)
	//	ATLTRACE(_T("Cached CListCacheItem %i was not used\n"), m_dwSerialNo);
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 May 2005 22:58:47	
	DESC:		
	IN:
	OUT:
*/
bool CListCacheItem::IsPrefetch(void) const
{
	return m_bPreFetchCreated;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 May 2005 22:58:51	
	DESC:		
	IN:
	OUT:
*/
bool CListCacheItem::IsFetched(void) const
{
	return m_bDataWasFetched;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   27 April 2005 20:56:02	
	DESC:		
	IN:
	OUT:
*/
void CListCacheItem::ResetData(void)
{
	ResetData(_T(".oO<< INVALID >>Oo."));
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   27 April 2005 21:35:12	
	DESC:		
	IN:
	OUT:
*/
void CListCacheItem::ResetData(const CString & strFill)
{
	for(ROWTYPE dwLoop = 0L ; dwLoop < m_dwNumStrings ; dwLoop ++)
		m_strsRowItems.SetAt(dwLoop, strFill);

	m_ullItemData = ULONGLONG(0);
	m_iImageIndex = 0;

	//Don't touch this...
	//m_bPreFetchCreated;
	//m_bDataWasFetched;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   27 April 2005 20:47:47	
	DESC:		
	IN:
	OUT:
*/
void CListCacheItem::SetItemData(const ULONGLONG ullItemData)
{
	m_ullItemData = ullItemData;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   27 April 2005 20:47:51	
	DESC:		
	IN:
	OUT:
*/
ULONGLONG CListCacheItem::GetItemData(void) const
{
	m_bDataWasFetched = true;
	return m_ullItemData;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	28-Apr-2005 12:57:24
	DESC:	
	IN:		
	OUT:	
*/
void CListCacheItem::SetImageIndex(const int iImageIndex)
{
	m_iImageIndex = iImageIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	28-Apr-2005 12:57:21
	DESC:	
	IN:		
	OUT:	
*/
int CListCacheItem::GetImageIndex(void) const
{
	m_bDataWasFetched = true;
	return m_iImageIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	26-Apr-2005 11:51:14
	DESC:	
	IN:		
	OUT:	
*/
bool CListCacheItem::SetRowItem(const ROWTYPE dwCol, const CString & strValue)
{
	bool bOK = false;

	if(dwCol < m_dwNumStrings){
		m_strsRowItems.SetAt(dwCol, strValue);
		bOK = true;
	}

	return bOK;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10-May-2005 12:34:01
	DESC:	
	IN:		
	OUT:	
*/
bool CListCacheItem::SetRowItemBool(const ROWTYPE dwCol, const VARIANT_BOOL bValue)
{
	CString strVal;

	if(VARIANT_TRUE == bValue)
		strVal = _T("true");
	else if(VARIANT_FALSE == bValue)
		strVal = _T("false");
	else
		strVal = _T("Invalid VARIANT_BOOL");

	return SetRowItem(dwCol, strVal);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10-May-2005 12:34:10
	DESC:	
	IN:		
	OUT:	
*/
bool CListCacheItem::SetRowItemLong(const ROWTYPE dwCol, const LONG lValue)
{
	CString strVal;

	strVal.Format(_T("%i"), lValue);

	return SetRowItem(dwCol, strVal);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10-May-2005 12:34:06
	DESC:	
	IN:		
	OUT:	
*/
bool CListCacheItem::SetRowItem(const ROWTYPE dwCol, const GUID & guidValue)
{
	USES_CONVERSION;

	CString strVal;

	if(GUID_NULL == guidValue){
		strVal = _T("GUID_NULL");
	}
	else{
		const DWORD dwBUFSIZE = 256L;
		WCHAR wszBuffer[dwBUFSIZE + 5L] = {0};

		StringFromGUID2(guidValue, wszBuffer, dwBUFSIZE);
		strVal = OLE2T(wszBuffer);
	}

	return SetRowItem(dwCol, strVal);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	26-Apr-2005 11:51:18
	DESC:	
	IN:		
	OUT:	
*/
CString CListCacheItem::GetRowItem(const ROWTYPE dwCol) const
{
	m_bDataWasFetched = true;

	CString strRet;
	if(dwCol < m_dwNumStrings)
		strRet = m_strsRowItems.GetAt(dwCol);

	return strRet;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   07 June 2005 12:10:03	
	DESC:		
	IN:
	OUT:
*/
void CListCacheItem::DumpStrings(void)
{
	for(DWORD dwLoop = 0L ; dwLoop < m_dwNumStrings ; dwLoop ++){
		ATLTRACE(_T("%i - %s\n"), dwLoop, m_strsRowItems.GetAt(dwLoop));
	}
}


}	// end of namespace LIST_CACHE
