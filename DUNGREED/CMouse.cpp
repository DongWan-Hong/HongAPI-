#include "pch.h"
#include "CMouse.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CPlayer.h"


CMouse::CMouse()
{
	ZeroMemory(&m_Mouse, sizeof(m_Mouse));
	ptMouse={};
	m_MouseX = 0;
	m_MouseY = 0;
	m_dwTime = 0;
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 48.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image3/Cursor/ShootingCursor_1.bmp", L"Cross_Hair");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image3/Cursor/BasicCursor1.bmp", L"Default_Cursor");

	ShowCursor(FALSE);  // Ä¿¼­¸¦ ¼û±è
}

int CMouse::Update()
{
	GetCursorPos(&ptMouse);  
	ScreenToClient(g_hWnd, &ptMouse);  

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}


void CMouse::Late_Update()
{
}

void CMouse::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	

	if (CPlayer::m_bInven == false)
	{
		HDC hCross = CBmpMgr::Get_Instance()->Find_Image(L"Cross_Hair");
		GdiTransparentBlt(hDC,
			(int)m_tInfo.fX - (int)m_tInfo.fCX / 2,
			(int)m_tInfo.fY - (int)m_tInfo.fCY / 2,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hCross,
			0, 0,
			(int)48.f, (int)48.f,
			RGB(255, 0, 255));
	}
	if (CPlayer::m_bInven == true)
	{
		HDC hCursor = CBmpMgr::Get_Instance()->Find_Image(L"Default_Cursor");
		GdiTransparentBlt(hDC,
			(int)m_tInfo.fX - (int)m_tInfo.fCX / 2,
			(int)m_tInfo.fY - (int)m_tInfo.fCY / 2,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hCursor,
			0, 0,
			(int)76.f, (int)76.f,
			RGB(255, 0, 255));
	}


	TCHAR szBuffer[64];
	_stprintf_s(szBuffer, _T("Mouse: X=%d, Y=%d"), (int)m_tInfo.fX- iScrollX, (int)m_tInfo.fY- iScrollY);


	SetTextColor(hDC, RGB(255, 255, 255)); 
	SetBkMode(hDC, TRANSPARENT);          
	TextOut(hDC, 10, 10, szBuffer, (int)_tcslen(szBuffer)); 
}



void CMouse::Release()
{
}
