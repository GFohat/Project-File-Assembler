//ConstReport.h

//#include "ConstReport.h"
//using namespace CONS_RPT;

#pragma once

namespace CONS_RPT{

	class _CONS_RPT{};

	typedef enum _eRPT_LINETYPE{
		eRLT_Comment
		, eRLT_CreateDir
		, eRLT_CopyFile
		, eRLT_DeleteFile
		, eRLT_DeleteDir
		, eRLT_CopySingleDirectory
		, eRLT_CopyDirSubDirs
		, eRLT_DirEmptied
		, eRLT__LAST
	} eRPT_LINETYPE;

	const TCHAR szsRPT_LINE_DESCRIPS[eRLT__LAST][40] = {
		_T("//")
		, _T("CREATE DIR")
		, _T("COPY FILE")
		, _T("DELETE FILE")
		, _T("DELETE DIR")
		, _T("COPY 1 DIR")
		, _T("COPY DIR + SUBDIRS")
		, _T("DIR EMPTIED")
	};

	const TCHAR szTIME_FORMAT[] = _T("%Y-%m-%d %H:%M:%S");
}