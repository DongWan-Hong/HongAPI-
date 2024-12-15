#pragma once
#include "CObj.h"

class CDifferent : public CObj  // 주인공 따라다니는 실드 만들어 놓기는 했는데 안쓸듯
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

