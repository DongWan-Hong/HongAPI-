#pragma once

#include "UIBase.h"
#include "Item.h"

class CInven {
public:
    CInven();
    ~CInven();

    SINGLE(CInven); // �� ��ũ�θ� ����

public:
    void AddItem(CObj* pItem);  // ������ �߰�
    void RemoveItem(CObj* pItem); // ������ ����
public:
    void Set_Player(CObj* pPlayer) { m_pInven_Player = pPlayer; }
    void Initialize();
    int Update();
    void Render(HDC hDC);
    void Release();

    void Equip_Item();
    void Unequip_Item();

    void ToggleEquip(CItem* pItem);

private:
    CObj* m_pInven_Player;
    vector<CObj*> m_vecInven;
    int m_iSize;
private:

    DWORD m_lastClickTime = 0; // ������ Ŭ�� �ð�
    const DWORD m_doubleClickInterval = 1000; // 1�� (1000 �и���)
};
