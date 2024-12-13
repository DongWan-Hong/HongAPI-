#include "pch.h" // �̸� �����ϵ� ��� ���� ����
#include "CLineMgr.h" // CLineMgr Ŭ���� ���� ����
#include "CKeyMgr.h" // CKeyMgr Ŭ���� ���� ����
#include "CScrollMgr.h" // CScrollMgr Ŭ���� ���� ����

// CLineMgr�� ���� ��� �ʱ�ȭ
CLineMgr* CLineMgr::m_pInstance = nullptr;


CLineMgr::CLineMgr()
{
    // ���� �������� ������ �ʱ�ȭ
    ZeroMemory(m_tLinePoint, sizeof(m_tLinePoint));
}


CLineMgr::~CLineMgr()
{
    Release();
}

// �÷��̾��� �߽���x�� ������ �浹 ���� Ȯ�� �� y��ǥ ��ȯ
//  Y��ǥ��  �÷��̾�Y= ���� �������� ���������� Y������/���� �������� ����
bool CLineMgr::Collision_Line(float _fX, float* pY)
{
    // �� ����Ʈ�� ��������� �浹 ����
    if (m_Linelist.empty())
        return false;

    CLine* pTargetLine = nullptr; // �浹�� ���� ������ ������

    // �� ����Ʈ�� ��ȸ�Ͽ� x��ǥ�� ���Ե� ���� ã��
    for (auto& pLine : m_Linelist)
    {
        if (_fX >= pLine->Get_Info()->tLPoint.fX &&
            _fX < pLine->Get_Info()->tRPoint.fX)
        {
            pTargetLine = pLine;
        }
    }

    // �浹�� ���� ������ false ��ȯ
    if (!pTargetLine)
        return false;

    // ���� �� �� �� ��ǥ ��������
    float x1 = pTargetLine->Get_Info()->tLPoint.fX;
    float y1 = pTargetLine->Get_Info()->tLPoint.fY;
    float x2 = pTargetLine->Get_Info()->tRPoint.fX;
    float y2 = pTargetLine->Get_Info()->tRPoint.fY;

    // ������ �������� �̿��� y��ǥ ���
    *pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

    return true;
}

// �ʱ�ȭ �Լ�
void CLineMgr::Initialize()
{
    // ����� Ư���� �۾� ����
}

// ������Ʈ �Լ�
int CLineMgr::Update()
{
    POINT ptMouse{};
    // ���콺 Ŀ�� ��ġ ��������
    GetCursorPos(&ptMouse);
    // ȭ�� ��ǥ�� Ŭ���̾�Ʈ ��ǥ�� ��ȯ
    ScreenToClient(g_hWnd, &ptMouse);
    // ��ũ�� ������ ����
    ptMouse.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();

    // ���콺 ���� ��ư Ŭ�� ��
    if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
    {
        // ù ��° ���� ��������� �ʱ�ȭ
        if ((!m_tLinePoint[LEFT].fX) && (!m_tLinePoint[LEFT].fY))
        {
            m_tLinePoint[LEFT].fX = (float)ptMouse.x;
            m_tLinePoint[LEFT].fY = (float)ptMouse.y;
        }
        else // �� ��° �� ���� �� �� �߰�
        {
            m_tLinePoint[RIGHT].fX = (float)ptMouse.x;
            m_tLinePoint[RIGHT].fY = (float)ptMouse.y;

            m_Linelist.push_back(new CLine(m_tLinePoint[LEFT], m_tLinePoint[RIGHT]));

            m_tLinePoint[LEFT].fX = m_tLinePoint[RIGHT].fX;
            m_tLinePoint[LEFT].fY = m_tLinePoint[RIGHT].fY;
        }
    }

    // 'S' Ű�� �� ����
    if (CKeyMgr::Get_Instance()->Key_Down('S'))
    {
        Save_Line();
        return 0;
    }

    // 'L' Ű�� �� �ҷ�����
    if (CKeyMgr::Get_Instance()->Key_Down('L'))
    {
        Load_Line();
        return 0;
    }

    // ���� ����Ű�� ��ũ�� �̵�
    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
        CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

    // ������ ����Ű�� ��ũ�� �̵�
    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
        CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

    return 0;
}

// ������Ʈ ���� �۾� ����
void CLineMgr::Late_Update()
{
    // ����� Ư���� �۾� ����
}

// ȭ�鿡 �� ������
void CLineMgr::Render(HDC hDC)
{
    for (auto& pLine : m_Linelist)
        pLine->Render(hDC);
}

// �޸� �� �ڿ� ����
void CLineMgr::Release()
{
    // �� ����Ʈ�� ��� ���� �����ϰ� ����
    for_each(m_Linelist.begin(), m_Linelist.end(), Safe_Delete<CLine*>);
    m_Linelist.clear();
}

// �� �����͸� ���Ͽ� ����
void CLineMgr::Save_Line()
{
    HANDLE hFile = CreateFile(
        L"../Data/Line.dat",     // ���� ��ο� �̸�
        GENERIC_WRITE,           // ���� ����
        NULL,                    // ���� ����
        NULL,                    // �⺻ ����
        CREATE_ALWAYS,           // ���� ���� �����
        FILE_ATTRIBUTE_NORMAL,   // �Ϲ� ���� �Ӽ�
        NULL                     // ���ø� ���� ����
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {
        MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
        return;
    }

    DWORD dwByte = 0;

    // ��� �� �����͸� ���Ͽ� ����
    for (auto& pLine : m_Linelist)
    {
        WriteFile(hFile, pLine->Get_Info(), sizeof(LINE), &dwByte, nullptr);
    }

    CloseHandle(hFile);

    MessageBox(g_hWnd, _T("Save �Ϸ�"), L"����", MB_OK);
}

// �� �����͸� ���Ͽ��� �ҷ�����
void CLineMgr::Load_Line()
{
    Release(); // ���� ������ ����

    HANDLE hFile = CreateFile(
        L"../Data/Line.dat",     // ���� ��ο� �̸�
        GENERIC_READ,            // �б� ����
        NULL,                    // ���� ����
        NULL,                    // �⺻ ����
        OPEN_EXISTING,           // ���� ���� ����
        FILE_ATTRIBUTE_NORMAL,   // �Ϲ� ���� �Ӽ�
        NULL                     // ���ø� ���� ����
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {
        MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
        return;
    }

    DWORD dwByte = 0;
    LINE tLine{};

    // ���Ͽ��� �� �����͸� �о�� ����Ʈ�� �߰�
    while (true)
    {
        ReadFile(hFile, &tLine, sizeof(LINE), &dwByte, nullptr);

        if (0 == dwByte) // ���� �����Ͱ� ������ ����
            break;

        m_Linelist.push_back(new CLine(tLine));
    }

    CloseHandle(hFile);

    MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
}
