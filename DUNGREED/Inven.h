#pragma once
#include "CPlayer.h"
#include "UIBase.h"

class CInven : public CUI
{
public:
	CInven();
	~CInven();

public:
	void		Set_Player(CObj* pPlayer) { m_pInven_Player = pPlayer; }

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	bool	Buy_Item(CObj* _pItem);
	bool	Sell_Item(int iInput, int* pMoney);

	void	Equip_Item();
	void	Unequip_Item();


private:
	CObj* m_pInven_Player;
	vector<CObj*>		m_vecInven;
	int	m_iSize; // ���׸���� �ִ� 15��

};

