#include "pch.h"          // 미리 컴파일된 헤더 파일 포함
#include "CLine.h"        // CLine 클래스의 선언 포함
#include "CScrollMgr.h"   // CScrollMgr 클래스의 선언 포함


CLine::CLine()
{

}

// CLine 클래스의 생성자: 두 개의 LINEPOINT 객체를 사용하여 초기화
CLine::CLine(LINEPOINT& tLeft, LINEPOINT& tRight)
    : m_tInfo(tLeft, tRight) // m_tInfo를 전달받은 tLeft와 tRight로 초기화
{
}

// CLine 클래스의 생성자: LINE 구조체를 사용하여 초기화
CLine::CLine(LINE& tInfo)
    : m_tInfo(tInfo) // m_tInfo를 전달받은 LINE 객체로 초기화
{
}


CLine::~CLine()
{

}


void CLine::Render(HDC hDC)
{
    // 현재 스크롤 위치를 가져옴 (x축 스크롤 오프셋)
    int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

    // 선의 시작 위치로 이동 (스크롤 위치를 적용하여 오프셋 조정)
    MoveToEx(
        hDC,                                 // 장치 컨텍스트 핸들
        (int)m_tInfo.tLPoint.fX + iScrollX, // 왼쪽 점의 x 좌표에 스크롤 오프셋 적용
        (int)m_tInfo.tLPoint.fY,            // 왼쪽 점의 y 좌표
        nullptr                             // 이전 위치를 저장하지 않음
    );

    // 선의 끝 위치로 선을 그림
    LineTo(
        hDC,                                 // 장치 컨텍스트 핸들
        (int)m_tInfo.tRPoint.fX + iScrollX, // 오른쪽 점의 x 좌표에 스크롤 오프셋 적용
        (int)m_tInfo.tRPoint.fY             // 오른쪽 점의 y 좌표
    );
}
