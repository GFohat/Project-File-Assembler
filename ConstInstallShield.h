//ConstInstallShield.h

//#include "ConstInstallShield.h"
//using namespace CONS_INSTALLSHIELD;

#pragma once

namespace CONS_INSTALLSHIELD{

	class _CONS_INSTALLSHIELD{};

	enum _ISVERSION{
		eISVer_Ten			= 0
		, eISVer_Twelve
		, eISVer__LAST
	};

	const TCHAR szsIS_ROOT_DIR[eISVer__LAST][MAX_PATH] = {
		_T("C:\\winlink\\Installation\\INSTALLSHIELD 10")
		, _T("C:\\winlink\\Installation\\InstallShield 12")
	};

	const TCHAR szISPROJ_EXT[] = _T(".ISM");
}