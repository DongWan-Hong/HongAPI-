#include "pch.h"          // 미리 컴파일된 헤더 파일 포함
#include "CKeyMgr.h"       // CKeyMgr 클래스 선언 포함

// CKeyMgr의 정적 멤버 초기화
CKeyMgr* CKeyMgr::m_pInstance = nullptr;

// 기본 생성자
CKeyMgr::CKeyMgr()
{
    // 키 상태 배열을 0으로 초기화
    ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

// 소멸자
CKeyMgr::~CKeyMgr()
{
    // 특별한 자원 해제 작업 없음
}

// 키가 계속 눌리고 있는지 확인
bool CKeyMgr::Key_Pressing(int _iKey)
{
    // GetAsyncKeyState를 사용하여 키가 눌려 있는지 확인
    // 0x8000 비트가 설정되어 있으면 눌려 있는 상태
    if (GetAsyncKeyState(_iKey) & 0x8000)
        return true;

    return false;
}

// 키가 한 번 눌렸는지 확인 (이전에 눌리지 않았고, 현재 눌림)
bool CKeyMgr::Key_Down(int _iKey)
{
    // 이전 상태에서 눌리지 않았고, 현재 눌린 상태인 경우
    if ((!m_bKeyState[_iKey]) && (GetAsyncKeyState(_iKey) & 0x8000))
    {
        // 키 상태를 "눌림"으로 변경
        m_bKeyState[_iKey] = !m_bKeyState[_iKey];
        return true;
    }

    return false;
}

// 키가 눌렸다가 떼졌는지 확인 (이전에 눌렸고, 현재 눌리지 않음)
bool CKeyMgr::Key_Up(int _iKey)
{
    // 이전 상태에서 눌려 있었고, 현재 눌리지 않은 상태인 경우
    if ((m_bKeyState[_iKey]) && !(GetAsyncKeyState(_iKey) & 0x8000))
    {
        // 키 상태를 "떼짐"으로 변경
        m_bKeyState[_iKey] = !m_bKeyState[_iKey];
        return true;
    }

    return false;
}

// 모든 키의 상태를 갱신
void CKeyMgr::Update()
{
    for (int i = 0; i < VK_MAX; ++i) // 모든 키 코드 순회
    {
        // 현재 키가 눌려 있는 경우 상태를 갱신
        if ((!m_bKeyState[i]) && (GetAsyncKeyState(i) & 0x8000))
            m_bKeyState[i] = !m_bKeyState[i];

        // 현재 키가 눌리지 않은 경우 상태를 갱신
        if ((m_bKeyState[i]) && !(GetAsyncKeyState(i) & 0x8000))
            m_bKeyState[i] = !m_bKeyState[i];
    }
}
