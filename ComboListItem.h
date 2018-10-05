#if !defined(AFX_COMBOLISTITEM_H__AD281BC5_1B41_4EBD_9839_9ACEBFCAD44D__INCLUDED_)
#define AFX_COMBOLISTITEM_H__AD281BC5_1B41_4EBD_9839_9ACEBFCAD44D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboListItem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComboListItem window

class CComboListItem : public CComboBox
{
// Construction
public:
	CComboListItem();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboListItem)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComboListItem();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboListItem)
		// NOTE - the ClassWizard will add and remove member functions here.
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

public:
	inline long GetItem			(void) const { return m_iItem; }
	inline long GetSubItem		(void) const { return m_iSubItem; }
	inline long GetProjectID	(void) const { return m_iProjectID; }
	inline long GetStepNumber	(void) const { return m_iStepNumber; }

//public:
//	inline void SetStepNumber	(const long iStepNumber) { m_iStepNumber = iStepNumber; } 

public:
	CString GetAssocFieldName	(void) const;
	long	GetAssocSQLValue	(void) const;

private:
	long m_iItem;
	long m_iSubItem;
	long m_iProjectID;
	long m_iStepNumber;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOLISTITEM_H__AD281BC5_1B41_4EBD_9839_9ACEBFCAD44D__INCLUDED_)
