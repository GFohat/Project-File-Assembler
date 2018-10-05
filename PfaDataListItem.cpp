// PfaDataListItem.cpp: implementation of the CPfaDataListItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "PfaDataListItem.h"

#include "ConstSQL.h"
using namespace CONS_SQL;

#include "ConstLists.h"
using namespace CONS_LISTS;

#include "ConstStepTypes.h"
using namespace CONS_STEP_TYPES;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPfaDataListItem::CPfaDataListItem(const CComPtr<ADODB::Fields> & spFields)
:	m_eStepStatus		(ePStatus_None)
	, m_bUnreadStatus	(true)
	, m_iSubStepNum		(0L)
{
#pragma message ("This looks horrible - find a better way")

	HRESULT hr = S_OK;

	try{
		ExtractFieldValue	(spFields, eSFld_szProjectName,		m_strProjectName);
		ExtractFieldValue	(spFields, eSFld_iProjectID,		m_iProjectID);
		ExtractFieldValue	(spFields, eSFld_iStep,				m_iStepNum);
		ExtractFieldValue	(spFields, eSFld_iStep,				m_iOpNum);
		ExtractFieldValue	(spFields, eSFld_iStepType,			m_iStepType);
		ExtractFieldValue	(spFields, eSFld_szStepType,		m_strStepType);
		ExtractFieldValue	(spFields, eSFld_SourceFile,		m_strSourceFile);
		ExtractFieldValue	(spFields, eSFld_SourceDir,			m_strSourceDir);
		ExtractFieldValue	(spFields, eSFld_DestDirectory,		m_strDestDirectory);
		ExtractFieldValue	(spFields, eSFld_DestFile,			m_strDestFile);
		ExtractFieldValue	(spFields, eSFld_Created,			m_strCreated);
		ExtractFieldValue	(spFields, eSFld_Modified,			m_strModified);

		m_strStepNum	.Format(_T("%i"), m_iStepNum);
		m_strSubStepNum	.Format(_T("%i"), m_iSubStepNum);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
	}
}
	
CPfaDataListItem::CPfaDataListItem(const CFileCopyReport & report)
:	m_bUnreadStatus	(true)
{
	m_iProjectID		= -1L;
	m_iOpNum			= report.GetOpNumber();
	m_iStepNum			= report.GetStepNumber();
	m_iSubStepNum		= report.GetSubStep();
	m_iStepType			= ePST_Comment;
	m_strProjectName	= _T("");
	m_strStepType		= _T("CFileCopyReport");
	m_strSourceFile		= report.GetFile();
	m_strSourceDir		= report.GetSource();
	m_strDestDirectory	= report.GetDestination();
	m_strDestFile		= report.GetCopiedName();	
	m_eStepStatus		= eSTEP_STATUS(report.GetStatus());

	m_strStepNum	.Format(_T("%i"), m_iStepNum);
	m_strSubStepNum	.Format(_T("%i"), m_iSubStepNum);
}

CPfaDataListItem::~CPfaDataListItem()
{

}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 08:38:11
	DESCRIP:	
	IN:
	OUT:
