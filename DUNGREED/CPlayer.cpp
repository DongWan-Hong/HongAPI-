#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CKeyMgr.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"

CPlayer::CPlayer()
	: m_bJump(false), m_fJumpPower(0.f), m_fTime(0.f),m_bDefatule_IDle(true), m_bDoubleJump(0)

{
	m_fGravity = 0.f;
	ZeroMemory(&m_tPosin, sizeof(POINT));
	ZeroMemory(&m_eCurState,sizeof(STATE));
	ZeroMemory(&m_ePreState,sizeof(STATE));
	m_bDashing = false;      
	m_fDash_Mouse_X = 0.f;
	m_fDash_Mouse_Y = 0.f;
	m_fDashSpeed = 30.f;     // �뽬 �ӵ�
	m_fFixScrollSpeedX = 30.f;
	m_fFixScrollSpeedY = 30.f;
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { 200.f,1100.f, 102.8f, 100.f }; // �÷��̾� ũ��
	m_fSpeed = 5.f; // �÷��̾� �ӵ�
	m_fDistance = 100.f; // 
	m_eOBJID = OBJ_PLAYER; // �÷��̾� ��Ī ���ݸ��� ����
	m_fJumpPower = 20.f; // �����Ŀ�


	ADD_BMP(L"../Image2/Player/baseCharIdle3.bmp", L"Player_IDLE_Right"); 
	ADD_BMP(L"../Image2/Player/baseCharIdleLeft3.bmp", L"Player_IDLE_Left"); 
	ADD_BMP(L"../Image2/Player/baseCharRun2.bmp", L"Player_Right"); 
	ADD_BMP(L"../Image2/Player/Dir/Left2.bmp", L"Player_Left"); 
	ADD_BMP(L"../Image2/Player/RunEffect2.bmp", L"Run_Effect"); 

	ADD_BMP(L"../Image2/Player/RunEffect2.bmp", L"")

	m_pImgKey = L"Player_IDLE_Right";  // �⺻ ���´� ������
	m_eCurState = IDLE;
	m_ePreState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 80; 
	m_tFrame.dwTime = GetTickCount64();
}




int CPlayer::Update()
{
	

	if (m_bDashing)
	{
		PerformDash(); // �뽬 �϶� �뽬 �Լ� ����
	}

	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (ptMouse.x > m_tInfo.fX) //  ���콺�� ���� ���⿡ ���� �¿� Ȯ��
		m_pImgKey = L"Player_IDLE_Right";
	else
		m_pImgKey = L"Player_IDLE_Left";

	Key_Input();
	Change_Motion();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}


void CPlayer::Late_Update()
{
	Jumping();
	Offset();

	__super::Move_Frame();
}


void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

	GdiTransparentBlt(hDC,			
		m_tRect.left + iScrollX,	// ���� ���� ��ġ ��ǥ X, Y	
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,			// ������ �̹��� ũ�� ����Ҳ���
		(int)m_tInfo.fCY,
		hMemDC,						
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,	// 		
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		102.8,			// ���� ũ�� �����ְ�
		100.f,
		RGB(255, 0, 255));		

	if (m_pImgKey == (L"Player_Right") || m_pImgKey == (L"Player_Left") && m_bJump == false)
	{

		HDC hEffectDC = CBmpMgr::Get_Instance()->Find_Image(L"Run_Effect");

		GdiTransparentBlt(hDC,
			(int)m_tInfo.fX + iScrollX - 50,
			(int)m_tInfo.fY + iScrollY,
			80, 80,  // ȿ�� ũ��
			hEffectDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			64, 64,
			RGB(255, 0, 255));
	}

	TCHAR szBuffer[128];
	_stprintf_s(szBuffer, _T("Jump: %d, Dash: %d"), m_bJump, m_bDoubleJump); // ���� ���� Ȯ�� ���߿� �������� �ٲܲ���

	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 100, 100, szBuffer, _tcslen(szBuffer));

	TCHAR szBuffer2[64];
	_stprintf_s(szBuffer2, _T("Plyer: X=%d, Y=%d"), (int)m_tInfo.fX - iScrollX, (int)m_tInfo.fY - iScrollY);


	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 200, 10, szBuffer2, _tcslen(szBuffer2));
}

