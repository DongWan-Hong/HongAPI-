#include "pch.h"
#include "CMyMenu.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"

CMyMenu::CMyMenu()
{
}

CMyMenu::~CMyMenu()
{
    Release();
}

void CMyMenu::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image2/StartScene/BackCloud.Bmp", L"Menu");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image2/StartScene/GameStart1.Bmp", L"Menu1");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image2/StartScene/Quit1.Bmp", L"Menu2");


    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image2/StartScene/GameStart1.Bmp", L"Edit");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");


    CObj* pButton = CAbstractFactory<CMyButton>::Create(200.f, 400.f);
    pButton->Set_ImgKey(L"Start");
    CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

    pButton = CAbstractFactory<CMyButton>::Create(400.f, 400.f);
    pButton->Set_ImgKey(L"Edit");
    CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

    pButton = CAbstractFactory<CMyButton>::Create(600.f, 400.f);
    pButton->Set_ImgKey(L"Exit");
    CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);
}

int CMyMenu::Update()
{
    CObjMgr::Get_Instance()->Update();

    return 0;
}

void CMyMenu::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC hDC)
{
    // "Menu" 배경 그리기
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");
    BitBlt(hDC,
        0, 0, WINCX, WINCY,
        hMemDC,
        0,
        0,
        SRCCOPY);

    // "Menu1" GameStart 버튼 그리기
    HDC hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"Menu1");
    BitBlt(hDC,
        100, 200, 200, 50, // 버튼 위치와 크기
        hMemDC1,
        0,
        0,
        SRCCOPY);

    // "Menu2" Quit 버튼 그리기
    HDC hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"Menu2");
    BitBlt(hDC,
        100, 300, 200, 50, // 버튼 위치와 크기
        hMemDC2,
        0,
        0,
        SRCCOPY);

    // 기타 오브젝트 렌더링
    CObjMgr::Get_Instance()->Render(hDC);

}

void CMyMenu::Release()
{
    CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);
}
