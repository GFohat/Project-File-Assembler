// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "axsimpledatagrid.h"

/////////////////////////////////////////////////////////////////////////////
// CAxSimpleDataGrid

IMPLEMENT_DYNCREATE(CAxSimpleDataGrid, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CAxSimpleDataGrid properties

/////////////////////////////////////////////////////////////////////////////
// CAxSimpleDataGrid operations

long CAxSimpleDataGrid::ConnectBYUDL(LPCTSTR szUDLFileName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szUDLFileName);
	return result;
}

long CAxSimpleDataGrid::SetQuery(LPCTSTR szQuery)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szQuery);
	return result;
}

void CAxSimpleDataGrid::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}