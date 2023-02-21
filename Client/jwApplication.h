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

	private:
		HWND mHwnd;
		HDC mHdc;

		Vector2 mPos;

		// ������
		//Scene mScene[100];
	};

}