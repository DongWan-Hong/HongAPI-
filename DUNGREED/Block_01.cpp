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

	//GdiTransparentBlt(hDC,			// 복사 받을 DC
	//	m_tRect.left + iScrollX,	// 복사 받을 위치 좌표 X, Y	
	//	m_tRect.top + iScrollY,
	//	(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
	//	(int)m_tInfo.fCY,
	//	hMemDC,						// 복사할 이미지 DC
	//	(int)m_tInfo.fCX,	// 		
	//	(int)m_tInfo.fCY,
	//	48.f,			// 복사할 이미지의 가로, 세로
	//	48.f,
	//	RGB(255, 0, 255));		// 제거할 색상


	BitBlt(hDC,						// 복사 받을 DC
		m_tRect.left + iScrollX,	// 복사 받을 위치 좌표 X, Y	
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
		(int)m_tInfo.fCY,
		hMemDC,						// 복사할 이미지 DC
		0.f,							// 비트맵 출력 시작 좌표(Left, top)
		0.f,
		SRCCOPY);					// 출력 효과 설정(그대로 출력)
}
