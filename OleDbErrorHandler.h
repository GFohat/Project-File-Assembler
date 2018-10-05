// OleDbErrorHandler.h: interface for the COleDbErrorHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OLEDBERRORHANDLER_H__D6581BED_C53D_4DBA_8E25_9A75A3BB0C60__INCLUDED_)
#define AFX_OLEDBERRORHANDLER_H__D6581BED_C53D_4DBA_8E25_9A75A3BB0C60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COleDbErrorHandler  
{
public:
	COleDbErrorHandler();
	virtual ~COleDbErrorHandler();

public:
	virtual void LogDbError(
						const CString & strFunc
						, const CString & strText
						, const CString & strSQL
					) = 0;

public:
	void HandleHR(
				_com_error & e
				, const CString & strFunc
				, const CString & strExtra
				, const CString & strSQL
				, const bool bLog
			);

private:
	bool IsRepetition(const HRESULT hr);
	CString XLateHR(const HRESULT hr) const;
	HRESULT m_hrLastError;
	DWORD m_dwLastTick;
};

#endif // !defined(AFX_OLEDBERRORHANDLER_H__D6581BED_C53D_4DBA_8E25_9A75A3BB0C60__INCLUDED_)
