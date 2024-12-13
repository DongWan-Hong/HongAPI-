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
    m_tInfo.fCX = 192.f;
    m_tInfo.fCY = 64.f;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image3/Town/MiddleFloor_Short.bmp", L"Block");
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
    int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Block");

    //BitBlt(hDC,						// ���� ���� DC
    //    m_tRect.left + iScrollX,	// ���� ���� ��ġ ��ǥ X, Y	
    //    m_tRect.top+ iScrollY,
    //    (int)m_tInfo.fCX,			// ���� ���� �̹����� ����, ����
    //    (int)m_tInfo.fCY,
    //    hMemDC,						// ������ �̹��� DC
    //    0,							// ��Ʈ�� ��� ���� ��ǥ(Left, top)
    //    0,
    //    SRCCOPY);					// ��� ȿ�� ����(�״�� ���)

    GdiTransparentBlt(hDC,
        m_tRect.left + iScrollX,
        m_tRect.top + iScrollY,
        (int)m_tInfo.fCX,			 // �޾ƿ� �̹��� ��� �Ҳ���
        (int)m_tInfo.fCY,
        hMemDC,
        0,			  // �̹��� ��ǥ
        0,
        (int)m_tInfo.fCX,			// ������ �̹����� ����, ����
        (int)m_tInfo.fCY,
        RGB(255, 0, 255));
}

void CBlock::Release()
{
}
