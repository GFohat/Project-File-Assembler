//ConstAppearance.h

#pragma once

//#include "ConstAppearance.h"
//using namespace CONS_APPEAR;

#include "ConstCsvSetup.h"
//using namespace CONS_CSV_SETUP;

#include "ConstStepTypes.h"
//using namespace CONS_STEP_TYPES;

#include "ConstColours.h"
using namespace CONS_COLOURS;

namespace CONS_APPEAR{

	class _CONS_APPEAR{};

	typedef enum _eFont{
		eFont_List			= 0
		, eFont_ListHeader
		, eFont_Help
		, eFont_Tab
		, eFont_Buttons
		, eFont_EdBoxes
		, eFont_EdBoxes_Title
		, eFont_Combo
		, eFont_Splash
		, eFont__LAST
	} eFont;

	const TCHAR	szsFONT_FACE[eFont__LAST][40] = {
		_T("Verdana")			//eFont_List
		, _T("Verdana")			//, eFont_ListHeader
		, _T("Verdana")			//, eFont_Help
		, _T("Verdana")			//, eFont_Tab
		, _T("Verdana")			//, eFont_Buttons
		, _T("Verdana")			//, eFont_EdBoxes
		, _T("Verdana")			//, eFont_EdBoxes_Title
		, _T("Verdana")			//, eFont_Combo
		, _T("Verdana")			//, eFont_Splash
	};

	const int isFONT_POINTS[eFont__LAST] = {
		10			//eFont_List
		, 10		//, eFont_ListHeader
		, 10		//, eFont_Help
		, 12		//, eFont_Tab
		, 10		//, eFont_Buttons
		, 10		//, eFont_EdBoxes
		, 12		//, eFont_EdBoxes_Title
		, 12		//, eFont_Combo
		, 12		//, eFont_Splash
	};

	const int isFONT_WEIGHTS[eFont__LAST] = {
		FW_MEDIUM		//eFont_List
		, FW_BOLD		//, eFont_ListHeader
		, FW_NORMAL		//, eFont_Help
		, FW_BOLD		//, eFont_Tab
		, FW_NORMAL		//, eFont_Buttons
		, FW_NORMAL		//, eFont_EdBoxes
		, FW_SEMIBOLD	//, eFont_EdBoxes_Title
		, FW_NORMAL		//, eFont_Combo
		, FW_BOLD		//, eFont_Splash
	};


	typedef enum _eRCV_LINE_TYPE{
		eRlt_Normal					= 0
		, eRlt_HighLight
		, eRlt_Warning
		, eRlt_Error
		, eRlt__LAST
	} eRCV_LINE_TYPE;

	const TCHAR	szsFONT_FACE_RCVTXT[eRlt__LAST][40] = {
		_T("Courier New")		//eRlt_Normal
		, _T("Verdana")			//eRlt_HighLight
		, _T("Verdana")			//eRlt_Warning
		, _T("Verdana")			//eRlt_Error
	};

	//font height is 20 times font points
	const int isFONT_HEIGHTS_RCVTXT[eRlt__LAST] = {
		10 * 20			//eRlt_Normal
		, 12 * 20		//eRlt_HighLight
		, 12 * 20		//eRlt_Warning
		, 12 * 20		//eRlt_Error
	};

	const int isFONT_WEIGHTS_RCVTXT[eRlt__LAST] = {
		FW_MEDIUM		//eRlt_Normal
		, FW_BOLD		//eRlt_HighLight
		, FW_BOLD		//eRlt_Warning
		, FW_BOLD		//eRlt_Error
	};

	const COLORREF crefsLINE_FORE_RCVTXT[eRlt__LAST] = {
		FORESTGREEN		//eRlt_Normal		
		, DARKBLUE		//eRlt_HighLight
		, BLACK			//eRlt_Warning
		, RED			//eRlt_Error
	};

	//Background colouring
	const COLORREF crefsLINE_BACK_RCVTXT[eRlt__LAST] = {
		WHITE			//eRlt_Normal		
		, WHITE			//eRlt_HighLight
		, YELLOW		//eRlt_Warning
		, WHITE			//eRlt_Error
	};

//	typedef enum _eCSV_LINE_TYPE{
//		eCLT_Comment			= 0
//		, eCLT_CopySingleFile
//		, eCLT_CopySingleDir
//		, eCLT_CopyDirAndSubDirs
//		, eCLT_CreateNewDir
//		, eCLT__LAST
//	} eCSV_LINE_TYPE;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		STAMP:	30/04/2007 08:15:24
		DESCRIP:
			
			  Following is text colouring for the original PFA dialog
			  which has now been converted to a property page.

		IN:
		OUT:
	*/
	//Text colouring
	const COLORREF crefsLINE_FORE[CONS_CSV_SETUP::eCLT__LAST] = {
		FORESTGREEN		//eCLT_Comment		
		, DARKBLUE		//, eCLT_CopySingleFile
		, PURPLE		//, eCLT_CopySingleDir
		, DARKBLUE		//, eCLT_CopyDirAndSubDirs
		, DARKRED		//, eCLT_CreateNewDir
	};

	//Background colouring
	const COLORREF crefsLINE_BACK[CONS_CSV_SETUP::eCLT__LAST] = {
		VERYLIGHTGRAY	//eCLT_Comment		
		, WHITE			//, eCLT_CopySingleFile
		, WHITE			//, eCLT_CopySingleDir
		, WHITE			//, eCLT_CopyDirAndSubDirs
		, WHITE			//, eCLT_CreateNewDir
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		STAMP:	30/04/2007 08:16:16
		DESCRIP:	
			
			  Following is text colouring for the new PFA dialog
			  which reads data from a database.

		IN:
		OUT:
	*/
	//Text colouring
	const COLORREF crefsLINE_FORE_OLEDB[CONS_STEP_TYPES::ePST__LAST] = {
		crefCOMMENT_FORE			//ePST_Comment	= 0
		, DARKBLUE					//, ePST_CopySingleDir
		, PURPLE					//, ePST_CopyDirAndSubDirs
		, DARKBLUE					//, ePST_DelDestFile
		, DARKRED					//, ePST_CreateNewDir
		, DARKBLUE					//, ePST_CopyFile
	};

	//Background colouring
	const COLORREF crefsLINE_BACK_OLEDB[CONS_STEP_TYPES::ePST__LAST] = {
		crefCOMMENT_BACK		//ePST_Comment	= 0
		, WHITE					//, ePST_CopySingleDir
		, WHITE					//, ePST_CopyDirAndSubDirs
		, WHITE					//, ePST_DelDestFile
		, WHITE					//, ePST_CreateNewDir
		, WHITE					//, ePST_CopyFile
	};


	const DWORD dwMAX_LIST_CELL_TEXT	= 75L;		//absolute maximum is about 259
	const DWORD dwMAX_COMBO_TEXT		= 75L;		//absolute maximum is about ?
}