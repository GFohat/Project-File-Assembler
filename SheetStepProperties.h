#if !defined(AFX_SHEETSTEPPROPERTIES_H__E20EF865_88C7_4CC3_8C16_4F01987E166C__INCLUDED_)
#define AFX_SHEETSTEPPROPERTIES_H__E20EF865_88C7_4CC3_8C16_4F01987E166C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SheetStepProperties.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CSheetStepProperties
#include "PageStepType.h"
#include "PageStepDetails.h"

#include "PfaDataListItem.h"
#include "ControlPopulator.h"

#include "PropSheetCommon.h"

class CSheetStepProperties 
:	public CPropertySheet
	, public CDataHandler
	, public CPropSheetCommon
{
	DECLARE_DYNAMIC(CSheetStepProperties)

// Construction
public:
	CSheetStepProperties(
						const CPfaDataListItem &	rData
						, const CString &			strDfltSrc
						, const CString &			strDfltDest
						, LPCTSTR					pszCaption
						, CWnd*						pParentWnd		= NULL
						, UINT						iSelectPage		= 0
					);

// Attributes
public:
	inline const CPfaDataListItem &		GetCurData		(void) const	{ return m_data; }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSheetStepProperties)
	public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSheetStepProperties();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSheetStepProperties)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void AddAllPages(void);

	//CPageStepType		m_pageStepType;
	CPageStepDetails	m_pageStepDetails;

private:
	CPfaDataListItem m_data;

public:
	void SaveData(void);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEETSTEPPROPERTIES_H__E20EF865_88C7_4CC3_8C16_4F01987E166C__INCLUDED_)
