//ConstSQL.h

//#include "ConstSQL.h"
//using namespace CONS_SQL;

#pragma once

namespace CONS_SQL{

	class _CONS_SQL{};

	/////////////////////////////////////////////////////////////////////////////////////////////
	const TCHAR szSQL_PROJECT_COMBO[] = 
							_T(" SELECT ")
							_T("	iProjectID ")
							_T("	, szProjectName ")
							_T(" FROM tblProjects ")
							_T(" ORDER BY szProjectName ");

	const TCHAR szFIELD_PROJECT_STRINGS	[]	= _T("szProjectName");
	const TCHAR szFIELD_PROJECT_IDS		[]	= _T("iProjectID");


	/////////////////////////////////////////////////////////////////////////////////////////////
	//SELECT tblStepTypes.iRecID, tblStepTypes.szStepType
	//FROM tblStepTypes;

	const TCHAR szSQL_STEPTYPE_COMBO[] = 
							_T(" SELECT ")
							_T("	iRecID ")
							_T("	, szStepType ")
							_T(" FROM tblStepTypes ")
							_T(" ORDER BY szStepType ");

	const TCHAR szFIELD_STEPTYPE_STRINGS	[]	= _T("szStepType");
	const TCHAR szFIELD_STEPTYPE_IDS		[]	= _T("iRecID");


	/////////////////////////////////////////////////////////////////////////////////////////////
	const TCHAR szSQL_ASSEMBLY_STEPS[] = 
							_T(" SELECT ")
							_T("     szProjectName ")
							_T("     , iProjectID ")
							_T("     , iStep ")
							_T("     , iStepType ")
							_T("     , szStepType ")
							_T("     , szSourceFile ")
							_T("     , szSourceDir ")
							_T("     , szDestDirectory ")
							_T("     , szDestFile ")
							_T("     , szCreated ")
							_T("     , szModified ")
							_T(" FROM vwProjectAssemblySteps ");


	typedef enum _eSTEP_FIELD{
		eSFld_szProjectName
		, eSFld_iProjectID
		, eSFld_iStep
		, eSFld_iStepType
		, eSFld_szStepType
		, eSFld_SourceFile
		, eSFld_SourceDir
		, eSFld_DestDirectory
		, eSFld_DestFile
		, eSFld_Created
		, eSFld_Modified
		, eSFld__LAST
	} eSTEP_FIELD;

	const BSTR bstrsSTEP_FIELDS[eSFld__LAST] = {
		L"szProjectName"
		, L"iProjectID"
		, L"iStep"
		, L"iStepType"
		, L"szStepType"
		, L"szSourceFile"
		, L"szSourceDir"
		, L"szDestDirectory"
		, L"szDestFile"
		, L"szCreated"
		, L"szModified"
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	const TCHAR szSQL_PROJECT_TABLE[] = 
							_T(" SELECT ")
							_T("     [iProjectID] ")
							_T("     , [szProjectName] ")
							_T("     , [szDefaultSourceDir] ")
							_T("     , [szDefaultDestDir] ")
							_T(" FROM [tblProjects] ");

	typedef enum _ePROJECT_FIELD{
		eProjFld_ProjectID		= 0
		, eProjFld_ProjectName	
		, eProjFld_DfltSrcDir	
		, eProjFld_DfltDestDir
		, eProjFld__LAST			
	} ePROJECT_FIELD;

	const BSTR bstrsPROJECT_FIELDS[eProjFld__LAST] = {
		L"iProjectID"
		, L"szProjectName"
		, L"szDefaultSourceDir"
		, L"szDefaultDestDir"
	};

	const bool bsIS_NUMERIC_PROJECT_FIELD[eProjFld__LAST] = {
		true
		, false
		, false
		, false
	};



	/////////////////////////////////////////////////////////////////////////////////////////////
	const TCHAR szSQL_LOG_LIST_ALL[] = 
							_T(" SELECT  ")				//TOP 35
							_T("     [iRecID] ")
							_T("     , [dtWhen] ")
							_T("     , [iType] ")
							_T("     , [szType] ")
							_T("     , [szLogon] ")
							_T("     , [szMachine] ")
							_T("     , [szSource] ")
							_T("     , [szText] ")
							_T("     , [szSQL] ")
							_T(" FROM tblLogging ")
						;

	enum _eLOG_LIST_COLS{
		eLogCol_RecID		= 0
		, eLogCol_When
		, eLogCol_iType
		, eLogCol_strType
		, eLogCol_Logon
		, eLogCol_Machine
		, eLogCol_Source
		, eLogCol_Text
		, eLogCol_SQL
		, eLogCol__LAST
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	const TCHAR szSQL_STEPS_TABLE[] = 
							_T(" SELECT ")
							_T("     [iRecID] ")
							_T("     , [iProjectID] ")
							_T("     , [iStep] ")
							_T("     , [iStepType] ")
							_T("     , [szSourceFile] ")
							_T("     , [szSourceDir] ")
							_T("     , [szDestDirectory] ")
							_T("     , [szDestFile] ")
							_T("     , [szCreated] ")
							_T("     , [szModified] ")
							_T(" FROM [tblProjectAssemblySteps]")
						;

	enum _eSTEPS_TABLE_FIELD{
		eStepFld_iRecID				= 0
		, eStepFld_iProjectID
		, eStepFld_iStep
		, eStepFld_iStepType
		, eStepFld_szSourceFile
		, eStepFld_szSourceDir
		, eStepFld_szDestDirectory
		, eStepFld_szDestFile
		, eStepFld_szCreated
		, eStepFld_szModified
		, eStepFld__LAST
	};

	const BSTR bstrsSTEP_TABLE_FIELDS[eStepFld__LAST] = {
		L"iRecID"
		, L"iProjectID"
		, L"iStep"
		, L"iStepType"
		, L"szSourceFile"
		, L"szSourceDir"
		, L"szDestDirectory"
		, L"szDestFile"
		, L"szCreated"
		, L"szModified"
	};

	const bool bsIS_NUMERIC_STEP_TABLE_FIELD[eStepFld__LAST] = {
		true
		, true
		, true
		, true
		, false
		, false
		, false
		, false
		, false
		, false
	};

}