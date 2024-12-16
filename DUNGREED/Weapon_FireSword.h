#pragma once
#include "Item.h"
#include "Define.h"
#include "CBmpMgr.h"

class CWeapon_FireSword : public CItem
{
public:
    CWeapon_FireSword() { Initialize(); }
    virtual ~CWeapon_FireSword() {}

    virtual void Initialize() override
    {
        m_tInfo = { 40.f, 0.f, 30.f, 108.f }; // 아이템 크기
        ADD_BMP(L"../Image3/Weapon/Hell/HellFirePoker1.bmp", L"Bow_Icon");
    }

    virtual void Render(HDC hDC) override
    {
        HDC hItemDC = FIND_BMP(L"Bow_Icon");
        GdiTransparentBlt(hDC, (int)m_tInfo.fX+20, (int)m_tInfo.fY,
            (int)m_tInfo.fCX, (int)m_tInfo.fCY,
            hItemDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
            RGB(255, 0, 255));
    }
    virtual int Update() override { return 0; }
    virtual void Late_Update() override {}
    virtual void Release() override {}
    virtual void Equip() override
    {
        
    }


};
