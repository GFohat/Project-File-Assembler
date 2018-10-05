#include "StdAfx.h"
#include "listcacheitemholder.h"
//#include "PragmaMessageDefines.h"

//#include <ConstRowImages.h>		//namespace IMAGES


namespace LIST_CACHE{


CListCacheItemHolder::CListCacheItemHolder(
									const ROWTYPE dwNumColumns
									, const DWORD_PTR dwMaxCacheItems
									, const DWORD_PTR dwNumToPrefetch
									, const DWORD_PTR dwNumToWhither
								)
:	m_dwNumStringsPerRow	(dwNumColumns)
	, m_dwMaxCacheItems		(dwMaxCacheItems)
	, m_dwNumToPrefetch		(dwNumToPrefetch)
	, m_dwNumToWhither		(dwNumToWhither)
	, m_dwCacheHit			(0)
	, m_dwCacheMiss			(0)
	, m_dwPreCacheHit		(0)
	, m_dwPreCacheMiss		(0)
	, m_dwPreFetchCalls		(0)
	, m_dwCurPrefetch		(0)
	, m_dwLastCacheFrom		(0)
	, m_dwLastCacheTo		(0)
	, m_dwPrefetchUsed		(0)
	, m_dwPrefetchWasted	(0)
	, m_dwCurItemSerNo		(0)
{
}

CListCacheItemHolder::~CListCacheItemHolder(void)
{
	ASSERTCACHESIZES();
	ClearCache();
	DumpStats();
	ASSERTCACHESIZES();
}
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   28 April 2005 19:44:15	
	DESC:		
	IN:
	OUT:
*/
void CListCacheItemHolder::SetNumColumns(const ROWTYPE dwNumColumns)
{
	//ASSERTCACHESIZES();
	ClearCache();
	m_dwNumStringsPerRow = dwNumColumns;
	//ASSERTCACHESIZES();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   27 April 2005 21:04:12	
	DESC:		
	IN:
	OUT:
*/
bool CListCacheItemHolder::SetItemData(const ROWTYPE dwRow, const ULONGLONG ullItemData)
{
	bool bFound = false;
	CListCacheItem * pItem = GetItemAtRow(dwRow);

	if(pItem){
		bFound = true;
		pItem->SetItemData(ullItemData);
	}

	return bFound;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   27 April 2005 20:52:44	
	DESC:		
	IN:
	OUT:
*/
bool CListCacheItemHolder::GetItemData(const ROWTYPE dwRow, ULONGLONG & ullValue)
{
	bool bFound = false;
	CListCacheItem * pItem = GetItemAtRow(dwRow);

	if(pItem){
		bFound = true;
		ullValue = pItem->GetItemData();
	}
	else{
		ullValue = ULONGLONG(-1);
	}

	return bFound;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   07 June 2005 12:12:00	
	DESC:		
	IN:
	OUT:
*/
void CListCacheItemHolder::DumpRow(const ROWTYPE dwRow)
{
	CListCacheItem * pItem = GetItemAtRow(dwRow);

	if(pItem)
		pItem->DumpStrings();
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	26-Apr-2005 11:54:44
	DESC:	
	IN:		
	OUT:	
*/
void CListCacheItemHolder::ClearCache(void)
{
	LRI_HOLDER_ITERATOR it;
	LRI_PAIR pair;
	CListCacheItem * pLri;

	MY_ATLTRACE(_T("ClearCache: %i items\n"), m_cacheStorage.size());

	while(!m_cacheStorage.empty()){
		it = m_cacheStorage.begin();

		pair = *it;

		pLri = pair.second;
		ATLASSERT(pLri);

		if(pLri){
			RecordStatistics(*pLri);
			delete pLri;
			pLri = 0;
		}

		m_cacheStorage.erase(it);
	}

	while(!m_cacheTracker.empty())
		m_cacheTracker.pop_front();

	m_dwCurPrefetch = 0L;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   10 July 2005 11:38:44	
	DESC:		
	IN:
	OUT:
*/
DWORD_PTR CListCacheItemHolder::GetNextItemSerNo(void)
{
	return m_dwCurItemSerNo ++;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   22 May 2005 23:04:16	
	DESC:		
	IN:
	OUT:
*/
void CListCacheItemHolder::RecordStatistics(const CListCacheItem & rLRI)
{
	if(rLRI.IsPrefetch()){
		if(rLRI.IsFetched())
			m_dwPrefetchUsed ++;
		else
			m_dwPrefetchWasted ++;
	}
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   29 April 2005 16:58:18	
	DESC:		
	IN:
	OUT:
*/
void CListCacheItemHolder::DumpStats(void) const
{
	double rlTotalPrecache	= m_dwPreCacheHit + m_dwPreCacheMiss;
	double rlTotalCache		= m_dwCacheHit + m_dwCacheMiss;
	
	double rlPreCachePCHit	= 100.0 * m_dwPreCacheHit / rlTotalPrecache;
	double rlCachePCHit		= 100.0 * m_dwCacheHit / rlTotalCache;

	double rlTotalPrefetech = m_dwPrefetchUsed + m_dwPrefetchWasted;
	double rlPrefetchUsage = 100.0 * m_dwPrefetchUsed / rlTotalPrefetech;

	MY_ATLTRACE(_T("=========================================================================================\n"));
	MY_ATLTRACE(_T("=	CListCacheItemHolder::DumpStats\n=\n"));
	MY_ATLTRACE(_T("= Precache:   Hit = %i, Miss = %i (%.2f%%)\n"), m_dwPreCacheHit, m_dwPreCacheMiss, rlPreCachePCHit);
	MY_ATLTRACE(_T("= Main cache: Hit = %i, Miss = %i (%.2f%%)\n"), m_dwCacheHit, m_dwCacheMiss, rlCachePCHit);
	MY_ATLTRACE(_T("= Pre Fetch Calls:	%i\n"), m_dwPreFetchCalls);
	MY_ATLTRACE(_T("= Pre Fetches Used = %i, Wasted = %i (Usage = %.2f%%)\n"), m_dwPrefetchUsed, m_dwPrefetchWasted, rlPrefetchUsage);
	MY_ATLTRACE(_T("=========================================================================================\n"));
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11-May-2005 12:07:24
	DESC:	
	IN:		
	OUT:	
*/
void CListCacheItemHolder::Prefetch(const ROWTYPE dwNumToPrefetch)
{
	//Prefetch_001();
	Prefetch_002(dwNumToPrefetch);
	m_dwPreFetchCalls ++;
}
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	11-May-2005 12:11:27
	DESC:	
	IN:		
	OUT:	
*/
void CListCacheItemHolder::Prefetch_002(const ROWTYPE dwNumToPrefetch)
{
	NMLVCACHEHINT cachehint;
	ZeroMemory(&cachehint, sizeof(NMLVCACHEHINT));

	cachehint.iFrom		= int(m_dwCurPrefetch);
	cachehint.iTo		= int(m_dwCurPrefetch + dwNumToPrefetch);

	if((m_cacheStorage.size() + dwNumToPrefetch) < m_dwMaxCacheItems){
		m_dwCurPrefetch = cachehint.iTo + 1;
		CacheHint(cachehint, true);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   29 April 2005 22:18:14	
	DESC:		
		iFrom
			Starting index of the requested range of items. 
			This value is inclusive. 

		iTo
			Ending index of the requested range of items. 
			This value is inclusive. 
	IN:
	OUT:
*/
void CListCacheItemHolder::Prefetch_001(void)	//call in idle moments
{
	//NMLVCACHEHINT cachehint;
	//ZeroMemory(&cachehint, sizeof(NMLVCACHEHINT));

	//if(m_bLastGoingUp){
	//	cachehint.iFrom		= m_dwLastCacheTo + 1;
	//	cachehint.iTo		= cachehint.iFrom + m_dwNumToPrefetch;
	//}
	//else{
	//	if(m_dwLastCacheFrom && (cachehint.iTo >= m_dwNumToPrefetch)){
	//		cachehint.iTo		= m_dwLastCacheFrom - 1;
	//		
	//		cachehint.iFrom		= cachehint.iTo - m_dwNumToPrefetch;
	//	}
	//	else{
	//		cachehint.iFrom = 1;
	//		cachehint.iTo = 0;
	//	}

	//}

	//ValidateCacheHint(cachehint);
	//WhitherTheCache();

	//if(!IsExcessivePrefetch(cachehint))
	//	CacheHint(cachehint, true);
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   30 April 2005 22:12:41	
	DESC:		
	IN:
	OUT:
*/
bool CListCacheItemHolder::ValidateCacheHint(NMLVCACHEHINT & cachehint) const
{
	int iTo		= cachehint.iTo;
	int iFrom	= cachehint.iFrom;

	//check zero or greater (row numbers!)
	while(iTo < 0 || iFrom < 0){
		iTo ++;
		iFrom ++;
	}


	bool bChanged = (cachehint.iFrom != iFrom) || (cachehint.iTo != iTo);

	cachehint.iFrom = iFrom;
	cachehint.iTo = iTo;

	return bChanged;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   30 April 2005 21:30:37	
	DESC:		
	IN:
	OUT:
*/
bool CListCacheItemHolder::ASSERTCACHESIZES(void) const
{
	//<<<DEBUGGING>>>
	DWORD_PTR dwCacheSize = m_cacheStorage.size();
	DWORD_PTR dwTrackSize = m_cacheTracker.size();

	bool bCacheSizesMatch = (dwCacheSize == dwTrackSize);

	ATLASSERT(dwCacheSize == dwTrackSize);

	return bCacheSizesMatch;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   29 April 2005 22:35:00	
	DESC:		
	IN:
	OUT:
*/
bool CListCacheItemHolder::IsExcessivePrefetch(const NMLVCACHEHINT & cachehint) const
{
	bool bIsExcessive = false;

	DWORD_PTR dwCurCacheSize = m_cacheStorage.size();

	if(dwCurCacheSize >= m_dwMaxCacheItems){
		MY_ATLTRACE(_T("Cache full, prefetch would be excessive...\n"));
		bIsExcessive = true;
	}

	return bIsExcessive;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   29 April 2005 22:37:18	
	DESC:		
		remove a number of items from the
		end of the cache (FIFO)
	IN:
	OUT:
*/
void CListCacheItemHolder::WhitherTheCache(void)
{
	if(m_cacheStorage.size() >= (m_dwMaxCacheItems - m_dwNumToWhither)){

		MY_ATLTRACE(_T("Whithering %i cache items\n"), m_dwNumToWhither);

		CACHE_TRACKER_ITERATOR it;

		bool bDeleted = true;

		for(ROWTYPE dwLoop = 0 ; (dwLoop < m_dwNumToWhither) && bDeleted ; dwLoop++){
			it = m_cacheTracker.begin();
			bDeleted = DeleteCacheItem(it);
		}
	}
	//else
	//	MY_ATLTRACE(_T("Not enough cache items to Whither\n"));
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	26-Apr-2005 12:06:32
	DESC:	
	IN:		
	OUT:	
*/
void CListCacheItemHolder::CacheHint(const NMLVCACHEHINT & cachehint, const bool bPreFetch)
{
	CListCacheItem * pProbe = 0;
		
	ROWTYPE dwAdded = 0L;
		
	bool bRecordStats = !bPreFetch;
	
	for(ROWTYPE dwLoop = ROWTYPE(cachehint.iFrom) ; dwLoop <= ROWTYPE(cachehint.iTo) ; dwLoop ++){
		
		pProbe = GetItemAtRow(dwLoop);

		if(pProbe){
			if(bRecordStats)
				m_dwPreCacheHit ++;
		}
		else{

			if(bRecordStats)
				m_dwPreCacheMiss ++;

			pProbe = NewCacheItem(dwLoop, bPreFetch);

			if(pProbe)
				dwAdded ++;
		}
	}
			
	DWORD_PTR dwNewCacheFrom = cachehint.iFrom;
	DWORD_PTR dwNewCacheTo = cachehint.iTo;

	if(dwNewCacheFrom > m_dwLastCacheFrom)
		m_bLastGoingUp = true;
	else if(dwNewCacheFrom < m_dwLastCacheFrom)
		m_bLastGoingUp = false;

	m_dwLastCacheFrom	= dwNewCacheFrom;
	m_dwLastCacheTo		= dwNewCacheTo;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	04-May-2005 10:58:43
	DESC:	
	IN:		
	OUT:	
*/
CListCacheItem * CListCacheItemHolder::NewCacheItem	(const ROWTYPE dwRow, const bool bPreFetch)
{
	m_dwCurItemSerNo ++;

	CListCacheItem * pItem = new CListCacheItem(m_dwNumStringsPerRow, bPreFetch, m_dwCurItemSerNo);
	ATLASSERT(pItem);

	if(pItem){
		HRESULT hr = RetrieveDataRow(dwRow, *pItem);

		bool bAdded = false;

		switch(hr){
			case S_OK:
				bAdded = AddCacheItem(dwRow, pItem);
				break;

			//case S_FALSE:
			//	ClearCache();
			//	break;
		}

		if(!bAdded){
			delete pItem;
			pItem = 0;
		}
	}

	return pItem;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	27-Apr-2005 08:46:17
	DESC:	
	IN:		
	OUT:	
*/
bool CListCacheItemHolder::AddCacheItem(const ROWTYPE dwRow, CListCacheItem * pData)
{
	bool bOK = false;

	if(pData){
		LRI_PAIR pair;
		pair.first = dwRow;
		pair.second = pData;

		m_cacheStorage.insert(pair);
		m_cacheTracker.push_back(dwRow);

		ClipCacheSize(m_dwMaxCacheItems);

		bOK = true;
	}

	return bOK;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   08 July 2005 21:37:45	
	DESC:		
	IN:
	OUT:
*/
bool CListCacheItemHolder::SetItemAtRow(CListCacheItem * pItem, const ROWTYPE dwRow)
{
	bool bAdded = false;

	CListCacheItem * pProbe = GetItemAtRow(dwRow);

	if(pProbe){
		bAdded = false;
	}
	else{
		bAdded = AddCacheItem(dwRow, pItem);
	}

	return bAdded;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	28-Apr-2005 12:23:39
	DESC:	
	IN:		
	OUT:	
*/
void CListCacheItemHolder::AdjustCacheSize(const DWORD_PTR dwMaxCacheItems)
{
	m_dwMaxCacheItems = dwMaxCacheItems;
	ClipCacheSize(m_dwMaxCacheItems);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	27-Apr-2005 08:46:23
	DESC:	
	IN:		
	OUT:	
*/
void CListCacheItemHolder::ClipCacheSize(const DWORD_PTR dwMaxItems)
{
	//quick debug check to make sure tracker is working properly...
	DWORD_PTR dwCacheSize = m_cacheStorage.size();
	DWORD_PTR dwTrackSize = m_cacheTracker.size();
	ATLASSERT(dwCacheSize == dwTrackSize);

	ROWTYPE dwRemoveRow	= 0L;
	ROWTYPE dwCount		= 0L;

	CACHE_TRACKER_ITERATOR it;

	bool bDeletionOK = true;

	while(dwCacheSize > dwMaxItems && bDeletionOK){
		//new tracked items (ie cached items) get 'push_back' 
		//so oldest item is at the front...

		//retrieve the oldest row number cached
		it = m_cacheTracker.begin();
		dwRemoveRow = *it;

		//delete the oldest row from the cache
		bDeletionOK = DeleteCacheItem(it);

		//new size values...
		dwCacheSize = m_cacheStorage.size();
		dwTrackSize = m_cacheTracker.size();
		ATLASSERT(dwCacheSize == dwTrackSize);
		
		dwCount ++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	27-Apr-2005 08:46:26
	DESC:	
	IN:		
	OUT:	
*/
bool CListCacheItemHolder::DeleteCacheItem(CACHE_TRACKER_ITERATOR & itTracker)
{
	bool bDeleted = false;

	CListCacheItem * pDel = 0;
	ROWTYPE dwRow = *itTracker;

	LRI_PAIR pair;
	LRI_HOLDER_ITERATOR itCache;

	itCache = m_cacheStorage.find(dwRow);

	if(itCache != m_cacheStorage.end()){
		pair = * itCache;
		pDel = pair.second;

		if(pDel){
			RecordStatistics(*pDel);
			delete pDel;
			pDel = 0;
			bDeleted = true;

			m_cacheStorage.erase(itCache);
			m_cacheTracker.erase(itTracker);
		}
	}

	ATLASSERT(bDeleted);

	return bDeleted;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	26-Apr-2005 12:06:35
	DESC:	
	IN:		
	OUT:	
*/
void CListCacheItemHolder::GetDispInfo(NMLVDISPINFO & rDispInfo)
{
	const int iRow		= rDispInfo.item.iItem;
	const int iColumn	= rDispInfo.item.iSubItem;
	const int iChars	= rDispInfo.item.cchTextMax;
		
	CListCacheItem * pLRI = GetItemAtRow(iRow);

	if(pLRI)
		m_dwCacheHit ++;
	else{
		bool bPrefetched = false;
		pLRI = NewCacheItem(iRow, bPrefetched);
		m_dwCacheMiss ++;
	}

	//these are not mutually exclusive
	//so we need to test each one
	if(rDispInfo.item.mask & LVIF_TEXT)
		GetDispInfo_TEXT(rDispInfo, pLRI);

	if(rDispInfo.item.mask & LVIF_IMAGE)
		GetDispInfo_IMAGE(rDispInfo, pLRI);

	if(rDispInfo.item.mask & LVIF_INDENT)
		GetDispInfo_INDENT(rDispInfo, pLRI);

	if(rDispInfo.item.mask & LVIF_STATE)
		GetDispInfo_STATE(rDispInfo, pLRI);

}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   28 April 2005 16:41:46	
	DESC:		
	IN:
	OUT:
*/
void CListCacheItemHolder::GetDispInfo_TEXT(NMLVDISPINFO & rDispInfo, CListCacheItem * pLRI)
{
	const int iRow		= rDispInfo.item.iItem;
	const int iColumn	= rDispInfo.item.iSubItem;
	const int iChars	= rDispInfo.item.cchTextMax - 1;

	CString strText;

	if(pLRI){
		strText = pLRI->GetRowItem(iColumn);
	}
	else{
		strText.Format(
					_T("No row item data for row %i, column %i")
					, iRow
					, iColumn
				);
	}

		
	_tcsncpy(rDispInfo.item.pszText, strText.Left(iChars), iChars);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   28 April 2005 16:45:01	
	DESC:		
		The iImage member specifies, or is to receive, 
		the index of the item's icon in the image list.

	state
		Indicates the item's state, state image, and overlay image. The 
		stateMask member indicates the valid bits of this member. 

		Bits 0 through 7 of this member contain the item state flags. This 
		can be one or more of the item state values.

		Bits 8 through 11 of this member specify the one-based overlay image 
		index. Both the full-sized icon image list and the small icon image 
		list can have overlay images. The overlay image is superimposed over 
		the item's icon image. If these bits are zero, the item has no overlay 
		image. To isolate these bits, use the LVIS_OVERLAYMASK mask. To set the 
		overlay image index in this member, you should use the INDEXTOOVERLAYMASK 
		macro. The image list's overlay images are set with the 
		ImageList_SetOverlayImage function.

		Bits 12 through 15 of this member specify the state image index. The state 
		image is displayed next to an item's icon to indicate an application-defined 
		state. If these bits are zero, the item has no state image. To isolate these 
		bits, use the LVIS_STATEIMAGEMASK mask. To set the state image index, use 
		the INDEXTOSTATEIMAGEMASK macro. The state image index specifies the index 
		of the image in the state image list that should be drawn. The state image 
		list is specified with the LVM_SETIMAGELIST message.

	IN:
	OUT:
*/
void CListCacheItemHolder::GetDispInfo_IMAGE(NMLVDISPINFO & rDispInfo, CListCacheItem * pLRI)
{
	//This gets called a lot...
	//MY_ATLTRACE(_T("GetDispInfo_IMAGE\n"));

	if(pLRI){
		if(rDispInfo.item.lParam){
			rDispInfo.item.iImage = int(rDispInfo.item.lParam);
		}
		else{
			rDispInfo.item.iImage = pLRI->GetImageIndex();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   28 April 2005 16:41:49	
	DESC:		
		lParam
			Value specific to the item. If you use the LVM_SORTITEMS 
			message, the list-view control passes this value to the 
			application-defined comparison function. You can also use 
			the LVM_FINDITEM message to search a list-view control for 
			an item with a specified lParam value. 
	IN:
	OUT:
*/
void CListCacheItemHolder::GetDispInfo_PARAM(NMLVDISPINFO & rDispInfo, CListCacheItem * pLRI)
{
	MY_ATLTRACE(_T("GetDispInfo_PARAM\n"));
	const int iRow		= rDispInfo.item.iItem;
	const int iColumn	= rDispInfo.item.iSubItem;

	if(pLRI){
		rDispInfo.item.lParam;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   28 April 2005 16:41:52	
	DESC:		
		state
			Indicates the item's state, state image, and overlay image. 
			The stateMask member indicates the valid bits of this member. 

			Bits 0 through 7 of this member contain the item state flags. 
			This can be one or more of the item state values.

			Bits 8 through 11 of this member specify the one-based overlay 
			image index. Both the full-sized icon image list and the small 
			icon image list can have overlay images. The overlay image is 
			superimposed over the item's icon image. If these bits are zero, 
			the item has no overlay image. To isolate these bits, use the 
			LVIS_OVERLAYMASK mask. To set the overlay image index in this 
			member, you should use the INDEXTOOVERLAYMASK macro. The image 
			list's overlay images are set with the ImageList_SetOverlayImage 
			function.

			Bits 12 through 15 of this member specify the state image index. 
			The state image is displayed next to an item's icon to indicate 
			an application-defined state. If these bits are zero, the item 
			has no state image. To isolate these bits, use the 
			LVIS_STATEIMAGEMASK mask. To set the state image index, use 
			the INDEXTOSTATEIMAGEMASK macro. The state image index specifies 
			the index of the image in the state image list that should be drawn. 
			The state image list is specified with the LVM_SETIMAGELIST message.

		stateMask
			Value specifying which bits of the state member will be retrieved 
			or modified. For example, setting this member to LVIS_SELECTED 
			will cause only the item's selection state to be retrieved. 

			This member allows you to modify one or more item states without 
			having to retrieve all of the item states first. For example, 
			setting this member to LVIS_SELECTED and state to zero will 
			cause the item's selection state to be cleared, but none of the 
			other states will be affected. 

			To retrieve or modify all of the states, set this member to (UINT)-1.

			You can use the macro ListView_SetItemState both to set and to 
			clear bits.	
	IN:
	OUT:
*/
void CListCacheItemHolder::GetDispInfo_STATE(NMLVDISPINFO & rDispInfo, CListCacheItem * pLRI)
{
	MY_ATLTRACE(_T("GetDispInfo_STATE\n"));
	const int iRow		= rDispInfo.item.iItem;
	const int iColumn	= rDispInfo.item.iSubItem;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   28 April 2005 16:41:55	
	DESC:		
		iIndent
			Version 4.70. Number of image widths to indent the item. 
			A single indentation equals the width of an item image. 
			Therefore, the value 1 indents the item by the width of 
			one image, the value 2 indents by two images, and so on. 
			Note that this field is supported only for items. Attempting 
			to set subitem indentation will cause the calling function to 
			fail. 
	IN:
	OUT:
*/
void CListCacheItemHolder::GetDispInfo_INDENT(NMLVDISPINFO & rDispInfo, CListCacheItem * pLRI)
{
	//This gets called a lot...
	//MY_ATLTRACE(_T("GetDispInfo_INDENT\n"));
	const int iRow		= rDispInfo.item.iItem;
	const int iColumn	= rDispInfo.item.iSubItem;

	if(pLRI){
		if(0 == iColumn){
			rDispInfo.item.iIndent = 0;	//test value...
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	26-Apr-2005 12:09:56
	DESC:	
	IN:		
	OUT:	
*/
CListCacheItem * CListCacheItemHolder::GetItemAtRow(const ROWTYPE dwRow)
{
	CListCacheItem * pRet = 0;

	LRI_PAIR pair;
	LRI_HOLDER_ITERATOR it;

	it = m_cacheStorage.find(dwRow);

	if(it != m_cacheStorage.end()){
		pair = * it;
		pRet = pair.second;
	}

	return pRet;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   14 August 2005 07:14:46	
	DESC:		
	IN:
	OUT:
*/
bool CListCacheItemHolder::DeleteItemAtRow(const ROWTYPE dwRow)
{
	bool bDelCache = false;
	bool bDelTrack = false;

	CListCacheItem * pDel = 0;

	LRI_PAIR pair;
	LRI_HOLDER_ITERATOR itCache;

	itCache = m_cacheStorage.find(dwRow);

	if(itCache != m_cacheStorage.end()){
		pair = * itCache;
		pDel = pair.second;

		if(pDel){
			RecordStatistics(*pDel);
			delete pDel;
			pDel = 0;
			bDelCache = true;

			CACHE_TRACKER_ITERATOR itTracker;
			for(itTracker = m_cacheTracker.begin() ; itTracker != m_cacheTracker.end() && !bDelTrack ; itTracker ++){
				if(dwRow == *itTracker){
					bDelTrack = true;
					m_cacheTracker.erase(itTracker);
				}
			}

			m_cacheStorage.erase(itCache);
		}
	}

	ATLASSERT(bDelCache && bDelTrack);

	return bDelCache && bDelTrack;
}


}	// end of namespace LIST_CACHE