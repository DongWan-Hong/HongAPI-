#include "pch.h"          // �̸� �����ϵ� ��� ���� ����
#include "CLine.h"        // CLine Ŭ������ ���� ����
#include "CScrollMgr.h"   // CScrollMgr Ŭ������ ���� ����


CLine::CLine()
{

}

// CLine Ŭ������ ������: �� ���� LINEPOINT ��ü�� ����Ͽ� �ʱ�ȭ
CLine::CLine(LINEPOINT& tLeft, LINEPOINT& tRight)
    : m_tInfo(tLeft, tRight) // m_tInfo�� ���޹��� tLeft�� tRight�� �ʱ�ȭ
{
}

// CLine Ŭ������ ������: LINE ����ü�� ����Ͽ� �ʱ�ȭ
CLine::CLine(LINE& tInfo)
    : m_tInfo(tInfo) // m_tInfo�� ���޹��� LINE ��ü�� �ʱ�ȭ
{
}


CLine::~CLine()
{

}


void CLine::Render(HDC hDC)
{
    // ���� ��ũ�� ��ġ�� ������ (x�� ��ũ�� ������)
    int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

    // ���� ���� ��ġ�� �̵� (��ũ�� ��ġ�� �����Ͽ� ������ ����)
    MoveToEx(
        hDC,                                 // ��ġ ���ؽ�Ʈ �ڵ�
        (int)m_tInfo.tLPoint.fX + iScrollX, // ���� ���� x ��ǥ�� ��ũ�� ������ ����
        (int)m_tInfo.tLPoint.fY,            // ���� ���� y ��ǥ
        nullptr                             // ���� ��ġ�� �������� ����
    );

    // ���� �� ��ġ�� ���� �׸�
    LineTo(
        hDC,                                 // ��ġ ���ؽ�Ʈ �ڵ�
        (int)m_tInfo.tRPoint.fX + iScrollX, // ������ ���� x ��ǥ�� ��ũ�� ������ ����
        (int)m_tInfo.tRPoint.fY             // ������ ���� y ��ǥ
    );
}
