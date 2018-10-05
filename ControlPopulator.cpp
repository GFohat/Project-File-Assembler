// ControlPopulator.cpp: implementation of the CDataHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "ControlPopulator.h"

#include "CSafe.h"

#include "ConstLists.h"
using namespace CONS_LISTS;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataHandler::CDataHandler()
:	m_spConnection	(0)
{

}

CDataHandler::~CDataHandler()
{
	DisconnectDb();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	02/04/2007 14:02:59
	DESCRIP:	
	IN:
	OUT:
*/
CString CDataHandler::SQLValue(const CString & strFieldValue) const
{
	CString strRet(strFieldValue);

	strRet.Replace(_T("'"), _T("''"));

	return strRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 14:46:35
	DESCRIP:	
	IN:
	OUT:
*/
CString CDataHandler::GetDateTimeString(void) const
{
	COleDateTime dtNow = COleDateTime::GetCurrentTime();

	CString strNow;
	strNow.Format(
				_T("%04i-%02i-%02i %02i:%02i:%02i")
				, dtNow.GetYear(), dtNow.GetMonth(), dtNow.GetDay()
				, dtNow.GetHour(), dtNow.GetMinute(), dtNow.GetSecond()
			);

	return strNow;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/03/2007 15:13:43
	DESCRIP:	
	IN:
	OUT:
*/
CString CDataHandler::GetConnString(void) const
{
	//const static TCHAR szCONN[] = _T("File Name=C:\\Program Files\\Common Files\\System\\Ole DB\\Data Links\\Project File Assembler.udl");

	CString strRet;
	strRet.Format(
				_T("File Name=%s")
				, szUDL
			);

	return strRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 07:35:15
	DESCRIP:	
	IN:
	OUT:
*/
//CString CDataHandler::GetUDLFile(void) const
//{
//
//	return szUDL;
//}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/03/2007 14:14:16
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::ConnectDb(void)
{
	HRESULT hr = S_OK;

	DisconnectDb();

	CString strConn = GetConnString();

	try{
		THR( hr = m_spConnection.CoCreateInstance(ADODB::CLSID_Connection) );
		THR( hr = m_spConnection->Open(strConn.AllocSysString(), L"", L"", 0) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::ConnectDb"), strConn, _T(""), false);	//Don't log - will fail
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/03/2007 14:14:19
	DESCRIP:	
	IN:
	OUT:
*/
void CDataHandler::DisconnectDb(void)
{
	if(m_spConnection){
		
		//MUST check state!
		if(ADODB::adStateClosed != m_spConnection->State)
			m_spConnection->Close();

		m_spConnection = 0;
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	03/05/2007 07:37:38
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::ReadDataSourceProps(CListCtrl & rList)
{
	using namespace CONS_DS_PROPS::PROPERTY_ORDINALS;

	HRESULT hr = S_OK;

	CString strUDL(szUDL);
	CDataSource db;

	int iCur = 0;
	int iNew = 0;

	try{
		THR( hr = db.OpenFromFileName(strUDL.AllocSysString()) );
		
		CDataSourceInfoHolder::SetPropertyValues(db);

		rList.DeleteAllItems();

		for(DWORD dwRow = 0L ; dwRow < iPO__LAST ; dwRow ++){
			iCur = rList.GetItemCount();

			iNew = rList.InsertItem(iCur, _T(""));

			rList.SetItemText(iNew, eDPCol_Name, szPROPERTY_NAMES[dwRow]);
			rList.SetItemText(iNew, eDPCol_Value, CDataSourceInfoHolder::GetPropertyValue(dwRow));

			rList.SetItemData(iNew, iNew);
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::ReadDataSourceProps"), strUDL, _T(""), true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 10:58:41
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::ReconnectDb(void)
{
	return ConnectDb();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	29/03/2007 11:55:30
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::CountRecords(
									const CString & strSQL
									, long & iCount
								)
{
	HRESULT hr = S_OK;

	CComPtr<ADODB::_Recordset>	spRst			= 0;

	try{
		THR( hr = OpenRecordSet(strSQL, true, spRst) );

		if( ! spRst->BOF && ! spRst->EndOfFile){
			THR( hr = spRst->MoveLast() );
			THR( hr = spRst->MoveFirst() );
		}

		iCount = long(spRst->RecordCount);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::CountRecords"), _T(""), strSQL, true);
	}

	return hr;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	05/02/2007 15:30:32
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::OpenRecordSet(
								const CString & strSQL
								, const bool bReadOnly
								, CComPtr<ADODB::_Recordset> & spRst
							)
{
	HRESULT hr = S_OK;
	ATLASSERT(m_spConnection);

	if(!m_spConnection)
		return E_POINTER;

	try{
		if(!spRst)
			THR( hr = spRst.CoCreateInstance(ADODB::CLSID_Recordset) );

		ADODB::CursorTypeEnum	eCursor	= bReadOnly ? ADODB::adOpenStatic	: ADODB::adOpenKeyset;
		ADODB::LockTypeEnum		eLock	= bReadOnly ? ADODB::adLockReadOnly	: ADODB::adLockOptimistic;

		THR( hr = spRst->Open(
							CComVariant(strSQL)
							, CComVariant(m_spConnection)
							, eCursor					//CursorType
							, eLock						//LockType
							, ADODB::adCmdText			//options
						) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::OpenRecordSet"), _T(""), strSQL, true);
	}

	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 15:28:56
	DESCRIP:	
	IN:
	OUT:
*/
// HRESULT CDataHandler::OpenRecordSetWrite(const CString & strSQL, CComPtr<ADODB::_Recordset> & spRst)
// {
// #pragma message ("MERGE WITH OpenRecordSet")
// 
// 	HRESULT hr = S_OK;
// 	ATLASSERT(m_spConnection);
// 
// 	if(!m_spConnection)
// 		return E_POINTER;
// 
// 	try{
// 		if(!spRst)
// 			THR( hr = spRst.CoCreateInstance(ADODB::CLSID_Recordset) );
// 
// 		THR( hr = spRst->Open(
// 							CComVariant(strSQL)
// 							, CComVariant(m_spConnection)
// 							, ADODB::adOpenKeyset			//CursorType
// 							, ADODB::adLockOptimistic		//LockType
// 							, ADODB::adCmdText				//options
// 						) );
// 	}
// 	//----------------------------------------------------------
// 	catch(_com_error & e){
// 		hr = e.Error();
// 		HandleHR(e, _T("CDataHandler::OpenRecordSet"), _T(""), strSQL, true);
// 	}
// 
// 	return hr;
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	19/03/2007 18:37:15
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::ExecSQL(
							const CString & strSQL
							, const CString & strSource
							, long * piRecsAffected
						)
{
	HRESULT hr = S_OK;

	CComPtr<ADODB::_Command> spCmd = 0;

	try{
		THR( hr = spCmd.CoCreateInstance(ADODB::CLSID_Command) );

		spCmd->ActiveConnection		= m_spConnection;
		spCmd->CommandText			= strSQL.AllocSysString();
		spCmd->CommandType			= ADODB::adCmdText;

		CComVariant varRecsAffected	(long(0L));
		CComVariant varParameters	(vtMissing);

		spCmd->Execute(&varRecsAffected, &varParameters, ADODB::adCmdText);
		LogDataEvent(
				eEvt_Information
				, strSource + _T(" (CDataHandler::ExecSQL)")
				, strSQL
				, _T("%i records affected")
				, varRecsAffected.lVal
			);
		
		ATLTRACE(_T("ExecSQL: %i recs affected\n"), varRecsAffected.lVal);

		if(piRecsAffected)
			*piRecsAffected = varRecsAffected.lVal;
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::ExecSQL"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 07:45:30
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::InsertNewProject(	
										const CString & strProjectName
										, const CString & strDfltSrcDir
										, const CString & strDfltDestDir
									)
{
	HRESULT hr = S_OK;

	CString strSQL;
	
	strSQL.Format(
				_T(" INSERT INTO tblProjects(szProjectName, szDefaultSourceDir, szDefaultDestDir) ")
				_T(" VALUES ('%s', '%s', '%s') ")
				, SQLValue(strProjectName)
				, SQLValue(strDfltSrcDir)
				, SQLValue(strDfltDestDir)
			);

	long iRecs = 0L;

	try{
		THR( hr = ExecSQL(strSQL, _T("CDataHandler::InsertNewProject"), &iRecs) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::InsertNewProject"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 14:20:33
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::CopyExistingProject(
											const long iExistProjID
											, const CString & strNewName
										)
{
	HRESULT hr = S_OK;

	CString strSQL;

	strSQL.Format(_T("SELECT iProjectID FROM tblProjects WHERE szProjectName = '%s' "), SQLValue(strNewName));

	long iNewProjID = 0L;

	try{
		//copy the project entry in tblProjects
		THR( hr = CopyProjectTableEntry	(iExistProjID, strNewName, iNewProjID) );

		//look up the new project's ID
		THR( hr = LookupNumber			(strSQL, -1L, iNewProjID) );

		//copy records in tblProjectAssemblySteps from iExistProjID to iNewProjID
		THR( hr = CopyProjectAssemblySteps(iExistProjID, iNewProjID) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::CopyExistingProject"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 14:56:25
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::CopyProjectAssemblySteps(
												const long iExistProjID
												, const long iNewProjID
											)
{
	HRESULT hr = S_OK;

	CString strSQL;

	strSQL.Format(
				_T(" INSERT INTO tblProjectAssemblySteps ")
				_T(" ( ")
				_T("     iProjectID ")
				_T("     , iStep ")
				_T("     , iStepType ")
				_T("     , szSourceFile ")
				_T("     , szSourceDir ")
				_T("     , szDestDirectory ")
				_T("     , szDestFile ")
				_T("     , szCreated ")
				_T("     , szModified ")
				_T(" ) ")
				_T(" SELECT ")
				_T("     %i ")							//new project ID
				_T("     , iStep ")
				_T("     , iStepType ")
				_T("     , szSourceFile ")
				_T("     , szSourceDir ")
				_T("     , szDestDirectory ")
				_T("     , szDestFile ")
				_T("     , '%s' ")
				_T("     , '%s' ")
				_T(" FROM tblProjectAssemblySteps ")
				_T(" WHERE iProjectID = %i ")			//existing project ID
				, iNewProjID
				, GetDateTimeString()
				, GetDateTimeString()
				, iExistProjID
			);

	long iRecs = 0L;

	try{
		THR( hr = ExecSQL(strSQL, _T("CDataHandler::CopyProjectAssemblySteps"), &iRecs) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::CopyProjectAssemblySteps"), _T(""), strSQL, true);
	}

	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 14:23:18
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::CopyProjectTableEntry(
											const long iExistProjID
											, const CString & strNewName
											, long & iNewProjID
										)
{
	HRESULT hr = S_OK;

	CString strSQL;

	strSQL.Format(
				_T(" INSERT INTO tblProjects ")
				_T("     (szProjectName, szDefaultSourceDir, szDefaultDestDir) ")
				_T(" SELECT '%s', szDefaultSourceDir, szDefaultDestDir ")
				_T(" FROM tblProjects ")
				_T(" WHERE iProjectID = %i ")
				, SQLValue(strNewName)
				, iExistProjID
			);

	long iRecs = 0L;

	try{
		THR( hr = ExecSQL(strSQL, _T("CDataHandler::CopyProjectTableEntry"), &iRecs) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::CopyProjectTableEntry"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 15:05:35
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::DeleteExistingProject(const long iProjectID)
{
	HRESULT hr = E_NOTIMPL;

//	try{
//	}
//	//----------------------------------------------------------
//	catch(_com_error & e){
//		hr = e.Error();
//		ASSERT(false);
//	}

	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 07:51:28
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::SetProjectDirectory(
											const long iProjectID
											, const CString & strDfltDir
											, const bool bIsSrcNotDest
										)
{
	HRESULT hr = S_OK;

	CString strSQL;

	strSQL.Format(
			_T(" UPDATE tblProjects ")
			_T(" SET %s = '%s' ")
			_T(" WHERE iProjectID = %i")
			, bIsSrcNotDest ? _T("szDefaultSourceDir") : _T("szDefaultDestDir")
			, SQLValue(strDfltDir)
			, iProjectID
		);

	long iRecs = 0L;

	try{
		THR( hr = ExecSQL(strSQL, _T("CDataHandler::SetProjectDirectory"), &iRecs) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::SetProjectDirectory"), _T(""), strSQL, true);
	}

	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 15:35:45
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::InsertNewStep(const long iProjectID, const long iInsertStep)
{
	//COleDateTime dtNow = COleDateTime::GetCurrentTime();

	//CString strNow;
	//strNow.Format(
	//			_T("%04i-%02i-%02i %02i:%02i:%02i")
	//			, dtNow.GetYear(), dtNow.GetMonth(), dtNow.GetDay()
	//			, dtNow.GetHour(), dtNow.GetMinute(), dtNow.GetSecond()
	//		);

	return InsertNewStep(
						iProjectID
						, iInsertStep
						, ePST_Comment
						, _T("")
						, _T("")
						, _T("")
						, _T("")
						, true		//create a gap
					);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/04/2007 09:23:26
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::InsertNewStep(
									const long iProjectID
									, const long iInsertStep
									, const ePFA_STEP_TYPE eStepType
									, const CString & strSrcFile
									, const CString & strSrcDir
									, const CString & strDestDir
									, const CString & strDestFile
									, const bool bCreateGap
								)
{
	HRESULT hr = S_OK;

	CString strSQL;

	strSQL.Format(
				_T(" INSERT INTO tblProjectAssemblySteps ")
				_T(" ( ")
				_T("     iProjectID ")
				_T("     , iStep ")
				_T("     , iStepType ")
				_T("     , szSourceFile ")
				_T("     , szSourceDir ")
				_T("     , szDestDirectory ")
				_T("     , szDestFile ")
				_T("     , szCreated ")
				_T("     , szModified ")
				_T(" ) VALUES ( ")
				_T("     %i ")			//project ID
				_T("     , %i ")		//step number (iStep)
				_T("     , %i ")		//step type
				_T("     , '%s' ")		//szSourceFile
				_T("     , '%s' ")		//szSourceDir
				_T("     , '%s' ")		//szDestDirectory
				_T("     , '%s' ")		//szDestFile
				_T("     , '%s' ")		//szCreated
				_T("     , '%s' ")		//szModified
				_T(" ) ")
				, iProjectID	, iInsertStep		, eStepType
				, strSrcFile	, strSrcDir			, strDestDir,		strDestFile
				, GetDateTimeString(), GetDateTimeString()
			);

	bool bIsNewRec = true;
	bool bOverRide = false;

	try{
		THR( hr = IsNewRecord(iProjectID, iInsertStep, eStepType, strSrcFile, strSrcDir, strDestDir, strDestFile, bIsNewRec) );

		if(!bIsNewRec){
			INT_PTR iReply = ::AfxMessageBox(_T("Insert duplicate?"), MB_YESNO);
			bOverRide = (iReply == IDYES);
		}

		if(bIsNewRec || bOverRide){
			
			if(bCreateGap)
				THR( hr = CreateNewStepGap(iProjectID, iInsertStep, 1L) );

			THR( hr = ExecSQL(strSQL, _T("CDataHandler::InsertNewStep"), 0) );
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::InsertNewStep"), _T(""), strSQL, true);
	}

	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/05/2007 18:36:35
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::InsertNewSteps(CPfaStepHolder & stepholder)
{
	HRESULT hr = S_OK;
		
	const long iStartStep = stepholder.GetMinStepNumber	();
	const long iProjectID = stepholder.GetProjectID		();
	const long iNumNewRecs = stepholder.GetStepList().size();

	STEP_LIST::iterator it;
	CPfaStep * pStep = 0;

	//for now, we'll just call InsertNewStep multiple times
	//but create a large 'step gap' before we start
	try{
		THR( hr = CreateNewStepGap(iProjectID, iStartStep, iNumNewRecs) );

		for(it = stepholder.GetStepList().begin() ; it != stepholder.GetStepList().end() ; it ++){
			pStep = * it;
			ATLASSERT(pStep);

			if(pStep){
				THR( hr = InsertNewStep(
										iProjectID
										, pStep->GetProjectStep()
										, pStep->GetStepType()
										, pStep->GetSrcFile()
										, pStep->GetSrcDir()
										, pStep->GetDestDir()
										, pStep->GetDestFile()
										, false						//already created a gap!
									) );
			}
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::InsertNewSteps"), _T(""), _T(""), true);
	}

	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 07:23:44
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::IsNewRecord(
									const long iProjectID
									, const long iInsertStep
									, const ePFA_STEP_TYPE eStepType
									, const CString & strSrcFile
									, const CString & strSrcDir
									, const CString & strDestDir
									, const CString & strDestFile
									, bool & bIsNewRec
								)
{
	HRESULT hr = S_OK;

	CString strSQL;

	strSQL.Format(
				_T(" SELECT iRecID ")
				_T(" FROM tblProjectAssemblySteps ")
				_T(" WHERE iProjectID     = %i ")
				_T(" AND iStepType        <> 0 ")			//ignore comments
				_T(" AND szSourceFile     = '%s' ")
				_T(" AND szSourceDir      = '%s' ")
				_T(" AND szDestDirectory  = '%s' ")
				_T(" AND szDestFile       = '%s' ")
				, iProjectID, strSrcFile, strSrcDir
				, strDestDir, strDestFile
			);

	long iCount = 0L;

	try{
		THR( hr = CountRecords(strSQL, iCount) );

		bIsNewRec = (iCount < 1L);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::IsNewRecord"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 08:32:01
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::CommitEditedCell(CEditListItem & edit)
{
	HRESULT hr = S_OK;

	CString strSQL;

	//if we changed the step number, we may need to move the existing 
	//entry for the new step number, and reordinate after the insertion
	bool bStepRenumber = (ePDataCol_StepNum == edit.GetSubItem());

	try{
		if(bStepRenumber){
			long iNewStep = _ttol(edit.GetAssocSQLValue());
		
			//this creates a gap in the steps at iStep
			//eg if iStep = 4 then the numbering should end up as '1, 2, 3, 5, 6...'
			THR( hr = CreateNewStepGap(edit.GetProjectID(), iNewStep, 1L) );
			ATLTRACE(_T("Added step at %i\n"), iNewStep);

			ReconnectDb();

			//thus the record that 'edit' refers to may itself have been moved!
			if(iNewStep <= edit.GetStepNumber()){
				long iEdStepNum = edit.GetStepNumber() + 1L;
				edit.SetStepNumber(iEdStepNum);
			}
		}

		strSQL.Format(
					_T(" UPDATE tblProjectAssemblySteps ")
					_T(" SET %s = '%s' ")
					_T(" , szModified = '%s' ")
					_T(" WHERE iProjectID = %i ")
					_T(" AND iStep = %i ")
					, edit.GetAssocFieldName()
					, SQLValue(edit.GetAssocSQLValue())		//may contain a ' character?
					, GetDateTimeString()
					, edit.GetProjectID()
					, edit.GetStepNumber()
				);

		THR( hr = ExecSQL(strSQL, _T("CDataHandler::CommitEditedCell(CEditListItem & edit)"), 0) );

		if(bStepRenumber){
			THR( hr = ReOrdinateSteps(edit.GetProjectID()) );
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::CommitEditedCell(CEditListItem & edit)"), _T(""), strSQL, true);
	}

	edit.HideWindow();

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 12:15:18
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::CommitEditedCell(CComboListItem & combo)
{
	HRESULT hr = S_OK;

	//currently only supports 'Step Type'
	ATLASSERT(ePDataCol_StepType == combo.GetSubItem());

	if(ePDataCol_StepType == combo.GetSubItem()){

		CString strSQL;
		strSQL.Format(
					_T(" UPDATE tblProjectAssemblySteps ")
					_T(" SET %s = %i ")
					_T(" WHERE iProjectID = %i ")
					_T(" AND iStep = %i ")
					, combo.GetAssocFieldName()
					, combo.GetAssocSQLValue()	//this will be num
					, combo.GetProjectID()
					, combo.GetStepNumber()
				);

		try{
			THR( hr = ExecSQL(strSQL, _T("CDataHandler::CommitEditedCell(CComboListItem & edit)"), 0) );
		}
		//----------------------------------------------------------
		catch(_com_error & e){
			hr = e.Error();
			HandleHR(e, _T("CDataHandler::CommitEditedCell(CComboListItem & combo)"), _T(""), strSQL, true);
		}
	}

	combo.HideWindow();

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	13/04/2007 08:32:04
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::CancelEditedCell(CEditListItem & edit)
{
	edit.HideWindow();

	return S_OK;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	29/03/2007 15:04:54
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::DeleteStep(const long iProjectID, const long iStep)
{
	HRESULT hr = S_OK;

	CString strSQL;

	strSQL.Format(
				_T(" DELETE FROM tblProjectAssemblySteps ")
				_T(" WHERE iProjectID = %i ")
				_T(" AND iStep = %i ")
				, iProjectID
				, iStep
			);

	try{
		THR( hr = ExecSQL(strSQL, _T("CDataHandler::DeleteStep"), 0) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::DeleteStep"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	31/03/2007 20:23:26
	DESCRIP:	
		INSERT INTO MyTable  (PriKey, Description)
			   SELECT ForeignKey, Description
			   FROM SomeView
	IN:
	OUT:
*/
HRESULT CDataHandler::CopyStep(const long iProjectID, const long iStep)
{
	HRESULT hr = S_OK;

	CString strSQL;

	strSQL.Format(
				_T(" INSERT INTO tblProjectAssemblySteps ")
				_T(" ( ")
				_T("     iProjectID ")
				_T("     , iStep ")
				_T("     , iStepType ")
				_T("     , szSourceFile ")
				_T("     , szSourceDir ")
				_T("     , szDestDirectory ")
				_T("     , szDestFile ")
				_T("     , szCreated ")
				_T("     , szModified ")
				_T(" ) ")
				_T("     SELECT ")
				_T("         iProjectID ")
				_T("         , %i ")
				_T("         , iStepType ")
				_T("         , szSourceFile ")
				_T("         , szSourceDir ")
				_T("         , szDestDirectory ")
				_T("         , szDestFile ")
				_T("         , '%s' ")
				_T("         , '%s' ")
				_T("     FROM  ")
				_T("         tblProjectAssemblySteps ")
				_T("     WHERE ")
				_T("         iProjectID = %i ")
				_T("     AND ")
				_T("         iStep = %i ")
				, iStep					//value for new record's iStep
				, GetDateTimeString()	//created
				, GetDateTimeString()	//modified
				, iProjectID			//project ID
				, iStep + 1				//the step to make a copy of will be moved up one...
			);

	try{
		//this creates a gap in the steps at iStep
		//eg if iStep = 4 then the numbering should end up as '1, 2, 3, 5, 6...'
		THR( hr = CreateNewStepGap(iProjectID, iStep, 1L) );

		//so we can now copy the step 'iStep + 1' as a new step 'iStep'
		THR( hr = ExecSQL(strSQL, _T("CDataHandler::CopyStep"), 0) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::CopyStep"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	29/03/2007 15:05:52
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::ReOrdinateSteps(const long iProjectID)
{
	HRESULT hr = S_OK;

	CString strSQL;
	strSQL.Format(
				_T(" SELECT * FROM tblProjectAssemblySteps ")
				_T(" WHERE iProjectID = %i ")
				_T(" ORDER BY iStep ")
				, iProjectID
			);

	CComPtr<ADODB::_Recordset>	spRst			= 0;
	CComPtr<ADODB::Field>		spField			= 0;
	
	long iNewStep = 1L;
	CComVariant varValue(long(1L));

	try{
		THR( hr = OpenRecordSet(strSQL, false, spRst) );

		while(!spRst->BOF && !spRst->EndOfFile){
			
			spField = spRst->Fields->Item[L"iStep"];
			varValue = iNewStep;
			spField->Value = varValue;
			
			THR( hr = spRst->Update(L"iStep", varValue) );

			iNewStep ++;
			THR( hr = spRst->MoveNext() );
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::ReOrdinateSteps"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	17/04/2007 18:56:24
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::CreateReOrdinationGap(const long iProjectID)
{
	HRESULT hr = S_OK;

	long iMaxStep = 0L;

	CString strSQL;
	strSQL.Format(
					_T(" SELECT MAX(iStep) AS iMaxStep FROM tblProjectAssemblySteps ")
					_T(" WHERE iProjectID = %i ")
					//_T(" ORDER BY iStep ")
					, iProjectID
				);

	CString strUpdate;

	try{
		THR( hr = LookupNumber(strSQL, -1L, iMaxStep) );

		iMaxStep += 100L;
		
		strSQL.Format(
					_T(" UPDATE tblProjectAssemblySteps ")
					_T(" SET iStep = (iStep + %i) ")
					_T(" WHERE iProjectID = %i  ")
					, iMaxStep
					, iProjectID
				);

		THR( hr = ExecSQL(strSQL, _T("CDataHandler::CreateReOrdinationGap"), 0) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::CreateReOrdinationGap"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	23/03/2007 15:18:15
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::CreateNewStepGap(
									const long iProjectID
									, const long iInsertStep
									, const long iNumNewRecs
								)
{
	HRESULT hr = S_OK;

	CString strSQL;
	strSQL.Format(
				_T(" SELECT ")
				_T("     iRecID ")
				_T("     , iProjectID ")
				_T("     , iStep ")
				_T("     , iStepType ")
				_T("     , szSourceFile ")
				_T("     , szSourceDir ")
				_T("     , szDestDirectory ")
				_T("     , szDestFile ")
				_T("     , szCreated ")
				_T("     , szModified ")
				_T(" FROM tblProjectAssemblySteps ")
				_T(" WHERE iProjectID = %i ")
				_T(" AND iStep >= %i ")
				_T(" ORDER BY iStep DESC ")
				, iProjectID
				, iInsertStep
			);

	/*
		eg: given the following steps for a project:
			1 2 3 4 5 6 7 8 9
		and we need a new rec at, say, 4
		we start at the last one (9) and add the gap size
		otherwise we could violate the project / step unique index
		(if we start at '1' then we end up with two off step '2')
			1 2 3 * 5 6 7 8 9 10
	*/

	CComPtr<ADODB::_Recordset>	spRst			= 0;
	CComPtr<ADODB::Field>		spField			= 0;
	
	CComVariant varValue;
	CString strDateTime = GetDateTimeString();

	try{
		THR( hr = OpenRecordSet(strSQL, false, spRst) );

		while(!spRst->BOF && !spRst->EndOfFile){

			spField = spRst->Fields->Item[L"iStep"];
			
			varValue = spField->Value;
			varValue.lVal += iNumNewRecs;

			//write the new step number to the database
			THR( hr = UpdateFieldValue(spRst, spField, _T("iStep"),			varValue) );
			
			//adjust the 'modified' time
			spField = spRst->Fields->Item[L"szModified"];
			THR( hr = UpdateFieldValue(spRst, spField, _T("szModified"),	strDateTime) );

			THR( hr = spRst->MoveNext() );
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::CreateNewStepGap"), _T(""), strSQL, true);
	}

	return hr;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	15/05/2007 17:49:45
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::UpdateFieldValue(
									CComPtr<ADODB::_Recordset>	& spRst
									, CComPtr<ADODB::Field>		& spField
									, const CString				& strFieldName
									, const CString				& strValue
								)
{
	CComVariant varValue(strValue);
	return UpdateFieldValue(spRst, spField, strFieldName, varValue);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	15/05/2007 17:49:39
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::UpdateFieldValue(
									CComPtr<ADODB::_Recordset>	& spRst
									, CComPtr<ADODB::Field>		& spField
									, const CString				& strFieldName
									, const long				iValue
								)
{
	CComVariant varValue(iValue);
	return UpdateFieldValue(spRst, spField, strFieldName, varValue);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	15/05/2007 17:49:42
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::UpdateFieldValue(
									CComPtr<ADODB::_Recordset>	& spRst
									, CComPtr<ADODB::Field>		& spField
									, const CString				& strFieldName
									, CComVariant				& varNewValue
								)
{
	HRESULT hr = S_OK;

	try{
		spField->Value = varNewValue;
		
		THR( hr = spRst->Update(strFieldName.AllocSysString(), varNewValue) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::UpdateFieldValue"), strFieldName, _T(""), true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	20/03/2007 07:25:16
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::PopulateComboBox(
										const CString & strSQL
										, const CString & strTextField
										, const CString & strIdField
										, CComboBox & rCmbo
									)
{
	HRESULT hr = S_OK;

	rCmbo.ResetContent();

	CComPtr<ADODB::_Recordset>	spRst			= 0;
	CComPtr<ADODB::Field>		spFieldText		= 0;
	CComPtr<ADODB::Field>		spFieldId		= 0;

	CString strEntry;
	int iNew = 0;

	try{
		THR( hr = OpenRecordSet(strSQL, true, spRst) );

		while(!spRst->BOF && !spRst->EndOfFile){

			spFieldText = spRst->Fields->Item[strTextField.AllocSysString()];
			spFieldId	= spRst->Fields->Item[strIdField.AllocSysString()];

			strEntry = XLateFieldText(spFieldText->Value, dwMAX_COMBO_TEXT, _T("..."));

			iNew = rCmbo.AddString(strEntry);
			rCmbo.SetItemData(iNew, XLateFieldNumber(spFieldId->Value));

			THR( hr = spRst->MoveNext() );
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::PopulateComboBox"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	31/03/2007 09:39:15
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::PopulateEditCtrl(const CString & strSQL, CEdit * pEdit)
{
	HRESULT hr = S_OK;

	ATLASSERT(pEdit && ::IsWindow(pEdit->m_hWnd));

	if(!pEdit || !::IsWindow(pEdit->m_hWnd))
		return E_INVALIDARG;

	CString strText;

	try{
		THR( hr = LookupString(strSQL, _T(""), strText) );

		pEdit->SetWindowText(strText);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::PopulateEditCtrl"), _T(""), strSQL, true);
	}

	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/05/2007 07:46:23
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::PopulateEditCtrl(const CString & strSQL, CRichEditCtrl * pRichEdit)
{
	HRESULT hr = S_OK;

	ATLASSERT(pRichEdit && ::IsWindow(pRichEdit->m_hWnd));

	if(!pRichEdit || !::IsWindow(pRichEdit->m_hWnd))
		return E_INVALIDARG;

	CString strText;

	try{
		THR( hr = LookupString(strSQL, _T(""), strText) );

		pRichEdit->SetWindowText(strText);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::PopulateEditCtrl"), _T(""), strSQL, true);
	}

	return hr;
}	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	31/03/2007 10:07:38
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::LookupString(const CString & strSQL, const CString & strDflt, CString & strValue)
{
	HRESULT hr = S_OK;

	CComPtr<ADODB::_Recordset>	spRst			= 0;
	CComPtr<ADODB::Field>		spFieldText		= 0;

	strValue = strDflt;

	try{
		THR( hr = OpenRecordSet(strSQL, true, spRst) );

		if(!spRst->BOF && !spRst->EndOfFile){
			spFieldText = spRst->Fields->Item[CComVariant(0L)];
			strValue = XLateFieldText(spFieldText->Value, 0, _T(""));
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::LookupString"), _T(""), strSQL, true);
	}

	if(strValue.GetLength() >= 512){
	
		ATLTRACE(_T("Long String: %i\n"), strValue.GetLength());
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	16/04/2007 14:41:55
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::LookupNumber(const CString & strSQL, const long iDflt, long & iValue)
{
	HRESULT hr = S_OK;

	CComPtr<ADODB::_Recordset>	spRst			= 0;
	CComPtr<ADODB::Field>		spFieldText		= 0;

	iValue = iDflt;

	try{
		THR( hr = OpenRecordSet(strSQL, true, spRst) );

		if(!spRst->BOF && !spRst->EndOfFile){
			spFieldText = spRst->Fields->Item[CComVariant(0L)];
			iValue = spFieldText->Value.lVal;
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::LookupNumber"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/02/2007 07:27:21
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::InitListCtrl(const CString & strSQL, CListCtrl & rList)
{
	HRESULT hr = S_OK;

	CComPtr<ADODB::_Recordset>	spRst			= 0;
	CComPtr<ADODB::Fields>		spFieldColl		= 0;

	DeleteAllColumns(rList);

	try{
		THR( hr = OpenRecordSet(strSQL, true, spRst) );

		spFieldColl = spRst->Fields;

		InitListCtrl(spFieldColl, rList);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::InitListCtrl"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/02/2007 07:34:09
	DESCRIP:	
	IN:
	OUT:
*/
void CDataHandler::DeleteAllColumns(CListCtrl & rList)
{
	CHeaderCtrl * pHdr = rList.GetHeaderCtrl();
	ATLASSERT(pHdr);

	if(pHdr){
		const int iNUM_COLS = pHdr->GetItemCount();

		for(int iDelCol = iNUM_COLS - 1 ; iDelCol >= 0 ; iDelCol--)
			rList.DeleteColumn(iDelCol);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/02/2007 07:31:25
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::InitListCtrl(const CComPtr<ADODB::Fields> & spFieldColl, CListCtrl & rList)
{
	HRESULT hr = S_OK;

	CWaitCursor wait;

	CComPtr<ADODB::Field>		spField		= 0;

	try{
		const long iFLD_COUNT = spFieldColl->Count;

		for(long iFld = 0 ; iFld < iFLD_COUNT ; iFld++){

			spField = spFieldColl->Item[iFld];

			THR( hr = AddListColumn(iFld, spField, rList) ); 
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::InitListCtrl"), _T(""), _T(""), true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/02/2007 07:31:22
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::AddListColumn(const long iColNum, const CComPtr<ADODB::Field> & spField, CListCtrl & rList)
{
	HRESULT hr = S_OK;

	try{
		rList.InsertColumn(
						iColNum
						, GetColHeaderName(spField->Name)
						, GetColHeaderFmt(spField->Type)
					);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::AddListColumn"), _T(""), _T(""), true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/02/2007 07:42:19
	DESCRIP:
		
		  convert eg 'strUserName' to 'User Name', etc

	IN:
	OUT:
*/
CString CDataHandler::GetColHeaderName(const _bstr_t & bstrFldName) const
{
	USES_CONVERSION;

	const CString strOrig = OLE2T(bstrFldName);

	CString strRet = strOrig;

//	TCHAR ch = 0;
//	bool bStarted = false;
//	const int iMAX = strOrig.GetLength();
//
//	for(int iCharPos = 0 ; iCharPos < iMAX ; iCharPos++ ){
//		ch = strOrig.GetAt(iCharPos);
//
//		if(_istupper(ch)){
//			bStarted = true;
//
//			if(!strRet.IsEmpty())
//				strRet += _T(" ");
//		}
//
//		if(bStarted)
//			strRet += ch;
//	}


	return strRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/02/2007 17:57:27
	DESCRIP:	
		typedef struct _HDITEM {
			UINT    mask; 
			int     cxy; 
			LPTSTR  pszText; 
			HBITMAP hbm; 
			int     cchTextMax; 
			int     fmt; 
			LPARAM  lParam; 
		#if (_WIN32_IE >= 0x0300)
			int     iImage;
			int     iOrder;
		#endif
		} HDITEM, FAR * LPHDITEM;
	IN:
	OUT:
*/
CString CDataHandler::GetColFieldName(const int iCol, CListCtrl & rList) const
{
	CString strRet;

	CHeaderCtrl * pHdr = rList.GetHeaderCtrl();
	ATLASSERT(pHdr && ::IsWindow(pHdr->m_hWnd));

	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		
		//max MS Access field name is about 60?
		const DWORD dwBUFSIZE = 100L;
		TCHAR szBuffer[dwBUFSIZE + 5] = {0};

		HDITEM hditem;
		::ZeroMemory(&hditem, sizeof(HDITEM));

		hditem.mask			= HDI_TEXT;
		hditem.pszText		= szBuffer;
		hditem.cchTextMax	= dwBUFSIZE;

		BOOL bOK = pHdr->GetItem(iCol, &hditem);
		ATLASSERT(bOK);

		strRet = szBuffer;

		if(strRet.Find(_T(' ')) >= 0){
			strRet = _T('[') + strRet + _T(']');
		}
	}

	return strRet;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/02/2007 07:42:21
	DESCRIP:
	
		adEmpty:
		adTinyInt:
		adSmallInt:
		adInteger:
		adBigInt:
		adUnsignedTinyInt:
		adUnsignedSmallInt:
		adUnsignedInt:
		adUnsignedBigInt:
		adSingle:
		adDouble:
		adCurrency:
		adDecimal:
		adNumeric:
		adBoolean:
		adError:
		adUserDefined:
		adVariant:
		adIDispatch:
		adIUnknown:
		adGUID:
		adDate:
		adDBDate:
		adDBTime:
		adDBTimeStamp:
		adBSTR:
		adChar:
		adVarChar:
		adLongVarChar:
		adWChar:
		adVarWChar:
		adLongVarWChar:
		adBinary:
		adVarBinary:
		adLongVarBinary:
		adChapter:
		adFileTime:
		adPropVariant:
		adVarNumeric:
		adArray:
	
	IN:
	OUT:
*/
int CDataHandler::GetColHeaderFmt(const ADODB::DataTypeEnum eType) const
{
	using namespace ADODB;

	int iFmt = LVCFMT_LEFT;
	LVCFMT_CENTER;
	LVCFMT_RIGHT;

	switch(eType){
		case adEmpty:
		case adUserDefined:
		case adVariant:
		case adIDispatch:
		case adIUnknown:
			break;

		case adTinyInt:
		case adSmallInt:
		case adInteger:
		case adBigInt:
		case adUnsignedTinyInt:
		case adUnsignedSmallInt:
		case adUnsignedInt:
		case adUnsignedBigInt:
		case adSingle:
		case adDouble:
		case adCurrency:
		case adDecimal:
		case adNumeric:
		case adError:
			iFmt = LVCFMT_RIGHT;
			break;

		case adBoolean:
		case adGUID:
		case adDate:
		case adDBDate:
		case adDBTime:
		case adDBTimeStamp:
		case adFileTime:
			iFmt = LVCFMT_CENTER;
			break;

		case adBSTR:
		case adChar:
		case adVarChar:
		case adLongVarChar:
		case adWChar:
		case adVarWChar:
		case adLongVarWChar:
		case adBinary:
		case adVarBinary:
		case adLongVarBinary:
		case adChapter:
		case adPropVariant:
		case adVarNumeric:
		case adArray:
			iFmt = LVCFMT_LEFT;
			break;
	}

	return iFmt;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/02/2007 07:27:19
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::PopulateListCtrl(
										const CString & strSQL
										, CListCtrl & rList
										, const bool bClearFirst
									)
{
	HRESULT hr = S_OK;

	CWaitCursor wait;

	rList.DeleteAllItems();
	rList.SendMessage(WM_SETREDRAW, FALSE, 0);


	CComPtr<ADODB::_Recordset> spRst = 0;

	try{
		THR( hr = OpenRecordSet(strSQL, true, spRst) );

		while(!spRst->BOF && !spRst->EndOfFile){

			THR( hr = AddListRow(spRst, rList) );

			THR( hr = spRst->MoveNext() );
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::PopulateListCtrl"), _T(""), _T(""), true);
	}

	rList.SendMessage(WM_SETREDRAW, TRUE, 0);

	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/02/2007 07:57:23
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::AddListRow(const CComPtr<ADODB::_Recordset> & spRst, CListCtrl & rList)
{
	HRESULT hr = S_OK;

	CComPtr<ADODB::Fields>	spFieldColl		= 0;
	CComPtr<ADODB::Field>	spField			= 0;

	int iCur = rList.GetItemCount();
	int iNew = rList.InsertItem(iCur, _T("dummy"));

	try{
		spFieldColl = spRst->Fields;

		const long iFLD_COUNT = spFieldColl->Count;

		for(long iFld = 0 ; iFld < iFLD_COUNT ; iFld++){

			spField = spFieldColl->Item[iFld];

			THR( hr = SetListCellText(iNew, iFld, spField, rList) );
		}

		rList.SetItemData(iNew, iNew);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::AddListRow"), _T(""), _T(""), true);
	}

	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	07/02/2007 08:00:24
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CDataHandler::SetListCellText(
										const int iItem
										, const int iSubItem
										, const CComPtr<ADODB::Field> & spField
										, CListCtrl & rList
									)
{
	HRESULT hr = S_OK;

	try{
		CComVariant varValue = spField->Value;

		rList.SetItemText(
						iItem
						, iSubItem
						, XLateFieldText(varValue, dwMAX_LIST_CELL_TEXT, _T("..."))
					);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::SetListCellText"), _T(""), _T(""), true);
	}

	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	09/02/2007 08:44:51
	DESCRIP:	
	IN:
	OUT:
*/
bool CDataHandler::GetListCellText(
									const int iItem
									, const CString & strFieldName
									, CListCtrl & rList
									, CString & strCellText
								)
{
	bool bOK = false;

	CHeaderCtrl * pHdr = rList.GetHeaderCtrl();
	ATLASSERT(pHdr && ::IsWindow(pHdr->m_hWnd));

	if(pHdr && ::IsWindow(pHdr->m_hWnd)){
		
		CString strColName = GetColHeaderName(strFieldName.AllocSysString());
		CString strProbe;

		const int iMAX_COLS = pHdr->GetItemCount();
		const DWORD dwBUFSIZE = 512L;

		TCHAR szBuffer[dwBUFSIZE + 5] = {0};

		HDITEM hditem;
		::memset(&hditem, 0, sizeof(HDITEM));

		hditem.mask			= HDI_TEXT;
		hditem.pszText		= szBuffer;
		hditem.cchTextMax	= dwBUFSIZE;

		for(int iCol = 0 ; iCol < iMAX_COLS && !bOK ; iCol++){
			pHdr->GetItem(iCol, &hditem);

			//may contain (ASC) or (DESC), so trim to length of passed
			//parameter, and then compare
			strProbe = szBuffer;
			strProbe = strProbe.Left(strColName.GetLength());

			if(0 == strColName.CompareNoCase(strProbe)){
				bOK = true;
				strCellText = rList.GetItemText(iItem, iCol);
			}
		}

		ATLASSERT(bOK);
	}

	return bOK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	09/02/2007 08:44:57
	DESCRIP:	
	IN:
	OUT:
*/
bool CDataHandler::GetListCellNumber(
									const int iItem
									, const CString & strFieldName
									, CListCtrl & rList
									, long & iCellText
								)
{
	CString strText;

	bool bOK = GetListCellText(iItem, strFieldName, rList, strText);

	if(bOK){
		iCellText = _ttol(strText);
	}

	return bOK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	30/03/2007 09:26:08
	DESCRIP:	
	strSQL.Format(
				_T(" SELECT ")
				_T("     iRecID ")
				_T("     , iProjectID ")
				_T("     , iStep ")
				_T("     , iStepType ")
				_T("     , szSourceFile ")
				_T("     , szSourceDir ")
				_T("     , szDestDirectory ")
				_T("     , szDestFile ")
				_T(" FROM tblProjectAssemblySteps ")
				_T(" WHERE iProjectID = %i ")
				_T(" AND iStep >= %i ")
				_T(" ORDER BY iStep DESC ")
				, iProjectID
				, iInsertStep
			);

	IN:
	OUT:
*/
HRESULT CDataHandler::SaveData(const CPfaDataListItem & rItem)
{
	HRESULT hr = S_OK;

	CString strSQL;
	strSQL.Format(
				_T(" UPDATE tblProjectAssemblySteps ")
				_T(" SET ")
				_T("     szSourceFile = '%s' ")
				_T("     , szSourceDir = '%s' ")
				_T("     , szDestDirectory = '%s' ")
				_T("     , szDestFile = '%s' ")
				_T("     , iStepType = %i ")
				_T(" WHERE iProjectID = %i ")
				_T(" AND iStep = %i ")
				, SQLValue(	rItem.GetSourceFile		()	)
				, SQLValue(	rItem.GetSourceDir		()	)
				, SQLValue(	rItem.GetDestDirectory	()	)
				, SQLValue(	rItem.GetDestFile		()	)
				, rItem.GetStepType()
				, rItem.GetProjectID()
				, rItem.GetStepNum()
			);

	try{
		THR( hr = ExecSQL(strSQL, _T("CDataHandler::SaveData"), 0) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		HandleHR(e, _T("CDataHandler::SaveData"), _T(""), strSQL, true);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	08/05/2007 08:40:14
	DESCRIP:	
	IN:
	OUT:
*/
/*virtual*/
void CDataHandler::LogDbError(
							const CString & strFunc
							, const CString & strText
							, const CString & strSQL
						)
{
	LogDataEventStr(
				eEvt_Error
				, strFunc
				, strText
				, strSQL
			);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	08/05/2007 07:35:12
	DESCRIP:	
		TCHAR    chMsg[256];
		va_list pArg;

		va_start(pArg, pFormat);
		vsprintf(chMsg, pFormat, pArg);
		va_end(pArg);

	IN:
	OUT:
*/
HRESULT __cdecl CDataHandler::LogDataEvent(
										const eEVT_TYPE eType
										, const CString & strSource
										, const CString & strSQL
										, LPCTSTR pszFormat
										, ...
									)
{
	TCHAR szMessage[dwLOG_BUF_SIZE + 5] = {0};

	HRESULT hr = E_INVALIDARG;

	if(pszFormat){

		va_list pArg;
		va_start(pArg, pszFormat);

		_vsntprintf(szMessage, dwLOG_BUF_SIZE, pszFormat, pArg);
		
		szMessage[dwLOG_BUF_SIZE] = 0;

		va_end(pArg);

		hr = LogDataEventStr(eType, strSource, szMessage, strSQL);
	}

	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	08/05/2007 07:35:15
	DESCRIP:	
		This is a close copy of ExecSQL, but I don't want to 
		call that since I will be logging ExecSQL, and I would
		end up in a bit of a loop. :@}
	IN:
	OUT:
*/
HRESULT CDataHandler::LogDataEventStr(
								const eEVT_TYPE eType
								, const CString & strSource
								, const CString & strText
								, const CString & strSQL
							)
{
	const DWORD dwTRACEMAX = 256L;

	HRESULT hr = S_OK;

	//if(strText.GetLength() < dwTRACEMAX)
	//	ATLTRACE(_T("LogDataEventStr: [%s]\n"), strText);
	//else
	//	ATLTRACE(_T("LogDataEventStr: (truncated) [%s]\n"), strText.Left(dwTRACEMAX));
	CString strDbText	= SQLValue(strText);
	CString strDbSQL	= SQLValue(strSQL);


	CString strExecSQL;

	strExecSQL.Format(
		_T(" INSERT INTO [ProjectFileAssembler].[dbo].[tblLogging] ")
			_T(" ( ")
			_T("     [iType] ")
			_T("     , [szType] ")
			_T("     , [szLogon] ")
			_T("     , [szMachine] ")
			_T("     , [szSource] ")
			_T("     , [szText] ")
			_T("     , [szSQL] ")
			_T(" ) ")
		_T(" VALUES ")
			_T(" ( ")
			_T("     %i ")			//<iType, int,>
			_T("     , '%s' ")			//<szType, nvarchar(50),>
			_T("     , '%s' ")			//<szLogon, nvarchar(50),>
			_T("     , '%s' ")			//<szMachine, nvarchar(50),>
			_T("     , '%s' ")			//<szSource, nvarchar(50),>
			_T("     , '%s' ")			//<szText, nvarchar(max),>
			_T("     , '%s' ")			//<szSQL, nvarchar(max),>
			_T(" ) ")
			, eType
			, szsEVENT_TYPE_NAMES[eType]
			, CLocalProps::GetUserName()
			, CLocalProps::GetMachineName()
			, strSource
			, strDbText
			, strDbSQL
		);

	CComPtr<ADODB::_Command> spCmd = 0;

	try{
		THR( hr = spCmd.CoCreateInstance(ADODB::CLSID_Command) );

		spCmd->ActiveConnection		= m_spConnection;
		spCmd->CommandText			= strExecSQL.AllocSysString();
		spCmd->CommandType			= ADODB::adCmdText;

		CComVariant varRecsAffected	(long(0L));
		CComVariant varParameters	(vtMissing);

		spCmd->Execute(&varRecsAffected, &varParameters, ADODB::adCmdText);
		ATLTRACE(_T("CDataHandler::LogDataEventStr: %i recs affected\n"), varRecsAffected.lVal);
	}
	//----------------------------------------------------------
	catch(_com_error & e){

		//do NOT attempt to log an error from here!!!
		//will just re-enter and fail again, repeatedly

		hr = e.Error();
		HandleHR(e, _T("CDataHandler::LogDataEventStr"), _T(""), strExecSQL, false);
	}

	return hr;
}

