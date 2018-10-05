// PfaStepHolder.h: interface for the CPfaStepHolder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PFASTEPHOLDER_H__937775F7_51A2_4007_8E69_D7334BC372C0__INCLUDED_)
#define AFX_PFASTEPHOLDER_H__937775F7_51A2_4007_8E69_D7334BC372C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <deque>
#include "PfaStep.h"

typedef std::deque<CPfaStep *> STEP_LIST;

class CPfaStepHolder  
{
public:
	CPfaStepHolder();
	virtual ~CPfaStepHolder();

public:
	bool AddPfaStep(const CPfaStep & step);
	void DeleteAll(void);

public:
	inline STEP_LIST &	GetStepList			(void)	{ return m_steplist; }
	inline long			GetMinStepNumber	(void)	{ return m_iMinStepNumber; }
	inline long			GetProjectID		(void)	{ return m_iProjectID; }

private:
	bool IsValidStep		(const CPfaStep & step);
	bool IsNewStepNumber	(const CPfaStep & step) const;

private:
	STEP_LIST	m_steplist;
	long		m_iMinStepNumber;
	long		m_iProjectID;
};

#endif // !defined(AFX_PFASTEPHOLDER_H__937775F7_51A2_4007_8E69_D7334BC372C0__INCLUDED_)