void CPlayer::Release()
{
}


//(���ǽ�) ? ���� �� �� : ������ �� ��;
void CPlayer::Key_Input()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	bool bMouseRight = (ptMouse.x - iScrollX > m_tInfo.fX);

	m_pImgKey = bMouseRight ? L"Player_IDLE_Right" : L"Player_IDLE_Left";

	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		m_tInfo.fX -= m_fSpeed;
		m_eCurState = WALK;
		m_pImgKey = bMouseRight ? L"Player_Right" : L"Player_Left";
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		m_tInfo.fX += m_fSpeed;
		m_eCurState = WALK;
		m_pImgKey = bMouseRight ? L"Player_Right" : L"Player_Left";
	}
	if (CKeyMgr::Get_Instance()->Key_Up('A') || CKeyMgr::Get_Instance()->Key_Up('D'))
	{
		m_pImgKey = bMouseRight ? L"Player_IDLE_Right" : L"Player_IDLE_Left";
		m_eCurState = IDLE;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if (!m_bJump && !m_bDashing) // �뽬 ���� �ƴ� ���� ���� ����
		{
			m_bJump = true;
			m_tInfo.fY -= m_fJumpPower;
		}
	}

	if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) && !m_bDashing) // ���콺 ��Ŭ������ �뽬
	{
		StartDash(ptMouse.x - iScrollX, ptMouse.y - iScrollY);
		m_bJump = false;
	}
}


void CPlayer::StartDash(float targetX, float targetY) // ���콺 ��ġ�� �뽬 ��������
{
	m_bDashing = true;      
	m_fDash_Mouse_X = targetX;
	m_fDash_Mouse_Y = targetY;
}

void CPlayer::PerformDash()
{
	// ���콺�� �÷��̾��� �Ÿ� ���ϱ�!
	float fDistanceX = m_fDash_Mouse_X - m_tInfo.fX;
	float fDistanceY = m_fDash_Mouse_Y - m_tInfo.fY;

	// �÷��̾ �뽬�����Ѱ��� ���Ǵ� ������ ����
	if (fabs(fDistanceX) <= m_fDashSpeed && fabs(fDistanceY) <= m_fDashSpeed)
	{
		m_tInfo.fX = m_fDash_Mouse_X;
		m_tInfo.fY = m_fDash_Mouse_Y;
		m_bDashing = false;
		return;
	}

	// �ִ� �뽬 �Ÿ� ����
	const float fMaxDashDistance = 200.0f; // �ִ� �뽬 ���� �Ÿ�

	float fTargetDistance = sqrt(fDistanceX * fDistanceX + fDistanceY * fDistanceY); // �ߵ���󽺷� �Ÿ� ���ϱ�

	if (fTargetDistance > fMaxDashDistance) // 
	{
		// ���� �Ÿ��� �ִ� �뽬 �Ÿ����� Ŭ ��� !!!!!
		float ratio = fMaxDashDistance / fTargetDistance; // Ÿ�ٰ� �Ÿ����� �ִ� �Ÿ���
		fDistanceX *= ratio;
		fDistanceY *= ratio;
		m_fDash_Mouse_X = m_tInfo.fX + fDistanceX;
		m_fDash_Mouse_Y = m_tInfo.fY + fDistanceY;
	}

	//  �̵� ���� ���
	float fTotalDistance = abs(fDistanceX) + abs(fDistanceY); // ��ü �Ÿ� ��� (X + Y)
	float ratioX = fDistanceX / fTotalDistance; // X�� �̵� ����
	float ratioY = fDistanceY / fTotalDistance; // Y�� �̵� ����

	// �뽬 �ӵ��ذ���ŭ�̵���Ű��  // ���Ⱑ ��ǻ� �밢�� �̱��� 
	m_tInfo.fX += ratioX * m_fDashSpeed;
	m_tInfo.fY += ratioY * m_fDashSpeed;

	// �뽬 �߿��� �߷¾ȹްԲ�!! ( �̰� ������ �ó�� �־���..)
	m_fGravity = 0.f;
	m_fTime = 0.f;
}




