#include "pch.h"
#include "UIMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "UIBase.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CKeyMgr.h"



void CUIMgr::Initialize()
{
}

void CUIMgr::Update()
{
    CScene* pCurScene = CSceneMgr::Get_Instance()->Get_CurScene();




    bool bLbtnTap = CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON);
    bool bLbtnAway = CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON);

    if (pCurScene)
    {
        const vector<CObj*>& vecUI = pCurScene->Get_UI_Group();

        for (CObj* pObj : vecUI)
        {
            CUI* pUI = dynamic_cast<CUI*>(pObj);
            if (pUI)
            {
                // 마우스가 UI에 올라가 있는지 체크
                if (pUI->Get_MouseOn())
                {
                    pUI->MouseOnCheck();


                    if (bLbtnTap)
                    {
                        pUI->MouseLbtnDown(); // 클릭 " 딸 깍 " 했을때
                        pUI->m_blbtnDown = true;
                    }
                    else if (bLbtnAway)
                    {
                        pUI->MouseLbtnUp(); 
                    }


                }
            }
        }
    }
}

void CUIMgr::Render(HDC hDC)
{
}

