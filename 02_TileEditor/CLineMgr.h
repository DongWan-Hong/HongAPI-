#pragma once // 헤더 파일 중복 포함 방지

#include "CLine.h" // CLine 클래스와 LINEPOINT 정의를 포함

// CLineMgr 클래스 선언: 선(Line)을 관리하는 클래스
class CLineMgr
{
private:
    // 기본 생성자: 객체를 초기화
    CLineMgr();

    // 소멸자: 객체 소멸 시 호출
    ~CLineMgr();

public:
    // 특정 x좌표(_fX)에서 선과의 충돌 여부를 확인하고, y좌표 값을 반환
    bool Collision_Line(float _fX, float* pY);

public:
    // 선 관리자를 초기화
    void Initialize();

    // 선 관리자를 업데이트 (마우스 입력 등)
    int Update();

    // 업데이트 이후 추가적인 처리
    void Late_Update();

    // 화면에 선을 그리는 함수
    void Render(HDC hDC);

    // 사용된 자원을 해제하는 함수
    void Release();

    // 현재 선 목록을 파일로 저장하는 함수
    void Save_Line();

    // 파일에서 선 목록을 불러오는 함수
    void Load_Line();

public:
    // 싱글톤 패턴 구현
    // 인스턴스를 반환하며, 필요 시 생성
    static CLineMgr* Get_Instance()
    {
        if (nullptr == m_pInstance) // 인스턴스가 없을 경우 생성
            m_pInstance = new CLineMgr;

        return m_pInstance;
    }

    // 싱글톤 인스턴스를 파괴하는 함수
    static void Destroy_Instance()
    {
        if (m_pInstance) // 인스턴스가 존재할 경우 파괴
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    // 싱글톤 패턴을 위한 정적 멤버 변수
    static CLineMgr* m_pInstance;

    // 관리할 선(CLine)의 리스트
    list<CLine*> m_Linelist;

    // 선을 구성할 두 점 (왼쪽과 오른쪽 끝점)
    LINEPOINT m_tLinePoint[DIR_END];
};
