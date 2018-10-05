#pragma once

//#include >localprops.h>

class CLocalProps
{
public:
	CLocalProps(void);
	~CLocalProps(void);

public:
	CString GetMachineName		(void) const;
	CString GetUserName			(void) const;
	CString GetUserAtMachine	(void) const;
};
