// PfaDataListItem.h: interface for the CPfaDataListItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PFADATALISTITEM_H__AC4BDF1C_7929_4A54_913C_A34B4926F7DD__INCLUDED_)
#define AFX_PFADATALISTITEM_H__AC4BDF1C_7929_4A54_913C_A34B4926F7DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XLateFieldText.h"
#include "FileCopyReport.h"

class CPfaDataListItem  
:	public CXLateFieldText
{
public:
	CPfaDataListItem(const CComPtr<ADODB::Fields> & spFields);
	CPfaDataListItem(const CFileCopyReport & report);
	CPfaDataListItem(const CPfaDataListItem & src){ *this = src; }

	virtual ~CPfaDataListItem();

public:
	const CPfaDataListItem & operator = (const CPfaDataListItem & src);

public:
	int Compare(const CPfaDataListItem & that, const int iListColumn, const int iColFormat) const;

public:
	inline const CString &	GetProjectName		(void) const { return m_strProjectName; }
	inline const CString &	GetStepTypeStr		(void) const { return m_strStepType; }
	inline const CString &	GetStepNumStr		(void) const { return m_strStepNum; }
	inline const CString &	GetSubStepNumStr	(void) const { return m_strSubStepNum; }
	inline const CString &	GetSourceFile		(void) const { return m_strSourceFile; }
	inline const CString &	GetSourceDir		(void) const { return m_strSourceDir; }
	inline const CString &	GetDestDirectory	(void) const { return m_strDestDirectory; }
	inline const CString &	GetDestFile			(void) const { return m_strDestFile; }
	inline const CString &	GetCreated			(void) const { return m_strCreated; }
	inline const CString &	GetModified			(void) const { return m_strModified; }

	inline eSTEP_STATUS		GetStepStatus		(void) const { return m_eStepStatus; }

	inline long GetProjectID	(void) const { return m_iProjectID; }
	inline long GetStepNum		(void) const { return m_iStepNum; }
	inline long GetSubStepNum	(void) const { return m_iSubStepNum; }
	inline long GetStepType		(void) const { return m_iStepType; }
	inline bool HasUnreadStatus	(void) const { return m_bUnreadStatus; }


	//if m_bUnreadStatus is true, then the list will refresh the status text
	//during the next NMCUSTOMDRAW message
	inline void SetUnreadStatus		(const bool bUnread)	{ m_bUnreadStatus				= bUnread; }

public:
	inline void SetStepType			(const int iType)		{ m_iStepType					= iType; }
	inline void	SetSourceFile		(const CString & str)	{ m_strSourceFile				= str; }
	inline void	SetSourceDir		(const CString & str)	{ m_strSourceDir				= str; }
	inline void	SetDestDirectory	(const CString & str)	{ m_strDestDirectory			= str; }
	inline void	SetDestFile			(const CString & str)	{ m_strDestFile					= str; }
	inline void	SetValidationFail	(const CString & str)	{ m_strValidationFailedReason	= str; }

public:
	CString GetItemText(const long iListColumn) const;
	bool IsActionable(void) const;

public:
	void		GetStepColouring	(const int iColumn, COLORREF & crefFG, COLORREF & crefBG) const;
	CString		GetStepStatusStr	(void) const;
	void		SetStepStatus		(const eSTEP_STATUS eStepStatus);

public:
	CString	GetCSVFileText(void);

public:
	bool Succeeded(void) const;

private:
	long			m_iProjectID;
	long			m_iOpNum;
	long			m_iStepNum;
	long			m_iSubStepNum;
	long			m_iStepType;
	CString			m_strProjectName;
	CString			m_strStepType;
	CString			m_strStepNum;
	CString			m_strSubStepNum;
	CString			m_strSourceFile;
	CString			m_strSourceDir;
	CString			m_strDestDirectory;
	CString			m_strDestFile;	
	CString			m_strValidationFailedReason;
	CString			m_strCreated;
	CString			m_strModified;
	eSTEP_STATUS	m_eStepStatus;

private:
	bool m_bUnreadStatus;
};

#endif // !defined(AFX_PFADATALISTITEM_H__AC4BDF1C_7929_4A54_913C_A34B4926F7DD__INCLUDED_)
