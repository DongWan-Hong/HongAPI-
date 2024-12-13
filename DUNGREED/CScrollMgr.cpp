#include "pch.h"
#include "CScrollMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr() : m_fScrollX(0.f), m_fScrollY(0.f)
{
}

CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock()
{
	if (0.f < m_fScrollX) // ��ũ���� 0�� �Ѿ�� ����
		m_fScrollX = 0.f;

	if (WINCX - 7616 > m_fScrollX) // ������ ��踦 �Ѿ�� ����
		m_fScrollX = WINCX - 7616;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCY - 1280.f > m_fScrollY)
		m_fScrollY = WINCY - 1280.f;
}
