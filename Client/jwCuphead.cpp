#include "jwCuphead.h"
#include "jwTime.h"
#include "jwSceneManager.h"
#include "jwInput.h"
#include "jwResources.h"
#include "jwTransform.h"


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
		mImage = Resources::Load<Image>(L"Cuphead", L"..\\Resources\\Image\\Cuphead\\Idle.bmp");

		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(100, 500));

		GameObject::Initialize();
	}
	void Cuphead::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKeyState(eKeyCode::A) == eKeyState::Pressed)
		{
			pos.x -= 400.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::Pressed)
		{
			pos.x += 400.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::Pressed)
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::S) == eKeyState::Pressed)
		{
			pos.y += 100.0f * Time::DeltaTime();
		}
		tr->SetPos(pos);

	}
	void Cuphead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//BitBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
		GdiTransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

				
	}
	void Cuphead::Release()
	{
		GameObject::Release();
	}
}