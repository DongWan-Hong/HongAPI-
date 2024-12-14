#include "pch.h"
#include "CStage.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "Block.h"
#include "BlockMgr.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image3/Town/SkyDay.bmp", L"Back1"); // �ǵ��� �ϴ�
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image3/Town/TownBGDay.bmp", L"Back2"); // �ǵڿ��� 2��°�� ��
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image3/Town/TownLayerDay.bmp", L"Back3"); // �ǵڿ��� 3��°�� ��
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image2/TownScene/Town.bmp", L"Ground");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image2/TownScene/Townx4.bmp", L"Ground3");

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	for (int i = 2; i < 10; i++) // �� ũ��� 180
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(i*50.f, 1200.f, 0.f));
	}
	




	//CTileMgr::Get_Instance()->Initialize();
	CBlockMgr::Get_Instance()->Initialize();

}

int CStage::Update()
{
	CObjMgr::Get_Instance()->Update();
	//CTileMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();
	return 0;
}

void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	//CTileMgr::Get_Instance()->Late_Update();
	CBlockMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hBack1DC = CBmpMgr::Get_Instance()->Find_Image(L"Back1");
	HDC hBack2DC = CBmpMgr::Get_Instance()->Find_Image(L"Back2");
	HDC hBack3DC = CBmpMgr::Get_Instance()->Find_Image(L"Back3");

	HDC hGroudkDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground3");
	
	//StretchBlt(hDC,
	//	iScrollX,
	//	iScrollY+700,
	//	2752,  // Ȯ��� ���� ũ��
	//	448,   // Ȯ��� ���� ũ��
	//	hBackDC,
	//	0,
	//	0,
	//	2752,      // ���� �̹��� ���� ũ��
	//	448,       // ���� �̹��� ���� ũ��
	//	SRCCOPY);  // ���� ���    // ������ ����

	BitBlt(hDC,
		0, 0, WINCX, WINCY,
		hBack1DC,
		0,
		0,
		SRCCOPY);

	GdiTransparentBlt(hDC,			
		0,
		200,
		1280.f,			 // �޾ƿ� �̹��� ��� �Ҳ���
		568.f,
		hBack2DC,
		0,			  // �̹��� ��ǥ
		0,
		1280.f,			// ������ �̹����� ����, ����
		568.f,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		iScrollX,
		iScrollY+900,
		1280.f,			 // �޾ƿ� �̹��� ��� �Ҳ���
		380.f,
		hBack3DC,
		0,			  // �̹��� ��ǥ
		0,
		1280.f,			// ������ �̹����� ����, ����
		380.f,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		iScrollX+1280,
		iScrollY + 900,
		1280.f,			 // �޾ƿ� �̹��� ��� �Ҳ���
		380.f,
		hBack3DC,
		0,			  // �̹��� ��ǥ
		0,
		1280.f,			// ������ �̹����� ����, ����
		380.f,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		iScrollX + 1280*2,
		iScrollY + 900,
		1280.f,			 // �޾ƿ� �̹��� ��� �Ҳ���
		380.f,
		hBack3DC,
		0,			  // �̹��� ��ǥ
		0,
		1280.f,			// ������ �̹����� ����, ����
		380.f,
		RGB(255, 0, 255));
	GdiTransparentBlt(hDC,
		iScrollX + 1280 * 3,
		iScrollY + 900,
		1280.f,			 // �޾ƿ� �̹��� ��� �Ҳ���
		380.f,
		hBack3DC,
		0,			  // �̹��� ��ǥ
		0,
		1280.f,			// ������ �̹����� ����, ����
		380.f,
		RGB(255, 0, 255));
	GdiTransparentBlt(hDC,
		iScrollX + 1280 * 4,
		iScrollY + 900,
		1280.f,			 // �޾ƿ� �̹��� ��� �Ҳ���
		380.f,
		hBack3DC,
		0,			  // �̹��� ��ǥ
		0,
		1280.f,			// ������ �̹����� ����, ����
		380.f,
		RGB(255, 0, 255));


	GdiTransparentBlt(hDC,
		iScrollX,
		iScrollY-200,
		7616.f,			 // �޾ƿ� �̹��� ��� �Ҳ���
		1536.f,
		hGroudkDC,
		0,			  // �̹��� ��ǥ
		0,
		7616.f,			// ������ �̹����� ����, ����
		1536.f,
		RGB(255,255, 255));

	// ������ ����


	CObjMgr::Get_Instance()->Render(hDC);
	//CTileMgr::Get_Instance()->Render(hDC);
	CBlockMgr::Get_Instance()->Render(hDC);
	
}

void CStage::Release()
{
	CBlockMgr::Get_Instance()->Destroy_Instance();
	CTileMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}
