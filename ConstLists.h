//ConstLists.h

#pragma once

//#include "ConstLists.h"
//using namespace CONS_LISTS;

namespace CONS_LISTS{

	class _CONS_LISTS{};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	enum _eDATA_PROP_COLS{
		eDPCol_Name				= 0
		, eDPCol_Value
		, eDPCol__LAST
	};

	const TCHAR szsCOL_NAMES_DATAPROPCOLS[eDPCol__LAST][40] = {
		_T("Name")
		, _T("Value")
	};

	const int isCOL_FMTS_DATAPROPCOLS[eDPCol__LAST] = {
		LVCFMT_LEFT			//eDPCol_Name
		, LVCFMT_CENTER		//eDPCol_Value
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	enum _PFA_LIST_COLS{
		ePCol_File				= 0
		, ePCol_Source
		, ePCol_Destination
		, ePCol_CopiedName
		, ePCol_Status
		, ePCol__LAST
	};

	const TCHAR szsCOL_NAMES_PFA[ePCol__LAST][40] = {
		_T("File")
		, _T("Source")
		, _T("Destination")
		, _T("Copied Name")
		, _T("Status")
	};

	const int isCOL_FMTS_PFA[ePCol__LAST] = {
		LVCFMT_LEFT			//ePCol_File
		, LVCFMT_LEFT		//ePCol_Source
		, LVCFMT_LEFT		//ePCol_Destination
		, LVCFMT_LEFT		//ePCol_CopiedName
		, LVCFMT_CENTER		//ePCol_Status
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	enum _BUILD_LIST_COLS{
		eBLC_File			= 0
		, eBLC_Source
		, eBLC_Destination
		, eBLC__LAST
	};

	const TCHAR szsCOL_NAMES_BUILDLIST[eBLC__LAST][40] = {
		_T("File")
		, _T("Source")
		, _T("Destination")
	};

	const int isCOL_FMTS_BUILDLIST[eBLC__LAST] = {
		LVCFMT_LEFT			//ePCol_File
		, LVCFMT_LEFT		//ePCol_Source
		, LVCFMT_LEFT		//ePCol_Destination
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	enum _PFADATA_LIST_COLS{
		ePDataCol_StepNum		= 0
		, ePDataCol_SubStepNum
		, ePDataCol_StepType
		, ePDataCol_Status
		, ePDataCol_File
		, ePDataCol_Source
		, ePDataCol_Destination
		, ePDataCol_CopiedName
		, ePDataCol_Created
		, ePDataCol_Modified
		, ePDataCol__LAST
	};

	const TCHAR szsCOL_NAMES_PFA_DATA[ePDataCol__LAST][40] = {
		_T("Step")
		, _T("Sub")
		, _T("Type")
		, _T("Status")
		, _T("File")
		, _T("Source")
		, _T("Destination")
		, _T("Copied Name")
		, _T("Created")
		, _T("Modified")
	};

	const int isCOL_FMTS_PFA_DATA[ePDataCol__LAST] = {
		LVCFMT_LEFT			
		, LVCFMT_LEFT		
		, LVCFMT_LEFT		
		, LVCFMT_CENTER		
		, LVCFMT_LEFT		
		, LVCFMT_LEFT		
		, LVCFMT_LEFT		
		, LVCFMT_LEFT		
		, LVCFMT_CENTER		
		, LVCFMT_CENTER		
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	enum _ADDFILES_LIST_COLS{
		eAFCol_FileName			= 0
		, eAFCol_FileExt
		, eAFCol_Directory
		, eAFCol__LAST
	};

	const TCHAR szsCOL_NAMES_ADDFILES_DATA[eAFCol__LAST][40] = {
		_T("File Name")
		, _T("File Ext")
		, _T("Directory")
	};

	const int isCOL_FMTS_ADDFILES_DATA[eAFCol__LAST] = {
		LVCFMT_LEFT			
		, LVCFMT_LEFT		
		, LVCFMT_LEFT		
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	enum _GENERAL_FILE_COLS{
		eGFC_NamePath		= 0
		, eGFC_LastMod
		, eGFC_Size
		, eGFC__LAST
	};

	const TCHAR szsCOL_NAMES_GENERAL_FILES[eGFC__LAST][40] = {
		_T("File Name")
		, _T("Last Mod")
		, _T("Size")
	};

	const int isCOL_FMTS_GENERAL_FILES[eGFC__LAST] = {
		LVCFMT_LEFT			
		, LVCFMT_CENTER		
		, LVCFMT_RIGHT		
	};
}