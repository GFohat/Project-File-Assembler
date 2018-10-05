#pragma once

//#include <atlstr.h>
//using namespace ATL;

namespace INCLUDE_SERVICES{


namespace BASE_THREAD3{


class CBasicThread3StartParams
{
public:
	CBasicThread3StartParams(void);
	virtual ~CBasicThread3StartParams(void);

public:
	LPTHREAD_START_ROUTINE	m_pThreadStartRoutine;
	CString					m_strThreadName;
	LPVOID					m_pParams;
};



}	//end of namespace BASE_THREAD3



}	//end of namespace INCLUDE_SERVICES
