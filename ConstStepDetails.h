//"ConstStepDetails.h"

//#include "ConstStepDetails.h"
//using namespace CONS_STEP_DETAILS;

#pragma once

#include "ConstCsvSetup.h"
using namespace CONS_CSV_SETUP;

namespace CONS_STEP_DETAILS{
	
	class _CONS_STEP_DETAILS{};

	//typedef enum _ePFA_STEP_TYPE{
	//	ePST_Comment	= 0
	//	, ePST_CopySingleDir
	//	, ePST_CopyDirAndSubDirs
	//	, ePST_DelDestFile
	//	, ePST_CreateNewDir
	//	, ePST_CopyFile
	//	, ePST__LAST
	//} ePFA_STEP_TYPE;

	/////////////////////////////////////////////////////////
	//	S O U R C E   F I L E

	//the text for the first label...
	const TCHAR szsLABEL_0_TEXTS[ePST__LAST][40] = {
		_T("Comment")		//	ePST_Comment
		, _T("N/A")			//	ePST_CopySingleDir
		, _T("N/A")			//	ePST_CopyDirAndSubDirs
		, _T("N/A")			//	ePST_DelDestFile
		, _T("N/A")			//	ePST_CreateNewDir
		, _T("File")		//	ePST_CopyFile
	};

	//the enable signal for the first text box...
	const bool bsENABLE_EDIT_0[ePST__LAST] = {
		true		//	ePST_Comment
		, false		//	ePST_CopySingleDir
		, false		//	ePST_CopyDirAndSubDirs
		, false		//	ePST_DelDestFile
		, false		//	ePST_CreateNewDir
		, true		//	ePST_CopyFile
	};

	/////////////////////////////////////////////////////////
	//	S O U R C E   D I R E C T O R Y

	//the text for the second label...
	const TCHAR szsLABEL_1_TEXTS[ePST__LAST][40] = {
		_T("Comment")			//	ePST_Comment
		, _T("Source")			//	ePST_CopySingleDir
		, _T("Source Root")		//	ePST_CopyDirAndSubDirs
		, _T("N/A")				//	ePST_DelDestFile
		, _T("N/A")				//	ePST_CreateNewDir
		, _T("Source")			//	ePST_CopyFile
	};

	//the enable signal for the second text box...
	const bool bsENABLE_EDIT_1[ePST__LAST] = {
		true		//	ePST_Comment
		, true		//	ePST_CopySingleDir
		, true		//	ePST_CopyDirAndSubDirs
		, false		//	ePST_DelDestFile
		, false		//	ePST_CreateNewDir
		, true		//	ePST_CopyFile
	};

	/////////////////////////////////////////////////////////
	//	D E S T I N A T I O N   D I R E C T O R Y

	//the text for the second label...
	const TCHAR szsLABEL_2_TEXTS[ePST__LAST][40] = {
		_T("Comment")				//	ePST_Comment
		, _T("Destination")			//	ePST_CopySingleDir
		, _T("Destination Root")	//	ePST_CopyDirAndSubDirs
		, _T("N/A")					//	ePST_DelDestFile
		, _T("Destination")			//	ePST_CreateNewDir
		, _T("Destination")			//	ePST_CopyFile
	};

	//the enable signal for the second text box...
	const bool bsENABLE_EDIT_2[ePST__LAST] = {
		true		//	ePST_Comment
		, true		//	ePST_CopySingleDir
		, true		//	ePST_CopyDirAndSubDirs
		, false		//	ePST_DelDestFile
		, true		//	ePST_CreateNewDir
		, true		//	ePST_CopyFile
	};

	/////////////////////////////////////////////////////////
	//	D E S T I N A T I O N   F I L E

	//the text for the second label...
	const TCHAR szsLABEL_3_TEXTS[ePST__LAST][40] = {
		_T("Comment")		//	ePST_Comment
		, _T("N/A")			//	ePST_CopySingleDir
		, _T("N/A")			//	ePST_CopyDirAndSubDirs
		, _T("N/A")			//	ePST_DelDestFile
		, _T("N/A")			//	ePST_CreateNewDir
		, _T("New Name")	//	ePST_CopyFile
	};

	//the enable signal for the second text box...
	const bool bsENABLE_EDIT_3[ePST__LAST] = {
		true		//	ePST_Comment
		, false		//	ePST_CopySingleDir
		, false		//	ePST_CopyDirAndSubDirs
		, false		//	ePST_DelDestFile
		, false		//	ePST_CreateNewDir
		, true		//	ePST_CopyFile
	};

}