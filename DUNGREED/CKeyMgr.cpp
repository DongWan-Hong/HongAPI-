#include "pch.h"
#include "CKeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::Key_Pressing(int _iKey)
{
	if (GetAsyncKeyState(_iKey) & 0x8000)
		return true;

	return false;
}
// 이전에 눌림이 없고, 현재 눌렸을 경우
// 이전에 눌림이 없고, 현재 눌렸을 경우
bool CKeyMgr::Key_Down(int _iKey)
{
    if (_iKey == VK_RBUTTON) // 우클릭 키 처리
    {
        // 우클릭이 눌린 상태이면
        if (GetAsyncKeyState(_iKey) & 0x8000)
        {
            if (!m_bKeyState[_iKey]) // 상태 갱신
            {
                m_bKeyState[_iKey] = true;
                return true; // 우클릭 감지 성공
            }
        }
        else
        {
            m_bKeyState[_iKey] = false; // 우클릭 해제
        }
    }
    else // 일반 키 처리
    {
        if ((!m_bKeyState[_iKey]) && (GetAsyncKeyState(_iKey) & 0x8000))
        {
            m_bKeyState[_iKey] = true;
            return true;
        }
    }
    return false;
}


// 이전에 눌림이 있고, 현재 누르지 않을 경우
bool CKeyMgr::Key_Up(int _iKey)
{
	if ((m_bKeyState[_iKey]) && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	return false;
}

void CKeyMgr::Update()
{
	for (int i = 0; i < VK_MAX; ++i)
	{
		if((!m_bKeyState[i]) && (GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];

		if ((m_bKeyState[i]) && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}
}
