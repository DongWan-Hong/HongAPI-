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
	m_fDashSpeed = 30.f;     // 대쉬 속도
	m_fFixScrollSpeedX = 30.f;
	m_fFixScrollSpeedY = 30.f;
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { 200.f,1100.f, 102.8f, 100.f }; // 플레이어 크기
	m_fSpeed = 5.f; // 플레이어 속도
	m_fDistance = 100.f; // 
	m_eOBJID = OBJ_PLAYER; // 플레이어 명칭 온콜리전 때매
	m_fJumpPower = 20.f; // 점프파워


	ADD_BMP(L"../Image2/Player/baseCharIdle3.bmp", L"Player_IDLE_Right"); 
	ADD_BMP(L"../Image2/Player/baseCharIdleLeft3.bmp", L"Player_IDLE_Left"); 
	ADD_BMP(L"../Image2/Player/baseCharRun2.bmp", L"Player_Right"); 
	ADD_BMP(L"../Image2/Player/Dir/Left2.bmp", L"Player_Left"); 
	ADD_BMP(L"../Image2/Player/RunEffect2.bmp", L"Run_Effect"); 

	ADD_BMP(L"../Image2/Player/RunEffect2.bmp", L"")

	m_pImgKey = L"Player_IDLE_Right";  // 기본 상태는 오른쪽
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
		PerformDash(); // 대쉬 일때 대쉬 함수 들어가기
	}

	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (ptMouse.x > m_tInfo.fX) //  마우스가 보는 방향에 따라 좌우 확인
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
		m_tRect.left + iScrollX,	// 복사 받을 위치 좌표 X, Y	
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,			// 복사한 이미지 크기 어떻게할껀지
		(int)m_tInfo.fCY,
		hMemDC,						
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,	// 		
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		102.8,			// 원본 크기 적어주고
		100.f,
		RGB(255, 0, 255));		

	if (m_pImgKey == (L"Player_Right") || m_pImgKey == (L"Player_Left") && m_bJump == false)
	{

		HDC hEffectDC = CBmpMgr::Get_Instance()->Find_Image(L"Run_Effect");

		GdiTransparentBlt(hDC,
			(int)m_tInfo.fX + iScrollX - 50,
			(int)m_tInfo.fY + iScrollY,
			80, 80,  // 효과 크기
			hEffectDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			64, 64,
			RGB(255, 0, 255));
	}

	TCHAR szBuffer[128];
	_stprintf_s(szBuffer, _T("Jump: %d, Dash: %d"), m_bJump, m_bDoubleJump); // 점프 여부 확인 나중에 게이지로 바꿀꺼임

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


//(조건식) ? 참일 때 값 : 거짓일 때 값;
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
		if (!m_bJump && !m_bDashing) // 대쉬 중이 아닐 때만 점프 가능
		{
			m_bJump = true;
			m_tInfo.fY -= m_fJumpPower;
		}
	}

	if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) && !m_bDashing) // 마우스 우클릭으로 대쉬
	{
		StartDash(ptMouse.x - iScrollX, ptMouse.y - iScrollY);
		m_bJump = false;
	}
}


void CPlayer::StartDash(float targetX, float targetY) // 마우스 위치로 대쉬 조질꺼임
{
	m_bDashing = true;      
	m_fDash_Mouse_X = targetX;
	m_fDash_Mouse_Y = targetY;
}

void CPlayer::PerformDash()
{
	// 마우스와 플레이어의 거리 구하기!
	float fDistanceX = m_fDash_Mouse_X - m_tInfo.fX;
	float fDistanceY = m_fDash_Mouse_Y - m_tInfo.fY;

	// 플레이어가 대쉬지정한곳에 거의다 왔을때 종료
	if (fabs(fDistanceX) <= m_fDashSpeed && fabs(fDistanceY) <= m_fDashSpeed)
	{
		m_tInfo.fX = m_fDash_Mouse_X;
		m_tInfo.fY = m_fDash_Mouse_Y;
		m_bDashing = false;
		return;
	}

	// 최대 대쉬 거리 제한
	const float fMaxDashDistance = 200.0f; // 최대 대쉬 가능 거리

	float fTargetDistance = sqrt(fDistanceX * fDistanceX + fDistanceY * fDistanceY); // 삐따고라스로 거리 구하기

	if (fTargetDistance > fMaxDashDistance) // 
	{
		// 현재 거리가 최대 대쉬 거리보다 클 경우 !!!!!
		float ratio = fMaxDashDistance / fTargetDistance; // 타겟과 거리분의 최대 거리는
		fDistanceX *= ratio;
		fDistanceY *= ratio;
		m_fDash_Mouse_X = m_tInfo.fX + fDistanceX;
		m_fDash_Mouse_Y = m_tInfo.fY + fDistanceY;
	}

	//  이동 비율 계산
	float fTotalDistance = abs(fDistanceX) + abs(fDistanceY); // 전체 거리 계산 (X + Y)
	float ratioX = fDistanceX / fTotalDistance; // X축 이동 비율
	float ratioY = fDistanceY / fTotalDistance; // Y축 이동 비율

	// 대쉬 속도준값만큼이동시키기  // 여기가 사실상 대각선 이긴함 
	m_tInfo.fX += ratioX * m_fDashSpeed;
	m_tInfo.fY += ratioY * m_fDashSpeed;

	// 대쉬 중에는 중력안받게끔!! ( 이거 없으면 곡선처럼 휘어짐..)
	m_fGravity = 0.f;
	m_fTime = 0.f;
}




void CPlayer::Jumping()
{
	float fY(0.f);
	if (m_bDashing) return; // 대쉬 중에는 Jumping 처리하지 ㄴㄴ
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	// 중력 적용 (항상 실행)
	m_tInfo.fY += 5.f;


	static float prevY = m_tInfo.fY; // 이부분은 절대 건들이지 말기!!!
	m_fGravity = m_tInfo.fY - prevY; // 이부분은 절대 건들이지 말기!!!
	prevY = m_tInfo.fY;              // 이부분은 절대 건들이지 말기!!!

	const float fFixedFallSpeed = 10.0f;

	if (m_bJump) // 점프 중
	{
		float jumpOffset = (m_fJumpPower * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;

		if (jumpOffset < 0.0f) // 낙하 중
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
	else if (bLineCol) // 바닥 충돌
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
	// X축에서 플레이어의 이동 가능한 최소/최대 위치를 설정
	int iOffSetminX = WINCX / 2 - 100; // 화면 왼쪽 한계값 (범위를 넓힘)
	int iOffSetmaxX = WINCX / 2 + 100; // 화면 오른쪽 한계값 (범위를 넓힘)

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
			m_tFrame.iFrameStart = 0; // 첫번째
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
			m_tFrame.iMotion = 2; // 예: 이중 점프 모션
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


