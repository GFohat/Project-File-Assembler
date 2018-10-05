//ConstMsgs.h

#pragma once

//#include "ConstMsgs.h"
//using namespace CONS_MSGS;

namespace CONS_MSGS{

	class _CONS_MSGS{};

	enum _MSGS{
		eWM_BEGIN_IMMEDIATE				= WM_APP
		, eWM_SINGLEFILE_PC_POS
		, eWM_DO_SINGLE_OP					//wparam is a list item index, lparam is a pointer to new CPfaDataListItem
		, eWM_VALIDATE_SINGLE_OP			//wparam is a list item index, lparam is a pointer to new CPfaDataListItem
		, eWM_SINGLE_OP_STATUS				//wparam is a list item index, lparam is a status enum
		, eWM_SINGLE_OP_RESULT				//wparam is a list item index, lparam is a pointer to new CPfaDataListItem
		, eWM_SINGLE_OP_VALIDATION			//wparam is a list item index, lparam is a pointer to new CPfaDataListItem
		, eWM_NO_MORE_ITEMS					//to reset the CDirInitHandler
		, eWM_EVENT_REPORT					//lparam is a pointer to a new CFileCopyReport
		, eWM_SKIPPED_SINGLE_OP				//wparam is a list item index that has been skipped
		, eWM_SKIPPED_SINGLE_VALIDATION		//wparam is a list item index that has been skipped
		, eWM_REFRESH_LIST					//no args
		, eWM_REARRANGE_CONTROLS			//no args
		, eWM_GET_FONT						//wParam is an enum, LPARAM is a pointer to a CWnd that needs a font setting
		, eWM_PIPE_DATA_RECEIVED			//LPARAM: TCHAR * pszRequest = new TCHAR[dwNumChars + 5]
		, eWM_PIPE_INSTANCE_STARTUP			//no args
		, eWM_PIPE_INSTANCE_SHUTDOWN		//no args
		, eWM_PAGE_ACTIVATED				//wparam is a page id, lparam = FALSE for inactive, TRUE for active
		, eWM_SET_APPEARANCE				//no args, fonts have been created ready to be 'gotten'
		, eWM_SPLASH_INIT_DONE				//no args, sent to the main pfa sheet when the splash screen 'oninitdialog' has finished
		, eWM_SPLASH_START_PIC_INIT			//no args
		, eWM_SPLASH_PIC_INIT_DONE			//no args
		, eWM_REFRESH_LOG_LIST				//no args
		, eWM__LAST
	};
}