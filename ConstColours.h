//ConstColours.h

//#include "ConstColours.h"
//using namespace CONS_COLOURS;

#pragma once

namespace CONS_COLOURS{
	
	class _CONS_COLOURS{};

	//! Enumerated color names.
	// Note, names are equal to COLORREF values to simplify assignment.
	enum _CLRS {
		//                  xxBBGGRR
		BLACK				= 0x00000000
		, RED				= 0x000000FF
		, GREEN				= 0x0000FF00
		, BLUE				= 0x00FF0000
		, CYAN				= 0x00FFFF00
		, MAGENTA			= 0x00FF00FF
		, YELLOW			= 0x0000FFFF
		, GRAY25			= 0x003F3F3F
		, GRAY50			= 0x007F7F7F
		, GRAY75			= 0x00BFBFBF
		, GRAY				= GRAY50
		, ORANGE			= 0x0000A5FF
		, BROWN				= 0x00A52A2A
		, PURPLE			= 0x00A020F0
		, DARKRED			= 0x00000080
		, DARKGREEN			= 0x00008000
		, DARKBLUE			= 0x00800000
		, DARKCYAN			= 0x00808000
		, DARKMAGENTA		= 0x00A000A0
		, DARKYELLOW		= 0x00008080
		, FORESTGREEN		= 0x00228B22
		, LIGHTGRAY			= 0x00DDDDDD
		, VERYLIGHTGRAY		= 0x00F0F0F0
		, WHITE				= 0x00FFFFFF
		, LIGHTGREEN		= 0x00DDFFDD
		, LIGHTRED			= 0x00DDDDFF
		, LIGHTBLUE			= 0x00FFDDDD
	};

	const COLORREF crefPAGE_BACK		= VERYLIGHTGRAY;
	const COLORREF crefSUCCESS_FORE		= BLACK;
	const COLORREF crefSUCCESS_BACK		= LIGHTGREEN;
	const COLORREF crefERROR_FORE		= BLACK;
	const COLORREF crefERROR_BACK		= LIGHTRED;
	const COLORREF crefACTIVE_FORE		= BLACK;
	const COLORREF crefACTIVE_BACK		= YELLOW;
	const COLORREF crefNORMAL_FORE		= BLACK;
	const COLORREF crefNORMAL_BACK		= WHITE;
	const COLORREF crefREADONLY_FORE	= BLACK;
	const COLORREF crefREADONLY_BACK	= LIGHTBLUE;
	const COLORREF crefCOMMENT_FORE		= BLACK;
	const COLORREF crefCOMMENT_BACK		= RGB(0xC3, 0xF7, 0xF7);

	//Text box background when performing direct editing of data
	//in the list control
// 	const COLORREF crefFLOAT_EDIT_BACK				= crefACTIVE_BACK;
// 	const COLORREF crefSPLASH_EDIT_BACK				= crefACTIVE_BACK;
// 	const COLORREF crefBATCH_FILE_CONTENTS_BACK		= crefREADONLY_BACK;
// 	const COLORREF crefLOG_TEXT_BACK				= crefREADONLY_BACK;

}