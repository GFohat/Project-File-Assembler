// BuildReporter.cpp: implementation of the CBuildReporter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "project file assembler.h"
#include "BuildReporter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBuildReporter::CBuildReporter()
{

}

CBuildReporter::~CBuildReporter()
{
	ExitReporting();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10/04/2007 13:23:45
	DESCRIP:	
		CFile::modeCreate		Directs the constructor to create a new file. If the file exists already, it is truncated to 0 length.
		CFile::modeNoTruncate	Combine this value with modeCreate. If the file being created already exists, it is not truncated to 0 length. Thus the file is guaranteed to open, either as a newly created file or as an existing file. This might be useful, for example, when opening a settings file that may or may not exist already. This option applies to CStdioFile as well.
		CFile::modeRead			Opens the file for reading only.
		CFile::modeReadWrite	Opens the file for reading and writing.
		CFile::modeWrite		Opens the file for writing only.
		CFile::modeNoInherit	Prevents the file from being inherited by child processes.
		CFile::shareDenyNone	Opens the file without denying other processes read or write access to the file. Create fails if the file has been opened in compatibility mode by any other process.
		CFile::shareDenyRead	Opens the file and denies other processes read access to the file. Create fails if the file has been opened in compatibility mode or for read access by any other process.
		CFile::shareDenyWrite	Opens the file and denies other processes write access to the file. Create fails if the file has been opened in compatibility mode or for write access by any other process.
		CFile::shareExclusive	Opens the file with exclusive mode, denying other processes both read and write access to the file. Construction fails if the file has been opened in any other mode for read or write access, even by the current process.
		CFile::shareCompat		This flag is not available in 32 bit MFC. This flag maps to CFile::shareExclusive when used in CFile::Open.
		CFile::typeText			Sets text mode with special processing for carriage return–linefeed pairs (used in derived classes only).
		CFile::typeBinary		Sets binary mode (used in derived classes only). 
	IN:
	OUT:
*/
bool CBuildReporter::InitReporting(const CString & strFileNAP)
{
	ExitReporting();

	DWORD dwFlags = 0
					| CFile::modeCreate
					//| CFile::modeNoTruncate
					| CFile::modeReadWrite
					| CFile::shareDenyNone
					| CFile::typeText
				;

	BOOL bOpened = m_filReport.Open(strFileNAP, dwFlags);

	return bOpened ? true : false;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10/04/2007 13:23:49
	DESCRIP:	
	IN:
	OUT:
*/
void CBuildReporter::ExitReporting(void)
{
	if(m_filReport.m_pStream){
		m_filReport.Close();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	STAMP:	10/04/2007 13:23:52
	DESCRIP:	
	IN:
	OUT:
*/
bool CBuildReporter::ReportLine(const CString & strLine)
{
	bool bOK = false;

	if(m_filReport.m_pStream){

		try{
			m_filReport.WriteString(strLine);
			bOK = true;
		}
		//----------------------------------------------------------
		catch(CFileException * pe){
			pe->Delete();
		}

	}

	return bOK;
}
