#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CKeyMgr.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"

bool CPlayer::m_bInven = false;

CPlayer::CPlayer()
	: m_bJump(false), m_fJumpPower(0.f), m_fTime(0.f),m_bDefatule_IDle(true)
{
	m_fGravity = 0.f;
	ZeroMemory(&m_tPosin, sizeof(POINT));
	ZeroMemory(&m_eCurState,sizeof(STATE));
	ZeroMemory(&m_ePreState,sizeof(STATE));
	m_bDashing = false;      
	m_bInven = false;
	m_fDash_Mouse_X = 0.f;
	m_fDash_Mouse_Y = 0.f;
	m_fDashSpeed = 25.f;     // 대쉬 속도
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

	ADD_BMP(L"../Image2/Player/RunEffect1.bmp", L"Run_Effect"); 

	//ADD_BMP(L"../Image3/Weapon/BasicShortSword.bmp", L"Player_Sword")

	ADD_BMP(L"../Image2/player/baseCharEffect1.bmp", L"Right_Dash")
	ADD_BMP(L"../Image2/player/baseCharEffect_Left1.bmp", L"Left_Dash")

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

	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	
	const wchar_t* imagePath = (ptMouse.x - iScrollX > m_tInfo.fX) ?
		L"../Image2/player/baseCharEffect1.bmp" :  // 오른쪽 이미지
		L"../Image2/player/baseCharEffect_Left1.bmp"; // 왼쪽 이미지

	int offsetX = (ptMouse.x - iScrollX > m_tInfo.fX) ? -70 : -20; // 

	
		for (const auto& trail : m_vTrails)
		{
			Graphics graphics(hDC);


			Image image(imagePath);


			BYTE alpha = (BYTE)(trail.alpha * 70);

			// ImageAttributes를 사용하여 특정 색상 (255, 0, 255)을 투명화
			ImageAttributes imgAttributes;
			Color transparentColor(255, 255, 0, 255);
			imgAttributes.SetColorKey(transparentColor, transparentColor);

			// 투명도 적용을 위한 색상 매트릭스 설정
			ColorMatrix colorMatrix = {
				1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, alpha / 255.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f, 1.0f
			};
			imgAttributes.SetColorMatrix(&colorMatrix);

			// 이미지 출력
			graphics.DrawImage(&image,
				Rect((int)trail.x + iScrollX + offsetX, (int)trail.y - 40 + iScrollY, 102, 100),
				0, 0, 102, 100, UnitPixel, &imgAttributes);
		}


	HDC hPlayerDC = FIND_BMP(m_pImgKey);
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hPlayerDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		102, 100, RGB(255, 0, 255));


	if (m_pImgKey == (L"Player_Right") || m_pImgKey == (L"Player_Left") && m_bJump == false)
	{
		Image image(L"../Image2/player/baseCharEffect_Left1.bmp");
		HDC hEffectDC = FIND_BMP(L"Run_Effect");

		GdiTransparentBlt(hDC,
			(int)m_tInfo.fX + iScrollX - 50,
			(int)m_tInfo.fY + iScrollY,
			64, 80,  // 효과 크기
			hEffectDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			64, 64,
			RGB(255, 0, 255));
	}

	if (m_bInven == true)
	{
		Graphics graphics(hDC);

		Image Inven(L"../Image3/Inventory/InventoryBase2.png");

		ImageAttributes imgAttributes;
		Color transparentColor(255, 255, 0, 255);
		imgAttributes.SetColorKey(transparentColor, transparentColor);

		// 이미지 출력
		graphics.DrawImage(
			&Inven,
			Rect(WINCX - 405,  // 화면 오른쪽에 고정 (10px 여백)
				WINCY-700, // 세로 중앙 정렬
				492, 752),         // 이미지 크기
			0, 0, 492, 752,
			UnitPixel, &imgAttributes);
	}




	TCHAR szBuffer[128];
	_stprintf_s(szBuffer, _T("Jump: %d, Dash: %d"), m_bJump, m_bDashing); // 점프 여부 확인 나중에 게이지로 바꿀꺼임
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 100, 100, szBuffer, _tcslen(szBuffer));

	TCHAR szBuffer2[64];
	_stprintf_s(szBuffer2, _T("Plyer: X=%d, Y=%d"), (int)m_tInfo.fX - iScrollX, (int)m_tInfo.fY - iScrollY);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 200, 10, szBuffer2, _tcslen(szBuffer2));

	TCHAR szBuffer3[128];
	_stprintf_s(szBuffer3, _T("Inven: %d"), m_bInven); // 점프 여부 확인 나중에 게이지로 바꿀꺼임
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 100, 200, szBuffer3, _tcslen(szBuffer3));

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
	if (m_bInven == false)
	{
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
		if (CKeyMgr::Get_Instance()->Key_Up('A') || CKeyMgr::Get_Instance()->Key_Up('D'))
		{
			m_pImgKey = bMouseRight ? L"Player_IDLE_Right" : L"Player_IDLE_Left";
			m_eCurState = IDLE;
		}
		if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) && !m_bDashing) // 마우스 우클릭으로 대쉬
		{
			StartDash(ptMouse.x - iScrollX, ptMouse.y - iScrollY);
			m_bJump = false;
			m_eCurState = DASH;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Down('I'))
	{
		m_bInven = !m_bInven;
	}
	
}


