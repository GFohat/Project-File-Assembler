#pragma once


namespace PIPE_SERVER{


class CPipeServerInstanceThreadParams
{
public:
	CPipeServerInstanceThreadParams(
								const HWND hwndTgt
								, const DWORD dwTgtTID
								, const HANDLE hPipe
							);

	~CPipeServerInstanceThreadParams(void);

public:
	inline HANDLE GetPipeHandle(void) const { return m_hPipe; }

public:
	bool PostTargetMessage(const DWORD dwMsg, const LPARAM lParam) const;

private:
	DWORD	m_dwTgtTID;
	HWND	m_hwndTgt;
	HANDLE	m_hPipe;
};



}	//end of namespace PIPE_SERVER
