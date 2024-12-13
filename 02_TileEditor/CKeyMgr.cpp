#include "pch.h"          // �̸� �����ϵ� ��� ���� ����
#include "CKeyMgr.h"       // CKeyMgr Ŭ���� ���� ����

// CKeyMgr�� ���� ��� �ʱ�ȭ
CKeyMgr* CKeyMgr::m_pInstance = nullptr;

// �⺻ ������
CKeyMgr::CKeyMgr()
{
    // Ű ���� �迭�� 0���� �ʱ�ȭ
    ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

// �Ҹ���
CKeyMgr::~CKeyMgr()
{
    // Ư���� �ڿ� ���� �۾� ����
}

// Ű�� ��� ������ �ִ��� Ȯ��
bool CKeyMgr::Key_Pressing(int _iKey)
{
    // GetAsyncKeyState�� ����Ͽ� Ű�� ���� �ִ��� Ȯ��
    // 0x8000 ��Ʈ�� �����Ǿ� ������ ���� �ִ� ����
    if (GetAsyncKeyState(_iKey) & 0x8000)
        return true;

    return false;
}

// Ű�� �� �� ���ȴ��� Ȯ�� (������ ������ �ʾҰ�, ���� ����)
bool CKeyMgr::Key_Down(int _iKey)
{
    // ���� ���¿��� ������ �ʾҰ�, ���� ���� ������ ���
    if ((!m_bKeyState[_iKey]) && (GetAsyncKeyState(_iKey) & 0x8000))
    {
        // Ű ���¸� "����"���� ����
        m_bKeyState[_iKey] = !m_bKeyState[_iKey];
        return true;
    }

    return false;
}

// Ű�� ���ȴٰ� �������� Ȯ�� (������ ���Ȱ�, ���� ������ ����)
bool CKeyMgr::Key_Up(int _iKey)
{
    // ���� ���¿��� ���� �־���, ���� ������ ���� ������ ���
    if ((m_bKeyState[_iKey]) && !(GetAsyncKeyState(_iKey) & 0x8000))
    {
        // Ű ���¸� "����"���� ����
        m_bKeyState[_iKey] = !m_bKeyState[_iKey];
        return true;
    }

    return false;
}

// ��� Ű�� ���¸� ����
void CKeyMgr::Update()
{
    for (int i = 0; i < VK_MAX; ++i) // ��� Ű �ڵ� ��ȸ
    {
        // ���� Ű�� ���� �ִ� ��� ���¸� ����
        if ((!m_bKeyState[i]) && (GetAsyncKeyState(i) & 0x8000))
            m_bKeyState[i] = !m_bKeyState[i];

        // ���� Ű�� ������ ���� ��� ���¸� ����
        if ((m_bKeyState[i]) && !(GetAsyncKeyState(i) & 0x8000))
            m_bKeyState[i] = !m_bKeyState[i];
    }
}
