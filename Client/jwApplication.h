#pragma once
#include "JongEngine.h"

namespace jw
{
	// 게임 전체를 총괄하는 곳
	class Application
	{
	public:
		Application();
		~Application();

		// 초기화
		void Initialize(HWND hwnd);
		void Run();
		// 로직 실행부
		void Update();
		// 렌더링
		void Render();

		//void Release();

		HWND GetHwnd() { return mHwnd; }

	private:
		HWND mHwnd;
		HDC mHdc;

		Vector2 mPos;

		// 씬구분
		//Scene mScene[100];
	};

}