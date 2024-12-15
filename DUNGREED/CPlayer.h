#pragma once
#include "CObj.h"
#include "Different.h"


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
  
    
    virtual void OnCollision(CObj* _op);

private:
    void        Key_Input();
 
    void        Jumping();
    void PerformDash();
    void StartDash(float targetX, float targetY);
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
    bool m_bDefatule_IDle;
    bool m_bDoubleJump;
 
private:
    bool m_bDashing;       // 대쉬 중인지 여부
    float m_fDash_Mouse_X;  // 대쉬 목표 지점 X
    float m_fDash_Mouse_Y;  // 대쉬 목표 지점 Y
    float m_fDashSpeed;    // 대쉬 속도

    float m_fFixScrollSpeedX; // 대쉬속도를 감당해줄 변수
    float m_fFixScrollSpeedY;

    vector<Trail> m_vTrails;

};

