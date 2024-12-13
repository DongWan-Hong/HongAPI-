#pragma once // ��� ���� �ߺ� ���� ����

#include "Define.h" // �ʿ��� ����� ���� ����

// CKeyMgr Ŭ����: Ű �Է� ����
class CKeyMgr
{
private:
    // ������: �ܺο��� ���� �������� ���ϵ��� private ó��
    CKeyMgr();

    // �Ҹ���: �ܺο��� ���� �Ҹ����� ���ϵ��� private ó��
    ~CKeyMgr();

public:
    // Ű�� ��� ������ �ִ��� Ȯ��
    bool Key_Pressing(int _iKey);

    // Ű�� �� �� �� ���ȴ��� Ȯ�� (���� ���� && ���� ���¿��� ������ ����)
    bool Key_Down(int _iKey);

    // Ű�� ���ȴٰ� �������� Ȯ�� (���� ������ ���� && ���� ���¿��� ����)
    bool Key_Up(int _iKey);

    // Ű �Է� ���¸� ���� (���� Ű ���¸� ����)
    void Update();

public:
    // �̱��� �ν��Ͻ��� ��ȯ�ϴ� ���� �Լ�
    static CKeyMgr* Get_Instance()
    {
        if (nullptr == m_pInstance) // �ν��Ͻ��� ������ ����
            m_pInstance = new CKeyMgr;

        return m_pInstance;
    }

    // �̱��� �ν��Ͻ��� �����ϰ� ����
    static void Destroy_Instance()
    {
        if (m_pInstance) // �ν��Ͻ��� �����ϸ� ����
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    // �̱��� �ν��Ͻ��� ���� ���� ��� ����
    static CKeyMgr* m_pInstance;

    // ���� Ű�� ���¸� �����ϴ� �迭 (ũ��� Ű�� �ִ밪�� ���� ����)
    bool m_bKeyState[VK_MAX];
};
