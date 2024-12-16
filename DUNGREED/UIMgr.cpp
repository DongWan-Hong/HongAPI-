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
                // ���콺�� UI�� �ö� �ִ��� üũ
                if (pUI->Get_MouseOn())
                {
                    pUI->MouseOnCheck();


                    if (bLbtnTap)
                    {
                        pUI->MouseLbtnDown(); // Ŭ�� " �� �� " ������
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

