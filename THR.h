//THR.h
//04 June 2005 11:50:49

//#include <THR.h>

#pragma once

#include <comdef.h>

namespace THR_NS{
	const DWORD dwClick = 0L;
}

inline void THR(const HRESULT hr)
{
	if(FAILED(hr))
		_com_issue_error(hr);
}

inline void TRR(const long iRegResult)
{
	if(ERROR_SUCCESS != iRegResult)
		_com_issue_error(iRegResult);
}

inline void TBL(const bool bResult)
{
	if(false == bResult)
		_com_issue_error(E_FAIL);
}

