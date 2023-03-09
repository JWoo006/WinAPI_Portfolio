#include "jwCuphead.h"
#include "jwTime.h"
#include "jwSceneManager.h"
#include "jwInput.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwBaseBullet.h"
#include "jwTestBullet.h"
#include "jwScene.h"
#include "jwPeashotSpark.h"
#include "jwObject.h"


namespace jw
{
	Cuphead::Cuphead()
		: mSecond(1.0f)
	{
	}
	Cuphead::~Cuphead()
	{
	}
	void Cuphead::Initialize()
	{
		//mImage = Resources::Load<Image>(L"Cuphead", L"..\\Resources\\Image\\Cuphead\\Idle\\Idle.bmp");
		//Image* mImage = Resources::Load<Image>(L"Cuphead", L"..\\Resources\\Image\\Cuphead\\Idle\\cuphead_idle_0001.bmp");

		/*Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(100.0f, 700.0f));
		tr->SetScale(Vector2(1.0f, 1.0f));*/

		mFiredelay = BaseBullet::GetDelay();

		//Scene* curScene = SceneManager::GetActiveScene();
		//spark = new PeashotSpark();
		////spark->GetComponent<Animator>()->Play(L"Weapon_peashotspark", true);
		//curScene->AddGameObject(spark, eLayerType::Effect);

		spark = object::Instantiate<PeashotSpark>(eLayerType::Effect, eSceneType::Play);

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Idle_L", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Idle_R", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Aim\\Straight_Shoot_L", Vector2::Zero, (mFiredelay * 0.3f));
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Aim\\Straight_Shoot_R", Vector2::Zero, (mFiredelay * 0.3f));

		mAnimator->GetCompleteEvent(L"CupheadIdle_R")
			= std::bind(&Cuphead::idleCompleteEvent, this);
		mAnimator->Play(L"CupheadIdle_R", true);
		
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));
		
		mState = eCupheadState::Idle_R;

		GameObject::Initialize();
	}
	void Cuphead::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		spark->GetComponent<Transform>()->SetPos(tr->GetPos());

		switch (mState)
		{
		case jw::Cuphead::eCupheadState::Move_L:
			move();
			break;
		case jw::Cuphead::eCupheadState::Move_R:
			move();
			break;
		case jw::Cuphead::eCupheadState::Shoot_L:
			shoot();
			break;
		case jw::Cuphead::eCupheadState::Shoot_R:
			shoot();
			break;
		case jw::Cuphead::eCupheadState::Shoot_UP:
			shoot();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Down:
			shoot();
			break;
		case jw::Cuphead::eCupheadState::Death:
			death();
			break;
		case jw::Cuphead::eCupheadState::Idle_L:
			idle();
			break;
		case jw::Cuphead::eCupheadState::Idle_R:
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
	void Cuphead::OnCollisionEnter(Collider* other)
	{
		int a = 0;
	}
	void Cuphead::OnCollisionStay(Collider* other)
	{
	}
	void Cuphead::OnCollisionExit(Collider* other)
	{
	}
	void Cuphead::move()
	{
		if (Input::GetKeyUp(eKeyCode::A) || Input::GetKeyUp(eKeyCode::W) || Input::GetKeyUp(eKeyCode::S))
		{
			mState = eCupheadState::Idle_L;
			mAnimator->Play(L"CupheadIdle_L", true);
		}
		if (Input::GetKeyUp(eKeyCode::D) || Input::GetKeyUp(eKeyCode::W) || Input::GetKeyUp(eKeyCode::S))
		{
			mState = eCupheadState::Idle_R;
			mAnimator->Play(L"CupheadIdle_R", true);
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 400.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 400.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::W))
		{
			//pos.y -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::S))
		{
			//pos.y += 100.0f * Time::DeltaTime();
		}
		tr->SetPos(pos);
	}
	void Cuphead::shoot()
	{
		Transform* tr = GetComponent<Transform>();

		if (GetCupheadState() == eCupheadState::Shoot_L)
		{
			if (Input::GetKey(eKeyCode::K))
		{
			mSecond += Time::DeltaTime();

			if (mSecond > mFiredelay)
			{
				TestBullet* testbullet
					= object::Instantiate<TestBullet>((tr->GetPos() + Vector2(0.0f, -60.0f))  , eLayerType::Bullet, eSceneType::Play);
				
				testbullet->SetDegree(180.0f);

				mSecond = 0.0f;
			}
		}
		else
		{
			mState = GetCupheadState();
			mState = eCupheadState::Idle_L;
			spark->SetOnShot(false);
			mAnimator->Play(L"CupheadIdle_L", true);
		}
		}
		else if (GetCupheadState() == eCupheadState::Shoot_R)
		{
			if (Input::GetKey(eKeyCode::K))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					TestBullet* testbullet
						= object::Instantiate<TestBullet>(tr->GetPos() + Vector2(0.0f, -60.0f), eLayerType::Bullet, eSceneType::Play);

					testbullet->SetDegree(0.0f);

					mSecond = 0.0f;
				}
			}
			else
			{
				mState = GetCupheadState();
				mState = eCupheadState::Idle_L;
				spark->SetOnShot(false);
				mAnimator->Play(L"CupheadIdle_R", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::S)
			|| Input::GetKeyDown(eKeyCode::W))
		{
			mState = eCupheadState::Move_L;
			spark->SetOnShot(false);
			mAnimator->Play(L"CupheadIdle_L", true);
		}

		if (Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyDown(eKeyCode::S)
			|| Input::GetKeyDown(eKeyCode::W))
		{
			mState = eCupheadState::Move_R;
			spark->SetOnShot(false);
			mAnimator->Play(L"CupheadIdle_R", true);
		}

	}
	void Cuphead::death()
	{
	}
	void Cuphead::idle()
	{
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::W) || Input::GetKeyDown(eKeyCode::S))
		{
			mState = eCupheadState::Move_L;
			mAnimator->Play(L"CupheadIdle_L", true);
		}

		if (Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W) || Input::GetKeyDown(eKeyCode::S))
		{
			mState = eCupheadState::Move_R;
			mAnimator->Play(L"CupheadIdle_R", true);
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			if (GetCupheadState() == eCupheadState::Idle_L)
			{
				mState = eCupheadState::Shoot_L;
				mAnimator->Play(L"AimStraight_Shoot_L", true);
				spark->SetOnShot(true);
			}
			else
			{
				mState = eCupheadState::Shoot_R;
				mAnimator->Play(L"AimStraight_Shoot_R", true);
				spark->SetOnShot(true);
			}
		}
	}
	void Cuphead::idleCompleteEvent()
	{
		// 총알- idle 애니매이센 끝날때마다 총알발사
		/*Transform* tr = GetComponent<Transform>();
		Scene* curScene = SceneManager::GetActiveScene();
		BaseBullet* bullet = new BaseBullet();
		bullet->GetComponent<Transform>()->SetPos(tr->GetPos());
		curScene->AddGameObject(bullet, eLayerType::Bullet);*/
	}
}