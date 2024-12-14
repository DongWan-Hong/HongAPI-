#include "pch.h"
#include "Block_01.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"

CBlock_01::CBlock_01()
{
	m_tInfo.fCX =48.f;
	m_tInfo.fCY = 48.f;

	m_eBlockType = BLOCK1;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sprite-0001.bmp", L"Block");
}

CBlock_01::~CBlock_01()
{
}

void CBlock_01::Initialize()
{
}

void CBlock_01::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Block");

	//GdiTransparentBlt(hDC,			// ���� ���� DC
	//	m_tRect.left + iScrollX,	// ���� ���� ��ġ ��ǥ X, Y	
	//	m_tRect.top + iScrollY,
	//	(int)m_tInfo.fCX,			// ���� ���� �̹����� ����, ����
	//	(int)m_tInfo.fCY,
	//	hMemDC,						// ������ �̹��� DC
	//	(int)m_tInfo.fCX,	// 		
	//	(int)m_tInfo.fCY,
	//	48.f,			// ������ �̹����� ����, ����
	//	48.f,
	//	RGB(255, 0, 255));		// ������ ����


	BitBlt(hDC,						// ���� ���� DC
		m_tRect.left + iScrollX,	// ���� ���� ��ġ ��ǥ X, Y	
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,			// ���� ���� �̹����� ����, ����
		(int)m_tInfo.fCY,
		hMemDC,						// ������ �̹��� DC
		0.f,							// ��Ʈ�� ��� ���� ��ǥ(Left, top)
		0.f,
		SRCCOPY);					// ��� ȿ�� ����(�״�� ���)
}
