#include "pch.h"
#include "Different.h"

CDifferent::CDifferent()
{
}

CDifferent::~CDifferent()
{
	Release();
}

void CDifferent::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
	m_fDistance = 100.f;
}

int CDifferent::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fAngle += m_fSpeed;

	m_tInfo.fX = m_pTarget->Get_Info().fX + (m_fDistance * cosf(m_fAngle * (PI / 180.f)));
	m_tInfo.fY = m_pTarget->Get_Info().fY - (m_fDistance * sinf(m_fAngle * (PI / 180.f)));

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CDifferent::Late_Update()
{
}

void CDifferent::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CDifferent::Release()
{
}
