#include "Resource.h"
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

		// ��Ʈ�� �ػ󵵸� �����ϱ� ���� ���� ������ ũ�⸦ ������ش�.
		RECT rect = { 0,0,mWidth,mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// ������ ũ�� ���� �� ��� ����
		SetWindowPos(mHwnd, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 0);
		
		ShowWindow(hwnd, true);

		// ����� ȭ�� ����(ũ��) �� dc����
		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);
		mBackHDC = CreateCompatibleDC(mHdc);
		// �޴� ���� �ޱ�
		mMenubar = LoadMenu(nullptr, MAKEINTRESOURCE(IDI_CLIENT));

		HBITMAP DefaultBitmap = (HBITMAP)SelectObject(mBackHDC, mBackBuffer);
		DeleteObject(DefaultBitmap);

		Time::Initialize();
		Input::Initialize();
		SceneManager::Initialize();
		Camera::Initialize();

		SetMenuBar(false);
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
		//Camera::Render(mBackHDC);

		// ������� ȭ���� ������ �ű��
		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHDC, 0, 0, SRCCOPY);

	}
	void Application::SetMenuBar(bool power)
	{
		SetMenu(mHwnd, mMenubar);

		RECT rect = { 0, 0, mWidth , mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, power);

		// ������ ũ�� ����� ��� ����
		SetWindowPos(mHwnd
			, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(mHwnd, true);
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