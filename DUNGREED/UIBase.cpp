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



	// UI ���콺 üũ
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
	m_fFinalX = m_tInfo.fX;  // �ڱ� �ڽ��� X ��ġ
	m_fFinalY = m_tInfo.fY;  // �ڱ� �ڽ��� Y ��ġ

	
	if (m_pParentUI) // �θ� �ִٸ� �θ��� ��ǥ�� �����ش�
	{
		m_fFinalX += m_pParentUI->m_fFinalX;  
		m_fFinalY += m_pParentUI->m_fFinalY;  
	}

	
	for (auto& child : m_vecChildUI) // �ڽ� UI�鵵 �ٽ� ������Ʈ!!
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
	GetCursorPos(&ptMouse);             // ���콺 ��ǥ�� ȭ�� ��ǥ�� ��������
	ScreenToClient(g_hWnd, &ptMouse);   // ȭ�� ��ǥ�� Ŭ���̾�Ʈ ��ǥ�� ��ȯ

	// ���콺�� UI ���� �ȿ� �ִ��� üũ
	if (ptMouse.x >= m_fFinalX && ptMouse.x <= m_fFinalX + m_tInfo.fCX &&
		ptMouse.y >= m_fFinalY && ptMouse.y <= m_fFinalY + m_tInfo.fCY)
	{
		m_bMouseOn = true;  // ���콺�� UI ���� �ȿ� ����
	}
	else
	{
		m_bMouseOn = false; // ���콺�� UI ���� �ۿ� ����
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



// ��뿹��

//// �θ� UI ����
//CUI* pParentUI = new CUI();
//pParentUI->Set_Pos(100, 100);  // �θ� ��ġ ����
//
//// �ڽ� UI ����
//CUI* pChildUI1 = new CUI();
//pChildUI1->Set_Pos(50, 50);  // �θ� ���� ��� ��ǥ
//
//CUI* pChildUI2 = new CUI();
//pChildUI2->Set_Pos(150, 150);
//
//// �θ� �ڽ� �߰�
//pParentUI->AddChild(pChildUI1);
//pParentUI->AddChild(pChildUI2);
//
//// ��ǥ ������Ʈ �� ������
//pParentUI->finalupdate();
//pParentUI->Render(hDC);