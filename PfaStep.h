// PfaStep.h: interface for the CPfaStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PFASTEP_H__90E07E34_DD11_4C0B_8491_9D5494251FBD__INCLUDED_)
#define AFX_PFASTEP_H__90E07E34_DD11_4C0B_8491_9D5494251FBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConstStepTypes.h"
using namespace CONS_STEP_TYPES;

class CPfaStep  
{
public:
	CPfaStep();
	CPfaStep(
			const long iProjectID
			, const long iProjectStep
			, const ePFA_STEP_TYPE eType
			, const CString & strSrcFile
			, const CString & strSrcDir
		);

	CPfaStep(const CPfaStep & src) { *this = src; }

	virtual ~CPfaStep();

public:
	const CPfaStep & operator = (const CPfaStep & src);

public:
	inline long				GetProjectID	(void) const { return m_iProjectID; }
	inline long				GetProjectStep	(void) const { return m_iProjectStep; }
	inline ePFA_STEP_TYPE	GetStepType		(void) const { return m_eStepType; }

	inline const CString &	GetSrcFile		(void) const { return m_strSrcFile; }
	inline const CString &	GetSrcDir		(void) const { return m_strSrcDir; }
	inline const CString &	GetDestDir		(void) const { return m_strDestDir; }
	inline const CString &	GetDestFile		(void) const { return m_strDestFile; }

public:
	inline void	SetProjectID	(const long				iProjId)	{ m_iProjectID		= iProjId; }
	inline void	SetProjectStep	(const long				iStep)		{ m_iProjectStep	= iStep; }
	inline void	SetStepType		(const ePFA_STEP_TYPE	eSet)		{ m_eStepType		= eSet; }

	inline void SetSrcFile		(const CString & str)				{ m_strSrcFile		= str; }
	inline void SetSrcDir		(const CString & str)				{ m_strSrcDir		= str; }
	inline void SetDestDir		(const CString & str)				{ m_strDestDir		= str; }
	inline void SetDestFile		(const CString & str)				{ m_strDestFile		= str; }

private:
	long			m_iProjectID;
	long			m_iProjectStep;
	ePFA_STEP_TYPE	m_eStepType;
	CString			m_strSrcFile;
	CString			m_strSrcDir;
	CString			m_strDestDir;
	CString			m_strDestFile;
};

#endif // !defined(AFX_PFASTEP_H__90E07E34_DD11_4C0B_8491_9D5494251FBD__INCLUDED_)
