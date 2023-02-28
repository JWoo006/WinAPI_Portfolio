#include "jwCuphead_Stage.h"
#include "jwTime.h"
#include "jwSceneManager.h"
#include "jwInput.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"


namespace jw
{
	Cuphead_Stage::Cuphead_Stage()
	{
		
	}
	Cuphead_Stage::~Cuphead_Stage()
	{
	}
	void Cuphead_Stage::Initialize()
	{
		Image* mImage = Resources::Load<Image>(L"Cuphead_Stage", L"..\\Resources\\Image\\Cuphead\\Cuphead_Stage.bmp");
		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimation(L"FowardRun", mImage
			, Vector2::Zero, 16, 8, 16, Vector2::Zero, 0.1);
		animator->CreateAnimation(L"FowardRight", mImage
			, Vector2(0.0f, 113.0f), 16, 8, 15, Vector2::Zero, 0.1);
		animator->CreateAnimation(L"Idle", mImage
			, Vector2(0.0f, 113.0f * 5), 16, 8, 9, Vector2::Zero, 0.1);

		animator->Play(L"Idle", true);

		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(100, 500));

		GameObject::Initialize();
	}
	void Cuphead_Stage::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Animator* animator = GetComponent<Animator>();

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
		if (Input::GetKeyState(eKeyCode::W) == eKeyState::Down)
		{
			animator->Play(L"FowardRun", true);
		}
		if (Input::GetKeyState(eKeyCode::W) == eKeyState::Up)
		{
			animator->Play(L"Idle", true);
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

		

	}
	void Cuphead_Stage::Release()
	{
		GameObject::Release();
	}
}
