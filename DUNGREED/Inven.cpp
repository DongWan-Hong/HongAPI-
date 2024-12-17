#include "pch.h"
#include "Inven.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CObj.h"
#include "CPlayer.h"
#include "CObjMgr.h"
#include "CScrollMgr.h"



CInven::CInven()
    : m_pInven_Player(nullptr), m_iSize(15) // 초기화 리스트
{
   
    m_vecInven.reserve(m_iSize); // 최대 크기 설정
}

CInven::~CInven()
{
    Release();
}

void CInven::AddItem(CObj* pItem)
{
    if (m_vecInven.size() >= m_iSize) // 인벤토리 크기 초과 방지
    {
       
        return;
    }

    m_vecInven.push_back(pItem);
  
}

void CInven::RemoveItem(CObj* pItem)
{
    auto it = std::find(m_vecInven.begin(), m_vecInven.end(), pItem);
    if (it != m_vecInven.end())
    {
        m_vecInven.erase(it);
     
    }
}


void CInven::Initialize()
{
    m_vecInven.clear(); // 기존 아이템 제거
    m_pInven_Player = nullptr; // 플레이어 초기화
    ADD_BMP(L"../Image3/Inventory/InventoryBase2.bmp",L"Inven_UI");


}

int CInven::Update()
{
    // UI 상태 확인 및 키 입력 처리
    if (CKeyMgr::Get_Instance()->Key_Down('i')) {
        CPlayer::m_bInven = !CPlayer::m_bInven; // 인벤토리 UI 토글
    }

    

    return OBJ_NOEVENT;
}

void CInven::Render(HDC hDC)
{
    if (!CPlayer::m_bInven) return; // 인벤토리 열려있지 않으면 리턴

    HDC hInvenDC = FIND_BMP(L"Inven_UI");
    BitBlt(hDC, 620, 80, WINCX, WINCY, hInvenDC, 0, 0, SRCCOPY);

    const int iEquipSlot_X = 670;
    const int iEquipSlot_Y = 180;

    const int iInven_Start_X = 654;
    const int iInven_Start_Y = 370;
    const int iSlot_Size = 50;
    const int iSLOT_Jump = 20;
    const int iSlot_width = 5;
    const int iSlot_length = 3;

    int iItemIndex = 0;

    POINT ptMouse;
    GetCursorPos(&ptMouse);
    ScreenToClient(g_hWnd, &ptMouse);

    int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
    int mouseX = ptMouse.x - iScrollX;
    int mouseY = ptMouse.y - iScrollY;

    // 마우스 좌표 출력
    TCHAR szMouseDebug[128];
    _stprintf_s(szMouseDebug, L"Mouse: X=%d, Y=%d", mouseX, mouseY);
    TextOut(hDC, 10, 300, szMouseDebug, _tcslen(szMouseDebug));

    for (int i = 0; i < iSlot_length; ++i)
    {
        for (int j = 0; j < iSlot_width; ++j)
        {
            if (iItemIndex >= m_vecInven.size()) return;

            CItem* pItem = dynamic_cast<CItem*>(m_vecInven[iItemIndex]);
            if (!pItem) continue;

            int posX = iInven_Start_X + j * (iSlot_Size + iSLOT_Jump) - iScrollX;
            int posY = iInven_Start_Y + i * (iSlot_Size + iSLOT_Jump) - iScrollY;

           
            TCHAR szSlotDebug[128];
            _stprintf_s(szSlotDebug, L"Slot[%d]: X=%d~%d, Y=%d~%d", iItemIndex, posX, posX + iSlot_Size, posY, posY + iSlot_Size);
            TextOut(hDC, 10, 350 + (iItemIndex * 20), szSlotDebug, _tcslen(szSlotDebug));

           
            if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON) && // Key_Pressing 사용
                mouseX >= posX && mouseX <= posX + iSlot_Size &&
                mouseY >= posY && mouseY <= posY + iSlot_Size)
            {
                ToggleEquip(pItem);
            }


            if (pItem->IsEquipped())
            {
                pItem->Set_Pos((float)iEquipSlot_X, (float)iEquipSlot_Y);
            }
            else
            {
                pItem->Set_Pos((float)posX + iScrollX, (float)posY + iScrollY);
            }

            pItem->Render(hDC);

            ++iItemIndex;
        }
    }
}





void CInven::Release()
{
    
    for (auto& pObj : m_vecInven) 
    {

        delete pObj;
        pObj = nullptr;
    }
    m_vecInven.clear();
    m_pInven_Player = nullptr;

  
}

void CInven::Equip_Item()
{
    if (m_pInven_Player && !m_vecInven.empty())
    {
        CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_pInven_Player);
        if (pPlayer)
        {
            CItem* pItem = dynamic_cast<CItem*>(m_vecInven.front());
            if (pItem)
            {
                pPlayer->Equip(pItem);
                m_vecInven.erase(m_vecInven.begin());
            }
        }
    }
}


void CInven::Unequip_Item()
{
    if (m_pInven_Player)
    {
        CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_pInven_Player);
        if (pPlayer)
        {
            CItem* pUnequippedItem = pPlayer->UnEquip();
            if (pUnequippedItem)
                m_vecInven.push_back(pUnequippedItem);
        }
    }
}

void CInven::ToggleEquip(CItem* pItem)
{
    if (!pItem) return;

    CPlayer* pPlayer = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player());
    if (!pPlayer) return;

    static DWORD dwLastClickTime = 0;  // 마지막 우클릭 시간
    DWORD currentTime = GetTickCount64();

    // 1초 이내에 두 번째 우클릭 감지
    if (currentTime - dwLastClickTime <= 1000)
    {
        // 아이템 장착 또는 해제
        if (pItem->IsEquipped()) // 이미 장착된 아이템이면 해제
        {
            pItem->SetEquipped(false); // 아이템 상태 해제
            if (!m_pInven_Player) return;

            // 플레이어에서 해제된 아이템을 인벤토리로 다시 추가
            pPlayer->UnEquip();
        }
        else // 장착되지 않은 아이템이면 장착
        {
            if (pPlayer->GetEquip_Item()) // 기존 아이템 해제
            {
                CItem* pUnequipped = pPlayer->UnEquip();
                if (pUnequipped)
                {
                    pUnequipped->SetEquipped(false);
                }
            }
            pItem->SetEquipped(true); // 새로운 아이템 장착
            pPlayer->Equip(pItem);
        }
    }

    dwLastClickTime = currentTime;  
}

