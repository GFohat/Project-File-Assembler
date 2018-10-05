// ComboListItem.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "ComboListItem.h"

#include "ConstLists.h"
using namespace CONS_LISTS;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboListItem

CComboListItem::CComboListItem()
:	m_iItem			(0L)
	, m_iSubItem	(0L)
	, m_iProjectID	(0L)
	, m_iStepNumber	(0L)
{
}

CComboListItem::~CComboListItem()
{
}


BEGIN_MESSAGE_MAP(CComboListItem, CComboBox)
	//{{AFX_MSG_MAP(CComboListItem)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboListItem message handlers

void CComboListItem::ShowWindow(
							int nCmdShow
							, const long iItem
							, const long iSubItem
							, const long iProjectID
							, const long iStepNumber
							, const CRect & rcCell
							, const CString & strText
						)
{
	m_iItem			= iItem;
	m_iSubItem		= iSubItem;
	m_iProjectID	= iProjectID;
	m_iStepNumber	= iStepNumber;

	CComboBox::ShowWindow(nCmdShow);

	SelectString	(-1, strText);
	MoveWindow		(rcCell);
	SetFocus		();
	ShowDropDown	();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 09:29:10
	DESCRIP:	
	IN:
	OUT:
*/
void CComboListItem::HideWindow(void)
{
	m_iItem			= 0L;
	m_iSubItem		= 0L;
	m_iProjectID	= 0L;
	m_iStepNumber	= 0L;

	SetWindowText	(_T(""));

	CComboBox::ShowWindow(SW_HIDE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 08:57:17
	DESCRIP:	
	IN:
	OUT:
*/
CString CComboListItem::GetAssocFieldName(void) const
{
	CString strFldName;

	ATLASSERT(ePDataCol_StepType == m_iSubItem);

	switch(m_iSubItem){

		case ePDataCol_StepType:		strFldName = _T("iStepType");			break;
		case ePDataCol_StepNum:			strFldName = _T("iStep");				break;
		case ePDataCol_File:			strFldName = _T("szSourceFile");		break;
		case ePDataCol_Source:			strFldName = _T("szSourceDir");			break;
		case ePDataCol_Destination:		strFldName = _T("szDestDirectory");		break;
		case ePDataCol_CopiedName:		strFldName = _T("szDestFile");			break;
			
		case ePDataCol_Status:
		default:
			ATLASSERT(false);
			break;
	}

	return strFldName;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 08:57:14
	DESCRIP:	
	IN:
	OUT:
*/
long CComboListItem::GetAssocSQLValue(void) const
{
	long iRet = -1L;

	ATLASSERT(ePDataCol_StepType == m_iSubItem);

	if(ePDataCol_StepType == m_iSubItem){
		int iSel = GetCurSel();
		iRet = GetItemData(iSel);
	}

	return iRet;
}
