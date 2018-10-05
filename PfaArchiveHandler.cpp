// PfaArchiveHandler.cpp: implementation of the CPfaArchiveHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "PfaArchiveHandler.h"

#include "ConstSQL.h"
using namespace CONS_SQL;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPfaArchiveHandler::CPfaArchiveHandler()
{

}

CPfaArchiveHandler::~CPfaArchiveHandler()
{

}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/05/2007 15:26:22
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaArchiveHandler::ArchiveProject(
										const CComPtr<ADODB::_Connection> & spConnection
										, const CString & strProjectName
										, const long iProjectID
									)
{
	HRESULT hr = S_OK;

	const static TCHAR szFILTER[] = _T("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||");

	CString strFileName;
	COleDateTime dtNow = COleDateTime::GetCurrentTime();

	strFileName.Format(
					_T("%04i-%02i-%02i %02i%02i%02i %s Archive.csv")
					, dtNow.GetYear(), dtNow.GetMonth(), dtNow.GetDay()
					, dtNow.GetHour(), dtNow.GetMinute(), dtNow.GetSecond()
					, strProjectName
				);

	CFileDialog dlg(
					TRUE
					, _T(".csv")		//LPCTSTR lpszDefExt = NULL
					, strFileName		//LPCTSTR lpszFileName = NULL
					, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT	//DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
					, szFILTER			//LPCTSTR lpszFilter = NULL
					, 0					//CWnd* pParentWnd = NULL
				);

	INT_PTR iReply = dlg.DoModal();

	if(IDOK == iReply)
		hr = ArchiveProject(spConnection, strProjectName, iProjectID, dlg.GetPathName());
	
	else
		hr = S_FALSE;

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/05/2007 15:26:24
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaArchiveHandler::ArchiveProject(
										const CComPtr<ADODB::_Connection> & spConnection
										, const CString & strProjectName
										, const long iProjectID
										, const CString & strFileName
									)
{
	HRESULT hr = S_OK;

	DWORD dwFileFlags = 
						CFile::modeCreate
						| CFile::modeReadWrite
						| CFile::shareDenyNone
						| CFile::typeText
					;

	CStdioFile filArchive;
	BOOL bOpened = filArchive.Open(strFileName, dwFileFlags);

	if(bOpened){

		CString strTitle;
		CSystemTime2 dtsys;
		
		dtsys.SetNow();

		strTitle.Format(_T("//Project export (id = %i) %s"), iProjectID, dtsys.GetCurDateTime());
		
		filArchive.WriteString(strTitle + _T("\n"));

		try{
			THR( hr = ArchiveProjectHeader	(spConnection, iProjectID, filArchive) );
			THR( hr = ArchiveProjectSteps	(spConnection, iProjectID, filArchive) );
		}
		//----------------------------------------------------------
		catch(_com_error & e){
			hr = e.Error();
			ASSERT(false);
		}

	}
	else
		hr = E_FAIL;

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/05/2007 15:32:57
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaArchiveHandler::ArchiveProjectHeader(
											const CComPtr<ADODB::_Connection> & spConnection
											, const long iProjectID
											, CStdioFile & filArchive
										)
{
	HRESULT hr = S_OK;

	CString strSQL;
	CComPtr<ADODB::_Recordset> spRst = 0L;

	strSQL.Format(_T("%s WHERE iProjectID = %i"), szSQL_PROJECT_TABLE, iProjectID);

	try{
		THR( hr = spRst.CoCreateInstance(ADODB::CLSID_Recordset) );

		ADODB::CursorTypeEnum	eCursor	= ADODB::adOpenStatic;
		ADODB::LockTypeEnum		eLock	= ADODB::adLockReadOnly;

		THR( hr = spRst->Open(
							CComVariant(strSQL)
							, CComVariant(spConnection)
							, eCursor					//CursorType
							, eLock						//LockType
							, ADODB::adCmdText			//options
						) );
		
		THR( hr = ArchiveProjectHeader(spRst, filArchive) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/05/2007 15:44:21
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaArchiveHandler::ArchiveProjectHeader(
											const CComPtr<ADODB::_Recordset> & spRst
											, CStdioFile & filArchive
										)
{
	HRESULT hr = S_OK;

	CComPtr<ADODB::Fields>	spFieldColl		= 0;

	CString strLine;

	try{
		THR( hr = spRst->MoveFirst() );

		//there should only ever be one record, but we'll
		//act as though there may be more, just in case
		//we decide to do a 'complete' backup?
		while(!spRst->BOF && !spRst->EndOfFile){
			
			spFieldColl = spRst->Fields;

			THR( hr = GetProjectHeaderLine(spFieldColl, strLine) );

			filArchive.WriteString(strLine + _T("\n"));

			THR( hr = spRst->MoveNext() );
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/05/2007 07:31:59
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaArchiveHandler::GetProjectHeaderLine(const CComPtr<ADODB::Fields> & spFieldColl, CString & strLine)
{
	HRESULT hr = S_OK;

	CString strAdd;
	CComPtr<ADODB::Field>	spField			= 0;

	strLine = szsARCLINE_INDICS[eArcLin_ProjectData];

	try{
		for(DWORD dwLoop = 0L ; dwLoop < eProjFld__LAST ; dwLoop ++){
		
			spField = spFieldColl->Item[ bstrsPROJECT_FIELDS [dwLoop] ];

			THR( hr = QuickXLate(
								spField
								, bsIS_NUMERIC_PROJECT_FIELD[dwLoop]
								, strAdd) 
							);

			strLine += strAdd;
		}

	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/05/2007 15:33:00
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaArchiveHandler::ArchiveProjectSteps(
											const CComPtr<ADODB::_Connection> & spConnection
											, const long iProjectID
											, CStdioFile & filArchive
										)
{
	HRESULT hr = S_OK;

	CString strSQL;
	CComPtr<ADODB::_Recordset> spRst = 0L;

	strSQL.Format(
				_T("%s WHERE iProjectID = %i ")
				_T(" ORDER BY iProjectID, iStep")
				, szSQL_STEPS_TABLE
				, iProjectID
			);

	try{
		THR( hr = spRst.CoCreateInstance(ADODB::CLSID_Recordset) );

		ADODB::CursorTypeEnum	eCursor	= ADODB::adOpenStatic;
		ADODB::LockTypeEnum		eLock	= ADODB::adLockReadOnly;

		THR( hr = spRst->Open(
							CComVariant(strSQL)
							, CComVariant(spConnection)
							, eCursor					//CursorType
							, eLock						//LockType
							, ADODB::adCmdText			//options
						) );
		
		THR( hr = ArchiveProjectSteps(spRst, filArchive) );
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	21/05/2007 15:44:26
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaArchiveHandler::ArchiveProjectSteps	(
											const CComPtr<ADODB::_Recordset> & spRst
											, CStdioFile & filArchive
										)
{
	HRESULT hr = S_OK;

	CComPtr<ADODB::Fields>	spFieldColl		= 0;

	CString strLine;

	try{
		THR( hr = spRst->MoveFirst() );

		while(!spRst->BOF && !spRst->EndOfFile){
			
			spFieldColl = spRst->Fields;

			THR( hr = GetProjectStepLine(spFieldColl, strLine) );

			filArchive.WriteString(strLine + _T("\n"));

			THR( hr = spRst->MoveNext() );
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/05/2007 07:45:07
	DESCRIP:	
	
	IN:
	OUT:
*/
HRESULT CPfaArchiveHandler::GetProjectStepLine(const CComPtr<ADODB::Fields> & spFieldColl, CString & strLine)
{
	HRESULT hr = S_OK;

	CString strAdd;
	CComPtr<ADODB::Field>	spField			= 0;

	strLine = szsARCLINE_INDICS[eArcLin_StepData];

	try{

		for(DWORD dwLoop = 0L ; dwLoop < eStepFld__LAST ; dwLoop++){
		
			spField = spFieldColl->Item[ bstrsSTEP_TABLE_FIELDS [dwLoop] ];

			THR( hr = QuickXLate(
								spField
								, bsIS_NUMERIC_STEP_TABLE_FIELD[dwLoop]
								, strAdd) 
							);

			strLine += strAdd;
		}
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
	}

	return hr;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	22/05/2007 08:43:14
	DESCRIP:	
	IN:
	OUT:
*/
HRESULT CPfaArchiveHandler::QuickXLate(
									const CComPtr<ADODB::Field> & spField
									, const bool bNumeric
									, CString & strCsvAdd
								)
{
	HRESULT hr = S_OK;

	USES_CONVERSION;

	try{
		if(bNumeric)
			strCsvAdd.Format(_T(",%i"), spField->Value.lVal);

		else
			strCsvAdd.Format(
							_T(",%s%s%s")
							, szsARCLINE_INDICS[eArcLin_OpenTextCell]
							, OLE2T(spField->Value.bstrVal)
							, szsARCLINE_INDICS[eArcLin_CloseTextCell]
						);
	}
	//----------------------------------------------------------
	catch(_com_error & e){
		hr = e.Error();
		ASSERT(false);
	}

	return hr;
}
