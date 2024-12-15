#pragma once

#include "CObj.h"

class CItem : public CObj
{
public:
	CItem();
	CItem(const char* pName, int _iHp, int _iAttack, int _iMoney = 1000);
	virtual ~CItem();

public:
	void			Set_ItemType(ITEMTYPE eType) { m_eType = eType; }
	void			Set_EquipState(STATE eState) { m_eState = eState; }

public:
	ITEMTYPE		Get_ItemType() { return m_eType; }
	STATE			Get_EquipState() { return m_eState; }

	ITEMTYPE		m_eType;
	STATE			m_eState;

	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};


