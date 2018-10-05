//ConstStepStatus.h

//#include "ConstStepStatus.h"
//using namespace CONS_STEP_STATUS;

#pragma once

namespace CONS_STEP_STATUS{

	class _CONS_STEP_STATUS{};

	typedef enum _PFA_STEP_STATUS{
		ePStatus_None			= 0
		, ePStatus_Copying
		, ePStatus_IncompleteLine
		, ePStatus_DirCreationOnly
		, ePStatus_SourceNonExistent
		, ePStatus_DirCreationFailed
		, ePStatus_DirCreationOK
		, ePStatus_DirCopyOK
		, ePStatus_DirBeingEmptied
		, ePStatus_DirEmptiedOK
		, ePStatus_DirEmptyCancelled
		, ePStatus_DirEmptiedFail
		, ePStatus_IgnoredLine
		, ePStatus_FileDeleteOK
		, ePStatus_FileDeleteFailed
		, ePStatus_CopyFile
		, ePStatus_CopyFileOK
		, ePStatus_CopyFileFailed
		, ePStatus_UserCancelled
		, ePStatus_DirIncSubDirs
		, ePStatus_Validation
		, ePStatus_Validating
		, ePStatus_ValidatedOK
		, ePStatus_ValidatedBad
		, ePStatus__LAST
	} eSTEP_STATUS;

	const TCHAR szsSTATUS_NAMES_PFA[ePStatus__LAST][40] = {
		_T("-")									////ePStatus_None			= 0
		, _T("Copying")							//, ePStatus_Copying
		, _T("Incomplete line")					//, ePStatus_IncompleteLine
		, _T("Dir creation only")				//, ePStatus_DirCreationOnly
		, _T("Source File does not exist")		//, ePStatus_SourceNonExistent
		, _T("Dir creation failed")				//, ePStatus_DirCreationFailed
		, _T("Dir created")						//, ePStatus_DirCreationOK
		, _T("Dir copied")						//, ePStatus_DirCopyOK
		, _T("Dir Being Emptied")				//, ePStatus_DirBeingEmptied
		, _T("Dir Empty OK")					//, ePStatus_DirEmptiedOK
		, _T("Dir Empty Cancelled")				//, ePStatus_DirEmptyCancelled
		, _T("Dir Empty FAILED")				//, ePStatus_DirEmptiedFail
		, _T("Ignored Line")					//, ePStatus_IgnoredLine
		, _T("File Deleted OK")					//, ePStatus_FileDeleteOK
		, _T("File Delete Failed")				//, ePStatus_FileDeleteFailed
		, _T("Copy File")						//, ePStatus_CopyFile
		, _T("Copy File OK")					//, ePStatus_CopyFileOK
		, _T("Copy File Failed")				//, ePStatus_CopyFileFailed
		, _T("Copy cancelled by user")			//, ePStatus_UserCancelled
		, _T("Dir including sub-dirs")			//, ePStatus_DirIncSubDirs
		, _T("Validation")						//, ePStatus_Validation
		, _T("Validating")						//, ePStatus_Validating
		, _T("Validated OK")					//, ePStatus_ValidatedOK
		, _T("-<< INVALID >>-")					//, ePStatus_ValidatedBad	
	};

	typedef enum _STEP_STATUS_TYPE{
		eSST_Information			= 0
		, eSST_Active
		, eSST_Success
		, eSST_Failure
	} eSTEP_STATUS_TYPE;

	const eSTEP_STATUS_TYPE eStatusTypes[ePStatus__LAST] = {
		eSST_Information			//ePStatus_None			= 0
		, eSST_Active				//, ePStatus_Copying
		, eSST_Information			//, ePStatus_IncompleteLine
		, eSST_Information			//, ePStatus_DirCreationOnly
		, eSST_Information			//, ePStatus_SourceNonExistent
		, eSST_Failure				//, ePStatus_DirCreationFailed
		, eSST_Success				//, ePStatus_DirCreationOK
		, eSST_Success				//, ePStatus_DirCopyOK
		, eSST_Active				//, ePStatus_DirBeingEmptied
		, eSST_Success				//, ePStatus_DirEmptiedOK
		, eSST_Information			//, ePStatus_DirEmptyCancelled
		, eSST_Failure				//, ePStatus_DirEmptiedFail
		, eSST_Information			//, ePStatus_IgnoredLine
		, eSST_Success				//, ePStatus_FileDeleteOK
		, eSST_Failure				//, ePStatus_FileDeleteFailed
		, eSST_Information			//, ePStatus_CopyFile
		, eSST_Success				//, ePStatus_CopyFileOK
		, eSST_Failure				//, ePStatus_CopyFileFailed
		, eSST_Failure				//, ePStatus_UserCancelled
		, eSST_Information			//, ePStatus_DirIncSubDirs
		, eSST_Active				//, ePStatus_Validation
		, eSST_Active				//, ePStatus_Validating
		, eSST_Success				//, ePStatus_ValidatedOK
		, eSST_Failure				//, ePStatus_ValidatedBad	
	};
}