#pragma once


namespace PIC_HELP{


class CPictureHelper
{
public:
	CPictureHelper(void);
	~CPictureHelper(void);

public:
	HRESULT LoadPicture		(LPCTSTR szFile);
	
	HRESULT LoadPicStream(
						CComPtr<ISequentialStream> & spSeqStream
						, const DWORD dwLeng
					);

	HRESULT LoadPicStream	(CComPtr<IStream> & spStream);

	bool IsPicLoaded(void) const;
	static bool IsPictureFile(const CString & strFAP);
	
	HRESULT RenderPicture(
						CDC * pDC
						, const CRect & rcBounds
						, const bool bKeepAspect
					);

	HRESULT RenderPicture(
						CDC * pDC
						, const CRect & rcBounds
						, const bool bKeepAspect
						, const double rlXOffsetPC
						, const double rlYOffsetPC
						, const double rlZoomFactor
					);

	HRESULT RenderPicture(
						CStatic & rStatic
						, const CRect & rcBounds
						, const bool bKeepAspect
						, const double rlXOffsetPC
						, const double rlYOffsetPC
						, const double rlZoomFactor
					);

	HRESULT AdjustAspectRatio(const CRect & rcBounds, CRect & rcDraw);

	inline HRESULT LastLoadResult	(void) const { return m_hrLastLoad; };

private:
	void ExitPicHelp(void);

	CComPtr<IPicture> m_spIPicture;
	HRESULT m_hrLastLoad;
};



}	//end of namespace PIC_HELP
