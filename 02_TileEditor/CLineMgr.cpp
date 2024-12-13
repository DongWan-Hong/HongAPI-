#include "pch.h" // 미리 컴파일된 헤더 파일 포함
#include "CLineMgr.h" // CLineMgr 클래스 선언 포함
#include "CKeyMgr.h" // CKeyMgr 클래스 선언 포함
#include "CScrollMgr.h" // CScrollMgr 클래스 선언 포함

// CLineMgr의 정적 멤버 초기화
CLineMgr* CLineMgr::m_pInstance = nullptr;


CLineMgr::CLineMgr()
{
    // 선의 시작점과 끝점을 초기화
    ZeroMemory(m_tLinePoint, sizeof(m_tLinePoint));
}


CLineMgr::~CLineMgr()
{
    Release();
}

// 플레이어의 중심축x에 선과의 충돌 여부 확인 및 y좌표 반환
//  Y좌표는  플레이어Y= 선의 시작점과 끝점사이의 Y증가량/선의 시작점과 끝점
bool CLineMgr::Collision_Line(float _fX, float* pY)
{
    // 선 리스트가 비어있으면 충돌 없음
    if (m_Linelist.empty())
        return false;

    CLine* pTargetLine = nullptr; // 충돌한 선을 저장할 포인터

    // 선 리스트를 순회하여 x좌표가 포함된 선을 찾음
    for (auto& pLine : m_Linelist)
    {
        if (_fX >= pLine->Get_Info()->tLPoint.fX &&
            _fX < pLine->Get_Info()->tRPoint.fX)
        {
            pTargetLine = pLine;
        }
    }

    // 충돌한 선이 없으면 false 반환
    if (!pTargetLine)
        return false;

    // 선의 양 끝 점 좌표 가져오기
    float x1 = pTargetLine->Get_Info()->tLPoint.fX;
    float y1 = pTargetLine->Get_Info()->tLPoint.fY;
    float x2 = pTargetLine->Get_Info()->tRPoint.fX;
    float y2 = pTargetLine->Get_Info()->tRPoint.fY;

    // 직선의 방정식을 이용해 y좌표 계산
    *pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

    return true;
}

// 초기화 함수
void CLineMgr::Initialize()
{
    // 현재는 특별한 작업 없음
}

// 업데이트 함수
int CLineMgr::Update()
{
    POINT ptMouse{};
    // 마우스 커서 위치 가져오기
    GetCursorPos(&ptMouse);
    // 화면 좌표를 클라이언트 좌표로 변환
    ScreenToClient(g_hWnd, &ptMouse);
    // 스크롤 오프셋 적용
    ptMouse.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();

    // 마우스 왼쪽 버튼 클릭 시
    if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
    {
        // 첫 번째 점이 비어있으면 초기화
        if ((!m_tLinePoint[LEFT].fX) && (!m_tLinePoint[LEFT].fY))
        {
            m_tLinePoint[LEFT].fX = (float)ptMouse.x;
            m_tLinePoint[LEFT].fY = (float)ptMouse.y;
        }
        else // 두 번째 점 설정 및 선 추가
        {
            m_tLinePoint[RIGHT].fX = (float)ptMouse.x;
            m_tLinePoint[RIGHT].fY = (float)ptMouse.y;

            m_Linelist.push_back(new CLine(m_tLinePoint[LEFT], m_tLinePoint[RIGHT]));

            m_tLinePoint[LEFT].fX = m_tLinePoint[RIGHT].fX;
            m_tLinePoint[LEFT].fY = m_tLinePoint[RIGHT].fY;
        }
    }

    // 'S' 키로 선 저장
    if (CKeyMgr::Get_Instance()->Key_Down('S'))
    {
        Save_Line();
        return 0;
    }

    // 'L' 키로 선 불러오기
    if (CKeyMgr::Get_Instance()->Key_Down('L'))
    {
        Load_Line();
        return 0;
    }

    // 왼쪽 방향키로 스크롤 이동
    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
        CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

    // 오른쪽 방향키로 스크롤 이동
    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
        CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

    return 0;
}

// 업데이트 이후 작업 수행
void CLineMgr::Late_Update()
{
    // 현재는 특별한 작업 없음
}

// 화면에 선 렌더링
void CLineMgr::Render(HDC hDC)
{
    for (auto& pLine : m_Linelist)
        pLine->Render(hDC);
}

// 메모리 및 자원 해제
void CLineMgr::Release()
{
    // 선 리스트의 모든 선을 안전하게 삭제
    for_each(m_Linelist.begin(), m_Linelist.end(), Safe_Delete<CLine*>);
    m_Linelist.clear();
}

// 선 데이터를 파일에 저장
void CLineMgr::Save_Line()
{
    HANDLE hFile = CreateFile(
        L"../Data/Line.dat",     // 파일 경로와 이름
        GENERIC_WRITE,           // 쓰기 전용
        NULL,                    // 공유 없음
        NULL,                    // 기본 보안
        CREATE_ALWAYS,           // 기존 파일 덮어쓰기
        FILE_ATTRIBUTE_NORMAL,   // 일반 파일 속성
        NULL                     // 템플릿 파일 없음
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {
        MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
        return;
    }

    DWORD dwByte = 0;

    // 모든 선 데이터를 파일에 저장
    for (auto& pLine : m_Linelist)
    {
        WriteFile(hFile, pLine->Get_Info(), sizeof(LINE), &dwByte, nullptr);
    }

    CloseHandle(hFile);

    MessageBox(g_hWnd, _T("Save 완료"), L"성공", MB_OK);
}

// 선 데이터를 파일에서 불러오기
void CLineMgr::Load_Line()
{
    Release(); // 기존 데이터 해제

    HANDLE hFile = CreateFile(
        L"../Data/Line.dat",     // 파일 경로와 이름
        GENERIC_READ,            // 읽기 전용
        NULL,                    // 공유 없음
        NULL,                    // 기본 보안
        OPEN_EXISTING,           // 기존 파일 열기
        FILE_ATTRIBUTE_NORMAL,   // 일반 파일 속성
        NULL                     // 템플릿 파일 없음
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {
        MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
        return;
    }

    DWORD dwByte = 0;
    LINE tLine{};

    // 파일에서 선 데이터를 읽어와 리스트에 추가
    while (true)
    {
        ReadFile(hFile, &tLine, sizeof(LINE), &dwByte, nullptr);

        if (0 == dwByte) // 읽을 데이터가 없으면 종료
            break;

        m_Linelist.push_back(new CLine(tLine));
    }

    CloseHandle(hFile);

    MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}
