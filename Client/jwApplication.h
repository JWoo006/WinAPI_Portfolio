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
		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		void clear();

	private:
		// 핸들
		HWND mHwnd;
		HDC mHdc;

		// 백버퍼 비트맵, dc
		HBITMAP mBackBuffer;
		HDC mBackHDC;

		// 해상도
		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;

		// 씬구분
		//Scene mScene[100];
	};

}