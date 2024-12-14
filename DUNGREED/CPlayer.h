#pragma once
#include "CObj.h"
#include "CShield.h"
#include "CScrewBullet.h"
#include "CGuideBullet.h"

class CPlayer :    public CObj
{
public:
    enum STATE { IDLE, WALK, ATTACK, HIT, DEAD, END };

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
  
    
    virtual void OnCollision(CObj* _op);

private:
    void        Key_Input();
    void        Jumping();
    void        Offset();
    

    CObj*       Create_Shield();
    void        Change_Motion();

 

private:
    POINT               m_tPosin;

    bool                m_bJump;

    float               m_fJumpPower;
    float               m_fTime;

    STATE               m_eCurState;
    STATE               m_ePreState;

    float m_fGravity;
    
    float m_fGt;

};

