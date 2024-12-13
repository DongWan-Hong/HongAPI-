#pragma once

#include "CTile.h"

class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	void		Picking_Tile(POINT pt, int iDrawID, int iOption);

public:
	static CTileMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CTileMgr;

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
	// 현재 타일 목록을 파일로 저장하는 함수
	void Save_Line();

	// 파일에서 선 목록을 불러오는 함수
	void Load_Line();

private:
	static CTileMgr* m_pInstance;

	vector<CObj*>	m_vecTile;

};

