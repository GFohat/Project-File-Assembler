#pragma once


namespace PIPE_SERVER{


class CPipeServerThreadParams
{
public:
	CPipeServerThreadParams(const CString & strPipeName, const DWORD dwTIDTgt, const HWND hWndTgt);
	CPipeServerThreadParams(const CPipeServerThreadParams & src);
	~CPipeServerThreadParams(void);

public:
	const CPipeServerThreadParams & operator = (const CPipeServerThreadParams & src);

public:
	inline const CString &	GetPipeName	(void) const { return m_strPipeName; }
	inline DWORD			GetTgtTID	(void) const { return m_dwTIDTgt; }
	inline HWND				GetTgtHWnd	(void) const { return m_hWndTgt; }

public:
	bool PostTargetMessage(const DWORD dwMsg, const LPARAM lParam) const;
	//CString GetFullPipeName(void) const;

private:
	CString m_strPipeName;
	DWORD m_dwTIDTgt;
	HWND m_hWndTgt;
};


}	// end of namespace PIPE_SERVER
