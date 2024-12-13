#include "pch.h"
#include "CMouse.h"
#include "CBmpMgr.h"


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
	m_tInfo.fCX = 63.f;
	m_tInfo.fCY = 63.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image2/UI/ShootingCursor2.bmp", L"Cross_Hair");
}

int CMouse::Update()
{
	

	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);



    
	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;


	__super::Update_Rect();

	//ShowCursor(FALSE);

	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
}

void CMouse::Render(HDC hDC)
{


	HDC		hCursor = CBmpMgr::Get_Instance()->Find_Image(L"Cross_Hair");

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hCursor,
		63, 63,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));





	TCHAR szBuffer[64];
	_stprintf_s(szBuffer, _T("Mouse: X=%d, Y=%d"), ptMouse.x, ptMouse.y);
	TextOut(hDC, 10, 10, szBuffer, _tcslen(szBuffer));

}


void CMouse::Release()
{
}
