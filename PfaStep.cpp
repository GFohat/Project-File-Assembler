// PfaStep.cpp: implementation of the CPfaStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "PfaStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPfaStep::CPfaStep()
:	m_iProjectID		(-1L)
	, m_iProjectStep	(-1L)
	, m_eStepType		(ePST_Comment)
	, m_strSrcFile		(_T(""))
	, m_strSrcDir		(_T(""))
	, m_strDestDir		(_T(""))
	, m_strDestFile		(_T(""))
{

}

CPfaStep::CPfaStep(
				const long iProjectID
				, const long iProjectStep
				, const ePFA_STEP_TYPE eType
				, const CString & strSrcFile
				, const CString & strSrcDir
			)
:	m_iProjectID		(iProjectID)
	, m_iProjectStep	(iProjectStep)
	, m_eStepType		(eType)
	, m_strSrcFile		(strSrcFile)
	, m_strSrcDir		(strSrcDir)
	, m_strDestDir		(_T(""))
	, m_strDestFile		(_T(""))
{

}

CPfaStep::~CPfaStep()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/05/2007 18:15:07
	DESCRIP:	
	IN:
	OUT:
*/
const CPfaStep & CPfaStep::operator = (const CPfaStep & src)
{
#pragma message("CPfaStep::operator =")

	m_iProjectID	= src.m_iProjectID;
	m_iProjectStep	= src.m_iProjectStep;
	m_eStepType		= src.m_eStepType;
	m_strSrcFile	= src.m_strSrcFile;
	m_strSrcDir		= src.m_strSrcDir;
	m_strDestDir	= src.m_strDestDir;
	m_strDestFile	= src.m_strDestFile;

	//this will assert on an un-initialized 'src'
	ATLASSERT(m_iProjectID		>= 1L);
	ATLASSERT(m_iProjectStep	>= iMINSTEPVAL);

	return * this;
}
