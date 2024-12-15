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
	m_vecItem[IT_WEAPON].push_back(new CItem("�ʱް�", 0, 10, 1000));
	dynamic_cast<CItem*>(m_vecItem[IT_WEAPON].back())->Set_ItemType(IT_WEAPON);

	m_vecItem[IT_WEAPON].push_back(new CItem("�߱ް�", 0, 20, 2000));
	dynamic_cast<CItem*>(m_vecItem[IT_WEAPON].back())->Set_ItemType(IT_WEAPON);

	m_vecItem[IT_WEAPON].push_back(new CItem("��ް�", 0, 30, 3000));
	dynamic_cast<CItem*>(m_vecItem[IT_WEAPON].back())->Set_ItemType(IT_WEAPON);

	m_vecItem[IT_SHIELD].push_back(new CItem("�ʱ޿�", 10, 0, 1000));
	dynamic_cast<CItem*>(m_vecItem[IT_SHIELD].back())->Set_ItemType(IT_SHIELD);

	m_vecItem[IT_SHIELD].push_back(new CItem("�߱޿�", 20, 0, 2000));
	dynamic_cast<CItem*>(m_vecItem[IT_SHIELD].back())->Set_ItemType(IT_SHIELD);

	m_vecItem[IT_SHIELD].push_back(new CItem("��޿�", 30, 0, 3000));
	dynamic_cast<CItem*>(m_vecItem[IT_SHIELD].back())->Set_ItemType(IT_SHIELD);
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
