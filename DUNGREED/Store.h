#pragma once
#include "CPlayer.h"
#include "Inven.h"
#include "Define.h"

class CStore
{
public:
	CStore();
	~CStore();

public:
	void		Set_Player(CObj* pPlayer) { m_pCopyPlayer = pPlayer; }
	void		Set_Inven(CInven* pInven) { m_pInven = pInven; }
public:
	void Initialize();
	void Update();
	void Render(ITEMTYPE eType);
	void Release();

private:
	void		Buy_Item(CObj* pItem);
	void		Sell_Item();


private:
	CObj* m_pCopyPlayer;
	CInven* m_pInven;
	vector<CObj*>		m_vecItem[IT_END];

};

