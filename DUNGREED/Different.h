#pragma once
#include "CObj.h"

class CDifferent : public CObj  // ���ΰ� ����ٴϴ� �ǵ� ����� ����� �ߴµ� �Ⱦ���
{
public:
	CDifferent();
	virtual ~CDifferent();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

