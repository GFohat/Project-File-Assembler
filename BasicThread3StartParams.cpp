#include "StdAfx.h"
#include "basicthread3startparams.h"



namespace INCLUDE_SERVICES{


namespace BASE_THREAD3{


CBasicThread3StartParams::CBasicThread3StartParams(void)
:	m_pThreadStartRoutine	(0)
	, m_strThreadName		(_T(""))
	, m_pParams				(0)
{
}

CBasicThread3StartParams::~CBasicThread3StartParams(void)
{
}



}	//end of namespace BASE_THREAD3



}	//end of namespace INCLUDE_SERVICES
