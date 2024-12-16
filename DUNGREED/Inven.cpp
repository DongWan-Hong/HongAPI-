#include "pch.h"
#include "Inven.h"
CInven::CInven()
    :m_pInven_Player(nullptr), m_iSize(15),CUI(false)
{
    m_vecInven.reserve(m_iSize);
}

CInven::~CInven()
{
}

void CInven::Initialize()
{
}

int CInven::Update()
{
    return 0;
}

void CInven::Render()
{
}

void CInven::Release()
{
}

bool CInven::Buy_Item(CObj* _pItem)
{
    return false;
}

bool CInven::Sell_Item(int iInput, int* pMoney)
{
    return false;
}

void CInven::Equip_Item()
{
}

void CInven::Unequip_Item()
{
}
