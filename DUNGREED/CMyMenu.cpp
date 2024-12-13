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
    
    static int scrollX = 0; // ������ ���� x ��ǥ
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");

    int iImageWidth = 2000; // ���� ���� ũ��

    // ������ ���������� 

    scrollX -= 2; // ��ũ�� �ӵ�
    if (scrollX <= -iImageWidth) 
    {
        scrollX = 0; // �̹����� �� �������� �ʱ�ȭ
    }

    // ù ��° ���� ���
    BitBlt(hDC,
        scrollX,  
        0, 
        iImageWidth, 
        WINCY, // ��ũ�� ��ġ�� ���� ���
        hMemDC,
        0,
        0,
        SRCCOPY);

    BitBlt(hDC, // ���� ��� ���
        scrollX + iImageWidth,
        0, 
        iImageWidth, 
        WINCY, // ù ��° �̹��� �ڿ� ���
        hMemDC,
        0, 0,
        SRCCOPY);

    
  

    hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MainLogo");


    GdiTransparentBlt(
        hDC,
        170,           // X ��ǥ
        60,          // Y ��ǥ
        693,                                   // �̹��� ���� ũ��
        333,                                   // �̹��� ���� ũ��
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
