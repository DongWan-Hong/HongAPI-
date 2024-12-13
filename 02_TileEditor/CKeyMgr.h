#pragma once // 헤더 파일 중복 포함 방지

#include "Define.h" // 필요한 상수와 정의 포함

// CKeyMgr 클래스: 키 입력 관리
class CKeyMgr
{
private:
    // 생성자: 외부에서 직접 생성하지 못하도록 private 처리
    CKeyMgr();

    // 소멸자: 외부에서 직접 소멸하지 못하도록 private 처리
    ~CKeyMgr();

public:
    // 키가 계속 눌리고 있는지 확인
    bool Key_Pressing(int _iKey);

    // 키가 딱 한 번 눌렸는지 확인 (현재 눌림 && 이전 상태에서 눌리지 않음)
    bool Key_Down(int _iKey);

    // 키가 눌렸다가 떼졌는지 확인 (현재 눌리지 않음 && 이전 상태에서 눌림)
    bool Key_Up(int _iKey);

    // 키 입력 상태를 갱신 (현재 키 상태를 저장)
    void Update();

public:
    // 싱글톤 인스턴스를 반환하는 정적 함수
    static CKeyMgr* Get_Instance()
    {
        if (nullptr == m_pInstance) // 인스턴스가 없으면 생성
            m_pInstance = new CKeyMgr;

        return m_pInstance;
    }

    // 싱글톤 인스턴스를 안전하게 삭제
    static void Destroy_Instance()
    {
        if (m_pInstance) // 인스턴스가 존재하면 삭제
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    // 싱글톤 인스턴스를 위한 정적 멤버 변수
    static CKeyMgr* m_pInstance;

    // 현재 키의 상태를 저장하는 배열 (크기는 키의 최대값에 따라 결정)
    bool m_bKeyState[VK_MAX];
};
