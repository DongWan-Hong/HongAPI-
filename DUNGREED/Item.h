#pragma once
#include "CObj.h" // 객체 기본 클래스

class CItem : public CObj
{
public:
    CItem() { m_eOBJID = OBJ_UI; } // 기본 객체 ID
    virtual ~CItem() = default;   // 가상 소멸자

    virtual void Equip();    // 장착 기능 
    virtual void Render(HDC hDC) override ; // 아이템 렌더링 

    bool IsEquipped() const { return m_bEquipped; }
    void SetEquipped(bool equipped) { m_bEquipped = equipped; }

protected:
    bool m_bEquipped; // 아이템 장착 상태
};

