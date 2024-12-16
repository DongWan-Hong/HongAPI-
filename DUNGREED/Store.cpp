#include "pch.h"
#include "Store.h"
#include "Item.h"

CStore::CStore() : m_pCopyPlayer(nullptr), m_pInven(nullptr)
{
	m_vecItem[IT_WEAPON].reserve(3);
	m_vecItem[IT_SHIELD].reserve(3);
}

CStore::~CStore()
{
	Release();
}

void CStore::Initialize()
{
	
}

void CStore::Update()
{
	int iInput(0);



}

void CStore::Render(ITEMTYPE eType)
{

	
}

void CStore::Release()
{
	for (size_t i = 0; i < IT_END; ++i)
	{
		for_each(m_vecItem[i].begin(), m_vecItem[i].end(), Safe_Delete<CObj*>);
		m_vecItem[i].clear();
	}

}

void CStore::Buy_Item(CObj* pItem)
{
	

}

void CStore::Sell_Item()
{
	

}
