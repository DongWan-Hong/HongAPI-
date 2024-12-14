#pragma once
#include "CCollisionMgr.h"

class CBoxCollider : public CCollisionMgr
{
public:
	CBoxCollider();
	~CBoxCollider();

public:
     void Initialize() ;
     int Update() ;
     void Late_Update() ;
     void Render(HDC hDC) ;
     void Release() ;

private:


 
};



