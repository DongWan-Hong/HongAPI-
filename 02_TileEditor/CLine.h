#pragma once 

#include "Define.h" 

class CLine
{
public:

    CLine();

    // ������: �� ���� LINEPOINT�� ����Ͽ� �� ���� �ʱ�ȭ
    CLine(LINEPOINT& tLeft, LINEPOINT& tRight);

    // ������: LINE ����ü�� ����Ͽ� �� ���� �ʱ�ȭ
    CLine(LINE& tInfo);

    ~CLine();

public:
    // �� ����(LINE ����ü)�� ��ȯ�ϴ� �Լ�
    // const �����͸� ��ȯ�Ͽ� ���� �����͸� ������ �� ������ ��ȣ
    const LINE* Get_Info() { return &m_tInfo; }

public:
    // ���� ȭ�鿡 �׸��� �Լ�
    void Render(HDC hDC);

private:
    // ���� ������ �����ϴ� ��� ����
    LINE m_tInfo;
};
