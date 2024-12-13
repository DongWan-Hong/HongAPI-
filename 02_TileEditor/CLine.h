#pragma once 

#include "Define.h" 

class CLine
{
public:

    CLine();

    // 생성자: 두 개의 LINEPOINT를 사용하여 선 정보 초기화
    CLine(LINEPOINT& tLeft, LINEPOINT& tRight);

    // 생성자: LINE 구조체를 사용하여 선 정보 초기화
    CLine(LINE& tInfo);

    ~CLine();

public:
    // 선 정보(LINE 구조체)를 반환하는 함수
    // const 포인터를 반환하여 원본 데이터를 수정할 수 없도록 보호
    const LINE* Get_Info() { return &m_tInfo; }

public:
    // 선을 화면에 그리는 함수
    void Render(HDC hDC);

private:
    // 선의 정보를 저장하는 멤버 변수
    LINE m_tInfo;
};
