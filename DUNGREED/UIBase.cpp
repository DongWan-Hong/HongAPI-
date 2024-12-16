#include "pch.h"
#include "UIBase.h"
#include "CScrollMgr.h"
#include "CSceneMgr.h"
#include "UIMgr.h"
#include "CKeyMgr.h"


CUI::CUI(bool _boffsetaff) : m_pParentUI(nullptr), m_fFinalX(0), m_fFinalY(0), m_bOffset_Affected(false), m_bMouseOn(false)
{
}

CUI::~CUI()
{
	Release();
}
void CUI::Initialize()
{

}

int CUI::Update()
{
	Update_Child();
	Update_Rect();

	return 0;
}

void CUI::Late_Update()
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();



	// UI 마우스 체크
	MouseOnCheck();

	LateUpdate_Child();


}

void CUI::Render(HDC hDC)
{

	if (m_bOffset_Affected)
	{
		int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	}

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	Render_Child(hDC);
}

void CUI::Update_Child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Update();
	}

}

void CUI::Render_Child(HDC hDC)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Render(hDC);
	}

}
void CUI::LateUpdate_Child()
{
	m_fFinalX = m_tInfo.fX;  // 자기 자신의 X 위치
	m_fFinalY = m_tInfo.fY;  // 자기 자신의 Y 위치

	
	if (m_pParentUI) // 부모가 있다면 부모의 좌표를 더해준다
	{
		m_fFinalX += m_pParentUI->m_fFinalX;  
		m_fFinalY += m_pParentUI->m_fFinalY;  
	}

	
	for (auto& child : m_vecChildUI) // 자식 UI들도 다시 업데이트!!
	{
		child->LateUpdate_Child();
	}
}
void CUI::Release()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Release();
	}

}

void CUI::MouseOnCheck()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);             // 마우스 좌표를 화면 좌표로 가져오기
	ScreenToClient(g_hWnd, &ptMouse);   // 화면 좌표를 클라이언트 좌표로 변환

	// 마우스가 UI 영역 안에 있는지 체크
	if (ptMouse.x >= m_fFinalX && ptMouse.x <= m_fFinalX + m_tInfo.fCX &&
		ptMouse.y >= m_fFinalY && ptMouse.y <= m_fFinalY + m_tInfo.fCY)
	{
		m_bMouseOn = true;  // 마우스가 UI 영역 안에 있음
	}
	else
	{
		m_bMouseOn = false; // 마우스가 UI 영역 밖에 있음
	}

	
}

void CUI::MouseOn()
{
}

void CUI::MouseLbtnDown()
{
}

void CUI::MouseLbtnUp()
{
}

void CUI::MouseLbtnClicked()
{
}



// 사용예시

//// 부모 UI 생성
//CUI* pParentUI = new CUI();
//pParentUI->Set_Pos(100, 100);  // 부모 위치 설정
//
//// 자식 UI 생성
//CUI* pChildUI1 = new CUI();
//pChildUI1->Set_Pos(50, 50);  // 부모 기준 상대 좌표
//
//CUI* pChildUI2 = new CUI();
//pChildUI2->Set_Pos(150, 150);
//
//// 부모에 자식 추가
//pParentUI->AddChild(pChildUI1);
//pParentUI->AddChild(pChildUI2);
//
//// 좌표 업데이트 및 렌더링
//pParentUI->finalupdate();
//pParentUI->Render(hDC);