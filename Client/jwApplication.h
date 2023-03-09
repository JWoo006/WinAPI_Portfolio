#pragma once
#include "JongEngine.h"

namespace jw
{
	// ���� ��ü�� �Ѱ��ϴ� ��
	class Application
	{
	public:
		Application();
		~Application();

		// �ʱ�ȭ
		void Initialize(HWND hwnd);
		void Run();
		// ���� �����
		void Update();
		// ������
		void Render();

		//void Release();

		HWND GetHwnd() { return mHwnd; }
		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		void clear();

	private:
		// �ڵ�
		HWND mHwnd;
		HDC mHdc;

		// ����� ��Ʈ��, dc
		HBITMAP mBackBuffer;
		HDC mBackHDC;

		// �ػ�
		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;

		// ������
		//Scene mScene[100];
	};

}