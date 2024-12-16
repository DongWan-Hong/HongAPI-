#pragma once
#include "CObj.h" // ��ü �⺻ Ŭ����

class CItem : public CObj
{
public:
    CItem() { m_eOBJID = OBJ_UI; } // �⺻ ��ü ID
    virtual ~CItem() = default;   // ���� �Ҹ���

    virtual void Equip();    // ���� ��� 
    virtual void Render(HDC hDC) override ; // ������ ������ 

    bool IsEquipped() const { return m_bEquipped; }
    void SetEquipped(bool equipped) { m_bEquipped = equipped; }

protected:
    bool m_bEquipped; // ������ ���� ����
};

