// EditListItem.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "EditListItem.h"

#include "ConstLists.h"
using namespace CONS_LISTS;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditListItem

CEditListItem::CEditListItem()
:	m_iItem			(0L)
	, m_iSubItem	(0L)
	, m_iProjectID	(0L)
	, m_iStepNumber	(0L)
{
}

CEditListItem::~CEditListItem()
{
}


BEGIN_MESSAGE_MAP(CEditListItem, CRichEditCtrl)
	//{{AFX_MSG_MAP(CEditListItem)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditListItem message handlers
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 08:25:42
	DESCRIP:	
	IN:
	OUT:
*/
void CEditListItem::ShowWindow(
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

	SetWindowText	(strText);

	//04/05/2007 15:30:45
	//so we can look for any changes 
	m_strOriginalText = strText;
	
	//SetSel			(strText.GetLength(), strText.GetLength());
	SetSel(0, -1);

	MoveWindow		(rcCell);
	CRichEditCtrl::ShowWindow(nCmdShow);

	SetFocus();
	SetActiveWindow();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 09:29:10
	DESCRIP:	
	IN:
	OUT:
*/
void CEditListItem::HideWindow(void)
{
	m_iItem			= 0L;
	m_iSubItem		= 0L;
	m_iProjectID	= 0L;
	m_iStepNumber	= 0L;

	SetWindowText	(_T(""));

	CRichEditCtrl::ShowWindow(SW_HIDE);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	04/05/2007 15:34:00
	DESCRIP:	
	IN:
	OUT:
*/
bool CEditListItem::HasChanges(void) const
{
	CString strNew;
	GetWindowText(strNew);

	int iCompare = strNew.Compare(m_strOriginalText);

	return (iCompare ? true : false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 08:57:17
	DESCRIP:	
	IN:
	OUT:
*/
CString CEditListItem::GetAssocFieldName(void) const
{
	CString strFldName;

	switch(m_iSubItem){

		case ePDataCol_StepType:		strFldName = _T("iStepType");			break;
		case ePDataCol_StepNum:			strFldName = _T("iStep");				break;
		case ePDataCol_File:			strFldName = _T("szSourceFile");		break;
		case ePDataCol_Source:			strFldName = _T("szSourceDir");			break;
		case ePDataCol_Destination:		strFldName = _T("szDestDirectory");		break;
		case ePDataCol_CopiedName:		strFldName = _T("szDestFile");			break;
		case ePDataCol_Created:			strFldName = _T("szCreated");			break;
			
		case ePDataCol_Modified:	//can't change 'modified'
		case ePDataCol_Status:		//status not in database!
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
CString CEditListItem::GetAssocSQLValue(void) const
{
	CString strSQLPhrase;

	CString strText;
	GetWindowText(strText);

	switch(m_iSubItem){

		//numerical fields go 'as is'
		case ePDataCol_StepType:
		case ePDataCol_StepNum:			
			strSQLPhrase = strText;	
			break;

		//text fields need wrapping in single quotes
		//2007-05-18 - now they don't!
		case ePDataCol_File:			
		case ePDataCol_Source:			
		case ePDataCol_Destination:		
		case ePDataCol_CopiedName:		
		case ePDataCol_Created:		
			//strSQLPhrase.Format(_T("'%s'"), strText);	
			strSQLPhrase = strText;	
			break;

		//this shouldn't get here!
		case ePDataCol_Modified:		
		case ePDataCol_Status:
		default:
			ATLASSERT(false);
			break;
	}

	return strSQLPhrase;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 12:30:14
	DESCRIP:	
	IN:
	OUT:
*/
//void CEditListItem::OnContextMenu(CWnd* pWnd, CPoint point) 
//{
//	ATLTRACE(_T("CEditListItem::OnContextMenu\n"));
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 12:34:48
	DESCRIP:	
	IN:
	OUT:
*/
//void CEditListItem::OnRButtonUp(UINT nFlags, CPoint point) 
//{
//	ATLTRACE(_T("CEditListItem::OnContextMenu\n"));
//	
//	CRichEditCtrl::OnRButtonUp(nFlags, point);
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/05/2007 07:10:25
	DESCRIP:	
	IN:
	OUT:
*/
void CEditListItem::OnChange() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CRichEditCtrl::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	ATLTRACE(_T("CEditListItem::OnChange\n"));
}
