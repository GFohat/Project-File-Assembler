#pragma once

namespace PARAMS{

class CParamsShowFilePCPosition 
{
public:
	CParamsShowFilePCPosition(
						const LARGE_INTEGER		liTotalFileSize				// file size
						, const LARGE_INTEGER	liTotalBytesTransferred		// bytes transferred
						, const DWORD			dwStreamNumber				// current stream
						, const DWORD			dwCallbackReason			// callback reason
					);

	CParamsShowFilePCPosition(const double rlPercent);

	~CParamsShowFilePCPosition(void);

public:
	inline 	double			GetPercent					(void) const { return m_rlPercent; } 
	inline 	LARGE_INTEGER	GetTotalFileSize			(void) const { return m_liTotalFileSize; }
	inline 	LARGE_INTEGER	GetTotalBytesTransferred	(void) const { return m_liTotalBytesTransferred; }
	inline 	DWORD			GetStreamNumber				(void) const { return m_dwStreamNumber; }
	inline 	DWORD			GetCallbackReason			(void) const { return m_dwCallbackReason; }

private:
	double				m_rlPercent;
	LARGE_INTEGER		m_liTotalFileSize;          // file size
	LARGE_INTEGER		m_liTotalBytesTransferred;  // bytes transferred
	DWORD				m_dwStreamNumber;           // current stream
	DWORD				m_dwCallbackReason;         // callback reason
};
	

};	//end of namespace PARAMS
