#pragma once
#include "CObj.h"
#include "CScrollMgr.h"

class CItem : public CObj
{
public:
    CItem()
        :m_bEquipped(false)
    { m_eOBJID = OBJ_UI; }
    
    virtual ~CItem() = default;

    // ��ũ�� �������� �ݿ��� Set_Pos �Լ�
    void Set_Pos_With_Scroll(float _fX, float _fY)
    {
        float iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
        float iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

        m_tInfo.fX = _fX - iScrollX; // ��ũ�� �ݿ�
        m_tInfo.fY = _fY - iScrollY; // ��ũ�� �ݿ�
    }

    virtual void Equip() {}
    virtual void Render(HDC hDC) override {}
    virtual void Render(HDC hDC, int renderX, int renderY);
    bool IsEquipped() const { return m_bEquipped; }
    void SetEquipped(bool equipped) { m_bEquipped = equipped; }

protected:
    bool m_bEquipped; // ������ ���� ����
};
