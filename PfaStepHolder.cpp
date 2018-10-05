// PfaStepHolder.cpp: implementation of the CPfaStepHolder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "PfaStepHolder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPfaStepHolder::CPfaStepHolder()
:	m_iMinStepNumber	(-1L)
	, m_iProjectID		(-1L)
{

}

CPfaStepHolder::~CPfaStepHolder()
{
	DeleteAll();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/05/2007 18:11:47
	DESCRIP:	
	IN:
	OUT:
*/
bool CPfaStepHolder::AddPfaStep(const CPfaStep & step)
{
	//must be either the first of a series, 
	//or the same project id with a new step number
	//in either case, must have a positive step number ( 1 or higher, NOT zero)
	bool bValid = IsValidStep(step);
	ATLASSERT(bValid);

	if(bValid){
		if(m_iMinStepNumber > step.GetProjectStep())
			m_iMinStepNumber = step.GetProjectStep();

		ATLASSERT(m_iMinStepNumber >= iMINSTEPVAL);

		if(m_iMinStepNumber >= iMINSTEPVAL){
			CPfaStep * pNew = new CPfaStep(step);
			ATLASSERT(pNew);
		
			m_steplist.push_back(pNew);
		}

	}

	return bValid;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/05/2007 18:42:00
	DESCRIP:	
		must be either 
			the first of a series, 
		or 
			the same project id with a new step number
	IN:
	OUT:
*/
bool CPfaStepHolder::IsValidStep(const CPfaStep & step)
{
	bool bValid = false;

	//if we're empty, anything goes!
	if( ! m_steplist.size()){
		m_iProjectID		= step.GetProjectID();	
		m_iMinStepNumber	= step.GetProjectStep();
		bValid				= true;
	}

	//we have already had a least one entry
	else{
	
		//we should have already initialized m_iProjectID :}
		if(step.GetProjectID() != m_iProjectID)
			bValid = false;

		//this iterates the entire list, so do it last
		else
			bValid = IsNewStepNumber(step);
	}

	return bValid;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/05/2007 19:03:00
	DESCRIP:	
	IN:
	OUT:
*/
bool CPfaStepHolder::IsNewStepNumber(const CPfaStep & step) const
{
	bool bNew = true;

	STEP_LIST::const_iterator it;
	const CPfaStep * pCompare = 0;
	
	for(it = m_steplist.begin() ; it != m_steplist.end() && bNew ; it ++){
		
		pCompare = *it;
		ATLASSERT(pCompare);
		
		if(pCompare){
			
			if(pCompare->GetProjectStep() == step.GetProjectStep())
				bNew = false;
			
		}
	}

	return bNew;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/05/2007 18:11:44
	DESCRIP:	
	IN:
	OUT:
*/
void CPfaStepHolder::DeleteAll(void)
{
	CPfaStep * pDel = 0;

	while(m_steplist.size()){

		pDel = m_steplist.at(0);
		ATLASSERT(pDel);
		
		if(pDel){
			delete pDel;
			pDel = 0;
		}

		m_steplist.pop_front();
	}

	m_iMinStepNumber = -1L;
	m_iProjectID = -1L;
}

