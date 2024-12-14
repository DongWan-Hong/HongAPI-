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
	: m_bJump(false), m_fJumpPower(0.f), m_fTime(0.f)

{
	m_fGravity = 0.f;
	ZeroMemory(&m_tPosin, sizeof(POINT));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { 200.f,1100.f, 77.f, 90.f };
	m_fSpeed = 5.f;
	m_fDistance = 100.f; //
	m_eOBJID = OBJ_PLAYER;
	m_fJumpPower = 20.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image2/Player/baseCharIdle.bmp",  L"Player_IDLE");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UP.bmp",	 L"Player_UP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image2/Player/baseCharRun.bmp", L"Player_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image2/Player/Dir/Left.bmp", L"Player_Left");
	
	


	m_pImgKey = L"Player_IDLE";
	m_eCurState = IDLE;
	m_ePreState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100; // �÷��̾� IDLE ��忡�� ��� ��ȯ�Ǵ¼ӵ�
	m_tFrame.dwTime = GetTickCount64();
}




int CPlayer::Update()
{
	
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

	GdiTransparentBlt(hDC,			// ���� ���� DC
		m_tRect.left + iScrollX,	// ���� ���� ��ġ ��ǥ X, Y	
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,			// ���� ���� �̹����� ����, ����
		(int)m_tInfo.fCY,
		hMemDC,						// ������ �̹��� DC
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,	// 		
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		63,			// ������ �̹����� ����, ����
		76,
		RGB(255, 0, 255));		// ������ ����

	

}

void CPlayer::Release()
{
}



void CPlayer::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		m_tInfo.fX -= m_fSpeed;
		m_pImgKey = L"Player_Left";
		m_eCurState = WALK;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		m_tInfo.fX += m_fSpeed;
		m_pImgKey = L"Player_Right";
		m_eCurState = WALK;
	}
	if (CKeyMgr::Get_Instance()->Key_Up('A') ||
		CKeyMgr::Get_Instance()->Key_Up('D')) // Ű�� ���� ��
	{
		m_pImgKey = L"Player_IDLE";
		m_eCurState = IDLE; // IDLE ���·� ��ȯ
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = true;
		m_tInfo.fY -= 0.1f;
	}
	else
	{
		m_eCurState = IDLE;
	}

}


void CPlayer::Jumping()
{
	float fY(0.f);

	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);


	
	static float prevY = m_tInfo.fY;
	m_fGravity = m_tInfo.fY - prevY;
	prevY = m_tInfo.fY;

	if (!m_bJump) 
	{
		m_tInfo.fY += 9.8f; // �߷� �� (�⺻������ �ϰ� �ӵ�)
	}

	if (m_bJump) // ���� ��
	{
		m_tInfo.fY -= (m_fJumpPower * sinf(90.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.25f;

		if (bLineCol && (m_tInfo.fY >= fY)) // �ٴڰ� �浹
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	else if (bLineCol) // �ٴڿ� ���� �� ��ġ ����
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

	int		iOffSetminX = 100;
	int		iOffSetmaxX = 700;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (iOffSetminX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetmaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	int		iOffSetminY = 100;
	int		iOffSetmaxY = 500;

	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iOffSetminY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffSetmaxY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
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
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CPlayer::WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
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


