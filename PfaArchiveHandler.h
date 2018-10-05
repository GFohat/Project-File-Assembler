// PfaArchiveHandler.h: interface for the CPfaArchiveHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PFAARCHIVEHANDLER_H__04D3B512_16B6_470E_944A_FD5BB618111F__INCLUDED_)
#define AFX_PFAARCHIVEHANDLER_H__04D3B512_16B6_470E_944A_FD5BB618111F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
	We need to be able to output a plain text version so we can
	put this into source safe. Thus we also need to be able to 
	import a plain text version as a new / replacement project.

	See below for text file data.
*/

enum _eARCHIVE_LINES{
	eArcLin_ProjectData		= 0
	, eArcLin_StepData
	, eArcLin_OpenTextCell
	, eArcLin_CloseTextCell
	, eArcLin__LAST
};

const TCHAR szsARCLINE_INDICS[eArcLin__LAST][40] = {
	_T("PROJECT")
	, _T("STEP")
	, _T("\"[")
	, _T("]\"")
};

class CPfaArchiveHandler  
{
public:
	CPfaArchiveHandler();
	virtual ~CPfaArchiveHandler();

public:
	HRESULT ArchiveProject(
						const CComPtr<ADODB::_Connection> & spConnection
						, const CString & strProjectName
						, const long iProjectID
					);

	HRESULT ArchiveProject(
						const CComPtr<ADODB::_Connection> & spConnection
						, const CString & strProjectName
						, const long iProjectID
						, const CString & strFileName
					);

private:
	HRESULT ArchiveProjectHeader	(const CComPtr<ADODB::_Connection> & spConnection, const long iProjectID, CStdioFile & filArchive);
	HRESULT ArchiveProjectHeader	(const CComPtr<ADODB::_Recordset> & spRst, CStdioFile & filArchive);
	HRESULT GetProjectHeaderLine	(const CComPtr<ADODB::Fields> & spFieldColl, CString & strLine);

	HRESULT ArchiveProjectSteps		(const CComPtr<ADODB::_Connection> & spConnection, const long iProjectID, CStdioFile & filArchive);
	HRESULT ArchiveProjectSteps		(const CComPtr<ADODB::_Recordset> & spRst, CStdioFile & filArchive);
	HRESULT GetProjectStepLine		(const CComPtr<ADODB::Fields> & spFieldColl, CString & strLine);

private:
	HRESULT QuickXLate				(const CComPtr<ADODB::Field> & spField, const bool bNumeric, CString & strCsvAdd);
};

#endif // !defined(AFX_PFAARCHIVEHANDLER_H__04D3B512_16B6_470E_944A_FD5BB618111F__INCLUDED_)


/*
	Text File Data
	--------------

	Basic type will be CSV to allow editing in Excel. Would prefer XML, but not
	as easy for user to adjust.

	1. General

		a) lines beginning with '//' will be ignored, and can be used for general info as required
		b) The first cell will denote the type of CSV line it is.
			
			+---------+------------------+
			| SYMBOL  |   LINE TYPE      |
			+---------+------------------+
			| PROJECT |   Header Line    |
			+---------+------------------+
			|  STEP   |   Step Line      |
			+---------+------------------+

	2. Header Section:

	One single row consisting of comma seperated values for the list below.
		a) Line Type (PROJECT)
		b) Project Name - unique name for a project.
		c) File purpose:
				
				'Backup'	A backup of the current data for a project.

				'Backup'	A complete replacement for a particular project.
				'Restore'	Prompt to delete and recreate the project if
							it already exists.
							May be a prompt to rename / save as the existing project?
							

		d) Project ID - probably not going to use this, set to -1 to ignore it.
		e) Project Default Source Directory.
		f) Project Default Destination Directory.

	
	3. An assembly step:

	One line per data row consisting of comma seperated values for:
		a) Line Type (STEP)
		b) iStep				'n'
		c) iStepType			'n'

					typedef enum _ePFA_STEP_TYPE{
						ePST_Comment				= 0
						, ePST_CopySingleDir
						, ePST_CopyDirAndSubDirs
						, ePST_DelDestFile
						, ePST_CreateNewDir
						, ePST_CopyFile
						, ePST__LAST
					} ePFA_STEP_TYPE;

		d) szSourceFile			'file.name'
		e) szSourceDir			'drive:\folder\subfolder0'
		f) szDestDirectory		'drive:\folder\subfolder0'
		g) szDestFile			'destination.file'
		h) szCreated			'YYYY-MM-DD hh:mm:ss'
		i) szModified			'YYYY-MM-DD hh:mm:ss'
	
*/