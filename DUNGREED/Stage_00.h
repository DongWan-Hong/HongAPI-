#pragma once
#include "CScene.h"
#include "Define.h"


class CStage_00 : public CScene
{
public:
	CStage_00();
	~CStage_00();

private:


	// CScene��(��) ���� ��ӵ�
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

};

