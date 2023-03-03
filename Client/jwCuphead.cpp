#include "jwCuphead.h"
#include "jwTime.h"
#include "jwSceneManager.h"
#include "jwInput.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwBaseBullet.h"
#include "jwScene.h"


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
		//mImage = Resources::Load<Image>(L"Cuphead", L"..\\Resources\\Image\\Cuphead\\Idle\\Idle.bmp");
		//Image* mImage = Resources::Load<Image>(L"Cuphead", L"..\\Resources\\Image\\Cuphead\\Idle\\cuphead_idle_0001.bmp");
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Idle", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Aim\\Straight", Vector2(10.0f,0.0f), 0.1f);


		mAnimator->Play(L"CupheadIdle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));
		
		mState = eCupheadState::Idle;

		GameObject::Initialize();
	}
	void Cuphead::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		switch (mState)
		{
		case jw::Cuphead::eCupheadState::Move:
			move();
			break;
		case jw::Cuphead::eCupheadState::Shoot:
			shoot();
			break;
		case jw::Cuphead::eCupheadState::Death:
			death();
			break;
		case jw::Cuphead::eCupheadState::Idle:
			idle();
			break;
		default:
			break;
		}

	}
	void Cuphead::Render(HDC hdc)
	{
		GameObject::Render(hdc);						
	}
	void Cuphead::Release()
	{
		GameObject::Release();
	}
	void Cuphead::move()
	{
		if (Input::GetKeyUp(eKeyCode::A) || Input::GetKeyUp(eKeyCode::D)
			|| Input::GetKeyUp(eKeyCode::W) || Input::GetKeyUp(eKeyCode::S))
		{
			mState = eCupheadState::Idle;
			//mAnimator->Play(L"Idle", true);
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 100.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::W))
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::S))
		{
			pos.y += 100.0f * Time::DeltaTime();
		}
		tr->SetPos(pos);
	}
	void Cuphead::shoot()
	{
		Transform* tr = GetComponent<Transform>();
		if (Input::GetKey(eKeyCode::K))
		{
			Scene* curScene = SceneManager::GetActiveScene();
			BaseBullet* bullet = new BaseBullet();
			bullet->GetComponent<Transform>()->SetPos(tr->GetPos());
			curScene->AddGameObject(bullet, eLayerType::Bullet);
		}

		if (Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyDown(eKeyCode::S)
			|| Input::GetKeyDown(eKeyCode::W))
		{
			mState = eCupheadState::Move;
			//mAnimator->Play(L"FowardRun", true);
			mAnimator->Play(L"CupheadIdle", true);
		}

	}
	void Cuphead::death()
	{
	}
	void Cuphead::idle()
	{
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyDown(eKeyCode::W) || Input::GetKeyDown(eKeyCode::S))
		{
			mState = eCupheadState::Move;
			//mAnimator->Play(L"FowardRun", true);
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			mState = eCupheadState::Shoot;
			mAnimator->Play(L"AimStraight", true);
		}
	}
}