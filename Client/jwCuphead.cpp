#include "jwCuphead.h"
#include "jwTime.h"
#include "jwSceneManager.h"
#include "jwInput.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwScene.h"
#include "jwBaseBullet.h"
#include "jwTestBullet.h"
#include "jwPeashot_L.h"
#include "jwPeashot_Up.h"
#include "jwPeashot_diagnal_L.h"
#include "jwPeashot_diagnal_R.h"
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
		mFiredelay = BaseBullet::GetDelay();

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Idle_L", Vector2::Zero, 0.07f);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Idle_R", Vector2::Zero, 0.07f);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Run\\Run_L", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Run\\Run_R", Vector2::Zero, 0.05f);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Duck_start_L", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Duck_start_R", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Idle_L", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Idle_R", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Shoot_L", Vector2::Zero, (mFiredelay * 0.3f));
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Shoot_R", Vector2::Zero, (mFiredelay * 0.3f));


		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Straight_Shoot_L", Vector2::Zero, (mFiredelay * 0.3f));
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Straight_Shoot_R", Vector2::Zero, (mFiredelay * 0.3f));
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Up_L", Vector2::Zero, (mFiredelay * 0.3f));
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Up_R", Vector2::Zero, (mFiredelay * 0.3f));
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Run_L", Vector2::Zero, (mFiredelay * 0.3f));
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Run_R", Vector2::Zero, (mFiredelay * 0.3f));
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Run_diagonal_up_L", Vector2::Zero, (mFiredelay * 0.3f));
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Run_diagonal_up_R", Vector2::Zero, (mFiredelay * 0.3f));

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Aim\\Up_L", Vector2::Zero, 0.07f);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Aim\\Up_R", Vector2::Zero, 0.07f);

		mAnimator->GetCompleteEvent(L"DuckDuck_start_L")
			= std::bind(&Cuphead::duckLCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"DuckDuck_start_R")
			= std::bind(&Cuphead::duckRCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"CupheadIdle_R")
			= std::bind(&Cuphead::idleCompleteEvent, this);

		mAnimator->Play(L"CupheadIdle_R", true);
		
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));
		collider->SetSize(Vector2(50.0f, 50.0f));
		
		mState = eCupheadState::Idle_R;

		GameObject::Initialize();
	}
	void Cuphead::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		//spark->GetComponent<Transform>()->SetPos(tr->GetPos());

		switch (mState)
		{

		case jw::Cuphead::eCupheadState::Move_L:
			move();
			break;
		case jw::Cuphead::eCupheadState::Move_R:
			move();
			break;
		case jw::Cuphead::eCupheadState::Duck_L:
			duck();
			break;
		case jw::Cuphead::eCupheadState::Duck_R:
			duck();
			break;
		case jw::Cuphead::eCupheadState::Duck_Shoot_L:
			shoot_duck();
			break;
		case jw::Cuphead::eCupheadState::Duck_Shoot_R:
			shoot_duck();
			break;
		case jw::Cuphead::eCupheadState::Aim_UP_L:
			aim_up();
			break;
		case jw::Cuphead::eCupheadState::Aim_UP_R:
			aim_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_L:
			shoot();
			break;
		case jw::Cuphead::eCupheadState::Shoot_R:
			shoot();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Run_L:
			shoot_run();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Run_R:
			shoot_run();
			break;
		case jw::Cuphead::eCupheadState::Shoot_UP_L:
			shoot_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_UP_R:
			shoot_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Run_diag_Up_L:
			shoot_run_diag_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Run_diag_Up_R:
			shoot_run_diag_up();
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

	void Cuphead::idle()
	{
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))
		{
			mState = eCupheadState::Move_L;
			mAnimator->Play(L"RunRun_L", true);
		}

		if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))
		{
			mState = eCupheadState::Move_R;
			mAnimator->Play(L"RunRun_R", true);
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			if (GetCupheadState() == eCupheadState::Idle_L)
			{
				mState = eCupheadState::Shoot_L;
				mAnimator->Play(L"ShootStraight_Shoot_L", true);
			}
			else
			{
				mState = eCupheadState::Shoot_R;
				mAnimator->Play(L"ShootStraight_Shoot_R", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			if (GetCupheadState() == eCupheadState::Idle_L)
			{
				mState = eCupheadState::Aim_UP_L;
				mAnimator->Play(L"AimUp_L", true);
			}
			else
			{
				mState = eCupheadState::Aim_UP_R;
				mAnimator->Play(L"AimUp_R", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (GetCupheadState() == eCupheadState::Idle_L)
			{
				mState = eCupheadState::Duck_L;
				mAnimator->Play(L"DuckDuck_start_L", false);
			}
			else if (GetCupheadState() == eCupheadState::Idle_R)
			{
				mState = eCupheadState::Duck_R;
				mAnimator->Play(L"DuckDuck_start_R", false);
			}
		}
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

		if (Input::GetKeyDown(eKeyCode::K))
		{
			if (GetCupheadState() == eCupheadState::Move_L)
			{
				mState = eCupheadState::Shoot_Run_L;
				mAnimator->Play(L"ShootRun_L", true);
			}
			else if(GetCupheadState() == eCupheadState::Move_R)
			{
				mState = eCupheadState::Shoot_Run_R;
				mAnimator->Play(L"ShootRun_R", true);
			}
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

		if (Input::GetKey(eKeyCode::W) && Input::GetKey(eKeyCode::A) && Input::GetKeyDown(eKeyCode::K))
		{
			mState = eCupheadState::Shoot_Run_diag_Up_L;
			mAnimator->Play(L"ShootRun_diagonal_up_L", true);
		}
		else if (Input::GetKey(eKeyCode::W) && Input::GetKey(eKeyCode::D) && Input::GetKeyDown(eKeyCode::K))
		{
			mState = eCupheadState::Shoot_Run_diag_Up_R;
			mAnimator->Play(L"ShootRun_diagonal_up_R", true);
		}


		if (Input::GetKeyDown(eKeyCode::S) && Input::GetKey(eKeyCode::A))
		{
			mState = eCupheadState::Duck_L;
			mAnimator->Play(L"DuckDuck_start_L", false);
		}
		else if (Input::GetKeyDown(eKeyCode::S) && Input::GetKey(eKeyCode::D))
		{
			mState = eCupheadState::Duck_R;
			mAnimator->Play(L"DuckDuck_start_R", false);
		}
		
		tr->SetPos(pos);
	}

	void Cuphead::duck()
	{
		if (Input::GetKeyDown(eKeyCode::A))
		{
			mState = eCupheadState::Duck_L;
			mAnimator->Play(L"DuckIdle_L", true);
		}
		else if (Input::GetKeyDown(eKeyCode::D))
		{
			mState = eCupheadState::Duck_R;
			mAnimator->Play(L"DuckIdle_R", true);
		}

		if (Input::GetKeyUp(eKeyCode::S) && GetCupheadState() == eCupheadState::Duck_L)
		{
			if (Input::GetKeyDown(eKeyCode::A))
			{
				mState = eCupheadState::Move_L;
				mAnimator->Play(L"RunRun_L", true);
			}
			else
			{
				mState = eCupheadState::Idle_L;
				mAnimator->Play(L"CupheadIdle_L", true);
			}
		}
		if (Input::GetKeyUp(eKeyCode::S) && GetCupheadState() == eCupheadState::Duck_R)
		{
			if (Input::GetKeyDown(eKeyCode::D))
			{
				mState = eCupheadState::Move_R;
				mAnimator->Play(L"RunRun_R", true);
			}
			else
			{
				mState = eCupheadState::Idle_R;
				mAnimator->Play(L"CupheadIdle_R", true);
			}
		}

		if (Input::GetKey(eKeyCode::K) || Input::GetKeyDown(eKeyCode::K))
		{
			if (GetCupheadState() == eCupheadState::Duck_L)
			{
				mState = eCupheadState::Duck_Shoot_L;
				mAnimator->Play(L"DuckShoot_L", true);
			}
			else
			{
				mState = eCupheadState::Duck_Shoot_R;
				mAnimator->Play(L"DuckShoot_R", true);
			}
		}

	}
	void Cuphead::aim_up()
	{
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))
		{
			mState = eCupheadState::Move_L;
			mAnimator->Play(L"RunRun_L", true);
		}

		if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))
		{
			mState = eCupheadState::Move_R;
			mAnimator->Play(L"RunRun_R", true);
		}

		if (Input::GetKey(eKeyCode::K))
		{
			if (GetCupheadState() == eCupheadState::Aim_UP_L)
			{
				mState = eCupheadState::Shoot_UP_L;
				mAnimator->Play(L"ShootUp_L", true);
			}
			else
			{
				mState = eCupheadState::Shoot_UP_R;
				mAnimator->Play(L"ShootUp_R", true);
			}
		}

		if (Input::GetKeyUp(eKeyCode::W))
		{
			if (GetCupheadState() == eCupheadState::Aim_UP_L
				|| GetCupheadState() == eCupheadState::Shoot_UP_L)
			{
				mState = eCupheadState::Idle_L;
				mAnimator->Play(L"CupheadIdle_L", true);
			}
			else if (GetCupheadState() == eCupheadState::Aim_UP_R
				|| GetCupheadState() == eCupheadState::Shoot_UP_R)
			{
				mState = eCupheadState::Idle_R;
				mAnimator->Play(L"CupheadIdle_R", true);
			}
		}
	}

	void Cuphead::shoot()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetCupheadState() == eCupheadState::Shoot_L)
		{
			if (Input::GetKey(eKeyCode::K))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_L* bullet;

					bullet = object::Instantiate<Peashot_L>((pos + Vector2(-60.0f, -60.0f)), eLayerType::Bullet);
					bullet->SetDegree(180.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(-70.0f, -40.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}

				if (Input::GetKeyDown(eKeyCode::D))
				{
					mState = eCupheadState::Shoot_Run_R;
					mAnimator->Play(L"ShootRun_R", true);
				}
				if (Input::GetKeyDown(eKeyCode::A))
				{
					mState = eCupheadState::Shoot_Run_L;
					mAnimator->Play(L"ShootRun_L", true);
				}

				if (Input::GetKeyDown(eKeyCode::S))
				{
					mState = eCupheadState::Duck_Shoot_L;
					mAnimator->Play(L"DuckShoot_L", true);
				}

				if (Input::GetKeyDown(eKeyCode::W))
				{
					mState = eCupheadState::Shoot_UP_L;
					mAnimator->Play(L"ShootUp_L", true);
				}

			}
			else
			{
				mState = eCupheadState::Idle_L;
				mAnimator->Play(L"CupheadIdle_L", true);
			}
		}
		if (GetCupheadState() == eCupheadState::Shoot_R)
		{
			if (Input::GetKey(eKeyCode::K))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					TestBullet* bullet
						= object::Instantiate<TestBullet>(pos + Vector2(60.0f, -60.0f), eLayerType::Bullet);

					bullet->SetDegree(0.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(70.0f, -40.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}

				if (Input::GetKeyDown(eKeyCode::D))
				{
					mState = eCupheadState::Shoot_Run_R;
					mAnimator->Play(L"ShootRun_R", true);
				}
				if (Input::GetKeyDown(eKeyCode::A))
				{
					mState = eCupheadState::Shoot_Run_L;
					mAnimator->Play(L"ShootRun_L", true);
				}

				if (Input::GetKeyDown(eKeyCode::S))
				{
					mState = eCupheadState::Duck_Shoot_R;
					mAnimator->Play(L"DuckShoot_R", true);
				}

				if (Input::GetKeyDown(eKeyCode::W))
				{
					mState = eCupheadState::Shoot_UP_R;
					mAnimator->Play(L"ShootUp_R", true);
				}
			}
			else
			{
				mState = eCupheadState::Idle_R;
				mAnimator->Play(L"CupheadIdle_R", true);
			}
		}

		/*if (Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::S)
			|| Input::GetKeyDown(eKeyCode::W))
		{
			mState = eCupheadState::Move_L;
			mAnimator->Play(L"CupheadIdle_L", true);
		}

		if (Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyDown(eKeyCode::S)
			|| Input::GetKeyDown(eKeyCode::W))
		{
			mState = eCupheadState::Move_R;
			mAnimator->Play(L"CupheadIdle_R", true);
		}*/

	}

	void Cuphead::shoot_run()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetCupheadState() == eCupheadState::Shoot_Run_L)
		{
			if (Input::GetKey(eKeyCode::K))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_L* bullet
						= object::Instantiate<Peashot_L>((pos + Vector2(-60.0f, -50.0f)), eLayerType::Bullet);
					bullet->SetDegree(180.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(-70.0f, -30.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}
				if (Input::GetKey(eKeyCode::A))
				{
					pos.x -= 400.0f * Time::DeltaTime();
				}
				tr->SetPos(pos);

				if (Input::GetKeyUp(eKeyCode::A))
				{
					mState = eCupheadState::Shoot_L;
					mAnimator->Play(L"ShootStraight_Shoot_L", true);
				}

				if (Input::GetKeyDown(eKeyCode::W))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_L;
					mAnimator->Play(L"ShootRun_diagonal_up_L", true);
				}

				if (Input::GetKeyDown(eKeyCode::D))
				{
					mState = eCupheadState::Shoot_Run_R;
					mAnimator->Play(L"ShootRun_R", true);
				}

				if (Input::GetKeyDown(eKeyCode::S))
				{
					mState = eCupheadState::Duck_Shoot_L;
					mAnimator->Play(L"DuckShoot_L", true);
				}

			}
			else if (Input::GetKey(eKeyCode::D) && Input::GetKeyUp(eKeyCode::K))
			{
				mState = eCupheadState::Move_L;
				mAnimator->Play(L"RunRun_L", true);
			}
			else
			{
				mState = eCupheadState::Idle_L;
				mAnimator->Play(L"CupheadIdle_L", true);
			}
		}
		if (GetCupheadState() == eCupheadState::Shoot_Run_R)
		{
			if (Input::GetKey(eKeyCode::K))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					TestBullet* bullet
						= object::Instantiate<TestBullet>((tr->GetPos() + Vector2(60.0f, -50.0f)), eLayerType::Bullet);
					bullet->SetDegree(0.0f);

					object::Instantiate<PeashotSpark>((tr->GetPos() + Vector2(70.0f, -30.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}
				if (Input::GetKey(eKeyCode::D))
				{
					pos.x += 400.0f * Time::DeltaTime();
				}
				tr->SetPos(pos);

				if (Input::GetKeyUp(eKeyCode::D))
				{
					mState = eCupheadState::Shoot_R;
					mAnimator->Play(L"ShootStraight_Shoot_R", true);
				}

				if (Input::GetKeyDown(eKeyCode::W))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_R;
					mAnimator->Play(L"ShootRun_diagonal_up_R", true);
				}

				if (Input::GetKeyDown(eKeyCode::A))
				{
					mState = eCupheadState::Shoot_Run_L;
					mAnimator->Play(L"ShootRun_L", true);
				}

				if (Input::GetKeyDown(eKeyCode::S))
				{
					mState = eCupheadState::Duck_Shoot_R;
					mAnimator->Play(L"DuckShoot_R", true);
				}

			}
			else if (Input::GetKey(eKeyCode::D) && Input::GetKeyUp(eKeyCode::K))
			{
				mState = eCupheadState::Move_R;
				mAnimator->Play(L"RunRun_R", true);
			}
			else
			{
				mState = eCupheadState::Idle_R;
				mAnimator->Play(L"CupheadIdle_R", true);
			}
		}
	}

	void Cuphead::shoot_duck()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetCupheadState() == eCupheadState::Duck_Shoot_L)
		{
			if (Input::GetKey(eKeyCode::K))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_L* bullet
						= object::Instantiate<Peashot_L>((tr->GetPos() + Vector2(-60.0f, -20.0f)), eLayerType::Bullet);
					bullet->SetDegree(180.0f);

					object::Instantiate<PeashotSpark>((tr->GetPos() + Vector2(-70.0f, -0.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}

				if (Input::GetKeyDown(eKeyCode::D))
				{
					mState = eCupheadState::Duck_Shoot_R;
					mAnimator->Play(L"DuckShoot_R", true);
				}
				if (Input::GetKey(eKeyCode::A) && Input::GetKeyUp(eKeyCode::S))
				{
					mState = eCupheadState::Shoot_Run_L;
					mAnimator->Play(L"ShootRun_L", true);
				}
				if (Input::GetKey(eKeyCode::D) && Input::GetKeyUp(eKeyCode::S))
				{
					mState = eCupheadState::Shoot_Run_R;
					mAnimator->Play(L"ShootRun_R", true);
				}
			}
			else if (Input::GetKey(eKeyCode::S))
			{
				mState = eCupheadState::Duck_L;
				mAnimator->Play(L"DuckIdle_L", true);
			}
		}
		if (GetCupheadState() == eCupheadState::Duck_Shoot_R)
		{
			if (Input::GetKey(eKeyCode::K))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					TestBullet* bullet
						= object::Instantiate<TestBullet>((tr->GetPos() + Vector2(60.0f, -20.0f)), eLayerType::Bullet);
					bullet->SetDegree(0.0f);

					object::Instantiate<PeashotSpark>((tr->GetPos() + Vector2(70.0f, -0.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}

				if (Input::GetKeyDown(eKeyCode::A))
				{
					mState = eCupheadState::Duck_Shoot_L;
					mAnimator->Play(L"DuckShoot_L", true);
				}
				if (Input::GetKey(eKeyCode::A) && Input::GetKeyUp(eKeyCode::S))
				{
					mState = eCupheadState::Shoot_Run_L;
					mAnimator->Play(L"ShootRun_L", true);
				}
				if (Input::GetKey(eKeyCode::D) && Input::GetKeyUp(eKeyCode::S))
				{
					mState = eCupheadState::Shoot_Run_R;
					mAnimator->Play(L"ShootRun_R", true);
				}
			}
			else if (Input::GetKey(eKeyCode::S))
			{
				mState = eCupheadState::Duck_R;
				mAnimator->Play(L"DuckIdle_R", true);
			}
		}
	}

	void Cuphead::shoot_up()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetCupheadState() == eCupheadState::Shoot_UP_L)
		{
			if (Input::GetKey(eKeyCode::K))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_Up* bullet
						= object::Instantiate<Peashot_Up>(pos + Vector2(-30.0f, -90.0f), eLayerType::Bullet);

					bullet->SetDegree(-90.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(-35.0f, -120.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}

				if (Input::GetKeyUp(eKeyCode::W))
				{
					mState = eCupheadState::Shoot_L;
					mAnimator->Play(L"ShootStraight_Shoot_L", true);
				}

				if (Input::GetKey(eKeyCode::A))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_L;
					mAnimator->Play(L"ShootRun_diagonal_up_L", true);
				}
				if (Input::GetKey(eKeyCode::D))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_R;
					mAnimator->Play(L"ShootRun_diagonal_up_R", true);
				}

			}
			else if (Input::GetKey(eKeyCode::W))
			{
				mState = eCupheadState::Aim_UP_L;
				mAnimator->Play(L"AimUp_L", true);
			}
			else
			{
				mState = eCupheadState::Idle_L;
				mAnimator->Play(L"CupheadIdle_L", true);
			}
		}
		if (GetCupheadState() == eCupheadState::Shoot_UP_R)
		{
			if (Input::GetKey(eKeyCode::K))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_Up* bullet
						= object::Instantiate<Peashot_Up>(pos + Vector2(30.0f, -90.0f), eLayerType::Bullet);

					bullet->SetDegree(-90.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(35.0f, -120.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}

				if (Input::GetKeyUp(eKeyCode::W))
				{
					mState = eCupheadState::Shoot_R;
					mAnimator->Play(L"ShootStraight_Shoot_R", true);
				}

				if (Input::GetKey(eKeyCode::A))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_L;
					mAnimator->Play(L"ShootRun_diagonal_up_L", true);
				}
				if (Input::GetKey(eKeyCode::D))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_R;
					mAnimator->Play(L"ShootRun_diagonal_up_R", true);
				}
			}
			else if (Input::GetKey(eKeyCode::W))
			{
				mState = eCupheadState::Aim_UP_R;
				mAnimator->Play(L"AimUp_R", true);
			}
			else
			{
				mState = eCupheadState::Idle_R;
				mAnimator->Play(L"CupheadIdle_R", true);
			}
		}
	}

	void Cuphead::shoot_run_diag_up()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetCupheadState() == eCupheadState::Shoot_Run_diag_Up_L)
		{
			if (Input::GetKey(eKeyCode::K))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_diagnal_L* bullet
						= object::Instantiate<Peashot_diagnal_L>((pos + Vector2(-60.0f, 0.0f)), eLayerType::Bullet);
					bullet->SetDegree(-135.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(-80.0f, -80.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}
				if (Input::GetKey(eKeyCode::A))
				{
					pos.x -= 400.0f * Time::DeltaTime();
				}
				tr->SetPos(pos);

				if (Input::GetKeyUp(eKeyCode::A))
				{
					mState = eCupheadState::Shoot_UP_L;
					mAnimator->Play(L"ShootUp_L", true);
				}

				if (Input::GetKeyUp(eKeyCode::W))
				{
					mState = eCupheadState::Shoot_Run_L;
					mAnimator->Play(L"ShootRun_L", true);
				}

				if (Input::GetKey(eKeyCode::D) && Input::GetKeyUp(eKeyCode::A))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_R;
					mAnimator->Play(L"ShootRun_diagonal_up_R", true);
				}

			}
			else if (Input::GetKey(eKeyCode::D) && Input::GetKeyUp(eKeyCode::K))
			{
				mState = eCupheadState::Move_L;
				mAnimator->Play(L"RunRun_L", true);
			}
			else
			{
				mState = eCupheadState::Idle_L;
				mAnimator->Play(L"CupheadIdle_L", true);
			}
		}
		if (GetCupheadState() == eCupheadState::Shoot_Run_diag_Up_R)
		{
			if (Input::GetKey(eKeyCode::K))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_diagnal_R* bullet
						= object::Instantiate<Peashot_diagnal_R>((tr->GetPos() + Vector2(60.0f, 0.0f)), eLayerType::Bullet);
					bullet->SetDegree(-45.0f);

					object::Instantiate<PeashotSpark>((tr->GetPos() + Vector2(80.0f, -80.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}
				if (Input::GetKey(eKeyCode::D))
				{
					pos.x += 400.0f * Time::DeltaTime();
				}
				tr->SetPos(pos);

				if (Input::GetKeyUp(eKeyCode::D))
				{
					mState = eCupheadState::Shoot_UP_R;
					mAnimator->Play(L"ShootUp_R", true);
				}

				if (Input::GetKeyUp(eKeyCode::W))
				{
					mState = eCupheadState::Shoot_Run_R;
					mAnimator->Play(L"ShootRun_R", true);
				}

				if (Input::GetKey(eKeyCode::A) && Input::GetKeyUp(eKeyCode::D))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_L;
					mAnimator->Play(L"ShootRun_diagonal_up_L", true);
				}

			}
			else if (Input::GetKey(eKeyCode::D) && Input::GetKeyUp(eKeyCode::K))
			{
				mState = eCupheadState::Move_R;
				mAnimator->Play(L"RunRun_R", true);
			}
			else
			{
				mState = eCupheadState::Idle_R;
				mAnimator->Play(L"CupheadIdle_R", true);
			}
		}
	}

	void Cuphead::death()
	{
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
	void Cuphead::duckLCompleteEvent()
	{
		mAnimator->Play(L"DuckIdle_L", true);
	}
	void Cuphead::duckRCompleteEvent()
	{
		mAnimator->Play(L"DuckIdle_R", true);
	}

}