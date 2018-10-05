//ConstStepTypes.h

#pragma once

//#include "ConstStepTypes.h"
//using namespace CONS_STEP_TYPES;

namespace CONS_STEP_TYPES{

	class _CONS_STEP_TYPES{};

	//===========================================
	//E X P O R T E D   F R O M   D A T A B A S E
	//===========================================

	//iRecID	szStepType
	//--------------------------------
	//0			Comment
	//1			Copy Single Directory
	//2			Copy Dir and Sub Dirs
	//3			Delete Dest File
	//4			Create New Dir
	//5			Copy Single File

	typedef enum _ePFA_STEP_TYPE{
		ePST_Comment				= 0
		, ePST_CopySingleDir
		, ePST_CopyDirAndSubDirs
		, ePST_DelDestFile
		, ePST_CreateNewDir
		, ePST_CopyFile
		, ePST__LAST
	} ePFA_STEP_TYPE;


}