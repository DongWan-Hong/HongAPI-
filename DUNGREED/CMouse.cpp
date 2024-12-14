#include "pch.h"
#include "CMouse.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"


CMouse::CMouse()
{
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

	HDC hCursor = CBmpMgr::Get_Instance()->Find_Image(L"Cross_Hair");

	GdiTransparentBlt(hDC,
		(int)m_tInfo.fX - (int)m_tInfo.fCX / 2,
		(int)m_tInfo.fY - (int)m_tInfo.fCY / 2,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hCursor,
		0, 0,  
		48.f, 48.f,  
		RGB(255, 0, 255));  


	TCHAR szBuffer[64];
	_stprintf_s(szBuffer, _T("Mouse: X=%d, Y=%d"), (int)m_tInfo.fX- iScrollX, (int)m_tInfo.fY- iScrollY);


	SetTextColor(hDC, RGB(255, 255, 255)); 
	SetBkMode(hDC, TRANSPARENT);          
	TextOut(hDC, 10, 10, szBuffer, _tcslen(szBuffer)); 
}



void CMouse::Release()
{
}
