#pragma once

class CFontHandler
{
public:
	CFontHandler(void);
	~CFontHandler(void);

public:
	void InitFont(
				CDC * pdc
				, const int iPoints
				, const int iWeight
				, const CString & strFace
			);

	void ExitFont(void);

	inline CFont * GetFont(void) { return &m_font; }

private:
	CFont m_font;
};
