#include "jwToolScene.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwApplication.h"
#include "jwImage.h"
#include "jwResources.h"
#include "jwTile.h"
#include "jwObject.h"
#include "jwInput.h"

extern jw::Application application;

namespace jw
{
	ToolScene::ToolScene()
	{
	}
	ToolScene::~ToolScene()
	{
	}
	void ToolScene::Initialize()
	{
        Scene::Initialize();

        Image* tile = Resources::Find<Image>(L"TileAtlas");
        Tile* test = object::Instantiate<Tile>(eLayerType::Tile);
        test->InitializeTile(tile, 0);

		
	}
	void ToolScene::Update()
	{
        Scene::Update();

        /*if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
        {
            int next = (int)eSceneType::Tool;
            next++;
            if (next == (int)eSceneType::End)
            {
                next = (int)eSceneType::Title;
            }

            SceneManager::LoadScene((eSceneType)next);
        }*/

        Vector2  temp = Input::GetMousePos();

        
	}
	void ToolScene::Render(HDC hdc)
	{
        //±×¸®µå
        HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
        HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

        int maxRow = application.GetHeight() / TILE_SIZE_Y + 1;
        for (size_t y = 0; y < maxRow; y++)
        {
            MoveToEx(hdc, 0, TILE_SIZE_Y * y, NULL);
            LineTo(hdc, application.GetWidth(), TILE_SIZE_Y * y);
        }
        int maxColumn = application.GetWidth() / TILE_SIZE_X + 1;
        for (size_t x = 0; x < maxColumn; x++)
        {
            MoveToEx(hdc, TILE_SIZE_X * x, 0, NULL);
            LineTo(hdc, TILE_SIZE_X * x, application.GetHeight());
        }
        (HPEN)SelectObject(hdc, oldPen);
        DeleteObject(redPen);

		Scene::Render(hdc);

        Scene::SceneText(hdc);
	}
	void ToolScene::Release()
	{
	}
	void ToolScene::OnEnter()
	{
	}
	void ToolScene::OnExit()
	{
	}
}

#include "Resource.h"
LRESULT CALLBACK AtlasWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        //512 384
        jw::Image* tile = jw::Resources::Load<jw::Image>(L"TileAtlas", L"..\\Resources\\Tile.bmp");
        RECT rect = { 0, 0, tile->GetWidth(), tile->GetHeight() };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

        SetWindowPos(hWnd
            , nullptr, 1600, 0
            , rect.right - rect.left
            , rect.bottom - rect.top
            , 0);
        ShowWindow(hWnd, true);
    }


    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        jw::Image* tile = jw::Resources::Find<jw::Image>(L"TileAtlas");
        BitBlt(hdc, 0, 0, tile->GetWidth(), tile->GetHeight(), tile->GetHdc(), 0, 0, SRCCOPY);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}