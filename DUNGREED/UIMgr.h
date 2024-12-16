#pragma once

#include "Define.h"
#include "UIBase.h"

class CUIMgr
{
public:
    SINGLE(CUIMgr);

    void Initialize();

    void Update();  

    void Render(HDC hDC);  



private:
	
    map<string, CUI*> m_UIElements; // UI 요소들을 저장

};

