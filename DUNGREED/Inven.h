#pragma once

#include "UIBase.h"
#include "Item.h"

class CInven {
public:
    CInven();
    ~CInven();

    SINGLE(CInven); // 새 매크로를 적용

public:
    void AddItem(CObj* pItem);  // 아이템 추가
    void RemoveItem(CObj* pItem); // 아이템 제거
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

    DWORD m_lastClickTime = 0; // 마지막 클릭 시간
    const DWORD m_doubleClickInterval = 1000; // 1초 (1000 밀리초)
};
