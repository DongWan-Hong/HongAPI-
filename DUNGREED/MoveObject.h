#pragma once

#include "CObj.h"



class CMoveObject : public CObj
{
public:
	CMoveObject ();
	~CMoveObject ();

private:


	
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;



};
