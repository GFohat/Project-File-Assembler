// FileCopyThreadParams.h: interface for the CFileCopyThreadParams class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILECOPYTHREADPARAMS_H__50BD6445_AADC_4B23_B8D3_90514A3334B5__INCLUDED_)
#define AFX_FILECOPYTHREADPARAMS_H__50BD6445_AADC_4B23_B8D3_90514A3334B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CopyHelper.h"
#include "DirInitHandler.h"

class CFileCopyThreadParams  
:	public CDirInitHandler
	, public CCopyHelper
{
public:
	CFileCopyThreadParams(HWND hwndTarget);
	CFileCopyThreadParams(const CFileCopyThreadParams & src){ *this = src; }
	virtual ~CFileCopyThreadParams();

public:
	const CFileCopyThreadParams & operator = (const CFileCopyThreadParams & src);

public:
	inline HWND GetTargetWnd(void) const { return m_hwndTarget; }

public:
	bool PostTargetMessage(DWORD dwMsg, WPARAM wParam, LPARAM lParam) const;

private:
	HWND m_hwndTarget;

private:
	virtual bool DoCreateDirectory(void);
	virtual bool DoEmptyDirectory(void);
	virtual void OnNewDirectory(const CString & strDir, const DWORD dwOPNumber, const DWORD dwStepNumber);

public:
	virtual void ReportDIEvent(const CFileCopyReport & report);
	virtual void ReportFCEvent(const CFileCopyReport & report);
};

#endif // !defined(AFX_FILECOPYTHREADPARAMS_H__50BD6445_AADC_4B23_B8D3_90514A3334B5__INCLUDED_)
