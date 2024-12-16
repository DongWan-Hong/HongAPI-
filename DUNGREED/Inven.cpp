#include "pch.h"
#include "Inven.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CObj.h"
#include "CPlayer.h"
#include "CObjMgr.h"
#include "CScrollMgr.h"



CInven::CInven()
    : m_pInven_Player(nullptr), m_iSize(15) // �ʱ�ȭ ����Ʈ
{
   
    m_vecInven.reserve(m_iSize); // �ִ� ũ�� ����
}

CInven::~CInven()
{
    Release();
}

void CInven::AddItem(CObj* pItem)
{
    if (m_vecInven.size() >= m_iSize) // �κ��丮 ũ�� �ʰ� ����
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
    m_vecInven.clear(); // ���� ������ ����
    m_pInven_Player = nullptr; // �÷��̾� �ʱ�ȭ
    ADD_BMP(L"../Image3/Inventory/InventoryBase2.bmp",L"Inven_UI");


}

int CInven::Update()
{
    // UI ���� Ȯ�� �� Ű �Է� ó��
    if (CKeyMgr::Get_Instance()->Key_Down('i')) {
        CPlayer::m_bInven = !CPlayer::m_bInven; // �κ��丮 UI ���
    }

    

    return OBJ_NOEVENT;
}

void CInven::Render(HDC hDC)
{
    if (!CPlayer::m_bInven) return;

    HDC hInvenDC = FIND_BMP(L"Inven_UI");
    BitBlt(hDC, 620, 80, WINCX, WINCY, hInvenDC, 0, 0, SRCCOPY);

    const int iInven_Start_X = 654;
    const int iInven_Start_Y = 370;
    const int iSlot_Size = 50;
    const int iSLOT_Jump = 20;
    const int iSlot_width = 5;
    const int iSlot_length = 3;

    int iItemIndex = 0;
    POINT ptMouse;
    GetCursorPos(&ptMouse);
    ScreenToClient(g_hWnd, &ptMouse); // ���콺 ��ǥ ��������

    int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
    ptMouse.x -= iScrollX;
    ptMouse.y -= iScrollY;

    TCHAR szBuffer[64];
    _stprintf_s(szBuffer, _T("inv: X=%d, Y=%d"), ptMouse.x, ptMouse.y);

    SetTextColor(hDC, RGB(255, 255, 255));  // ���� ���� (���)
    SetBkMode(hDC, TRANSPARENT);           // ��� ���� ó��
    TextOut(hDC, 10, 300, szBuffer, (int)_tcslen(szBuffer)); // ��ǥ ��� ��ġ (10, 10)


    for (int i = 0; i < iSlot_length; ++i)
    {
        for (int j = 0; j < iSlot_width; ++j)
        {
            if (iItemIndex >= m_vecInven.size()) return;

            int posX = iInven_Start_X + j * (iSlot_Size + iSLOT_Jump);
            int posY = iInven_Start_Y + i * (iSlot_Size + iSLOT_Jump);

            TCHAR szSlotBuffer[128];
            _stprintf_s(szSlotBuffer, _T("Slot[%d]: X=%d, Y=%d"), iItemIndex, posX, posY);
            TextOut(hDC, 10, 320 + (iItemIndex * 20), szSlotBuffer, (int)_tcslen(szSlotBuffer));

            // ���콺 ��Ŭ�� ����
            if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON) &&
                ptMouse.x >= posX && ptMouse.x <= posX + iSlot_Size &&
                ptMouse.y >= posY && ptMouse.y <= posY + iSlot_Size)
            {
                CItem* pItem = dynamic_cast<CItem*>(m_vecInven[iItemIndex]);
                if (pItem) // ��ȯ�� �������� ���� ����
                {
                    ToggleEquip(pItem);
                }

            }

            m_vecInven[iItemIndex]->Set_Pos((float)posX, (float)posY);
            m_vecInven[iItemIndex]->Render(hDC);
            ++iItemIndex;
        }
    }



}


void CInven::Release()
{
    // �޸� ����
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

    if (pItem->IsEquipped()) // �̹� ������ �������̸� ����
    {
        pItem->SetEquipped(false); // ������ ���� ����
        CItem* pUnequipped = pPlayer->UnEquip(); // �÷��̾��� ���� ����
        if (pUnequipped) m_vecInven.push_back(pUnequipped); // ������ �������� �κ��丮�� �߰�
    }
    else // �������� ���� �������̸� ����
    {
        if (pPlayer->GetEquip_Item()) // ���� ������ ����
        {
            CItem* pUnequipped = pPlayer->UnEquip();
            if (pUnequipped) m_vecInven.push_back(pUnequipped);
        }

        pItem->SetEquipped(true); // ������ ���� ����
        pPlayer->Equip(pItem);    // �÷��̾ ������ ����
    }
}