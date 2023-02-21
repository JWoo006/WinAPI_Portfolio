#include "jwCuphead.h"
#include "jwTime.h"
#include "jwScenenManager.h"
#include "jwInput.h"

namespace jw
{
	Cuphead::Cuphead()
	{
	}
	Cuphead::~Cuphead()
	{
	}
	void Cuphead::Initialize()
	{
		GameObject::Initialize();
	}
	void Cuphead::Update()
	{
		GameObject::Update();

		if (Input::GetKeyState(eKeyCode::A) == eKeyState::Pressed)
		{
			mPos.x -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::Pressed)
		{
			mPos.x += 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::Pressed)
		{
			mPos.y -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::S) == eKeyState::Pressed)
		{
			mPos.y += 100.0f * Time::DeltaTime();
		}
	}
	void Cuphead::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		// stock 오브젝트
		// 기본으로 생성되는 펜(검은색)과 브러쉬(하얀색)

		// selectobject(HDC, HGDIOBJ);
		// 위 함수의 반환값은 HGDIOBJ로 기존에 쓰던 스톡오브젝트

		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		//Rectangle(mHdc, -1, -1, 1601, 901);

		HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc, mPos.x, mPos.y, mPos.x + 100, mPos.y + 100);

		// 메모리 릭이 남지 않게 처리
		SelectObject(hdc, oldPen);
		DeleteObject(pen);
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);
	}
	void Cuphead::Release()
	{
		GameObject::Release();
	}
}