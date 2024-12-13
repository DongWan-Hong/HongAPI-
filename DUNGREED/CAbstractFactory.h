#pragma once

#include "CObj.h"
#include "Block.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {};

public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _fAngle = 0.f)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		
		if(0.f != _fAngle)
			pObj->Set_Angle(_fAngle);

		return pObj;
	}
	static CObj* Create_Block(float _fX, float _fY, float _fCX, float _fCY)
	{
		CBlock* pBlock = new CBlock(_fX, _fY, _fCX, _fCY);
		pBlock->Initialize();
		return pBlock;
	}
	
};

