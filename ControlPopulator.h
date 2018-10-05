// ControlPopulator.h: interface for the CControlPopulator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLPOPULATOR_H__6F8B400F_D7E1_40ED_AAFA_CF2C46C079DB__INCLUDED_)
#define AFX_CONTROLPOPULATOR_H__6F8B400F_D7E1_40ED_AAFA_CF2C46C079DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XLateFieldText.h"
#include "OleDbErrorHandler.h"
#include "PfaDataListItem.h"
#include "EditListItem.h"
#include "ComboListItem.h"
#include "datasourceinfoholder.h"
#include "localprops.h"
#include "PfaStepHolder.h"

#include "ConstStepTypes.h"
using namespace CONS_STEP_TYPES;

#include "ConstEventTypes.h"
using namespace CONS_EVT_TYPES;

const DWORD dwLOG_BUF_SIZE = 4000L * sizeof(TCHAR);

class CDataHandler  
:	public CXLateFieldText
	, public COleDbErrorHandler
	, public CDataSourceInfoHolder
	, public CLocalProps
{
public:
	CDataHandler();
	virtual ~CDataHandler();


public:
	inline const CComPtr<ADODB::_Connection> & GetConnection(void) const { return m_spConnection; }

private:
	CComPtr<ADODB::_Connection> m_spConnection;

public:
	HRESULT ConnectDb(void);
	void DisconnectDb(void);
	HRESULT ReconnectDb(void);

public:
	HRESULT ReadDataSourceProps(CListCtrl & rList);

public:
	CString GetConnString	(void) const;

public:

	HRESULT OpenRecordSet(
						const CString & strSQL
						, const bool bReadOnly
						, CComPtr<ADODB::_Recordset> & spRst
					);

	//HRESULT OpenRecordSetWrite(
	//					const CString & strSQL
	//					, CComPtr<ADODB::_Recordset> & spRst
	//				);

	HRESULT CountRecords(
						const CString & strSQL
						, long & iCount
					);


public:
	HRESULT InsertNewProject(	
						const CString & strProjectName
						, const CString & strDfltSrcDir
						, const CString & strDfltDestDir
					);

	HRESULT CopyExistingProject(
						const long iExistProjID
						, const CString & strNewName
					);

	HRESULT CopyProjectTableEntry(
						const long iExistProjID
						, const CString & strNewName
						, long & iNewProjID
					);

	HRESULT CopyProjectAssemblySteps(
						const long iExistProjID
						, const long iNewProjID
					);

	HRESULT DeleteExistingProject(const long iProjectID);

	HRESULT SetProjectDirectory(
						const long iProjectID
						, const CString & strDfltDir
						, const bool bIsSrcNotDest
					);

	HRESULT InsertNewStep(
						const long iProjectID
						, const long iInsertStep
						, const ePFA_STEP_TYPE eStepType
						, const CString & strSrcFile
						, const CString & strSrcDir
						, const CString & strDestDir
						, const CString & strDestFile
						, const bool bCreateGap
					);

	HRESULT InsertNewSteps(CPfaStepHolder & stepholder);

	HRESULT IsNewRecord(
						const long iProjectID
						, const long iInsertStep
						, const ePFA_STEP_TYPE eStepType
						, const CString & strSrcFile
						, const CString & strSrcDir
						, const CString & strDestDir
						, const CString & strDestFile
						, bool & bIsNewRec
					);

	HRESULT CreateNewStepGap(
						const long iProjectID
						, const long iInsertStep
						, const long iNumNewRecs
					);

	HRESULT InsertNewStep			(const long iProjectID, const long iInsertStep);
	HRESULT DeleteStep				(const long iProjectID, const long iStep);
	HRESULT CopyStep				(const long iProjectID, const long iStep);
	HRESULT ReOrdinateSteps			(const long iProjectID);
	HRESULT CreateReOrdinationGap	(const long iProjectID);

	HRESULT UpdateFieldValue(
							CComPtr<ADODB::_Recordset>	& spRst
							, CComPtr<ADODB::Field>		& spField
							, const CString				& strFieldName
							, const CString				& strValue
						);
	
	HRESULT UpdateFieldValue(
							CComPtr<ADODB::_Recordset>	& spRst
							, CComPtr<ADODB::Field>		& spField
							, const CString				& strFieldName
							, const long				iValue
						);
	
	HRESULT UpdateFieldValue(
							CComPtr<ADODB::_Recordset>	& spRst
							, CComPtr<ADODB::Field>		& spField
							, const CString				& strFieldName
							, CComVariant				& varNewValue
						);

	HRESULT CommitEditedCell		(CEditListItem & edit);
	HRESULT CommitEditedCell		(CComboListItem & combo);
	HRESULT CancelEditedCell		(CEditListItem & edit);

	CString SQLValue			(const CString & strFieldValue) const;
	CString GetDateTimeString	(void) const;

public:
	HRESULT InitListCtrl(
						const CString & strSQL
						, CListCtrl & rList
					);

	HRESULT PopulateListCtrl(
						const CString & strSQL
						, CListCtrl & rList
						, const bool bClearFirst
					);

	bool GetListCellText(
						const int iItem
						, const CString & strFieldName
						, CListCtrl & rList
						, CString & strCellText
					);

	bool GetListCellNumber(
						const int iItem
						, const CString & strFieldName
						, CListCtrl & rList
						, long & iCellText
					);

public:
	HRESULT PopulateComboBox(
						const CString & strSQL
						, const CString & strTextField
						, const CString & strIdField
						, CComboBox & rCmbo
					);

	HRESULT PopulateEditCtrl	(const CString & strSQL, CEdit * pEdit);
	HRESULT PopulateEditCtrl	(const CString & strSQL, CRichEditCtrl * pRichEdit);
	HRESULT LookupString		(const CString & strSQL, const CString & strDflt, CString & strValue);
	HRESULT LookupNumber		(const CString & strSQL, const long iDflt, long & iValue);

public:
	HRESULT SaveData	(const CPfaDataListItem & rItem);
	
	HRESULT ExecSQL(
					const CString & strSQL
					, const CString & strSource
					, long * piRecsAffected
				);

private:

	void DeleteAllColumns(CListCtrl & rList);

	HRESULT InitListCtrl(
						const CComPtr<ADODB::Fields> & spFieldColl
						, CListCtrl & rList
					);

	HRESULT AddListColumn(
						const long iColNum
						, const CComPtr<ADODB::Field> & spField
						, CListCtrl & rList
					);

	CString		GetColHeaderName	(const _bstr_t & bstrFldName) const;
	CString		GetColFieldName		(const int iCol, CListCtrl & rList) const;
	int			GetColHeaderFmt		(const ADODB::DataTypeEnum eType) const;


	HRESULT AddListRow(const CComPtr<ADODB::_Recordset> & spRst, CListCtrl & rList);

	HRESULT SetListCellText(
						const int iItem
						, const int iSubItem
						, const CComPtr<ADODB::Field> & spField
						, CListCtrl & rList
					);


public:
	virtual void LogDbError(
						const CString & strFunc
						, const CString & strText
						, const CString & strSQL
					);

	HRESULT __cdecl LogDataEvent(
						const eEVT_TYPE eType
						, const CString & strSource
						, const CString & strSQL
						, LPCTSTR pszFormat
						, ...
					);

	HRESULT LogDataEventStr(
						const eEVT_TYPE eType
						, const CString & strSource
						, const CString & strText
						, const CString & strSQL
					);

};

#endif // !defined(AFX_CONTROLPOPULATOR_H__6F8B400F_D7E1_40ED_AAFA_CF2C46C079DB__INCLUDED_)
