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
			// 키
			eKeyCode key;
			// 상태
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
		// 사용할 키의 개수 만큼 할당
		// 반복문으로 순회하면서 각 키들의 상태를 체크
		static std::vector<Key> mKeys;
	};

}


