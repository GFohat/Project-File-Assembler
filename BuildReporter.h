// BuildReporter.h: interface for the CBuildReporter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUILDREPORTER_H__E8EFAC32_B87C_4DD5_BEEB_011DCB90E0A3__INCLUDED_)
#define AFX_BUILDREPORTER_H__E8EFAC32_B87C_4DD5_BEEB_011DCB90E0A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBuildReporter  
{
public:
	CBuildReporter();
	virtual ~CBuildReporter();

public:
	bool InitReporting(const CString & strFileNAP);
	void ExitReporting(void);

public:
	bool ReportLine(const CString & strLine);

private:
	CStdioFile m_filReport;
};

#endif // !defined(AFX_BUILDREPORTER_H__E8EFAC32_B87C_4DD5_BEEB_011DCB90E0A3__INCLUDED_)