*/
const CPfaDataListItem & CPfaDataListItem::operator = (const CPfaDataListItem & src)
{
#pragma message ("CPfaDataListItem::operator =")

	m_bUnreadStatus					= src.m_bUnreadStatus;
	m_eStepStatus					= src.m_eStepStatus;
	m_iProjectID					= src.m_iProjectID;
	m_iOpNum						= src.m_iOpNum;
	m_iStepNum						= src.m_iStepNum;
	m_iSubStepNum					= src.m_iSubStepNum;
	m_iStepType						= src.m_iStepType;
	m_strDestDirectory				= src.m_strDestDirectory;
	m_strDestFile					= src.m_strDestFile;	
	m_strProjectName				= src.m_strProjectName;
	m_strSourceDir					= src.m_strSourceDir;
	m_strSourceFile					= src.m_strSourceFile;
	m_strStepNum					= src.m_strStepNum;
	m_strSubStepNum					= src.m_strSubStepNum;
	m_strStepType					= src.m_strStepType;
	m_strCreated					= src.m_strCreated;
	m_strModified					= src.m_strModified;
	m_strValidationFailedReason		= src.m_strValidationFailedReason;

	return * this;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	26/04/2007 12:38:21
	DESCRIP:	
	IN:
	OUT:
		int as if from _tcsicmp();
		Return Value	Description 
		< 0				this less than that 
		0				this identical to that 
		> 0				this greater than that 
*/
int CPfaDataListItem::Compare(const CPfaDataListItem & that, const int iListColumn, const int iColFormat) const
{
	int iCmp = 0;

	switch(iListColumn){
		case ePDataCol_StepNum:
		case ePDataCol_SubStepNum:		

			if(m_iStepNum > that.m_iStepNum)
				iCmp = 1;
			else if(m_iStepNum < that.m_iStepNum)
				iCmp = -1;

			//if steps are the same, compare substep
			else{
				if(m_iSubStepNum > that.m_iSubStepNum)
					iCmp = 1;
				else if(m_iSubStepNum < that.m_iSubStepNum)
					iCmp = -1;
			}

			break;

		case ePDataCol_StepType:	
		case ePDataCol_Status:		
		case ePDataCol_File:		
		case ePDataCol_Source:		
		case ePDataCol_Destination:	
		case ePDataCol_CopiedName:	
		case ePDataCol_Created:	
		case ePDataCol_Modified:	
			{
				CString strThis = GetItemText(iListColumn);
				CString strThat = that.GetItemText(iListColumn);

				iCmp = _tcsicmp(strThis, strThat);
			}
			break;

		default:
			ATLASSERT(false);
	}

	return iCmp;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/04/2007 09:32:25
	DESCRIP:	
	IN:
	OUT:
*/
bool CPfaDataListItem::IsActionable(void) const
{
	return (m_iStepNum >= iMINSTEPVAL) && (m_iSubStepNum == 0L);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 07:21:12
	DESCRIP:	
	IN:
	OUT:
*/
CString CPfaDataListItem::GetStepStatusStr(void) const
{
	CString strRet(_T("<null>"));

	ATLASSERT(m_eStepStatus >= 0 && m_eStepStatus < ePStatus__LAST);

	if(m_eStepStatus >= 0 && m_eStepStatus < ePStatus__LAST)
		strRet = szsSTATUS_NAMES_PFA[m_eStepStatus];

	if(ePStatus_ValidatedBad == m_eStepStatus)
		strRet = m_strValidationFailedReason;
	
	return strRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 07:21:10
	DESCRIP:	
	IN:
	OUT:
*/
void CPfaDataListItem::SetStepStatus(const eSTEP_STATUS eStepStatus)
{
	m_bUnreadStatus = true;

	ATLASSERT(eStepStatus >= 0 && eStepStatus < ePStatus__LAST);

	if(eStepStatus >= 0 && eStepStatus < ePStatus__LAST)
		m_eStepStatus = eStepStatus;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/03/2007 07:25:16
	DESCRIP:	
		
		Get colouring based on type of step, then modify according to status

	IN:
	OUT:
*/
void CPfaDataListItem::GetStepColouring(const int iColumn, COLORREF & crefFG, COLORREF & crefBG) const
{
	ATLASSERT(m_iStepType >= 0 && m_iStepType < ePST__LAST);

	if(m_iStepType >= 0 && m_iStepType < ePST__LAST){
		crefFG = crefsLINE_FORE_OLEDB[m_iStepType];
		crefBG = crefsLINE_BACK_OLEDB[m_iStepType];
	}

	ATLASSERT(m_eStepStatus >= 0 && m_eStepStatus < ePStatus__LAST);

	if(ePDataCol_Status == iColumn){
		if(m_eStepStatus >= 0 && m_eStepStatus < ePStatus__LAST){

			switch(eStatusTypes[m_eStepStatus]){
				//no changes...
				case eSST_Information:		
					//crefBG = crefCOMMENT_BACK;	
					//crefFG = crefCOMMENT_FORE;
					//break;

				//success...
				case eSST_Success:
					crefBG = crefSUCCESS_BACK;
					crefFG = crefSUCCESS_FORE;
					break;

				case eSST_Active:
					crefBG = crefACTIVE_BACK;
					crefFG = crefACTIVE_FORE;
					break;

				//failure...
				case eSST_Failure:
					crefBG = crefERROR_BACK;
					crefFG = crefERROR_FORE;
					break;

				default:
					ATLASSERT(false);
					break;
			}

		}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 10:59:06
	DESCRIP:	
	IN:
	OUT:
*/
CString CPfaDataListItem::GetItemText(const long iListColumn) const
{
	CString strRet;

	switch(iListColumn){
		case ePDataCol_StepNum:			strRet = GetStepNumStr();		break;
		case ePDataCol_SubStepNum:		strRet = GetSubStepNumStr();	break;
		case ePDataCol_StepType:		strRet = GetStepTypeStr();		break;
		case ePDataCol_Status:			strRet = GetStepStatusStr();	break;
		case ePDataCol_File:			strRet = GetSourceFile();		break;
		case ePDataCol_Source:			strRet = GetSourceDir();		break;
		case ePDataCol_Destination:		strRet = GetDestDirectory();	break;
		case ePDataCol_CopiedName:		strRet = GetDestFile();			break;
		case ePDataCol_Created:			strRet = GetCreated();			break;
		case ePDataCol_Modified:		strRet = GetModified();			break;

		default:
			ATLASSERT(false);
	}

	return strRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	18/04/2007 08:35:59
	DESCRIP:	
	IN:
	OUT:
*/
CString	CPfaDataListItem::GetCSVFileText(void)
{
	CString strText;

	for(long iLoop = 0 ; iLoop < ePDataCol__LAST ; iLoop++){
		strText += GetItemText(iLoop);
		strText += _T(',');
	}

	strText.TrimRight(_T(','));

	return strText;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	15/05/2007 07:21:08
	DESCRIP:	
	IN:
	OUT:
*/
bool CPfaDataListItem::Succeeded(void) const
{
	bool bSuccess = false;

	switch(m_eStepStatus){
		case ePStatus_None:
		case ePStatus_Copying:
		case ePStatus_IncompleteLine:
		case ePStatus_DirCreationOnly:
		case ePStatus_SourceNonExistent:
		case ePStatus_DirCreationFailed:
		case ePStatus_DirBeingEmptied:
		case ePStatus_DirEmptiedFail:
		case ePStatus_FileDeleteFailed:
		case ePStatus_CopyFileFailed:
		case ePStatus_UserCancelled:
		case ePStatus_CopyFile:
		case ePStatus_DirIncSubDirs:
		case ePStatus_Validation:
		case ePStatus_Validating:
		case ePStatus_ValidatedBad:
			bSuccess = false;
			break;

		case ePStatus_DirEmptyCancelled:	//<-- success, since we always do this
		case ePStatus_DirCreationOK:
		case ePStatus_DirCopyOK:
		case ePStatus_DirEmptiedOK:
		case ePStatus_IgnoredLine:
		case ePStatus_FileDeleteOK:
		case ePStatus_CopyFileOK:
		case ePStatus_ValidatedOK:
			bSuccess = true;
			break;

		default:
			ATLASSERT(false);
			ATLTRACE(_T("New unhandled status enum\n"));
			break;
	}

	return bSuccess;
}
