#pragma once

#include "Define.h"
#include "CObj.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void		Initialize()	PURE;
	virtual int			Update()		PURE;
	virtual void		Late_Update()	PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release()		PURE;

	void Add_UI(CObj* pUI)
	{
		m_vecUI.push_back(pUI);
	}

	const std::vector<CObj*>& Get_UI_Group() const
	{
		return m_vecUI;
	}
protected:

	vector<CObj*> m_vecUI;


};

