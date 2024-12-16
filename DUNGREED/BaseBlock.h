#pragma once
#include "CObj.h"
class CBaseBlock :
    public CObj
{
public:
    CBaseBlock();
    CBaseBlock(float _fX, float _fY, float _fCX , float _fCY);
    virtual ~CBaseBlock();
public:
    INFO* Get_Info() { return &m_tInfo; }

public:
    // CObj��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
public:
    BLOCKTYPE Get_BlockType() { return m_eBlockType; }

protected:
    BLOCKTYPE m_eBlockType;
  
};

