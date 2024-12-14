#pragma once
#include "CObj.h"

class CStaticObj :public CObj
{
public:
	CStaticObj();
	~CStaticObj();

private:

	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

};

