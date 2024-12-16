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
	m_fDashSpeed = 25.f;     // �뽬 �ӵ�
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

	ADD_BMP(L"../Image2/Player/RunEffect1.bmp", L"Run_Effect"); 

	//ADD_BMP(L"../Image3/Weapon/BasicShortSword.bmp", L"Player_Sword")

	ADD_BMP(L"../Image2/player/baseCharEffect1.bmp", L"Right_Dash")
	ADD_BMP(L"../Image2/player/baseCharEffect_Left1.bmp", L"Left_Dash")

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

	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	
	const wchar_t* imagePath = (ptMouse.x - iScrollX > m_tInfo.fX) ?
		L"../Image2/player/baseCharEffect1.bmp" :  // ������ �̹���
		L"../Image2/player/baseCharEffect_Left1.bmp"; // ���� �̹���

	int offsetX = (ptMouse.x - iScrollX > m_tInfo.fX) ? -70 : -20; // 

	
		for (const auto& trail : m_vTrails)
		{
			Graphics graphics(hDC);


			Image image(imagePath);


			BYTE alpha = (BYTE)(trail.alpha * 70);

			// ImageAttributes�� ����Ͽ� Ư�� ���� (255, 0, 255)�� ����ȭ
			ImageAttributes imgAttributes;
			Color transparentColor(255, 255, 0, 255);
			imgAttributes.SetColorKey(transparentColor, transparentColor);

			// ���� ������ ���� ���� ��Ʈ���� ����
			ColorMatrix colorMatrix = {
				1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, alpha / 255.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f, 1.0f
			};
			imgAttributes.SetColorMatrix(&colorMatrix);

			// �̹��� ���
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
			64, 80,  // ȿ�� ũ��
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

		// �̹��� ���
		graphics.DrawImage(
			&Inven,
			Rect(WINCX - 405,  // ȭ�� �����ʿ� ���� (10px ����)
				WINCY-700, // ���� �߾� ����
				492, 752),         // �̹��� ũ��
			0, 0, 492, 752,
			UnitPixel, &imgAttributes);
	}




	TCHAR szBuffer[128];
	_stprintf_s(szBuffer, _T("Jump: %d, Dash: %d"), m_bJump, m_bDashing); // ���� ���� Ȯ�� ���߿� �������� �ٲܲ���
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 100, 100, szBuffer, _tcslen(szBuffer));

	TCHAR szBuffer2[64];
	_stprintf_s(szBuffer2, _T("Plyer: X=%d, Y=%d"), (int)m_tInfo.fX - iScrollX, (int)m_tInfo.fY - iScrollY);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 200, 10, szBuffer2, _tcslen(szBuffer2));

	TCHAR szBuffer3[128];
	_stprintf_s(szBuffer3, _T("Inven: %d"), m_bInven); // ���� ���� Ȯ�� ���߿� �������� �ٲܲ���
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 100, 200, szBuffer3, _tcslen(szBuffer3));

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
			if (!m_bJump && !m_bDashing) // �뽬 ���� �ƴ� ���� ���� ����
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
		if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) && !m_bDashing) // ���콺 ��Ŭ������ �뽬
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

	
	float maxDashDistance = 200.0f;  // �����̶� �Ȱ��� �� 4�������� �뽬�ϰ� 

	// ���� �÷��̾���� x��y �Ÿ� ���
	float deltaX = targetX - m_tInfo.fX; 
	float deltaY = targetY - m_tInfo.fY; 

	// ��Ÿ��󽺷� �Ÿ� ������
	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);


	if (distance > maxDashDistance)
	{
		
		float ratio = maxDashDistance / distance; // �ִ� �Ÿ� / ���� �Ÿ� = ���� ����! << GPT�� �˷���

		deltaX *= ratio; // X�� �Ÿ� ����
		deltaY *= ratio; // Y�� �Ÿ� ����
	}

	m_fDash_Mouse_X = m_tInfo.fX + deltaX; 
	m_fDash_Mouse_Y = m_tInfo.fY + deltaY; 
}

void CPlayer::PerformDash()
{
	// �÷����� ���콺��ġ����
	float fDistanceX = m_fDash_Mouse_X - m_tInfo.fX; 
	float fDistanceY = m_fDash_Mouse_Y - m_tInfo.fY;

	// ���࿡ �Ÿ����̰� �뽬�ӵ��ٴ� ������ �����Ѱɷ�
	if (fabs(fDistanceX) <= m_fDashSpeed && fabs(fDistanceY) <= m_fDashSpeed)
	{
		
		m_tInfo.fX = m_fDash_Mouse_X;
		m_tInfo.fY = m_fDash_Mouse_Y;

		m_bDashing = false;

		m_vTrails.clear();
		return; 
	}


	// �뽬�� ��ӵǴ� ���, ��ǥ ��ġ�� �̵��� ���� ���
	float fTotalDistance = abs(fDistanceX) + abs(fDistanceY); 
	float ratioX = fDistanceX / fTotalDistance; 
	float ratioY = fDistanceY / fTotalDistance; 

	// �뽬 �ӵ��� ������ ���ؼ� ���� �������� �̵��� ���
	m_tInfo.fX += ratioX * m_fDashSpeed; 
	m_tInfo.fY += ratioY * m_fDashSpeed; 

	Trail newTrail;
	newTrail.x = m_tInfo.fX; 
	newTrail.y = m_tInfo.fY;
	newTrail.alpha = 1.0f; // (ó������ ������ ���̰� ����) ���� �����ϴ°���
	newTrail.startTime = GetTickCount64(); 
	m_vTrails.push_back(newTrail); // �ܻ��� trail ��Ͽ� �߰�

	DWORD currentTime = GetTickCount64(); // ���� �ð� ��������
	m_vTrails.erase(remove_if(m_vTrails.begin(), m_vTrails.end(),
		[currentTime](const Trail& trail) // gpt�� ������� ����
		{
			return (currentTime - trail.startTime > 100);
		}), m_vTrails.end());
}

//[ĸó ����Ʈ](�Ű�����) -> ��ȯ Ÿ�� { �Լ� ���� };
//currentTime ������ ���� ���ο��� ����ϰڴٴ� �ǹ�
// (const Trail& trail) �� ���� �Լ��� ���޵Ǵ� �Ű������̰�
// currentTime - trail.startTime > 100  �̰� �����̰�
// ������ �� 100ms�� ������ �����Ҳ��� remove_if��


void CPlayer::Jumping()
{
	float fY(0.f);
	if (m_bDashing) return; // �뽬 �߿��� Jumping ó������ ����
	//bool bLineCol = CLineMgr::Get_Instance()->(m_tInfo.fX, &fY);
	
	// �߷� ���� (�׻� ����)
	m_tInfo.fY += 8.f;

	static float prevY = m_tInfo.fY; // �̺κ��� ���� �ǵ����� ����!!!
	m_fGravity = m_tInfo.fY - prevY; // �̺κ��� ���� �ǵ����� ����!!!
	prevY = m_tInfo.fY;              // �̺κ��� ���� �ǵ����� ����!!!



	const float fFixedFallSpeed = 10.0f; //�ִ�ӵ�

	if (m_bJump) // ���� ��
	{
		float jumpOffset = (m_fJumpPower * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;

		if (jumpOffset < 0.0f) // �Ӱ��� �����ϸ� 10.f �� �������� �ϰڴ���
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
			m_tFrame.iFrameStart = 0; // ù��°
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


