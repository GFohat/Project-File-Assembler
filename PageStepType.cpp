// PageStepType.cpp : implementation file
//

#include "stdafx.h"
#include "project file assembler.h"
#include "PageStepType.h"

#include "SheetStepProperties.h"

#include "ConstSQL.h"
using namespace CONS_SQL;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageStepType dialog


CPageStepType::CPageStepType(CWnd* pParent /*=NULL*/)
:	CPropertyPage(CPageStepType::IDD)
{
	//{{AFX_DATA_INIT(CPageStepType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPageStepType::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageStepType)
	DDX_Control(pDX, IDC_CMBO_STEP_TYPE, m_cmboStepType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageStepType, CPropertyPage)
	//{{AFX_MSG_MAP(CPageStepType)
	ON_CBN_SELCHANGE(IDC_CMBO_STEP_TYPE, OnSelchangeCmboStepType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageStepType message handlers

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 13:20:14
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageStepType::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	RefreshCombo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 13:20:11
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageStepType::OnSetActive() 
{
	return CPropertyPage::OnSetActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 13:20:09
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageStepType::OnKillActive() 
{
	return CPropertyPage::OnKillActive();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 13:33:29
	DESCRIP:	
	IN:
	OUT:
*/
CSheetStepProperties * CPageStepType::GetMainSheet(void)
{
	CSheetStepProperties * pSheet = reinterpret_cast<CSheetStepProperties *>(GetParent());
	ATLASSERT(pSheet && ::IsWindow(pSheet->m_hWnd));
	return pSheet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 08:01:43
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepType::RefreshCombo(void)
{
	m_cmboStepType.ResetContent();

	GetMainSheet()->PopulateComboBox(
									szSQL_STEPTYPE_COMBO
									, szFIELD_STEPTYPE_STRINGS
									, szFIELD_STEPTYPE_IDS
									, m_cmboStepType
								);

	int iStepType = GetMainSheet()->GetCurData().GetStepType();

	const int iMAX = m_cmboStepType.GetCount();
	bool bFound = false;
	int iTest = 0;

	//looking for the item who's data matches the current step type
	for(int iItem = 0 ; iItem < iMAX && !bFound ; iItem++){
		iTest = m_cmboStepType.GetItemData(iItem);

		if(iTest == iStepType){
			bFound = true;
			m_cmboStepType.SetCurSel(iItem);
		}
	}

	ATLASSERT(bFound);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 08:49:12
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepType::SetAppearance(void)
{
	m_cmboStepType.SetFont(GetMainSheet()->GetTheFont(eFont_Combo));
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 09:20:32
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepType::PageToData(CPfaDataListItem & rItem) const
{
//	int iCurSel = m_cmboStepType.GetCurSel();
//
//	if(iCurSel >= 0){
//		int iStepType = m_cmboStepType.GetItemData(iCurSel);
//		rItem.SetStepType(iStepType);
//	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 09:32:36
	DESCRIP:	
	IN:
	OUT:
*/
BOOL CPageStepType::OnApply() 
{
	GetMainSheet()->SaveData();
	
	return CPropertyPage::OnApply();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 09:32:38
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepType::OnOK() 
{
	GetMainSheet()->SaveData();
	
	CPropertyPage::OnOK();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 09:46:03
	DESCRIP:	
	IN:
	OUT:
*/
void CPageStepType::OnSelchangeCmboStepType() 
{
	SetModified(TRUE);	
}
