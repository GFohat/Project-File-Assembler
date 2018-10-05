#pragma once

#include <map>
#include <deque>

/*
c:\program files\microsoft visual studio\vc98\atl\include\atlconv.h(151) : 
warning C4786: 
'std::_Tree<
	unsigned long
	, std::pair<unsigned long const ,LIST_CACHE::CListCacheItem *>
	, std::map<
					unsigned long,LIST_CACHE::CListCacheItem *
					, std::less<unsigned long>
					, std::allocator<LIST_CACHE::CListCacheItem *> >::_Kfn
					, std::less<unsigned long>
					, std::allocator<LIST_CACHE::CListCacheItem *> 
				>' 
: identifier was truncated to '255' characters in the debug information
*/

//#pragma warning( disable : 4786)

namespace LIST_CACHE{


	class CListCacheItem;

	typedef DWORD_PTR ROWTYPE;

	typedef std::map	<ROWTYPE, CListCacheItem *>	LRI_HOLDER;
	typedef std::pair	<ROWTYPE, CListCacheItem *>	LRI_PAIR;
	typedef LRI_HOLDER::iterator					LRI_HOLDER_ITERATOR;
	typedef LRI_HOLDER::const_iterator				LRI_HOLDER_ITERATOR_CONST;

	typedef std::deque	<ROWTYPE>					CACHE_TRACKER;
	typedef CACHE_TRACKER::iterator					CACHE_TRACKER_ITERATOR;
	typedef CACHE_TRACKER::const_iterator			CACHE_TRACKER_ITERATOR_CONST;

	
class CListCacheItem
{
public:
	CListCacheItem(
				const ROWTYPE dwNumColumns
				, const bool bPreFetchCreated
				, const DWORD_PTR dwSerialNo
			);

	virtual ~CListCacheItem(void);

public:
	bool SetRowItem		(const ROWTYPE dwCol, const CString & strValue);
	bool SetRowItem		(const ROWTYPE dwCol, const GUID & guidValue);

	bool SetRowItemBool	(const ROWTYPE dwCol, const VARIANT_BOOL bValue);
	bool SetRowItemLong	(const ROWTYPE dwCol, const LONG lValue);

	CString GetRowItem(const ROWTYPE dwCol) const;

	void SetItemData(const ULONGLONG ullItemData);
	ULONGLONG GetItemData(void) const;

	void SetImageIndex(const int iImageIndex);
	int GetImageIndex(void) const;

	void DumpStrings(void);

	inline ROWTYPE GetNumColumns(void) const { return m_dwNumStrings; };

public:
	void ResetData(void);
	void ResetData(const CString & strFill);


private:
	DWORD_PTR		m_dwSerialNo;
	ROWTYPE			m_dwNumStrings;
	CStringArray	m_strsRowItems;
	ULONGLONG		m_ullItemData;
	int				m_iImageIndex;

//for statistics measurement, eg "% prefetch wasted"
public:
	bool IsPrefetch(void) const;
	bool IsFetched(void) const;

private:
	bool			m_bPreFetchCreated;
	mutable bool	m_bDataWasFetched;
};

//#pragma warning( default : 4786)

}	// end of namespace LIST_CACHE
