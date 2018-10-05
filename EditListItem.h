#if !defined(AFX_EDITLISTITEM_H__462D21A4_C742_4C86_A116_C22C1B117875__INCLUDED_)
#define AFX_EDITLISTITEM_H__462D21A4_C742_4C86_A116_C22C1B117875__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditListItem.h : header file
//

#include "PfaDataListItem.h"

/////////////////////////////////////////////////////////////////////////////
// CEditListItem window

class CEditListItem : public CRichEditCtrl
{
// Construction
public:
	CEditListItem();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditListItem)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditListItem();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditListItem)
	afx_msg void OnChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	void ShowWindow(
					int nCmdShow
					, const long iItem
					, const long iSubItem
					, const long iProjectID
					, const long iStepNumber
					, const CRect & rcCell
					, const CString & strText
				);

	void HideWindow(void);

	bool HasChanges(void) const;

public:
	inline long GetItem			(void) const { return m_iItem; }
	inline long GetSubItem		(void) const { return m_iSubItem; }
	inline long GetProjectID	(void) const { return m_iProjectID; }
	inline long GetStepNumber	(void) const { return m_iStepNumber; }

public:
	inline void SetStepNumber	(const long iStepNumber) { m_iStepNumber = iStepNumber; } 

public:
	CString GetAssocFieldName(void) const;
	CString GetAssocSQLValue(void) const;

private:
	long m_iItem;
	long m_iSubItem;
	long m_iProjectID;
	long m_iStepNumber;
	CString m_strOriginalText;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLISTITEM_H__462D21A4_C742_4C86_A116_C22C1B117875__INCLUDED_)