void CPlayer::Jumping()
{
	float fY(0.f);
	if (m_bDashing) return; // �뽬 �߿��� Jumping ó������ ����
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	// �߷� ���� (�׻� ����)
	m_tInfo.fY += 5.f;


	static float prevY = m_tInfo.fY; // �̺κ��� ���� �ǵ����� ����!!!
	m_fGravity = m_tInfo.fY - prevY; // �̺κ��� ���� �ǵ����� ����!!!
	prevY = m_tInfo.fY;              // �̺κ��� ���� �ǵ����� ����!!!

	const float fFixedFallSpeed = 10.0f;

	if (m_bJump) // ���� ��
	{
		float jumpOffset = (m_fJumpPower * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;

		if (jumpOffset < 0.0f) // ���� ��
		{
			m_tInfo.fY += fFixedFallSpeed;
		}
		else
		{
			m_tInfo.fY -= jumpOffset;
		}

		m_fTime += 0.25f;
		if (bLineCol && (m_tInfo.fY >= fY))
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	else if (bLineCol) // �ٴ� �浹
	{
		m_tInfo.fY = fY;
	}
}






void CPlayer::OnCollision(CObj* _op)
{

	switch (_op->Get_OBJID())
	{
	case OBJ_BLOCK:
		m_bJump = false;
		m_fTime = 0.f;
		break;
	default:
		break;
	}

}




void CPlayer::Offset()
{
	// X�࿡�� �÷��̾��� �̵� ������ �ּ�/�ִ� ��ġ�� ����
	int iOffSetminX = WINCX / 2 - 100; // ȭ�� ���� �Ѱ谪 (������ ����)
	int iOffSetmaxX = WINCX / 2 + 100; // ȭ�� ������ �Ѱ谪 (������ ����)

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	
	if (iOffSetminX > m_tInfo.fX + iScrollX)
	{
		if (m_bDashing)
			CScrollMgr::Get_Instance()->Set_ScrollX(m_fDashSpeed); 
		else
			CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed); 
	}

	else if (iOffSetmaxX < m_tInfo.fX + iScrollX)
	{
		if (m_bDashing)
			CScrollMgr::Get_Instance()->Set_ScrollX(-m_fDashSpeed); 
		else
			CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
	}

	int iOffSetminY = WINCY / 2 - 200; 
	int iOffSetmaxY = WINCY / 2 + 200; 
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iOffSetminY > m_tInfo.fY + iScrollY)
	{
		if (m_bDashing)
			CScrollMgr::Get_Instance()->Set_ScrollY(m_fDashSpeed); 
		else
			CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed); 
	}

	else if (iOffSetmaxY < m_tInfo.fY + iScrollY)
	{
		if (m_bDashing)
			CScrollMgr::Get_Instance()->Set_ScrollY(-m_fDashSpeed); 
		else
			CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed); 
	}
}



CObj* CPlayer::Create_Shield()
{
	CObj* pShield = CAbstractFactory<CShield>::Create();

	pShield->Set_Target(this);

	return pShield;
}

void CPlayer::Change_Motion()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CPlayer::IDLE:
			m_tFrame.iFrameStart = 0; // ù��°
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CPlayer::WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CPlayer::EffECT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CPlayer::DOUBLEJUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 2; // ��: ���� ���� ���
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();
			break;


		case CPlayer::ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CPlayer::HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CPlayer::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}

}


