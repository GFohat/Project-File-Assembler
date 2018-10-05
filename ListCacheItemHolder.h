#pragma once

#include "listcacheitem.h"

#ifndef MY_ATLTRACE
#define MY_ATLTRACE ATLTRACE
#endif

namespace LIST_CACHE{

class CListCacheItemHolder
{
public:
	CListCacheItemHolder(
					const ROWTYPE dwNumColumns
					, const DWORD_PTR dwMaxCacheItems
					, const DWORD_PTR dwNumToPrefetch
					, const DWORD_PTR dwNumToWhither
				);

	~CListCacheItemHolder(void);

protected:
	virtual HRESULT RetrieveDataRow(const ROWTYPE dwRow, CListCacheItem & rItem) = 0;

protected:
	void GetDispInfo		(NMLVDISPINFO & rDispInfo);

	bool SetItemData		(const ROWTYPE dwRow, const ULONGLONG ullItemData);
	bool GetItemData		(const ROWTYPE dwRow, ULONGLONG & ullValue);
	void DumpRow			(const ROWTYPE dwRow);

	void SetNumColumns		(const ROWTYPE dwNumColumns);

	void DumpStats			(void) const;

public:
	CListCacheItem * GetItemAtRow(const ROWTYPE dwRow);
	bool SetItemAtRow(CListCacheItem * pItem, const ROWTYPE dwRow);
	bool DeleteItemAtRow(const ROWTYPE dwRow);

private:
	void GetDispInfo_TEXT	(NMLVDISPINFO & rDispInfo, CListCacheItem * pLRI);
	void GetDispInfo_PARAM	(NMLVDISPINFO & rDispInfo, CListCacheItem * pLRI);
	void GetDispInfo_STATE	(NMLVDISPINFO & rDispInfo, CListCacheItem * pLRI);
	void GetDispInfo_INDENT	(NMLVDISPINFO & rDispInfo, CListCacheItem * pLRI);
	void GetDispInfo_IMAGE	(NMLVDISPINFO & rDispInfo, CListCacheItem * pLRI);

protected:
	void AdjustCacheSize	(const DWORD_PTR dwMaxCacheItems);
	void ClearCache			(void);
	void CacheHint			(const NMLVCACHEHINT & cachehint, const bool bPreFetch);

	bool			AddCacheItem		(const ROWTYPE dwRow, CListCacheItem * pData);

private:
	CListCacheItem *	NewCacheItem		(const ROWTYPE dwRow, const bool bPreFetch);
	void				ClipCacheSize		(const DWORD_PTR dwMaxItems);
	bool				DeleteCacheItem		(CACHE_TRACKER_ITERATOR & itTracker);

	ROWTYPE			m_dwNumStringsPerRow;
	DWORD_PTR		m_dwMaxCacheItems;

	LRI_HOLDER		m_cacheStorage;
	CACHE_TRACKER	m_cacheTracker;

	bool ASSERTCACHESIZES(void) const;

//Statistics...
public:
	DWORD_PTR GetNextItemSerNo(void);

private:
	DWORD_PTR		m_dwPreCacheHit;
	DWORD_PTR		m_dwPreCacheMiss;
	DWORD_PTR		m_dwCacheHit;
	DWORD_PTR		m_dwCacheMiss;
	DWORD_PTR		m_dwPreFetchCalls;
	DWORD_PTR		m_dwPrefetchWasted;
	DWORD_PTR		m_dwPrefetchUsed;
	DWORD_PTR		m_dwCurItemSerNo;

	void RecordStatistics(const CListCacheItem & rLRI);

//Prefetch...
protected:
	void Prefetch(const ROWTYPE dwNumToPrefetch);	//call in idle moments

private:
	void		Prefetch_001(void);	//call in idle moments
	bool		m_bLastGoingUp;
	ROWTYPE		m_dwLastCacheFrom;
	ROWTYPE		m_dwLastCacheTo;
	bool		ValidateCacheHint(NMLVCACHEHINT & cachehint) const;
	bool		IsExcessivePrefetch(const NMLVCACHEHINT & cachehint) const;
	void		WhitherTheCache(void);

	DWORD_PTR	m_dwNumToPrefetch;
	DWORD_PTR	m_dwNumToWhither;

private:
	void		Prefetch_002(const ROWTYPE dwNumToPrefetch);	//call in idle moments
	ROWTYPE		m_dwCurPrefetch;
};


}	// end of namespace LIST_CACHE
