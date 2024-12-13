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
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image2/StartScene/MainLogo.Bmp", L"MainLogo");
    



    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image2/StartScene/GameStart1.Bmp", L"Start");
   //CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
   CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image2/StartScene/Edit.bmp", L"Edit");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image2/StartScene/Quit1.Bmp", L"Exit");


    CObj* pButton = CAbstractFactory<CMyButton>::Create(520.f, 500.f);
    pButton->Set_ImgKey(L"Start");
    CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

   pButton = CAbstractFactory<CMyButton>::Create(350.f, 600.f);
   pButton->Set_ImgKey(L"Edit");
   CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

    pButton = CAbstractFactory<CMyButton>::Create(520.f, 600.f);
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
    
    static int scrollX = 0; // 구름의 현재 x 좌표
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");

    int iImageWidth = 2000; // 구름 가로 크기

    // 구름을 오른쪽으로 

    scrollX -= 2; // 스크롤 속도
    if (scrollX <= -iImageWidth) 
    {
        scrollX = 0; // 이미지가 다 지나가면 초기화
    }

    // 첫 번째 구름 출력
    BitBlt(hDC,
        scrollX,  
        0, 
        iImageWidth, 
        WINCY, // 스크롤 위치에 따라 출력
        hMemDC,
        0,
        0,
        SRCCOPY);

    BitBlt(hDC, // 구름 계속 출력
        scrollX + iImageWidth,
        0, 
        iImageWidth, 
        WINCY, // 첫 번째 이미지 뒤에 출력
        hMemDC,
        0, 0,
        SRCCOPY);

    
  

    hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MainLogo");


    GdiTransparentBlt(
        hDC,
        170,           // X 좌표
        60,          // Y 좌표
        693,                                   // 이미지 가로 크기
        333,                                   // 이미지 세로 크기
        hMemDC,
        0,
        0,
        693,
        333,
        RGB(255, 0, 255));



   

    


    CObjMgr::Get_Instance()->Render(hDC);

}

void CMyMenu::Release()
{
    CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);
}
