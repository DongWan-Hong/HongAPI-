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

    // 스크롤 오프셋을 반영한 Set_Pos 함수
    void Set_Pos_With_Scroll(float _fX, float _fY)
    {
        float iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
        float iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

        m_tInfo.fX = _fX - iScrollX; // 스크롤 반영
        m_tInfo.fY = _fY - iScrollY; // 스크롤 반영
    }

    virtual void Equip() {}
    virtual void Render(HDC hDC) override {}
    virtual void Render(HDC hDC, int renderX, int renderY);
    bool IsEquipped() const { return m_bEquipped; }
    void SetEquipped(bool equipped) { m_bEquipped = equipped; }

protected:
    bool m_bEquipped; // 아이템 장착 상태
};
