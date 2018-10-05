#include "stdafx.h"
#include ".\paramsshowfilepcposition.h"

namespace PARAMS{

CParamsShowFilePCPosition::CParamsShowFilePCPosition(
						const LARGE_INTEGER		liTotalFileSize				// file size
						, const LARGE_INTEGER	liTotalBytesTransferred		// bytes transferred
						, const DWORD			dwStreamNumber				// current stream
						, const DWORD			dwCallbackReason			// callback reason
					)
:	m_liTotalFileSize				(liTotalFileSize)			// file size
	, m_liTotalBytesTransferred		(liTotalBytesTransferred)	// bytes transferred
	, m_dwStreamNumber				(dwStreamNumber)			// current stream
	, m_dwCallbackReason			(dwCallbackReason)			// callback reason
	, m_rlPercent					(0.0f)
{
	m_rlPercent = double(m_liTotalBytesTransferred.QuadPart) / double(m_liTotalFileSize.QuadPart);
	m_rlPercent *= 100.0f;
}
	
CParamsShowFilePCPosition::CParamsShowFilePCPosition(const double rlPercent)
:	m_rlPercent					(rlPercent)
	, m_dwStreamNumber			(0L)			// current stream
	, m_dwCallbackReason		(0L)			// callback reason
{
	m_liTotalBytesTransferred.QuadPart		= LONGLONG(m_rlPercent);
	m_liTotalFileSize.QuadPart				= 0;
}

CParamsShowFilePCPosition::~CParamsShowFilePCPosition(void)
{
}

};	//end of namespace PARAMS
