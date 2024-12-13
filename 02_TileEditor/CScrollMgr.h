#pragma once // ��� ���� �ߺ� ���� ����

#include "Define.h" // �ʿ��� ���ǿ� ��� ����

// CScrollMgr Ŭ����: ��ũ�� ������ ���� �̱��� Ŭ����
class CScrollMgr
{
private:
    // ������: �ܺο��� ���� �������� ���ϵ��� private ó��
    CScrollMgr();

    // �Ҹ���: �ܺο��� ���� �Ҹ����� ���ϵ��� private ó��
    ~CScrollMgr();

public:
    // ���� x�� ��ũ�� ���� ��ȯ
    float Get_ScrollX() { return m_fScrollX; }

    // ���� y�� ��ũ�� ���� ��ȯ
    float Get_ScrollY() { return m_fScrollY; }

    // x�� ��ũ�� ���� ���� (�Էµ� ����ŭ ����)
    void Set_ScrollX(float _fX) { m_fScrollX += _fX; }

    // y�� ��ũ�� ���� ���� (�Էµ� ����ŭ ����)
    void Set_ScrollY(float _fY) { m_fScrollY += _fY; }

public:
    // �̱��� �ν��Ͻ��� ��ȯ�ϴ� ���� �Լ�
    static CScrollMgr* Get_Instance()
    {
        // �ν��Ͻ��� ������ ����
        if (nullptr == m_pInstance)
            m_pInstance = new CScrollMgr;

        return m_pInstance;
    }

    // �̱��� �ν��Ͻ��� �����ϴ� ���� �Լ�
    static void Destroy_Instance()
    {
        // �ν��Ͻ��� �����ϸ� ����
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    // �̱��� �ν��Ͻ��� �����ϴ� ���� ��� ����
    static CScrollMgr* m_pInstance;

    // x�� ��ũ�� ��
    float m_fScrollX;

    // y�� ��ũ�� ��
    float m_fScrollY;
};
