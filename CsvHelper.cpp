// CsvHelper.cpp: implementation of the CCsvHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "CsvHelper.h"

#include "ConstTokens.h"
using namespace CONS_TOKENS;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCsvHelper::CCsvHelper()
{

}

CCsvHelper::~CCsvHelper()
{

}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 08:27:55
	DESCRIP:	
	IN:
	OUT:
*/
void CCsvHelper::CsvToListCtrl(const CString & strCSVFile, CListCtrl & rList) const
{
	UINT uFlags = CFile::modeRead | CFile::shareDenyNone | CFile::typeText;

	CStdioFile csvfile;
	BOOL bOpened = csvfile.Open(strCSVFile, uFlags);

	if(bOpened){
		rList.DeleteAllItems();
		CsvToListCtrl(csvfile, rList);
	}
	else{
		::AfxMessageBox(_T("Failed to open file:\n") + strCSVFile);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 08:32:06
	DESCRIP:	
	IN:
	OUT:
*/
void CCsvHelper::CsvToListCtrl(CStdioFile & csvfile, CListCtrl & rList) const
{
	CString strLine;

	csvfile.SeekToBegin();

	while(csvfile.ReadString(strLine)){
		CsvLineToListCtrl(strLine, rList);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 08:35:02
	DESCRIP:	
	IN:
	OUT:
*/
void CCsvHelper::CsvLineToListCtrl(const CString & strCSVLine, CListCtrl & rList) const
{
	int iCur		= rList.GetItemCount();
	int iNew		= rList.InsertItem(iCur, _T(""));
	int iSubItem	= 0;

	CString strItem;

	TCHAR chProbe = 0;
	int iCharPos = 0;
	const int iMAXPOS = strCSVLine.GetLength();

	for(iCharPos = 0 ; iCharPos < iMAXPOS ; iCharPos++){
		chProbe = strCSVLine.GetAt(iCharPos);

		if(szCOMMA[0] == chProbe){
			rList.SetItemText(iNew, iSubItem, strItem);
			iSubItem ++;
			strItem.Empty();
		}
		else{
			strItem += chProbe;
		}
	}

	//the last column may not have a comma terminator
	if(!strItem.IsEmpty()){
		rList.SetItemText(iNew, iSubItem, strItem);
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	12/03/2007 20:26:05
	DESCRIP:	
	IN:
	OUT:
*/
void CCsvHelper::CsvLineToStrings(
								const CString & strCSVLine
								, CStringArray & rArray
								, const DWORD dwMinItems
							) const
{
	rArray.RemoveAll();

	CString strItem;

	TCHAR chProbe = 0;
	int iCharPos = 0;
	const int iMAXPOS = strCSVLine.GetLength();

	for(iCharPos = 0 ; iCharPos < iMAXPOS ; iCharPos++){
		chProbe = strCSVLine.GetAt(iCharPos);

		if(szCOMMA[0] == chProbe){
			rArray.Add(strItem);
			strItem.Empty();
		}
		else{
			strItem += chProbe;
		}
	}

	//the last column may not have a comma terminator
	if(!strItem.IsEmpty()){
		rArray.Add(strItem);
	}

	//make it up to the minimum number of items
	//if we have too few
	while(DWORD(rArray.GetSize()) < dwMinItems)
		rArray.Add(_T(""));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	14/03/2007 07:31:28
	DESCRIP:	
	IN:
	OUT:
*/
CString CCsvHelper::StringsToCsvLine(
									const CStringArray & rArray
									, const DWORD dwMinItems
								) const
{
	CString strCsvLine;
	DWORD dwLoop = 0L;

	for(dwLoop = 0L ; dwLoop < DWORD(rArray.GetSize()) ; dwLoop++){
		strCsvLine += rArray.GetAt(dwLoop);
		strCsvLine += szCOMMA;
	}

	//make it up to the minimum number of terms
	for(dwLoop = rArray.GetSize() ; dwLoop < dwMinItems ; dwLoop++){
		strCsvLine += szCOMMA;
	}

	return strCsvLine;
}
