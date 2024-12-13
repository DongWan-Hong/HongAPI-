#pragma once

#include "CObj.h"

class CMouse : public CObj
{
public:
	CMouse();
	virtual ~CMouse();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;


private:

	TCHAR		m_Mouse[16];
	int			m_MouseX;
	int         m_MouseY;
	ULONGLONG m_dwTime;

	POINT       ptMouse;

};

