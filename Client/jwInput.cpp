#include "jwInput.h"

namespace jw
{
	int ASCII[(UINT)eKeyCode::END] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,
	};

	//          이너클래스여서 접근제어 지정해줘야함
	std::vector<Input::Key> Input::mKeys;

	void Input::Initialize()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			Key keyInfo;
			keyInfo.key = (eKeyCode)i;
			keyInfo.state = eKeyState::None;
			keyInfo.bPressed = false;

			mKeys.push_back(keyInfo);
		}
	}
	void Input::Update()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				// 이전 프레임에도 눌려 있었다면
				if (mKeys[i].bPressed)
				{
					mKeys[i].state = eKeyState::Pressed;
				}
				else
				{
					mKeys[i].state = eKeyState::Down;
				}
				mKeys[i].bPressed = true;
			}
			else // 현재 프레임에 키가 눌려있지 않다
			{
				if (mKeys[i].bPressed)
				{
					mKeys[i].state = eKeyState::Up;
				}
				else
				{
					mKeys[i].state = eKeyState::None;
				}
				mKeys[i].bPressed = false;
			}
		}
	}
	void Input::Render(HDC hdc)
	{
	}
}
