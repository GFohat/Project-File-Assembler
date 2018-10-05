#pragma once

typedef enum _META_TYPE{
	eMeta_FileVersion		= 0
	, eMeta_ProductVersion
	, eMeta_Signature		
	, eMeta_StrucVersion		
	, eMeta_FileFlagsMask	
	, eMeta_FileFlags		
	, eMeta_FileOS			
	, eMeta_FileType			
	, eMeta_FileSubtype		
	, eMeta_FileDate
	, eMeta__LAST
} eMETA_TYPE;

class CFixedFileInfo
{
public:
	CFixedFileInfo(void);
	~CFixedFileInfo(void);

public:
	const CFixedFileInfo & operator = (const VS_FIXEDFILEINFO & ffinfo);
	//void operator >> (VS_FIXEDFILEINFO & ffinfo) const;

	inline const VS_FIXEDFILEINFO & GetFFInfo(void) const { return m_fixedfileinfo; }

public:
	eCMP_RSLT CompareFFInfo(const CFixedFileInfo & rCmp) const;

public:
	//void SetFileVersion		(const WORD wdHH, const WORD wdHL, const WORD wdLH, const WORD wdLL);
	//void SetProductVersion	(const WORD wdHH, const WORD wdHL, const WORD wdLH, const WORD wdLL);

public:
	CString GetFileMetaData		(const eMETA_TYPE eType) const;

	CString GetFileVersion		(void) const;
	CString GetProductVersion	(void) const;


public:
	CString GetSignature		(void) const;	/* e.g. 0xfeef04bd */
	CString GetStrucVersion		(void) const;	/* e.g. 0x00000042 = "0.42" */
	CString GetFileFlagsMask	(void) const;	/* = 0x3F for version "0.42" */
	CString GetFileFlags		(void) const;	/* e.g. VFF_DEBUG | VFF_PRERELEASE */
	CString GetFileOS			(void) const;	/* e.g. VOS_DOS_WINDOWS16 */
	CString GetFileType			(void) const;	/* e.g. VFT_DRIVER */
	CString GetFileSubtype		(void) const;	/* e.g. VFT2_DRV_KEYBOARD */
	CString GetFileDate			(void) const;	/* e.g. 0 */

public:
	//void SetFixedFileInfo(VS_FIXEDFILEINFO & ffinfo, const DWORD dwMetaType) const;
	bool SetEditEnable(const DWORD dwMetaType, const bool bEnable);
	void ResetEnables(const bool bEnable);

private:
	bool m_bDataValid;
	VS_FIXEDFILEINFO m_fixedfileinfo;

	bool m_bsEnableEditMetaData[eMeta__LAST];
};

//typedef struct tagVS_FIXEDFILEINFO
//{
//    DWORD   dwSignature;            /* e.g. 0xfeef04bd */
//    DWORD   dwStrucVersion;         /* e.g. 0x0000 0042 = "0.42" */
//    DWORD   dwFileVersionMS;        /* e.g. 0x0003 0075 = "3.75" */
//    DWORD   dwFileVersionLS;        /* e.g. 0x0000 0031 = "0.31" */
//    DWORD   dwProductVersionMS;     /* e.g. 0x0003 0010 = "3.10" */
//    DWORD   dwProductVersionLS;     /* e.g. 0x0000 0031 = "0.31" */
//    DWORD   dwFileFlagsMask;        /* = 0x3F for version "0.42" */
//    DWORD   dwFileFlags;            /* e.g. VFF_DEBUG | VFF_PRERELEASE */
//    DWORD   dwFileOS;               /* e.g. VOS_DOS_WINDOWS16 */
//    DWORD   dwFileType;             /* e.g. VFT_DRIVER */
//    DWORD   dwFileSubtype;          /* e.g. VFT2_DRV_KEYBOARD */
//    DWORD   dwFileDateMS;           /* e.g. 0 */
//    DWORD   dwFileDateLS;           /* e.g. 0 */
//} VS_FIXEDFILEINFO;
