#include "jwCuphead_Stage.h"
#include "jwTime.h"
#include "jwSceneManager.h"
#include "jwInput.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"


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
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(800.0f, 450.0f));

		Image* mImage = Resources::Load<Image>(L"Cuphead_Stage", L"..\\Resources\\Image\\Cuphead\\StageMove\\Cuphead_Stage.bmp");
		mAnimator = AddComponent<Animator>();
		/*mAnimator->CreateAnimation(L"FowardRun", mImage
			, Vector2::Zero, 16, 8, 16, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"FowardRight", mImage
			, Vector2(0.0f, 113.0f), 16, 8, 15, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Idle", mImage
			, Vector2(0.0f, 113.0f * 5), 16, 8, 9, Vector2::Zero, 0.1);

		mAnimator->Play(L"Idle", true);*/

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));

		mState = eCupheadState::Idle;

		GameObject::Initialize();
	}
	void Cuphead_Stage::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case jw::Cuphead_Stage::eCupheadState::Move:
			move();
			break;
		case jw::Cuphead_Stage::eCupheadState::Shoot:
			shoot();
			break;
		case jw::Cuphead_Stage::eCupheadState::Death:
			death();
			break;
		case jw::Cuphead_Stage::eCupheadState::Idle:
			idle();
			break;
		default:
			break;
		}

		/*Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKeyState(eKeyCode::A) == eKeyState::Pressed)
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::Pressed)
		{
			pos.x += 100.0f * Time::DeltaTime();
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
		tr->SetPos(pos);*/
	}
	void Cuphead_Stage::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Cuphead_Stage::Release()
	{
		GameObject::Release();
	}
	void Cuphead_Stage::move()
	{
		if (Input::GetKeyUp(eKeyCode::LEFT) || Input::GetKeyUp(eKeyCode::RIGHT)
			|| Input::GetKeyUp(eKeyCode::UP) || Input::GetKeyUp(eKeyCode::DOWN))
		{
			mState = eCupheadState::Idle;
			mAnimator->Play(L"Idle", true);
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 200.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 200.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::UP))
		{
			pos.y -= 200.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y += 200.0f * Time::DeltaTime();
		}
		tr->SetPos(pos);
	}
	void Cuphead_Stage::shoot()
	{
	}
	void Cuphead_Stage::death()
	{
	}
	void Cuphead_Stage::idle()
	{
		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::UP) || Input::GetKeyDown(eKeyCode::DOWN))
		{
			mState = eCupheadState::Move;
			mAnimator->Play(L"FowardRun", true);
		}
	}
}
