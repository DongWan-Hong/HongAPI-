#include "pch.h"
#include "CSceneMgr.h"
#include "Stage_00.h"
#include "BlockMgr.h"
#include "CAbstractFactory.h"
#include "UIBase.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr() : m_pScene(nullptr), 
m_eCurScene(SC_LOGO), m_ePreScene(SC_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Set_Scene(SCENEID eID)
{
	

	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CLogo;
			break;

		case SC_MENU:
			m_pScene = new CMyMenu;
			break;

		case SC_EDIT:
			m_pScene = new CMyEdit;
			break;

		case SC_Test:
			m_pScene = new CStage_00;
			CBlockMgr::Get_Instance()->Load_Block(L"../Data/00_Stage.dat"); 
			break;

		case SC_STAGE:
			m_pScene = new CStage;
			break;
		}

		m_pScene->Initialize();

		//CObj* pUI = CAbstractFactory<CUI>::Create_UI(true);
		//m_pScene->Add_UI(pUI);

		m_ePreScene = m_eCurScene;
	}
}

int CSceneMgr::Update()
{
	m_pScene->Update();

	return 0;
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);

}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}
