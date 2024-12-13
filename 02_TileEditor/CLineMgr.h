#pragma once // ��� ���� �ߺ� ���� ����

#include "CLine.h" // CLine Ŭ������ LINEPOINT ���Ǹ� ����

// CLineMgr Ŭ���� ����: ��(Line)�� �����ϴ� Ŭ����
class CLineMgr
{
private:
    // �⺻ ������: ��ü�� �ʱ�ȭ
    CLineMgr();

    // �Ҹ���: ��ü �Ҹ� �� ȣ��
    ~CLineMgr();

public:
    // Ư�� x��ǥ(_fX)���� ������ �浹 ���θ� Ȯ���ϰ�, y��ǥ ���� ��ȯ
    bool Collision_Line(float _fX, float* pY);

public:
    // �� �����ڸ� �ʱ�ȭ
    void Initialize();

    // �� �����ڸ� ������Ʈ (���콺 �Է� ��)
    int Update();

    // ������Ʈ ���� �߰����� ó��
    void Late_Update();

    // ȭ�鿡 ���� �׸��� �Լ�
    void Render(HDC hDC);

    // ���� �ڿ��� �����ϴ� �Լ�
    void Release();

    // ���� �� ����� ���Ϸ� �����ϴ� �Լ�
    void Save_Line();

    // ���Ͽ��� �� ����� �ҷ����� �Լ�
    void Load_Line();

public:
    // �̱��� ���� ����
    // �ν��Ͻ��� ��ȯ�ϸ�, �ʿ� �� ����
    static CLineMgr* Get_Instance()
    {
        if (nullptr == m_pInstance) // �ν��Ͻ��� ���� ��� ����
            m_pInstance = new CLineMgr;

        return m_pInstance;
    }

    // �̱��� �ν��Ͻ��� �ı��ϴ� �Լ�
    static void Destroy_Instance()
    {
        if (m_pInstance) // �ν��Ͻ��� ������ ��� �ı�
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    // �̱��� ������ ���� ���� ��� ����
    static CLineMgr* m_pInstance;

    // ������ ��(CLine)�� ����Ʈ
    list<CLine*> m_Linelist;

    // ���� ������ �� �� (���ʰ� ������ ����)
    LINEPOINT m_tLinePoint[DIR_END];
};
