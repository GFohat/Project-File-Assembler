//ConstOptions.h

#pragma once

//#include "ConstOptions.h"
//using namespace CONS_OPTIONS;

namespace CONS_OPTIONS{

	class _CONS_OPTIONS{};

	typedef enum _eOPTION{
		eOpt_SaveValidateReport	= 0
		, eOpt_SaveCopyReport
		, eOPt_SaveBuildReport
		, eOpt__LAST
	} eOPTION;

	const TCHAR szsOPT_NAMES[eOpt__LAST][49] = {
		_T("Save Validate Report")	//eOpt_SaveValidateReport
		, _T("Save Copy Report")	//eOpt_SaveCopyReport
		, _T("Save Build Report")	//eOPt_SaveBuildReport
	};

	const TCHAR szsOPT_DEFAULTS[eOpt__LAST][49] = {
		_T("false")		//eOpt_SaveValidateReport
		, _T("true")	//eOpt_SaveCopyReport
		, _T("true")	//eOPt_SaveBuildReport
	};

}