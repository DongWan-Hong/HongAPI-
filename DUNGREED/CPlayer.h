#pragma once
#include "CObj.h"
#include "Different.h"
#include "Item.h"
#include "Define.h"

class CPlayer :    public CObj
{
public:
    enum STATE { IDLE, DOUBLEJUMP, WALK,EffECT, DASH,ATTACK, HIT, DEAD, END };

public:
    CPlayer();
    virtual ~CPlayer();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    void Set_Jump()
    {
        m_bJump = false;
    }
    float Get_Grivity()
        {
        return m_fGravity;
        }
    bool Get_InvenCheck() // ���콺 Ŀ�� �ٲٷ���
    {
        return m_bInven;
    }
    static bool m_bInven;
    virtual void OnCollision(CObj* _op);

private:
    void        Key_Input();
 
    void        Jumping();
    void PerformDash();
    void StartDash(float targetX, float targetY);
    void        Offset();
    

    CObj*       Create_Shield();
    void        Change_Motion();
   
public:

    void OpenInventory();   // �κ��丮 ����/�ݱ� �Լ� �߰�
    void AddItemToInventory(CObj* item); // ������ �߰� �Լ�
    void EquipItemFromInventory();       // �κ��丮���� ������ ����
    void UnequipItemToInventory();
    void Equip(CItem* pItem);
    CItem* UnEquip();
    CItem* GetEquip_Item()
    {
        return m_pEquippedItem;
    }
    CItem* GetEquippedItem()
    {
        return m_pEquippedItem;
    }

    CItem* m_pEquippedItem; // ������ ������
private:
    POINT               m_tPosin;

    bool                m_bJump;

    float               m_fJumpPower;
    float               m_fTime;

    STATE               m_eCurState;
    STATE               m_ePreState;

    float m_fGravity;
    bool m_bDefatule_IDle;
    //bool m_bDoubleJump;

private:
    bool m_bDashing;       // �뽬 ������ ����
    float m_fDash_Mouse_X;  // �뽬 ��ǥ ���� X
    float m_fDash_Mouse_Y;  // �뽬 ��ǥ ���� Y
    float m_fDashSpeed;    // �뽬 �ӵ�

    float m_fFixScrollSpeedX; // �뽬�ӵ��� �������� ����
    float m_fFixScrollSpeedY;

    vector<Trail> m_vTrails;

   
  
};

