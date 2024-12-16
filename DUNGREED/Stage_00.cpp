#include "pch.h"
#include "Stage_00.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "BaseBlock.h"
#include "BlockMgr.h"
#include "CPlayer.h"
#include "UIBase.h"
#include "Inven.h"

CStage_00::CStage_00()
{
}

CStage_00::~CStage_00()
{
	Release();
}

void CStage_00::Initialize()
{
	ADD_BMP(L"../Image3/Dungeon/SubBG2.bmp", L"Back1");

	ADD_BMP(L"../Image3/UI/Keyboard_Space2.bmp", L"Key_SapceBar");

	ADD_BMP(L"../Image3/UI/Keyboard_S2.bmp", L"Key_S");

	ADD_BMP(L"../Image3/UI/Keyboard_Plus1.bmp", L"Key_Plus");

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	//CBlockMgr::Get_Instance()->Initialize();

	// UI 매니저 테스트


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



	HDC hBack1DC = FIND_BMP(L"Back1");

	HDC h_Space_DC = FIND_BMP(L"Key_SapceBar");

	HDC h_Space_DC2 = FIND_BMP(L"Key_SapceBar");

	HDC hKey_S_DC = FIND_BMP(L"Key_S");

	HDC hKey_Plus_DC = FIND_BMP(L"Key_Plus");

	BitBlt(hDC,
		0, 0, WINCX, WINCY,
		hBack1DC,
		0,
		0,
		SRCCOPY);



	GdiTransparentBlt(hDC,
		 iScrollX+700,
		 iScrollY+900,
		186, 84,  // 효과 크기
		h_Space_DC,
		0,
		0,
		186, 84,
		RGB(255, 255, 255));

	GdiTransparentBlt(hDC,
		iScrollX + 2330,
		iScrollY + 705,
		65, 70,  // 효과 크기
		hKey_S_DC,
		0,
		0,
		65, 70,
		RGB(255, 255, 255));

	GdiTransparentBlt(hDC,
		iScrollX + 2450,
		iScrollY + 700,
		186, 84,  // 효과 크기
		h_Space_DC2,
		0,
		0,
		186, 84,
		RGB(255, 255, 255));


	GdiTransparentBlt(hDC,
		iScrollX + 2390,
		iScrollY + 710,
		60, 60,  // 효과 크기
		hKey_Plus_DC,
		0,
		0,
		60, 60,
		RGB(255, 255, 255));


	CObjMgr::Get_Instance()->Render(hDC);

	//CBlockMgr::Get_Instance()->Render(hDC);

}

void CStage_00::Release()
{
	CBlockMgr::Get_Instance()->Destroy_Instance();
	CTileMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}
