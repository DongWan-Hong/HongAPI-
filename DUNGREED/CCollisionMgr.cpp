#include "pch.h"
#include "CCollisionMgr.h"
#include "CPlayer.h"

void CCollisionMgr::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, Dst->Get_Rect(), Src->Get_Rect()))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}

}

void CCollisionMgr::Collision_Circle(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Circle(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Circle(CObj* _Dst, CObj* _Src)
{
	float fRadius = (_Dst->Get_Info().fCX + _Src->Get_Info().fCX) * 0.5f;

	float fWidth  = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float fHeight = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);

	float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	return fRadius >= fDiagonal;
}
void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY))
			{
				CPlayer* pPlayer = dynamic_cast<CPlayer*>(Dst);
				if (pPlayer)
				{
					if (pPlayer->Get_Grivity()>=0)
					{ 
					if (fX > fY)// 상 하 충돌
					{
						// 상 충돌
						if (Dst->Get_Info().fY < Src->Get_Info().fY) // 플레이어 Y가 블럭 Y보다 높을때
						{
							if (Dst->Get_OBJID() == OBJ_PLAYER && Src->Get_OBJID() == OBJ_BLOCK)
							{
								Dst->OnCollision(Src);

							}
							Dst->Set_PosY(-fY);
						}
						// 하 충돌
						else
						{
							//Dst->Set_PosY(+fY);
						}

					}
					// 좌 우 충돌
					else
					{
						// 좌 충돌
						if (Dst->Get_Info().fX < Src->Get_Info().fX)
						{
							/*Dst->Set_PosX(-fX);*/
						}
						// 우 충돌
						else
						{
							/*Dst->Set_PosX(fX);*/
						}
					}
					}
				}
			}
		}
	}
}



void CCollisionMgr::Check_Block(list<CObj*> _Dst, list<CObj*> _Src) // 주체 Dst 
{
	RECT rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, Dst->Get_Rect(), Src->Get_Rect()))
			{
				
			
				
			}
		}
	}

}

bool CCollisionMgr::Check_Rect(CObj* _Dst, CObj* _Src, float* pX, float* pY)
{

	float		fX = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float		fY = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);

	float		fRadiusX = (_Dst->Get_Info().fCX + _Src->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (_Dst->Get_Info().fCY + _Src->Get_Info().fCY) * 0.5f;

	if ((fRadiusX >= fX) && (fRadiusY >= fY))
	{
		*pX = fRadiusX - fX;
		*pY = fRadiusY - fY;
		return true;
	}

	return false;
}
