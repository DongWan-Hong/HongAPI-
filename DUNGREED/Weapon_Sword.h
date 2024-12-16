#pragma once
#include "Item.h"
#include "Define.h"
#include "CBmpMgr.h"


class CWeapon_Sword : public CItem
{
public:
    CWeapon_Sword() { Initialize(); }
    virtual ~CWeapon_Sword() {}

    virtual void Initialize() override
    {
        m_tInfo = { 0.f, 0.f, 76.f, 76.f }; // ������ ũ��
        ADD_BMP(L"../Image3/Weapon/BasicShortSword.bmp", L"Sword_Icon");
    }

    virtual void Render(HDC hDC) override
    {
        HDC hItemDC = FIND_BMP(L"Sword_Icon");
        GdiTransparentBlt(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY,
            (int)m_tInfo.fCX, (int)m_tInfo.fCY,
            hItemDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
            RGB(255, 0, 255));
    }

    virtual int Update() override
    {
        // ������ ������Ʈ ���� (�ʿ�� �߰�)
        return 0;
    }

    virtual void Late_Update() override
    {
        // �ļ� ������Ʈ ���� (�ʿ�� �߰�)
    }

    virtual void Release() override
    {
        // �ڿ� ���� ���� (�ʿ�� �߰�)
    }

    virtual void Equip() override
    {
        OutputDebugString(L"�� ����!\n");
    }
};
