//ConstEventTypes.h

#pragma once

//#include "ConstEventTypes.h"
//using namespace CONS_EVT_TYPES;

//#ifndef _CONS_EVT_TYPES_INCLUDED
//#define _CONS_EVT_TYPES_INCLUDED


namespace CONS_EVT_TYPES{

	class _CONS_EVT_TYPES{};

	typedef enum _eEVT_TYPE{
		eEvt_None		= 0
		, eEvt_Debugging
		, eEvt_Information
		, eEvt_Warning
		, eEvt_Error
		, eEvt__LAST
	} eEVT_TYPE;

	const TCHAR szsEVENT_TYPE_NAMES[eEvt__LAST][40] = {
		_T("None")
		, _T("Debugging")
		, _T("Information")
		, _T("Warning")
		, _T("Error")
	};

	const COLORREF crefEVENT_BACK[eEvt__LAST] = {
		LIGHTGREEN		//eEvt_None		= 0
		, LIGHTGREEN	//, eEvt_Debugging
		, WHITE			//, eEvt_Information
		, YELLOW		//, eEvt_Warning
		, LIGHTRED		//, eEvt_Error
	};

	const COLORREF crefEVENT_FORE[eEvt__LAST] = {
		BLACK			//eEvt_None		= 0
		, BLACK			//, eEvt_Debugging
		, BLACK			//, eEvt_Information
		, BLACK			//, eEvt_Warning
		, BLACK			//, eEvt_Error
	};

}

//#endif