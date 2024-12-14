#include "pch.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"
#include "Block.h"


CBlock::CBlock()
    
{
    ZeroMemory(&m_eBlockType, sizeof(m_eBlockType));
}

CBlock::CBlock(float _fX, float _fY, float _fCX, float _fCY)
{
    ZeroMemory(&m_eBlockType, sizeof(m_eBlockType));
    Set_Pos(_fX, _fX);
    Set_Size(_fCX, _fCY);
}

CBlock::~CBlock()
{
}

void CBlock::Initialize()
{
    m_tInfo.fCX = 50.f;
    m_tInfo.fCY = 50.f;

    m_eOBJID = OBJ_BLOCK;

    
}

int CBlock::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CBlock::Late_Update()
{
}

void CBlock::Render(HDC hDC)
{
    int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    Rectangle(hDC,
        m_tRect.left + iScrollX,   // 왼쪽 위 X 좌표
        m_tRect.top + iScrollY,    // 왼쪽 위 Y 좌표
        m_tRect.right + iScrollX,  // 오른쪽 아래 X 좌표
        m_tRect.bottom + iScrollY);  // 오른쪽 아래 Y 좌표
    
}


void CBlock::Release()
{
}
