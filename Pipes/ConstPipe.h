//
//	ConstPipe.h
//
//	Copyright (C) Pete Cooke 11-Jul-2006 13:41:35
//
//#include "pipes\ConstPipe.h" //namespace CONS_PIPE
//

#pragma once

namespace CONS_PIPE{

	const DWORD dwDFLT_BUF_SIZE		= 4096L;
	const DWORD dwIN_BUF_SIZE		= dwDFLT_BUF_SIZE;
	const DWORD dwOUT_BUF_SIZE		= dwDFLT_BUF_SIZE;
	const DWORD dwDFLT_TIME_OUT		= 5000L;

	const TCHAR szCENTRAL_PIPE_NAME[]	= _T("Central_Pipe");
	const TCHAR szCELL_PIPE_ROOT[]		= _T("Cell_Pipe");

}	//end of namespace CONS_PIPE
