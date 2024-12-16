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
		m_vecChildUI.push_back(_pUI);  // �ڽ� UI�� ������ ���Ϳ� �־��ְ�
		_pUI->m_pParentUI = this;  // ���Ϳ� �θ� �־��ֱ�

	}
	bool Get_MouseOn() // ���콺�� UI ���� �ִ��� ����
	{
		return m_bMouseOn;
	}
private:
	void Update_Child();
	void Render_Child(HDC hDC);
	void LateUpdate_Child();

public:
	// CObj��(��) ���� ��ӵ�
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
	float m_fFinalX;  // ���� X ��ǥ
	float m_fFinalY;  // ���� Y ��ǥ


	bool m_bOffset_Affected;// UI�� ī�޶� ������ �޴��� ���� 
	bool m_bMouseOn;    // UI ���� ���콺�� �ִ���!
	bool m_blbtnDown;   // UI �� ���ʹ�ư�� �������� �ִ���

	friend class CUIMgr;
};



