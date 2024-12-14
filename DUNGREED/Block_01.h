#pragma once
#include "Block.h"

class CBlock_01 :public CBlock
{
public:
	CBlock_01();
	~CBlock_01();

	void Initialize() override;
	void Render(HDC hDC) override;
private:

};