void CPlayer::StartDash(float targetX, float targetY)
{
	
	m_bDashing = true;

	
	float maxDashDistance = 200.0f;  // 원작이랑 똑같이 블럭 4개정도만 대쉬하게 

	// 현재 플레이어와의 x랑y 거리 계산
	float deltaX = targetX - m_tInfo.fX; 
	float deltaY = targetY - m_tInfo.fY; 

	// 피타고라스로 거리 조지기
	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);


	if (distance > maxDashDistance)
	{
		
		float ratio = maxDashDistance / distance; // 최대 거리 / 현재 거리 = 조정 비율! << GPT가 알려줌

		deltaX *= ratio; // X축 거리 조정
		deltaY *= ratio; // Y축 거리 조정
	}

	m_fDash_Mouse_X = m_tInfo.fX + deltaX; 
	m_fDash_Mouse_Y = m_tInfo.fY + deltaY; 
}

void CPlayer::PerformDash()
{
	// 플레어어랑 마우스위치차이
	float fDistanceX = m_fDash_Mouse_X - m_tInfo.fX; 
	float fDistanceY = m_fDash_Mouse_Y - m_tInfo.fY;

	// 만약에 거리차이가 대쉬속도바다 작으면 도착한걸로
	if (fabs(fDistanceX) <= m_fDashSpeed && fabs(fDistanceY) <= m_fDashSpeed)
	{
		
		m_tInfo.fX = m_fDash_Mouse_X;
		m_tInfo.fY = m_fDash_Mouse_Y;

		m_bDashing = false;

		m_vTrails.clear();
		return; 
	}


	// 대쉬가 계속되는 경우, 목표 위치로 이동할 비율 계산
	float fTotalDistance = abs(fDistanceX) + abs(fDistanceY); 
	float ratioX = fDistanceX / fTotalDistance; 
	float ratioY = fDistanceY / fTotalDistance; 

	// 대쉬 속도에 비율을 곱해서 다음 프레임의 이동량 계산
	m_tInfo.fX += ratioX * m_fDashSpeed; 
	m_tInfo.fY += ratioY * m_fDashSpeed; 

	Trail newTrail;
	newTrail.x = m_tInfo.fX; 
	newTrail.y = m_tInfo.fY;
	newTrail.alpha = 1.0f; // (처음에는 완전히 보이게 설정) 투명도 설정하는곳임
	newTrail.startTime = GetTickCount64(); 
	m_vTrails.push_back(newTrail); // 잔상을 trail 목록에 추가

	DWORD currentTime = GetTickCount64(); // 현재 시간 가져오기
	m_vTrails.erase(remove_if(m_vTrails.begin(), m_vTrails.end(),
		[currentTime](const Trail& trail) // gpt가 만들어준 람다
		{
			return (currentTime - trail.startTime > 100);
		}), m_vTrails.end());
}

//[캡처 리스트](매개변수) -> 반환 타입 { 함수 본문 };
//currentTime 변수를 람다 내부에서 사용하겠다는 의미
// (const Trail& trail) 는 람다 함수에 전달되는 매개변수이고
// currentTime - trail.startTime > 100  이게 조건이고
// 생성된 지 100ms가 지나면 삭제할꺼임 remove_if로


void CPlayer::Jumping()
{
	float fY(0.f);
	if (m_bDashing) return; // 대쉬 중에는 Jumping 처리하지 ㄴㄴ
	//bool bLineCol = CLineMgr::Get_Instance()->(m_tInfo.fX, &fY);
	
	// 중력 적용 (항상 실행)
	m_tInfo.fY += 8.f;

	static float prevY = m_tInfo.fY; // 이부분은 절대 건들이지 말기!!!
	m_fGravity = m_tInfo.fY - prevY; // 이부분은 절대 건들이지 말기!!!
	prevY = m_tInfo.fY;              // 이부분은 절대 건들이지 말기!!!



	const float fFixedFallSpeed = 10.0f; //최대속도

	if (m_bJump) // 점프 중
	{
		float jumpOffset = (m_fJumpPower * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;

		if (jumpOffset < 0.0f) // 임계점 도달하면 10.f 로 떨어지게 하겠다임
		{
			m_tInfo.fY += fFixedFallSpeed;
		}
		else
		{
			m_tInfo.fY -= jumpOffset;
		}

		m_fTime += 0.25f;
		
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
	CObj* pShield = CAbstractFactory<CDifferent>::Create();

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
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CPlayer::WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CPlayer::DASH:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 300;
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


