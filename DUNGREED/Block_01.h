#pragma once
#include "BaseBlock.h"

class CBlock_01 :public CBaseBlock
{
public:
	CBlock_01();
	~CBlock_01();

	void Initialize() override;
	void Render(HDC hDC) override;
private:

};





