#pragma once

namespace INCLUDE_SERVICES{


namespace DBGTMR{

//#include <debugtimer.h>
//using namespace INCLUDE_SERVICES::DBGTMR;

class CDebugTimer
{
public:
	CDebugTimer(
			const CString & strName
		);

	CDebugTimer(
			const DWORD dwStartTickCount
			, const CString & strName
		);

	~CDebugTimer(void);

public:
	void ReportTime(const bool bResetStopwatch);
	void ResetStopWatch(const DWORD dwStartTickCount);
	DWORD GetCurLapse(void) const;

private:
	DWORD		m_dwStartTickCount;
	bool		m_bReported;
	CString		m_strName;
};



}	//end of namespace DBGTMR



}	//end of namespace INCLUDE_SERVICES
