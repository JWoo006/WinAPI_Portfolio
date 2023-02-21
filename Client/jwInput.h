#pragma once
#include "JongEngine.h"

namespace jw
{
	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		END,
	};

	enum class eKeyState
	{
		Down,
		Pressed,
		Up,
		None,
	};

	class Input
	{
	public:
		struct Key
		{
			// Ű
			eKeyCode key;
			// ����
			eKeyState state;
			bool bPressed;
		};


		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		inline static eKeyState GetKeyState(eKeyCode keyCode)
		{
			return mKeys[(UINT)keyCode].state;
		}

	private:
		// ����� Ű�� ���� ��ŭ �Ҵ�
		// �ݺ������� ��ȸ�ϸ鼭 �� Ű���� ���¸� üũ
		static std::vector<Key> mKeys;
	};

}


