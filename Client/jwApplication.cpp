#include "jwApplication.h"
#include "jwSceneManager.h"
#include "jwTime.h"
#include "jwInput.h"
#include "jwCollisionManager.h"
#include "jwCamera.h"

namespace jw
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
	{
	}
	Application::~Application()
	{
		//ScenenManager::Release();
		//Time::Release();
	}
	void Application::Initialize(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);
		mWidth = 1600;
		mHeight = 900;

		// 비트맵 해상도를 설정하기 위한 실제 윈도우 크기를 계산해준다.
		RECT rect = { 0,0,mWidth,mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// 윈도우 크기 변경 및 출력 설정
		SetWindowPos(mHwnd, nullptr, 100, 50, rect.right - rect.left, rect.bottom - rect.top, 0);
		
		ShowWindow(hwnd, true);

		// 백버퍼 화면 생성(크기) 및 dc생성
		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);
		mBackHDC = CreateCompatibleDC(mHdc);
		HBITMAP DefaultBitmap = (HBITMAP)SelectObject(mBackHDC, mBackBuffer);
		DeleteObject(DefaultBitmap);

		Time::Initialize();
		Input::Initialize();
		SceneManager::Initialize();
		Camera::Initialize();
	}
	void Application::Run()
	{
		Update();
		Render();
		SceneManager::Destroy();
	}
	void Application::Update()
	{
		Time::Update();
		Input::Update();
		Camera::Update();
		SceneManager::Update();
		CollisionManager::Update();
	}
	void Application::Render()
	{
		// clear
		clear();

		Time::Render(mBackHDC);
		Input::Render(mBackHDC);
		SceneManager::Render(mBackHDC);

		// 백버퍼의 화면을 원본에 옮기기
		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHDC, 0, 0, SRCCOPY);

	}
	void Application::clear()
	{
		HBRUSH grayBrush = CreateSolidBrush(RGB(121, 121, 121));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHDC, grayBrush);
		Rectangle(mBackHDC, -1, -1, 1602, 902);
		SelectObject(mBackHDC, oldBrush);
		DeleteObject(grayBrush);
	}
}