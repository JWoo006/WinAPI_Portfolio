#pragma once
#include "JongEngine.h"

namespace jw
{
	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		UP, DOWN, LEFT, RIGHT, SPACE,
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

		// GetKey()	- 키를 누르는 시간만큼 true를 반환(pressed)
		// GetKeyDown() - 키를 눌렀을때, 한번 true를 반환
		// GetKeyUp() - 키를 누르다 땠을 때, 한번 true를 반환

		static __forceinline bool GetKey(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Pressed;
		}
		static __forceinline bool GetKeyDown(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Down;
		}
		static __forceinline bool GetKeyUp(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Up;
		}

		static __forceinline Vector2 GetMousePos() { return mMousePos; }

	private:
		// 사용할 키의 개수 만큼 할당
		// 반복문으로 순회하면서 각 키들의 상태를 체크
		static std::vector<Key> mKeys;
		static Vector2 mMousePos;
	};

}


