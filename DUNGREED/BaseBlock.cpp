#include "pch.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"
#include "BaseBlock.h"


CBaseBlock::CBaseBlock()
    
{
    ZeroMemory(&m_eBlockType, sizeof(m_eBlockType));
}

CBaseBlock::CBaseBlock(float _fX, float _fY, float _fCX, float _fCY)
{
    ZeroMemory(&m_eBlockType, sizeof(m_eBlockType));
    Set_Pos(_fX, _fX);
    Set_Size(_fCX, _fCY);
}

CBaseBlock::~CBaseBlock()
{
}

void CBaseBlock::Initialize()
{
    m_tInfo.fCX = 50.f;
    m_tInfo.fCY = 50.f;

    m_eOBJID = OBJ_BLOCK;

    
}

int CBaseBlock::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CBaseBlock::Late_Update()
{
}

void CBaseBlock::Render(HDC hDC)
{
    int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    Rectangle(hDC,
        m_tRect.left + iScrollX,   // 왼쪽 위 X 좌표
        m_tRect.top + iScrollY,    // 왼쪽 위 Y 좌표
        m_tRect.right + iScrollX,  // 오른쪽 아래 X 좌표
        m_tRect.bottom + iScrollY);  // 오른쪽 아래 Y 좌표
    
}


void CBaseBlock::Release()
{
}
