#include "StdAfx.h"
#include ".\picturehelper.h"
#include <olectl.h>


namespace PIC_HELP{


CPictureHelper::CPictureHelper(void)
:	m_hrLastLoad	(S_OK)
	, m_spIPicture	(0)
{
	//::CoInitialize(0);
}

CPictureHelper::~CPictureHelper(void)
{
	ExitPicHelp();
	//::CoUninitialize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   17 June 2005 12:22:10	
	DESC:		
	IN:
	OUT:
*/
void CPictureHelper::ExitPicHelp(void)
{
	if(m_spIPicture != 0){
		m_spIPicture = 0;
	}
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   17 June 2005 18:34:05	
	DESC:		
	IN:
	OUT:
*/
HRESULT CPictureHelper::LoadPicture(LPCTSTR szFile)
{
	USES_CONVERSION;

	HRESULT hr = S_OK;

	ExitPicHelp();

	try{
		IUnknown * pUnkAggregate = 0;
		DWORD dwReserved = 0L;
		COLORREF crefTransparent = CLR_NONE;
		::AfxMessageBox(L"CProjectFileAssemblerDlg::LoadPicture");

		//THR( hr = ::OleLoadPicturePath(
		//							T2W(szFile)
		//							, 0		//[in] Points to IUnknown for COM aggregation.
		//							, 0		//dwReserved
		//							, crefTransparent	//[in] The color you want to reserve to be transparent.
		//							, IID_IPicture		//[in] Reference to the identifier of the interface describing the type of interface pointer to return in ppvRet. 
		//							, reinterpret_cast<void **>(&m_spIPicture)
		//						) );

	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
	}
	catch(...){
		hr = E_FAIL;
	}

	m_hrLastLoad = hr;
	ATLTRACE(_T("Last Picture Load returned 0x%X\n"), m_hrLastLoad);

	return hr;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   24 November 2006 20:57:59	
	DESC:		
	IN:
	OUT:
*/
HRESULT CPictureHelper::LoadPicStream(
									CComPtr<ISequentialStream> & spSeqStream
									, const DWORD dwLeng
								)
{
	HRESULT hr = E_FAIL;

	CDebugTimer tmr(::GetTickCount(), _T("CPictureHelper::LoadPicStream"));

	CComPtr<IStream>	spIStream	= 0;
	LPVOID pBuffer = ::CoTaskMemAlloc(dwLeng);
	ATLASSERT(pBuffer);

	try{
		if(pBuffer){
			hr = S_OK;
			THR( hr = spSeqStream->Read(pBuffer, dwLeng, 0) );
		
			//TRUE means that the stream will be automatically released
			THR( hr = ::CreateStreamOnHGlobal(pBuffer, TRUE, &spIStream) );
			THR( hr = LoadPicStream(spIStream) );
		}
	}
	//-----------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ATLASSERT(false);
	}

	//TRUE means that the stream will be automatically released
	//::CoTaskMemFree(pBuffer);
	 
	return hr;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   21 November 2006 18:45:06	
	DESC:		
	IN:
	OUT:
*/
HRESULT CPictureHelper::LoadPicStream(CComPtr<IStream> & spStream)
{
	HRESULT hr = S_OK;

	ExitPicHelp();

	try{
		//THR( hr = ::OleLoadFromStream(
		//							spStream
		//							, IID_IPicture
		//							, reinterpret_cast<void **>(&m_spIPicture)
		//						) );

		// load the IPicture from the IStream
		//if (::OleLoadPicture(pIStream, 0, FALSE, IID_IPicture,
		//			(LPVOID*)&pIPicture) == S_OK)
		THR( hr = ::OleLoadPicture(
									spStream		//[in] Pointer to the stream that contains the picture's data. 
									, 0				//[in] Number of bytes that should be read from the stream, or zero if the entire stream should be read. 
									, FALSE			//[in] The opposite of the initial value of the KeepOriginalFormat property.
									, IID_IPicture	//
									, reinterpret_cast<void **>(&m_spIPicture)
								) );

	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
	}
	catch(...){
		hr = E_FAIL;
	}

	m_hrLastLoad = hr;

	return hr;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   24 September 2005 07:24:19	
	DESC:		
	IN:
	OUT:
*/
bool CPictureHelper::IsPicLoaded(void) const
{
	if(m_spIPicture)
		return true;
	else
		return false;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   21 November 2006 19:34:57	
	DESC:		
	IN:
	OUT:
*/
/*static*/
bool CPictureHelper::IsPictureFile(const CString & strFAP)
{
	TCHAR szExt[_MAX_EXT];
	_tsplitpath(strFAP, 0, 0, 0, szExt);

	bool bIsPic = false;

	if(0 == _tcsicmp(szExt, _T(".JPG")))
		bIsPic = true;

	else if(0 == _tcsicmp(szExt, _T(".GIF")))
		bIsPic = true;

	else if(0 == _tcsicmp(szExt, _T(".BMP")))
		bIsPic = true;

	return bIsPic;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   17 June 2005 12:49:53	
	DESC:		
	IN:
	OUT:
*/
//HRESULT CPictureHelper::LoadPicture001(LPCTSTR szFile)
//{
//	//ExitPicHelp();
//
//	//// open file
//	//HANDLE hFile = ::CreateFile(szFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
//	//if(INVALID_HANDLE_VALUE == hFile)
//	//	return E_FAIL;
//	//_ASSERTE(INVALID_HANDLE_VALUE != hFile);
//
//	//// get file size
//	//DWORD dwFileSize = ::GetFileSize(hFile, NULL);
//	//if(-1 == dwFileSize)
//	//	return E_FAIL;
//
//	//_ASSERTE(-1 != dwFileSize);
//
//	//LPVOID pvData = NULL;
//	//// alloc memory based on file size
//	//HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);
//	//_ASSERTE(NULL != hGlobal);
//
//	//pvData = GlobalLock(hGlobal);
//	//_ASSERTE(NULL != pvData);
//
//	//DWORD dwBytesRead = 0;
//	//// read file and store in global memory
//	//BOOL bRead = ReadFile(hFile, pvData, dwFileSize, &dwBytesRead, NULL);
//	//_ASSERTE(FALSE != bRead);
//	//GlobalUnlock(hGlobal);
//	//CloseHandle(hFile);
//
//	//LPSTREAM pstm = NULL;
//	//// create IStream* from global memory
//	//HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pstm);
//	//_ASSERTE(SUCCEEDED(hr) && pstm);
//
//	//// Create IPicture from image file
//	////if (m_pPicture)
//	////	m_pPicture->Release();
//
//	//hr = ::OleLoadPicture(pstm, dwFileSize, FALSE, IID_IPicture, (LPVOID *)&m_spIPicture);
//	////_ASSERTE(SUCCEEDED(hr) && m_pPicture);	
//
//	//pstm->Release();
//
//	//return hr;
//	return E_NOTIMPL;
//}
HRESULT CPictureHelper::RenderPicture(
									CDC * pDC
									, const CRect & rcBounds
									, const bool bKeepAspect
								)
{
	//return RenderPicture(pDC, rcBounds, bKeepAspect, 0.0, 0.0, 1.0);
	//testing...
	double rlXOffsetPC = 0;
	double rlYOffsetPC = 0;
	double rlZoom = 1.0;

	return RenderPicture(
						pDC
						, rcBounds
						, bKeepAspect
						, rlXOffsetPC
						, rlYOffsetPC
						, rlZoom
					);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CREATED:   17 June 2005 12:54:38	
	DESC:		
	IN:
	OUT:
*/
HRESULT CPictureHelper::RenderPicture(
									CDC * pDC
									, const CRect & rcBounds
									, const bool bKeepAspect
									, const double rlXOffsetPC
									, const double rlYOffsetPC
									, const double rlZoomFactor
								)
{
	HRESULT hr = m_hrLastLoad;

	CBrush brshBack(RGB(0x00, 0x00, 0x00));

	pDC->FillRect(rcBounds, &brshBack);

	if(brshBack.m_hObject)
		brshBack.DeleteObject();
	
	if(m_spIPicture){

		try{
			const LONG iRectWidth	= rcBounds.Width()  ? rcBounds.Width()  : 1;
			const LONG iRectHeight	= rcBounds.Height() ? rcBounds.Height() : 1;
			OLE_XSIZE_HIMETRIC iPicWidth = 0;
			OLE_YSIZE_HIMETRIC iPicHeight = 0;

			THR( hr = m_spIPicture->get_Width(&iPicWidth) );
			THR( hr = m_spIPicture->get_Height(&iPicHeight) );

			if(iPicWidth < 1)
				iPicWidth = 1;

			if(iPicHeight < 1)
				iPicHeight = 1;

			CRect rcDest = rcBounds;

			if(bKeepAspect)
				AdjustAspectRatio(rcBounds, rcDest);

			//this is where to draw the picture
			LONG iXPosition = (rcBounds.Width() - rcDest.Width()) / 2;
			LONG iYPosition = (rcBounds.Height() - rcDest.Height()) / 2;

			//2006-12-16
			iXPosition += rcBounds.left;
			iYPosition += rcBounds.top;

			//this is what part of the picture to draw
			LONG iVerticalOffset	= iPicHeight - (iPicHeight * (rlYOffsetPC / 100));
			LONG iHorizontalOffset	= iPicWidth * (rlXOffsetPC / 100);
			
			//this is how much of the picture to draw
			LONG iAmountVertical	= -iPicHeight	/ (rlZoomFactor ? rlZoomFactor : 1);
			LONG iAmountHorizontal	= iPicWidth		/ (rlZoomFactor ? rlZoomFactor : 1);

			THR( hr = m_spIPicture->Render(
										pDC->m_hDC				//Handle of device context on which to render the image
										, iXPosition			//Horiz pos of image in hdc
										, iYPosition			//Vert pos of image in hdc
										, rcDest.Width()		//Horiz dim of dest rect
										, rcDest.Height()		//Vert dim of dest rect
										, iHorizontalOffset		//Horiz offset in source picture
										, iVerticalOffset		//Vert offset in source picture
										, iAmountHorizontal		//Amount to copy horizontally in source picture
										, iAmountVertical		//Amount to copy vertically in source picture
										, &rcDest				//Pointer to position of destination for a metafile hdc
									) ); 
		}
		//---------------------------------------------
		catch(_com_error & e){
			hr = e.Error();
			ATLASSERT(SUCCEEDED(hr));
		}

	}

	return hr;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   25 November 2006 07:59:35	
	DESC:		
			AR = W / H
			H = W / AR
			W = AR * H
	IN:
	OUT:
*/
HRESULT CPictureHelper::AdjustAspectRatio(const CRect & rcBounds, CRect & rcDraw)
{
	HRESULT hr = m_hrLastLoad;

	if(m_spIPicture){

		try{
			const LONG iRectWidth	= rcBounds.Width()  ? rcBounds.Width()  : 1;
			const LONG iRectHeight	= rcBounds.Height() ? rcBounds.Height() : 1;
			OLE_XSIZE_HIMETRIC iPicWidth = 0;
			OLE_YSIZE_HIMETRIC iPicHeight = 0;

			THR( hr = m_spIPicture->get_Width(&iPicWidth) );
			THR( hr = m_spIPicture->get_Height(&iPicHeight) );

			if(iPicWidth < 1)
				iPicWidth = 1;

			if(iPicHeight < 1)
				iPicHeight = 1;

			rcDraw = rcBounds;

			const double rlPicAspect = double(iPicWidth) / double(iPicHeight);
			const double rlRectAspect = double(iRectWidth) / double(iRectHeight);
			
			if(rlPicAspect > rlRectAspect){
				//ATLTRACE(_T("Shrink Pic Vertically\n"));
				//set height
				//int iOrigHeight = rcDest.Height();
				int iNewHeight = int(double(rcDraw.Width()) / rlPicAspect);

				rcDraw.bottom = rcDraw.top + iNewHeight;
			}

			else if(rlPicAspect < rlRectAspect){
				//ATLTRACE(_T("Shrink Pic Horizontally\n"));
				//set width
				//int iOrigWid = rcDest.Width();
				int iNewWid = int(rlPicAspect * double(rcDraw.Height()));

				rcDraw.right = rcDraw.left + iNewWid;
			}		
		}
		//-----------------------------------------------------
		catch(_com_error & e){
			hr = e.Error();
			ATLASSERT(false);
		}
	}

	return hr;
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:   25 November 2006 07:52:47	
	DESC:		
	IN:
	OUT:
*/
HRESULT CPictureHelper::RenderPicture(
									CStatic & rStatic
									, const CRect & rcBounds
									, const bool bKeepAspect
									, const double rlXOffsetPC
									, const double rlYOffsetPC
									, const double rlZoomFactor
								)
{
	HRESULT hr = m_hrLastLoad;

	if(m_spIPicture){

		try{
			OLE_HANDLE handle;
			m_spIPicture->get_Handle(&handle);
			rStatic.SetBitmap((HBITMAP)handle);
		}
		//-----------------------------------------------------
		catch(_com_error & e){
			hr = e.Error();
			ATLASSERT(false);
		}

	}

	return hr;
}



}	//end of namespace PIC_HELP
