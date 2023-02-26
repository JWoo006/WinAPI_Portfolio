#include "jwCuphead_Stage.h"
#include "jwTime.h"
#include "jwSceneManager.h"
#include "jwInput.h"
#include "jwResources.h"
#include "jwTransform.h"


namespace jw
{
	Cuphead_Stage::Cuphead_Stage()
		: mTime(0.0f)
		, mIdx(0)
	{
		
	}
	Cuphead_Stage::~Cuphead_Stage()
	{
	}
	void Cuphead_Stage::Initialize()
	{
		mImage = Resources::Load<Image>(L"Cuphead_Stage", L"..\\Resources\\Image\\Cuphead\\Cuphead_Stage.bmp");

		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(100, 500));

		GameObject::Initialize();
	}
	void Cuphead_Stage::Update()
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
	void Cuphead_Stage::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mTime += Time::DeltaTime();
		
		if (mIdx >= 16)
		{
			mIdx = 0;
		}

		if (mTime > 0.1f)
		{
			mIdx++;
			mTime = 0.0f;
		}

		TransparentBlt(hdc, pos.x, pos.y, 103, 113, mImage->GetHdc()
			, (103 * mIdx), 0, 103, 113, RGB(255, 0, 255));

	}
	void Cuphead_Stage::Release()
	{
		GameObject::Release();
	}
}
