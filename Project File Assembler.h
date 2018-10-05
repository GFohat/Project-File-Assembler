// Project File Assembler.h : main header file for the PROJECT FILE ASSEMBLER application
//

#if !defined(AFX_PROJECTFILEASSEMBLER_H__B2719BCF_3BCA_48E7_A4D1_52D51D6C77F8__INCLUDED_)
#define AFX_PROJECTFILEASSEMBLER_H__B2719BCF_3BCA_48E7_A4D1_52D51D6C77F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "ProjectFileAssembler_i.h"

/////////////////////////////////////////////////////////////////////////////
// CProjectFileAssemblerApp:
// See Project File Assembler.cpp for the implementation of this class
//

class CProjectFileAssemblerApp : public CWinApp
{
public:
	CProjectFileAssemblerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectFileAssemblerApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProjectFileAssemblerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTFILEASSEMBLER_H__B2719BCF_3BCA_48E7_A4D1_52D51D6C77F8__INCLUDED_)
