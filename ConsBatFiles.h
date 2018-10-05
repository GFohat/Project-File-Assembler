//ConsBatFiles.h

//#include "ConsBatFiles.h"
//using namespace CONS_BAT_FILES;

#pragma once

#define EMAS_ROOT _T("C:\\Winlink\\Installation\\InstallShield 12\\EMAS\\")
#define LINK_ROOT _T("C:\\Winlink\\Installation\\InstallShield 12\\Link\\")

namespace CONS_BAT_FILES{

	class _CONS_BAT_FILES{};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		The 'type' of batch file to process
	*/
	typedef enum _eBATFILE{
		eBF_BuildEmas					= 0
		, eBF_BuildLinkInstall
		, eBF_BuildLinkUpdate
		, eBF_BuildEmas_PIPED
		, eBF_BuildLinkInstall_PIPED
		, eBF_BuildLinkUpdate_PIPED
		, eBF__LAST
	} eBATFILE;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		Whether or not the batch file is redirected to a named pipe
	*/
	const bool bsIS_PIPED[eBF__LAST] = {
		false, false, false
		, true, true, true
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		'Pretty' names for the user to select from.
	*/
	const TCHAR szsBAT_FILE_TITLES[eBF__LAST][40] = {
		_T("Build eMAS")							//eBF_BuildEmas
		, _T("Build Link Install")					//eBF_BuildLinkInstall
		, _T("Build Link Update")					//eBF_BuildLinkUpdate
		, _T("Build eMAS (Piped)")					//eBF_BuildEmas_PIPED
		, _T("Build Link Install (Piped)")			//eBF_BuildLinkInstall_PIPED
		, _T("Build Link Update (Piped)")			//eBF_BuildLinkUpdate_PIPED
	};



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		Actual file names of the batch files
	*/
	const TCHAR szsBAT_FILE_FILENAMES[eBF__LAST][MAX_PATH] = {
		EMAS_ROOT		_T("BuildEMAS.bat")						//eBF_BuildEmas
		, LINK_ROOT		_T("BuildLINKInstall.IS12.bat")			//eBF_BuildLinkInstall
		, LINK_ROOT		_T("BuildLINKUpdate.IS12.bat")			//eBF_BuildLinkUpdate
		, EMAS_ROOT		_T("BuildEMAS.PIPED.bat")				//eBF_BuildEmas_PIPED
		, LINK_ROOT		_T("BuildLINKInstall.PIPED.IS12.bat")	//eBF_BuildLinkInstall_PIPED
		, LINK_ROOT		_T("BuildLINKUpdate.PIPED.IS12.bat")	//eBF_BuildLinkUpdate_PIPED
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		Whether or not we need to stop and wait for the 'CreateProcess' for the batch
		file to complete.

		'true'		means stop and wait for the process to finish.
		'false'		means don't wait (the process will be sending data 
					via the named pipe and we will need to deal with it)
	*/
	const bool bsWAIT_REQUIRED[eBF__LAST] = {
		true		//eBF_BuildEmas
		, true		//, eBF_BuildLinkInstall
		, true		//, eBF_BuildLinkUpdate
		, false		//, eBF_BuildEmas_PIPED
		, false		//, eBF_BuildLinkInstall_PIPED
		, false		//, eBF_BuildLinkUpdate_PIPED
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		Actual current working directories for the batch files
	*/
	const TCHAR szsBAT_FILE_RUNDIRS[eBF__LAST][MAX_PATH] = {
		EMAS_ROOT			//eBF_BuildEmas
		, LINK_ROOT			//eBF_BuildLinkInstall
		, LINK_ROOT			//eBF_BuildLinkUpdate
		, EMAS_ROOT			//eBF_BuildEmas_PIPED
		, LINK_ROOT			//eBF_BuildLinkInstall_PIPED
		, LINK_ROOT			//eBF_BuildLinkUpdate_PIPED
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		Results files for the batch files redirection
		
		NOTE: For the 'piped' variants, we will be writing to this file...
	*/
	const TCHAR szsRESULT_FILE_FILENAMES[eBF__LAST][MAX_PATH] = {
		EMAS_ROOT		_T("BuildResults.log")		//eBF_BuildEmas
		, LINK_ROOT		_T("BuildResults.log")		//eBF_BuildLinkInstall
		, LINK_ROOT		_T("BuildResults.log")		//eBF_BuildLinkUpdate
		, EMAS_ROOT		_T("BuildResults.log")		//eBF_BuildEmas_PIPED
		, LINK_ROOT		_T("BuildResults.log")		//eBF_BuildLinkInstall_PIPED
		, LINK_ROOT		_T("BuildResults.log")		//eBF_BuildLinkUpdate_PIPED
	};

}