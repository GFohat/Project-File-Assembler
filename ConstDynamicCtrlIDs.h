
//ConstDynamicCtrlIDs.h

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/05/2007 09:33:31
	DESCRIP:	
		Control IDs for items that are created dynamically (ie not assigned using class wizard)
*/

//#include "ConstDynamicCtrlIDs.h" 
//using namespace CONS_CTL_IDS;

#pragma once

namespace CONS_CTL_IDS{

	//control IDs for dynamic controls
	enum _CTL_IDS{
		//dwIDC_CMBO_STEPTYPE		= eMnuID__LAST	//last menu ID //eWM__LAST		//last 'user' message (as a uniqueifier)
		dwIDC_CMBO_STEPTYPE		= eWM__LAST		//last 'user' message (as a uniqueifier)
		, dwIDC_RED_EDIT
		, dwIDC_BN_BROWSE
	};

}
