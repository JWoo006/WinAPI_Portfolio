#include "jwApplication.h"
#include "jwScenenManager.h"
#include "jwTime.h"
#include "jwInput.h"

namespace jw
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
	{
	}
	Application::~Application()
	{
		ScenenManager::Release();
		//Time::Release();
	}
	void Application::Initialize(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		Time::Initialize();
		Input::Initialize();
		ScenenManager::Initialize();
	}
	void Application::Run()
	{
		Update();
		Render();
	}
	void Application::Update()
	{
		Time::Update();
		Input::Update();
		ScenenManager::Update();
	}
	void Application::Render()
	{
		Time::Render(mHdc);
		Input::Render(mHdc);
		ScenenManager::Render(mHdc);	
	}
}