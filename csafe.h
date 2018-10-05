


#ifndef __CSAFEARRAY__H__

#define __CSAFEARRAY__H__

class CSafeArray
{

public:

	/*
	** Default constructor
	*/
	CSafeArray	()
	{
		m_lNoDim	= 0;
		m_pSA		= NULL;;
	}

	/*
	** Constructor which calls the init function
	*/
	CSafeArray	(long lnoDims, VARENUM vt, long* lBounds)
	{
		m_lNoDim = lnoDims;

		Init(lnoDims, vt, lBounds);
	}

	/*
	** The one and only destructor
	*/
	~CSafeArray ()
	{
		if (m_pSA)
		{
			::SafeArrayDestroy(m_pSA);
		}
	}

	/*
	** The function which creates the SafeArray inside.. Takes as parameters the number of 
	** dimensions and the array of lower bound and no of elements of all dimensions...  
	** For example for a 2 dimensional array of 2 rows and 3 cols, lBounds = {0, 3, 0, 2}
	** Remember crazy safe arrays take rows and cols in the reverse way...
	*/
	HRESULT Init(long lnoDims, VARENUM vt, long* lBounds)
	{
		
		HRESULT hOk = E_FAIL;

		m_lNoDim = lnoDims;

		SAFEARRAYBOUND* pSafeBound = new SAFEARRAYBOUND[m_lNoDim];

		for (long lIter=0; lIter< m_lNoDim; lIter++)
		{
			pSafeBound[lIter].lLbound  = lBounds[lIter*2];
			pSafeBound[lIter].cElements= lBounds[lIter*2 + 1];
			
		}

		m_pSA = ::SafeArrayCreate(vt, m_lNoDim, pSafeBound);


		delete [] pSafeBound;

		if (m_pSA)
		{
			hOk = S_OK;
		}

		return hOk;	

	}

	/*
	** Function for getting the number of elements in any dimension
	*/
	long GetElementCount(long lDim)
	{
		long lCount = -1;
		long llBound = GetLowerBound(lDim);
		long luBound = GetUpperBound(lDim);

		if ((llBound != -1) && (luBound != -1))
		{
			lCount = luBound - llBound + 1;
		}
		return lCount;

	}
	/*
	** Functions for getting the upper and lower bound of specified dimension.. On failure returns
	** bound as -1
	*/
	long GetLowerBound(long lDim)
	{

		HRESULT hOk  = E_FAIL;
		
		long lBound;

		hOk = ::SafeArrayGetLBound(m_pSA, lDim, &lBound);

		if (FAILED (hOk))
		{
			lBound = -1;
		}

		return lBound;

	}
	
	long GetUpperBound(long lDim)
	{
		HRESULT hOk  = E_FAIL;
		long lBound;

		hOk = ::SafeArrayGetUBound(m_pSA, lDim, &lBound);

		if (FAILED (hOk))
		{
			lBound = -1;
		}

		return lBound;
	}
	
	
	/*
	** Redimension -- remember u can only redimension the last dimension..
	**  eg in case of 2 dimensional arrays, only the no of rows
	*/
	HRESULT ReDimArray(long lLBound, long lcElements)
	{

		HRESULT hOk = S_OK;

		SAFEARRAYBOUND  safeBound ;

		safeBound.cElements = lcElements;
		safeBound.lLbound   = lLBound;

		hOk = ::SafeArrayRedim(m_pSA, &safeBound);

		return hOk;
	}
	
	/*
	** Functions which gets and sets the element at specified index... 
	** eg : to get the element at the 3rd col second row of 2 dimensional array, 
	** lIndex should be of type long[2] and the values should be lIndex[0]=2 and lIndex[1]=1;
	*/
	HRESULT GetElement(long* lIndex, VARIANT* pvtElement)
	{
		HRESULT hOk = E_FAIL;

		::VariantInit(pvtElement);

		_variant_t vtVal;

		hOk = ::SafeArrayGetElement(m_pSA, lIndex, &vtVal);

		hOk = ::VariantCopy(pvtElement, &(vtVal.Detach()));

		return hOk;	
	}

	HRESULT SetElement(long* lIndex, VARIANT vtElement)
	{
		HRESULT hOk = E_FAIL;

		_variant_t vtVal = vtElement;

		hOk = ::SafeArrayPutElement(m_pSA, lIndex, &vtVal);

		return hOk;	
	}

	/*
	** Return the encapsulated safearray
	*/
	HRESULT GetSafeArray(SAFEARRAY ** ppArray)
	{
		HRESULT  hOk = E_FAIL;

		if (ppArray)
		{
			*ppArray = NULL;

			hOk = ::SafeArrayCopy(m_pSA, ppArray);

		}
		return hOk;
	}

	/*
	** Returns the number of dimensions of encapsulated array
	*/
	long	GetNoDimensions()
	{
		if (m_pSA)
		{
			return m_lNoDim;
		}

		else
			return -1;
	}

	/*
	** Functions which wrap up safearray functions access and unacces data
	*/

	HRESULT  AccessData(void HUGEP ** ppData)
	{
		HRESULT hOk = E_FAIL;

		if (m_pSA )
		{
			hOk = ::SafeArrayAccessData(m_pSA, ppData);	
		}

		return hOk;
	}

	HRESULT UnAccessData()
	{
		HRESULT hOk = E_FAIL;

		if (m_pSA)
		{			
			hOk = ::SafeArrayUnaccessData(m_pSA);
		}		

		return hOk;
	}


private:
	/*
	** The data members -- 
	*/
	long		m_lNoDim;
	SAFEARRAY*	m_pSA;

};


#endif // __CSAFEARRAY__H__