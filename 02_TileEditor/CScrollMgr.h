#pragma once // 헤더 파일 중복 포함 방지

#include "Define.h" // 필요한 정의와 상수 포함

// CScrollMgr 클래스: 스크롤 관리를 위한 싱글톤 클래스
class CScrollMgr
{
private:
    // 생성자: 외부에서 직접 생성하지 못하도록 private 처리
    CScrollMgr();

    // 소멸자: 외부에서 직접 소멸하지 못하도록 private 처리
    ~CScrollMgr();

public:
    // 현재 x축 스크롤 값을 반환
    float Get_ScrollX() { return m_fScrollX; }

    // 현재 y축 스크롤 값을 반환
    float Get_ScrollY() { return m_fScrollY; }

    // x축 스크롤 값을 증가 (입력된 값만큼 더함)
    void Set_ScrollX(float _fX) { m_fScrollX += _fX; }

    // y축 스크롤 값을 증가 (입력된 값만큼 더함)
    void Set_ScrollY(float _fY) { m_fScrollY += _fY; }

public:
    // 싱글톤 인스턴스를 반환하는 정적 함수
    static CScrollMgr* Get_Instance()
    {
        // 인스턴스가 없으면 생성
        if (nullptr == m_pInstance)
            m_pInstance = new CScrollMgr;

        return m_pInstance;
    }

    // 싱글톤 인스턴스를 삭제하는 정적 함수
    static void Destroy_Instance()
    {
        // 인스턴스가 존재하면 삭제
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    // 싱글톤 인스턴스를 관리하는 정적 멤버 변수
    static CScrollMgr* m_pInstance;

    // x축 스크롤 값
    float m_fScrollX;

    // y축 스크롤 값
    float m_fScrollY;
};
