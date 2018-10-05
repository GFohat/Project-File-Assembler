//ConstCsvSetup.h

//#include "ConstCsvSetup.h"
//using namespace CONS_CSV_SETUP;

#pragma once

namespace CONS_CSV_SETUP{
	
	class _CONS_CSV_SETUP{};

	//index into the colums of the CSV file
	enum _CSV_ITEMS{
		eCI_File		= 0
		, eCI_SourceDir
		, eCI_DestDir
		, eCI_CopiedName
		, eCI__LAST
	};

	typedef enum _eCSV_LINE_TYPE{
		eCLT_Comment			= 0
		, eCLT_CopySingleFile
		, eCLT_CopySingleDir
		, eCLT_CopyDirAndSubDirs
		, eCLT_CreateNewDir
		, eCLT__LAST
	} eCSV_LINE_TYPE;

	const TCHAR szsCLT_DESCRIPS[eCLT__LAST][40] = {
		_T("Comment")
		, _T("Copy Single File")
		, _T("Copy Single Dir")
		, _T("Copy Dir and Sub-Dirs")
		, _T("Create New Dir")
	};

}
