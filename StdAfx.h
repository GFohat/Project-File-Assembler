// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E1383058_88A3_4727_84F4_0BA9FDEA846D__INCLUDED_)
#define AFX_STDAFX_H__E1383058_88A3_4727_84F4_0BA9FDEA846D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0A00		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0A00		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif						

//#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
//#define _WIN32_WINDOWS 0x0510 // Change this to the appropriate value to target Windows Me or later.
//#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0A00	// Change this to the appropriate value to target IE 5.0 or later.
#endif


#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//#ifndef ATLTRACE
//#define ATLTRACE TRACE
//#endif

//#ifndef ATLASSERT
//#define ATLASSERT ASSERT
//#endif

#ifndef __LOC__
#define __LOC__ ">>>>    "
#endif

#ifndef DWORD_PTR
#define DWORD_PTR DWORD
#endif

#ifndef INT_PTR
#define INT_PTR int
#endif

#include <AFXPRIV.H>

#include "THR.h"
#include "systemtime2.h"
using namespace INCLUDE_SERVICES::SYS_TIME2;

#include "pipes\pipeserverthread.h"
using namespace PIPE_SERVER;

#include "ConstGlobals.h"
using namespace CONS_GLOBAL;

#include "ConstAppearance.h"
using namespace CONS_APPEAR;

#include "ConstCsvSetup.h"
using namespace CONS_CSV_SETUP;

#include "ConstStepStatus.h"
using namespace CONS_STEP_STATUS;

#include "ConstMsgs.h"
using namespace CONS_MSGS;

#include "ConstCompareResult.h"
using namespace CONS_CMP_RES;

#include "ConstOptions.h"
using namespace CONS_OPTIONS;

#include "debugtimer.h"
using namespace INCLUDE_SERVICES::DBGTMR;

//#include "ConstEventTypes.h"
//using namespace CONS_EVT_TYPES;

#include "fonthandler.h"
#include "BrushHolder.h"
#include "FileCopyReport.h"

//#include <atlbase.h>

//dummy class that shows up in class view
//for easy double-click navigation to this file :)
class STDAFX_H{};

#include "ConstUDL.h"
using namespace CONS_UDL;


#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CProjectFileAssemblerModule : public CComModule
{
public:
	LONG Unlock();
	LONG Lock();
	LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2);
	DWORD dwThreadID;
};

extern CProjectFileAssemblerModule _Module;

#include <atlcom.h>
#include "ImportADO.h"
#include <atldbcli.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E1383058_88A3_4727_84F4_0BA9FDEA846D__INCLUDED_)
