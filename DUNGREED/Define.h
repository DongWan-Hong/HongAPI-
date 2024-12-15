#pragma once

#define WINCX		1024
#define WINCY		768

#define	PURE		= 0
#define PI			3.141592f

#define OBJ_NOEVENT			0
#define OBJ_DEAD			1	

#define VK_MAX				0xff

#define	TILECX				64
#define	TILECY				64

#define TILEX				5
#define TILEY				5

#define ADD_BMP(file, name)   CBmpMgr::Get_Instance()->Insert_Bmp(file, name); 
#define FIND_BMP(key) CBmpMgr::Get_Instance()->Find_Image(key)

extern HWND		g_hWnd;
extern bool m_bInven;
enum DRAWPOINT { HEAD, TAIL, DRAWPOINT_END };
enum DRAWDIR { NO_DIR, HORIZONTAL, VERTICAL, DRAWDIR_END };
enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_END };


enum RENDERID { RENDER_BACKGROUND, RENDER_GAMEOBJECT, RENDER_UI, RENDER_EFFECT, RENDER_END };

enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_Test,SC_STAGE,SC_END };

enum BLOCKTYPE { BLOCK1, BLOCK2, BLOCK3, BLOCK4, BLOCK5, BLOCKTYPE_END };

enum ITEMTYPE { IT_WEAPON, IT_SHIELD, IT_END };

enum STATE { EQUIP, UNEQUIP, ST_END };

struct Trail 
{
	float x, y;       // 잔상의 위치
	float alpha;      // 잔상의 투명도
	DWORD startTime;  // 잔상 생성 시간
};


enum OBJID 
{ 
	OBJ_MOUSE,
	OBJ_BLOCK,
	OBJ_PLAYER,
	OBJ_BULLET, 
	OBJ_MONSTER, 
	OBJ_SHIELD, 
	OBJ_BUTTON,
	OBJ_END 
};



typedef struct tagInfo
{
	float		fX, fY;
	float		fCX, fCY;	// 가로, 세로 길이

}INFO;

typedef struct tagLinePoint
{
	float		fX, fY;

	tagLinePoint()	{ZeroMemory(this, sizeof(tagLinePoint));}
		tagLinePoint(float _fX, float _fY)
		: fX(_fX), fY(_fY)
	{	}

}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT	tLPoint;
	LINEPOINT	tRPoint;

	tagLine() { 	ZeroMemory(this, sizeof(tagLine));	}
	tagLine(LINEPOINT& _tLPoint, LINEPOINT& _tRPoint)
		: tLPoint(_tLPoint), tRPoint(_tRPoint) {	}

}LINE;

typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;
	ULONGLONG	dwSpeed;
	ULONGLONG	dwTime;

}FRAME;


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

struct tagFinder
{
public:
	tagFinder(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool	operator()(T& rObj)
	{
		return !lstrcmp(m_pString, rObj.first);
	}

private:
	const TCHAR* m_pString;
};

struct DeleteMap
{
public:
	template<typename T>
	void	operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};

