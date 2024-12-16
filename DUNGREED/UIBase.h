#pragma once
#include "CObj.h"

class CUI : public CObj
{
	

public:
	CUI(bool _boffsetaff);
	virtual ~CUI();
private:
	vector<CUI*> m_vecChildUI;
	CUI* m_pParentUI;
public:
	CUI* Get_Parent() { return m_pParentUI; }
	void AddChild(CUI* _pUI) 
	{ 
		m_vecChildUI.push_back(_pUI);  // 자식 UI가 들어오면 벡터에 넣어주고
		_pUI->m_pParentUI = this;  // 벡터에 부모 넣어주기

	}
	bool Get_MouseOn() // 마우스가 UI 위에 있는지 여부
	{
		return m_bMouseOn;
	}
private:
	void Update_Child();
	void Render_Child(HDC hDC);
	void LateUpdate_Child();

public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;
	virtual void MouseOn();

public:

	virtual void MouseOnCheck();


	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked(); \


private:
	float m_fFinalX;  // 최종 X 좌표
	float m_fFinalY;  // 최종 Y 좌표


	bool m_bOffset_Affected;// UI가 카메라 영향을 받는지 여부 
	bool m_bMouseOn;    // UI 위에 마우스가 있는지!
	bool m_blbtnDown;   // UI 에 왼쪽버튼이 눌린적이 있는지

	friend class CUIMgr;
};



