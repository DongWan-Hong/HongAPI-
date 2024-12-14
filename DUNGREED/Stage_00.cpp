#include "pch.h"
#include "Stage_00.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "Block.h"
#include "BlockMgr.h"
#include "CPlayer.h"

CStage_00::CStage_00()
{
}

CStage_00::~CStage_00()
{
	Release();
}

void CStage_00::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image3/Town/SkyDay.bmp", L"Back1"); // 맨뒤의 하늘


	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	for (int i = 2; i < 30; i++) // 블럭 크기는 180
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(i * 50.f, 1175.f, 0.f));
	}
		CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(500.f, 1060.f, 0.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(550.f, 1060.f, 0.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(600.f, 1060.f, 0.f));



	//CTileMgr::Get_Instance()->Initialize();
	//CBlockMgr::Get_Instance()->Initialize();

}

int CStage_00::Update()
{
	CObjMgr::Get_Instance()->Update();
	//CBlockMgr::Get_Instance()->Update();
	return 0;
}

void CStage_00::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	//CBlockMgr::Get_Instance()->Late_Update();
}

void CStage_00::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hBack1DC = CBmpMgr::Get_Instance()->Find_Image(L"Back1");



StretchBlt(hDC,
	0,
	0,
	1280,  // 확대된 가로 크기
	900,   // 확대된 세로 크기
	hBack1DC,
	0,
	0,
	1280,      // 원본 이미지 가로 크기
	720,       // 원본 이미지 세로 크기
	SRCCOPY);  // 복사 방식    // 제거할 색상



  

	

	

	CObjMgr::Get_Instance()->Render(hDC);
	//CBlockMgr::Get_Instance()->Render(hDC);

}

void CStage_00::Release()
{
	CBlockMgr::Get_Instance()->Destroy_Instance();
	CTileMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}
