#pragma once

namespace PARAMS{

class CParamsCopyProgress
{
public:
	CParamsCopyProgress(const HWND hwndMsgTarget);
	~CParamsCopyProgress(void);

public:
	BOOL PostMsg(const DWORD dwMsg, WPARAM wParam, LPARAM lParam) const;
	BOOL SendMsg(const DWORD dwMsg, WPARAM wParam, LPARAM lParam) const;
	DWORD SeenInCPR(void);

private:
	DWORD m_dwSeenInCPR;	//how many times seen in CopyProgressRoutine?
	HWND m_hwndMsgTarget;
};

};	//end of namespace PARAMS
