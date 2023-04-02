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
#include "jwRigidbody.h"


namespace jw
{
	Cuphead::Cuphead()
		: mSecond(1.0f)
		, mJumpCount(1)
		, mbGroundCheck(true)
		, mJumpScale(1000.0f)
	{
	}
	Cuphead::~Cuphead()
	{
	}
	void Cuphead::Initialize()
	{
		mFiredelay = BaseBullet::GetDelay();

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Idle_L", Vector2::Zero, 0.07f, eImageFormat::PNG, true);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Idle_R", Vector2::Zero, 0.07f, eImageFormat::PNG, false);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Run\\Run_L", Vector2::Zero, 0.05f, eImageFormat::PNG, true);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Run\\Run_R", Vector2::Zero, 0.05f, eImageFormat::PNG, false);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Jump\\Jump_L", Vector2::Zero, 0.05f, eImageFormat::PNG, true);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Jump\\Jump_R", Vector2::Zero, 0.05f, eImageFormat::PNG, false);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Duck_start_L", Vector2::Zero, 0.05f, eImageFormat::PNG, true);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Duck_start_R", Vector2::Zero, 0.05f, eImageFormat::PNG, false);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Idle_L", Vector2::Zero, 0.05f, eImageFormat::PNG, true);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Idle_R", Vector2::Zero, 0.05f, eImageFormat::PNG, false);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Shoot_L", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, true);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Shoot_R", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, false);


		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Straight_Shoot_L", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, true);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Straight_Shoot_R", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, false);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Up_L", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, true);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Up_R", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, false);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Run_L", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, true);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Run_R", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, false);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Run_diagonal_up_L", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, true);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Run_diagonal_up_R", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, false);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Aim\\Up_L", Vector2::Zero, 0.07f, eImageFormat::PNG, true);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Aim\\Up_R", Vector2::Zero, 0.07f, eImageFormat::PNG, false);

		mAnimator->GetCompleteEvent(L"DuckDuck_start_L")
			= std::bind(&Cuphead::duckLCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"DuckDuck_start_R")
			= std::bind(&Cuphead::duckRCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"CupheadIdle_R")
			= std::bind(&Cuphead::idleCompleteEvent, this);

		mAnimator->Play(L"CupheadIdle_R", true);
		
		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-75.0f, -145.0f));
		collider->SetSize(Vector2(150.0f, 150.0f));
		
		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

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
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			move();
			break;
		case jw::Cuphead::eCupheadState::Move_R:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			move();
			break;
		case jw::Cuphead::eCupheadState::Jump_L:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			jump();
			break;
		case jw::Cuphead::eCupheadState::Jump_R:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			jump();
			break;
		case jw::Cuphead::eCupheadState::Duck_L:
			collider->SetCenter(Vector2(-75.0f, -65.0f));
			collider->SetSize(Vector2(150.0f, 70.0f));
			duck();
			break;
		case jw::Cuphead::eCupheadState::Duck_R:
			collider->SetCenter(Vector2(-75.0f, -65.0f));
			collider->SetSize(Vector2(150.0f, 70.0f));
			duck();
			break;
		case jw::Cuphead::eCupheadState::Duck_Shoot_L:
			collider->SetCenter(Vector2(-75.0f, -65.0f));
			collider->SetSize(Vector2(150.0f, 70.0f));
			shoot_duck();
			break;
		case jw::Cuphead::eCupheadState::Duck_Shoot_R:
			collider->SetCenter(Vector2(-75.0f, -65.0f));
			collider->SetSize(Vector2(150.0f, 70.0f));
			shoot_duck();
			break;
		case jw::Cuphead::eCupheadState::Aim_UP_L:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			aim_up();
			break;
		case jw::Cuphead::eCupheadState::Aim_UP_R:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			aim_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_L:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			shoot();
			break;
		case jw::Cuphead::eCupheadState::Shoot_R:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			shoot();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Run_L:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			shoot_run();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Run_R:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			shoot_run();
			break;
		case jw::Cuphead::eCupheadState::Shoot_UP_L:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			shoot_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_UP_R:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			shoot_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Run_diag_Up_L:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			shoot_run_diag_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Run_diag_Up_R:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			shoot_run_diag_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Jump_L:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			shoot_jump();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Jump_R:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			shoot_jump();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Jump_Up_L:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			shoot_jump_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Jump_Up_R:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			shoot_jump_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Jump_diag_Up_L:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			shoot_jump_diag_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Jump_diag_Up_R:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			shoot_jump_diag_up();
			break;
		case jw::Cuphead::eCupheadState::Death:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			death();
			break;
		case jw::Cuphead::eCupheadState::Idle_L:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
			idle();
			break;
		case jw::Cuphead::eCupheadState::Idle_R:
			collider->SetCenter(Vector2(-75.0f, -145.0f));
			collider->SetSize(Vector2(150.0f, 150.0f));
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
		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT))
		{
			mState = eCupheadState::Move_L;
			mAnimator->Play(L"RunRun_L", true);
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT))
		{
			mState = eCupheadState::Move_R;
			mAnimator->Play(L"RunRun_R", true);
		}

		if (Input::GetKeyDown(eKeyCode::X))
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

		if (Input::GetKeyDown(eKeyCode::UP))
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

		if (Input::GetKeyDown(eKeyCode::DOWN))
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

		if (Input::GetKeyDown(eKeyCode::Z) && mJumpCount >= 1)
		{
			mJumpCount--;
			mbGroundCheck = false;

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= mJumpScale;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			if (Cuphead::GetCupheadState() == eCupheadState::Idle_L)
			{
				mState = eCupheadState::Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else
			{
				mState = eCupheadState::Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
		}
	}
	void Cuphead::move()
	{
		if (Input::GetKeyUp(eKeyCode::LEFT) || Input::GetKeyUp(eKeyCode::UP) || Input::GetKeyUp(eKeyCode::DOWN))
		{
			mState = eCupheadState::Idle_L;
			mAnimator->Play(L"CupheadIdle_L", true);
		}
		if (Input::GetKeyUp(eKeyCode::RIGHT) || Input::GetKeyUp(eKeyCode::UP) || Input::GetKeyUp(eKeyCode::DOWN))
		{
			mState = eCupheadState::Idle_R;
			mAnimator->Play(L"CupheadIdle_R", true);
		}

		if (Input::GetKeyDown(eKeyCode::X))
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

		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 400.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 400.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::UP) && Input::GetKey(eKeyCode::LEFT) && Input::GetKeyDown(eKeyCode::X))
		{
			mState = eCupheadState::Shoot_Run_diag_Up_L;
			mAnimator->Play(L"ShootRun_diagonal_up_L", true);
		}
		else if (Input::GetKey(eKeyCode::UP) && Input::GetKey(eKeyCode::RIGHT) && Input::GetKeyDown(eKeyCode::X))
		{
			mState = eCupheadState::Shoot_Run_diag_Up_R;
			mAnimator->Play(L"ShootRun_diagonal_up_R", true);
		}


		if (Input::GetKeyDown(eKeyCode::DOWN) && Input::GetKey(eKeyCode::LEFT))
		{
			mState = eCupheadState::Duck_L;
			mAnimator->Play(L"DuckDuck_start_L", false);
		}
		else if (Input::GetKeyDown(eKeyCode::DOWN) && Input::GetKey(eKeyCode::RIGHT))
		{
			mState = eCupheadState::Duck_R;
			mAnimator->Play(L"DuckDuck_start_R", false);
		}

		if (Input::GetKeyDown(eKeyCode::Z) && mJumpCount >= 1)
		{
			mJumpCount--;
			mbGroundCheck = false;

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= mJumpScale;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			if (Cuphead::GetCupheadState() == eCupheadState::Move_L)
			{
				mState = eCupheadState::Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else
			{
				mState = eCupheadState::Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
		}
		
		tr->SetPos(pos);
	}

	void Cuphead::jump()
	{
		if (mbGroundCheck)
		{
			if (GetCupheadState() == eCupheadState::Jump_L)
			{
				mState = eCupheadState::Idle_L;
				mAnimator->Play(L"CupheadIdle_L", true);
			}
			else if (GetCupheadState() == eCupheadState::Jump_R)
			{
				mState = eCupheadState::Idle_R;
				mAnimator->Play(L"CupheadIdle_R", true);
			}
		
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::LEFT))
		{
			pos.x -= 400.0f * Time::DeltaTime();
			if (GetCupheadState() == eCupheadState::Jump_R)
			{
				mState = eCupheadState::Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
		}

		if (Input::GetKey(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::RIGHT))
		{
			pos.x += 400.0f * Time::DeltaTime();
			if (GetCupheadState() == eCupheadState::Jump_L)
			{
				mState = eCupheadState::Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::X) || Input::GetKey(eKeyCode::X))
		{
			if (GetCupheadState() == eCupheadState::Jump_L)
			{
				mState = eCupheadState::Shoot_Jump_L;
			}
			else if (GetCupheadState() == eCupheadState::Jump_R)
			{
				mState = eCupheadState::Shoot_Jump_R;
			}
		}

		tr->SetPos(pos);
	}

	void Cuphead::duck()
	{
		
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mState = eCupheadState::Duck_L;
			mAnimator->Play(L"DuckIdle_L", true);
		}
		else if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mState = eCupheadState::Duck_R;
			mAnimator->Play(L"DuckIdle_R", true);
		}

		if (Input::GetKeyUp(eKeyCode::DOWN) && GetCupheadState() == eCupheadState::Duck_L)
		{

			if (Input::GetKeyDown(eKeyCode::LEFT))
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
		if (Input::GetKeyUp(eKeyCode::DOWN) && GetCupheadState() == eCupheadState::Duck_R)
		{

			if (Input::GetKeyDown(eKeyCode::RIGHT))
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

		if (Input::GetKey(eKeyCode::X) || Input::GetKeyDown(eKeyCode::X))
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

		if (Input::GetKeyDown(eKeyCode::Z) && mJumpCount >= 1)
		{

			mJumpCount--;
			mbGroundCheck = false;

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= mJumpScale;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			if (Cuphead::GetCupheadState() == eCupheadState::Duck_L)
			{
				mState = eCupheadState::Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else
			{
				mState = eCupheadState::Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
		}

	}
	void Cuphead::aim_up()
	{
		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT))
		{
			mState = eCupheadState::Move_L;
			mAnimator->Play(L"RunRun_L", true);
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT))
		{
			mState = eCupheadState::Move_R;
			mAnimator->Play(L"RunRun_R", true);
		}

		if (Input::GetKey(eKeyCode::X))
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

		if (Input::GetKeyUp(eKeyCode::UP))
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

		if (Input::GetKeyDown(eKeyCode::Z) && mJumpCount >= 1)
		{
			mJumpCount--;
			mbGroundCheck = false;

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= mJumpScale;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			if (Cuphead::GetCupheadState() == eCupheadState::Aim_UP_L)
			{
				mState = eCupheadState::Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else
			{
				mState = eCupheadState::Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
		}
	}

	void Cuphead::shoot()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetCupheadState() == eCupheadState::Shoot_L)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_L* bullet;

					bullet = object::Instantiate<Peashot_L>((pos + Vector2(-60.0f, -60.0f)), eLayerType::Bullet);
					bullet->SetDegree(180.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(-80.0f, -80.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}

				if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT))
				{
					mState = eCupheadState::Shoot_Run_R;
					mAnimator->Play(L"ShootRun_R", true);
				}
				if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT))
				{
					mState = eCupheadState::Shoot_Run_L;
					mAnimator->Play(L"ShootRun_L", true);
				}

				if (Input::GetKeyDown(eKeyCode::DOWN))
				{
					mState = eCupheadState::Duck_Shoot_L;
					mAnimator->Play(L"DuckShoot_L", true);
				}

				if (Input::GetKeyDown(eKeyCode::UP))
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
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					TestBullet* bullet
						= object::Instantiate<TestBullet>(pos + Vector2(60.0f, -60.0f), eLayerType::Bullet);

					bullet->SetDegree(0.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(40.0f, -80.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}

				if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT))
				{
					mState = eCupheadState::Shoot_Run_R;
					mAnimator->Play(L"ShootRun_R", true);
				}
				if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT))
				{
					mState = eCupheadState::Shoot_Run_L;
					mAnimator->Play(L"ShootRun_L", true);
				}

				if (Input::GetKeyDown(eKeyCode::DOWN))
				{
					mState = eCupheadState::Duck_Shoot_R;
					mAnimator->Play(L"DuckShoot_R", true);
				}

				if (Input::GetKeyDown(eKeyCode::UP))
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

		if (Input::GetKeyDown(eKeyCode::Z) && mJumpCount >= 1)
		{
			mJumpCount--;
			mbGroundCheck = false;

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= mJumpScale;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			if (Cuphead::GetCupheadState() == eCupheadState::Shoot_L)
			{
				mState = eCupheadState::Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else
			{
				mState = eCupheadState::Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
		}

	}

	void Cuphead::shoot_run()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetCupheadState() == eCupheadState::Shoot_Run_L)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_L* bullet
						= object::Instantiate<Peashot_L>((pos + Vector2(-60.0f, -50.0f)), eLayerType::Bullet);
					bullet->SetDegree(180.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(-110.0f, -70.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}
				if (Input::GetKey(eKeyCode::LEFT))
				{
					pos.x -= 400.0f * Time::DeltaTime();
				}
				tr->SetPos(pos);

				if (Input::GetKeyUp(eKeyCode::LEFT))
				{
					mState = eCupheadState::Shoot_L;
					mAnimator->Play(L"ShootStraight_Shoot_L", true);
				}

				if (Input::GetKeyDown(eKeyCode::UP))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_L;
					mAnimator->Play(L"ShootRun_diagonal_up_L", true);
				}

				if (Input::GetKeyDown(eKeyCode::RIGHT))
				{
					mState = eCupheadState::Shoot_Run_R;
					mAnimator->Play(L"ShootRun_R", true);
				}

				if (Input::GetKeyDown(eKeyCode::DOWN))
				{
					mState = eCupheadState::Duck_Shoot_L;
					mAnimator->Play(L"DuckShoot_L", true);
				}

			}
			else if (Input::GetKey(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::X))
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
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					TestBullet* bullet
						= object::Instantiate<TestBullet>((tr->GetPos() + Vector2(60.0f, -50.0f)), eLayerType::Bullet);
					bullet->SetDegree(0.0f);

					object::Instantiate<PeashotSpark>((tr->GetPos() + Vector2(70.0f, -70.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}
				if (Input::GetKey(eKeyCode::RIGHT))
				{
					pos.x += 400.0f * Time::DeltaTime();
				}
				tr->SetPos(pos);

				if (Input::GetKeyUp(eKeyCode::RIGHT))
				{
					mState = eCupheadState::Shoot_R;
					mAnimator->Play(L"ShootStraight_Shoot_R", true);
				}

				if (Input::GetKeyDown(eKeyCode::UP))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_R;
					mAnimator->Play(L"ShootRun_diagonal_up_R", true);
				}

				if (Input::GetKeyDown(eKeyCode::LEFT))
				{
					mState = eCupheadState::Shoot_Run_L;
					mAnimator->Play(L"ShootRun_L", true);
				}

				if (Input::GetKeyDown(eKeyCode::DOWN))
				{
					mState = eCupheadState::Duck_Shoot_R;
					mAnimator->Play(L"DuckShoot_R", true);
				}

			}
			else if (Input::GetKey(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::X))
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

		if (Input::GetKeyDown(eKeyCode::Z) && mJumpCount >= 1)
		{
			mJumpCount--;
			mbGroundCheck = false;

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= mJumpScale;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			if (Cuphead::GetCupheadState() == eCupheadState::Shoot_Run_L)
			{
				mState = eCupheadState::Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else
			{
				mState = eCupheadState::Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
		}
	}

	void Cuphead::shoot_duck()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetCupheadState() == eCupheadState::Duck_Shoot_L)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_L* bullet
						= object::Instantiate<Peashot_L>((tr->GetPos() + Vector2(-60.0f, -20.0f)), eLayerType::Bullet);
					bullet->SetDegree(180.0f);

					object::Instantiate<PeashotSpark>((tr->GetPos() + Vector2(-90.0f, -40.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}

				if (Input::GetKeyDown(eKeyCode::RIGHT))
				{
					mState = eCupheadState::Duck_Shoot_R;
					mAnimator->Play(L"DuckShoot_R", true);
				}
				if (Input::GetKey(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::DOWN))
				{
					mState = eCupheadState::Shoot_Run_L;
					mAnimator->Play(L"ShootRun_L", true);
				}
				if (Input::GetKey(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::DOWN))
				{
					mState = eCupheadState::Shoot_Run_R;
					mAnimator->Play(L"ShootRun_R", true);
				}
				if (Input::GetKeyUp(eKeyCode::DOWN))
				{
					mState = eCupheadState::Shoot_L;
					mAnimator->Play(L"ShootStraight_Shoot_L", true);
				}

			}
			else if (Input::GetKey(eKeyCode::DOWN))
			{
				mState = eCupheadState::Duck_L;
				mAnimator->Play(L"DuckIdle_L", true);
			}
		}
		if (GetCupheadState() == eCupheadState::Duck_Shoot_R)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					TestBullet* bullet
						= object::Instantiate<TestBullet>((tr->GetPos() + Vector2(60.0f, -20.0f)), eLayerType::Bullet);
					bullet->SetDegree(0.0f);

					object::Instantiate<PeashotSpark>((tr->GetPos() + Vector2(70.0f, -40.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}

				if (Input::GetKeyDown(eKeyCode::LEFT))
				{
					mState = eCupheadState::Duck_Shoot_L;
					mAnimator->Play(L"DuckShoot_L", true);
				}
				if (Input::GetKey(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::DOWN))
				{
					mState = eCupheadState::Shoot_Run_L;
					mAnimator->Play(L"ShootRun_L", true);
				}
				if (Input::GetKey(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::DOWN))
				{
					mState = eCupheadState::Shoot_Run_R;
					mAnimator->Play(L"ShootRun_R", true);
				}
				if (Input::GetKeyUp(eKeyCode::DOWN))
				{
					mState = eCupheadState::Shoot_R;
					mAnimator->Play(L"ShootStraight_Shoot_R", true);
				}
			}
			else if (Input::GetKey(eKeyCode::DOWN))
			{
				mState = eCupheadState::Duck_R;
				mAnimator->Play(L"DuckIdle_R", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z) && mJumpCount >= 1)
		{
			mJumpCount--;
			mbGroundCheck = false;

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= mJumpScale;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			if (Cuphead::GetCupheadState() == eCupheadState::Duck_Shoot_L)
			{
				mState = eCupheadState::Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else
			{
				mState = eCupheadState::Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
		}
	}

	void Cuphead::shoot_up()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetCupheadState() == eCupheadState::Shoot_UP_L)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_Up* bullet
						= object::Instantiate<Peashot_Up>(pos + Vector2(-30.0f, -90.0f), eLayerType::Bullet);

					bullet->SetDegree(-90.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(-60.0f, -150.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}

				if (Input::GetKeyUp(eKeyCode::UP))
				{
					mState = eCupheadState::Shoot_L;
					mAnimator->Play(L"ShootStraight_Shoot_L", true);
				}

				if (Input::GetKey(eKeyCode::LEFT))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_L;
					mAnimator->Play(L"ShootRun_diagonal_up_L", true);
				}
				if (Input::GetKey(eKeyCode::RIGHT))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_R;
					mAnimator->Play(L"ShootRun_diagonal_up_R", true);
				}

			}
			else if (Input::GetKey(eKeyCode::UP))
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
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_Up* bullet
						= object::Instantiate<Peashot_Up>(pos + Vector2(30.0f, -90.0f), eLayerType::Bullet);

					bullet->SetDegree(-90.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(20.0f, -150.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}

				if (Input::GetKeyUp(eKeyCode::UP))
				{
					mState = eCupheadState::Shoot_R;
					mAnimator->Play(L"ShootStraight_Shoot_R", true);
				}

				if (Input::GetKey(eKeyCode::LEFT))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_L;
					mAnimator->Play(L"ShootRun_diagonal_up_L", true);
				}
				if (Input::GetKey(eKeyCode::RIGHT))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_R;
					mAnimator->Play(L"ShootRun_diagonal_up_R", true);
				}
			}
			else if (Input::GetKey(eKeyCode::UP))
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

		if (Input::GetKeyDown(eKeyCode::Z) && mJumpCount >= 1)
		{
			mJumpCount--;
			mbGroundCheck = false;

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= mJumpScale;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			if (Cuphead::GetCupheadState() == eCupheadState::Shoot_UP_L)
			{
				mState = eCupheadState::Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else
			{
				mState = eCupheadState::Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
		}
	}

	void Cuphead::shoot_run_diag_up()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetCupheadState() == eCupheadState::Shoot_Run_diag_Up_L)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_diagnal_L* bullet
						= object::Instantiate<Peashot_diagnal_L>((pos + Vector2(-60.0f, -40.0f)), eLayerType::Bullet);
					bullet->SetDegree(-135.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(-90.0f, -120.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}
				if (Input::GetKey(eKeyCode::LEFT))
				{
					pos.x -= 400.0f * Time::DeltaTime();
				}
				tr->SetPos(pos);

				if (Input::GetKeyUp(eKeyCode::LEFT))
				{
					mState = eCupheadState::Shoot_UP_L;
					mAnimator->Play(L"ShootUp_L", true);
				}

				if (Input::GetKeyUp(eKeyCode::UP))
				{
					mState = eCupheadState::Shoot_Run_L;
					mAnimator->Play(L"ShootRun_L", true);
				}

				if (Input::GetKey(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_R;
					mAnimator->Play(L"ShootRun_diagonal_up_R", true);
				}

			}
			else if (Input::GetKey(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::X))
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
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_diagnal_R* bullet
						= object::Instantiate<Peashot_diagnal_R>((tr->GetPos() + Vector2(60.0f, -40.0f)), eLayerType::Bullet);
					bullet->SetDegree(-45.0f);

					object::Instantiate<PeashotSpark>((tr->GetPos() + Vector2(70.0f, -120.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}
				if (Input::GetKey(eKeyCode::RIGHT))
				{
					pos.x += 400.0f * Time::DeltaTime();
				}
				tr->SetPos(pos);

				if (Input::GetKeyUp(eKeyCode::RIGHT))
				{
					mState = eCupheadState::Shoot_UP_R;
					mAnimator->Play(L"ShootUp_R", true);
				}

				if (Input::GetKeyUp(eKeyCode::UP))
				{
					mState = eCupheadState::Shoot_Run_R;
					mAnimator->Play(L"ShootRun_R", true);
				}

				if (Input::GetKey(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
				{
					mState = eCupheadState::Shoot_Run_diag_Up_L;
					mAnimator->Play(L"ShootRun_diagonal_up_L", true);
				}

			}
			else if (Input::GetKey(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::X))
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

		if (Input::GetKeyDown(eKeyCode::Z) && mJumpCount >= 1)
		{
			mJumpCount--;
			mbGroundCheck = false;

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= mJumpScale;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			if (Cuphead::GetCupheadState() == eCupheadState::Shoot_Run_diag_Up_L)
			{
				mState = eCupheadState::Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else
			{
				mState = eCupheadState::Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
		}
	}

	void Cuphead::shoot_jump()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetCupheadState() == eCupheadState::Shoot_Jump_L)
		{
			if (Input::GetKey(eKeyCode::X))
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

				if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT))
				{
					mState = eCupheadState::Shoot_Jump_R;
					mAnimator->Play(L"JumpJump_R", true);
				}
				if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT))
				{
					pos.x -= 400.0f * Time::DeltaTime();
					mState = eCupheadState::Shoot_Jump_L;
				}

				if (Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
				{
					mState = eCupheadState::Shoot_Jump_Up_L;
				}

				if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
					&& (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
				{
					mState = eCupheadState::Shoot_Jump_diag_Up_L;
				}

				if (mbGroundCheck)
				{
					if ((Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
					{
						mState = eCupheadState::Shoot_Run_L;
						mAnimator->Play(L"ShootRun_L", true);
					}
					if ((Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
					{
						mState = eCupheadState::Shoot_Run_R;
						mAnimator->Play(L"ShootRun_R", true);
					}
					if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
						&& (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
					{
						mState = eCupheadState::Shoot_Run_diag_Up_L;
						mAnimator->Play(L"ShootRun_diagonal_up_L", true);
					}
					if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
						&& (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
					{
						mState = eCupheadState::Shoot_Run_diag_Up_R;
						mAnimator->Play(L"ShootRun_diagonal_up_R", true);
					}
					if (Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
					{
						mState = eCupheadState::Shoot_UP_L;
						mAnimator->Play(L"ShootUp_L", true);
					}

					if (Input::GetKeyUp(eKeyCode::UP) && Input::GetKeyUp(eKeyCode::RIGHT)
						&& Input::GetKeyUp(eKeyCode::LEFT))
					{
						mState = eCupheadState::Shoot_L;
						mAnimator->Play(L"ShootStraight_Shoot_L", true);
					}
				}



			}
			else if(!mbGroundCheck)
			{
				mState = eCupheadState::Jump_L;
			}
			else if (mbGroundCheck)
			{
				mState = eCupheadState::Idle_L;
			}
			
		}
		if (GetCupheadState() == eCupheadState::Shoot_Jump_R)
		{
			if (Input::GetKey(eKeyCode::X))
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

				if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT))
				{
					mState = eCupheadState::Shoot_Jump_L;
					mAnimator->Play(L"JumpJump_L", true);
				}
				if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT))
				{
					pos.x += 400.0f * Time::DeltaTime();
					mState = eCupheadState::Shoot_Jump_R;
				}

				if (Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
				{
					mState = eCupheadState::Shoot_Jump_Up_R;
				}

				if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
					&& (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
				{
					mState = eCupheadState::Shoot_Jump_diag_Up_R;
				}

				if (mbGroundCheck)
				{
					if ((Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
					{
						mState = eCupheadState::Shoot_Run_L;
						mAnimator->Play(L"ShootRun_L", true);
					}
					if ((Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
					{
						mState = eCupheadState::Shoot_Run_R;
						mAnimator->Play(L"ShootRun_R", true);
					}
					if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
						&& (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
					{
						mState = eCupheadState::Shoot_Run_diag_Up_L;
						mAnimator->Play(L"ShootRun_diagonal_up_L", true);
					}
					if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
						&& (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
					{
						mState = eCupheadState::Shoot_Run_diag_Up_R;
						mAnimator->Play(L"ShootRun_diagonal_up_R", true);
					}
					if (Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
					{
						mState = eCupheadState::Shoot_UP_R;
						mAnimator->Play(L"ShootUp_R", true);
					}

					if (Input::GetKeyUp(eKeyCode::UP) && Input::GetKeyUp(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
					{
						mState = eCupheadState::Shoot_R;
						mAnimator->Play(L"ShootStraight_Shoot_R", true);
					}
				}
			}
			else if (!mbGroundCheck)
			{
				mState = eCupheadState::Jump_R;
			}
			else if (mbGroundCheck)
			{
				mState = eCupheadState::Idle_R;
			}
		
		}

		tr->SetPos(pos);
	}

	void Cuphead::shoot_jump_up()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetCupheadState() == eCupheadState::Shoot_Jump_Up_L)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_Up* bullet
						= object::Instantiate<Peashot_Up>(pos + Vector2(-30.0f, -90.0f), eLayerType::Bullet);

					bullet->SetDegree(-90.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(-60.0f, -150.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}

				if (Input::GetKeyUp(eKeyCode::UP))
				{
					mState = eCupheadState::Shoot_Jump_L;
				}

				if ((Input::GetKey(eKeyCode::UP))
					&& (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
				{
					mState = eCupheadState::Shoot_Jump_diag_Up_R;
				}

				if ((Input::GetKey(eKeyCode::UP))
					&& (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
				{
					mState = eCupheadState::Shoot_Jump_diag_Up_L;
				}

				if (mbGroundCheck)
				{
					if ((Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
					{
						mState = eCupheadState::Shoot_Run_L;
						mAnimator->Play(L"ShootRun_L", true);
					}
					if ((Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
					{
						mState = eCupheadState::Shoot_Run_R;
						mAnimator->Play(L"ShootRun_R", true);
					}
					if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
						&& (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
					{
						mState = eCupheadState::Shoot_Run_diag_Up_L;
						mAnimator->Play(L"ShootRun_diagonal_up_L", true);
					}
					if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
						&& (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
					{
						mState = eCupheadState::Shoot_Run_diag_Up_R;
						mAnimator->Play(L"ShootRun_diagonal_up_R", true);
					}
					if (Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
					{
						mState = eCupheadState::Shoot_UP_L;
						mAnimator->Play(L"ShootUp_L", true);
					}

					if (Input::GetKeyUp(eKeyCode::UP) && Input::GetKeyUp(eKeyCode::RIGHT)
						&& Input::GetKeyUp(eKeyCode::LEFT))
					{
						mState = eCupheadState::Shoot_L;
						mAnimator->Play(L"ShootStraight_Shoot_L", true);
					}
				}
			}
			else if (!mbGroundCheck)
			{
				mState = eCupheadState::Jump_L;
			}
			else if (mbGroundCheck)
			{
				mState = eCupheadState::Idle_L;
			}
		}
		if (GetCupheadState() == eCupheadState::Shoot_Jump_Up_R)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					Peashot_Up* bullet
						= object::Instantiate<Peashot_Up>(pos + Vector2(10.0f, -90.0f), eLayerType::Bullet);

					bullet->SetDegree(-90.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(0.0f, -150.0f)), eLayerType::Effect);

					mSecond = 0.0f;
				}
				if (Input::GetKeyUp(eKeyCode::UP))
				{
					mState = eCupheadState::Shoot_Jump_R;
				}

				if ((Input::GetKey(eKeyCode::UP))
					&& (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
				{
					mState = eCupheadState::Shoot_Jump_diag_Up_R;
				}

				if ((Input::GetKey(eKeyCode::UP))
					&& (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
				{
					mState = eCupheadState::Shoot_Jump_diag_Up_L;
				}

				if (mbGroundCheck)
				{
					if ((Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
					{
						mState = eCupheadState::Shoot_Run_L;
						mAnimator->Play(L"ShootRun_L", true);
					}
					if ((Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
					{
						mState = eCupheadState::Shoot_Run_R;
						mAnimator->Play(L"ShootRun_R", true);
					}
					if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
						&& (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
					{
						mState = eCupheadState::Shoot_Run_diag_Up_L;
						mAnimator->Play(L"ShootRun_diagonal_up_L", true);
					}
					if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
						&& (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
					{
						mState = eCupheadState::Shoot_Run_diag_Up_R;
						mAnimator->Play(L"ShootRun_diagonal_up_R", true);
					}
					if (Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
					{
						mState = eCupheadState::Shoot_UP_R;
						mAnimator->Play(L"ShootUp_R", true);
					}
					if (Input::GetKeyUp(eKeyCode::UP) && Input::GetKeyUp(eKeyCode::RIGHT)
						&& Input::GetKeyUp(eKeyCode::LEFT))
					{
						mState = eCupheadState::Shoot_R;
						mAnimator->Play(L"ShootStraight_Shoot_R", true);
					}
					
				}
			}
			else if (!mbGroundCheck)
			{
				mState = eCupheadState::Jump_R;
			}
			else if (mbGroundCheck)
			{
				mState = eCupheadState::Idle_R;
			}
		}
	}

	void Cuphead::shoot_jump_diag_up()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetCupheadState() == eCupheadState::Shoot_Jump_diag_Up_L)
		{
			if (Input::GetKey(eKeyCode::X))
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

				if (Input::GetKeyUp(eKeyCode::UP) && Input::GetKeyUp(eKeyCode::LEFT))
				{
					mState = eCupheadState::Shoot_Jump_L;
				}

				if (Input::GetKeyUp(eKeyCode::UP) && Input::GetKey(eKeyCode::LEFT))
				{
					mState = eCupheadState::Shoot_Jump_L;
				}

				if (Input::GetKey(eKeyCode::UP) && Input::GetKey(eKeyCode::LEFT))
				{
					pos.x -= 400.0f * Time::DeltaTime();
				}

				if (Input::GetKeyUp(eKeyCode::UP) && Input::GetKey(eKeyCode::RIGHT))
				{
					mState = eCupheadState::Shoot_Jump_R;
				}

				if (Input::GetKey(eKeyCode::UP) && Input::GetKeyUp(eKeyCode::LEFT))
				{
					mState = eCupheadState::Shoot_Jump_Up_L;
				}

				if ((Input::GetKey(eKeyCode::UP))
					&& (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
				{
					mState = eCupheadState::Shoot_Jump_diag_Up_L;
				}

				if (mbGroundCheck)
				{
					if ((Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
					{
						mState = eCupheadState::Shoot_Run_L;
						mAnimator->Play(L"ShootRun_L", true);
					}
					if ((Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
					{
						mState = eCupheadState::Shoot_Run_R;
						mAnimator->Play(L"ShootRun_R", true);
					}
					if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
						&& (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
					{
						mState = eCupheadState::Shoot_Run_diag_Up_L;
						mAnimator->Play(L"ShootRun_diagonal_up_L", true);
					}
					if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
						&& (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
					{
						mState = eCupheadState::Shoot_Run_diag_Up_R;
						mAnimator->Play(L"ShootRun_diagonal_up_R", true);
					}
					if (Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
					{
						mState = eCupheadState::Shoot_UP_L;
						mAnimator->Play(L"ShootUp_L", true);
					}

					if (Input::GetKeyUp(eKeyCode::UP) && Input::GetKeyUp(eKeyCode::RIGHT)
						&& Input::GetKeyUp(eKeyCode::LEFT))
					{
						mState = eCupheadState::Shoot_L;
						mAnimator->Play(L"ShootStraight_Shoot_L", true);
					}
				}
			}
			else if (!mbGroundCheck)
			{
				mState = eCupheadState::Jump_L;
			}
			else if (mbGroundCheck)
			{
				mState = eCupheadState::Idle_L;
			}
		}
		if (GetCupheadState() == eCupheadState::Shoot_Jump_diag_Up_R)
		{
			if (Input::GetKey(eKeyCode::X))
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

				if (Input::GetKeyUp(eKeyCode::UP) && Input::GetKeyUp(eKeyCode::LEFT))
				{
					mState = eCupheadState::Shoot_Jump_R;
				}

				if (Input::GetKeyUp(eKeyCode::UP) && Input::GetKey(eKeyCode::LEFT))
				{
					mState = eCupheadState::Shoot_Jump_L;
				}

				if (Input::GetKeyUp(eKeyCode::UP) && Input::GetKey(eKeyCode::RIGHT))
				{
					mState = eCupheadState::Shoot_Jump_R;
				}

				if (Input::GetKey(eKeyCode::UP) && Input::GetKey(eKeyCode::RIGHT))
				{
					pos.x += 400.0f * Time::DeltaTime();
				}

				if (Input::GetKey(eKeyCode::UP) && Input::GetKeyUp(eKeyCode::RIGHT))
				{
					mState = eCupheadState::Shoot_Jump_Up_R;
				}

				if ((Input::GetKey(eKeyCode::UP))
					&& (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
				{
					mState = eCupheadState::Shoot_Jump_diag_Up_L;
				}

				if (mbGroundCheck)
				{
					if ((Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
					{
						mState = eCupheadState::Shoot_Run_L;
						mAnimator->Play(L"ShootRun_L", true);
					}
					if ((Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
					{
						mState = eCupheadState::Shoot_Run_R;
						mAnimator->Play(L"ShootRun_R", true);
					}
					if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
						&& (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
					{
						mState = eCupheadState::Shoot_Run_diag_Up_L;
						mAnimator->Play(L"ShootRun_diagonal_up_L", true);
					}
					if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
						&& (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
					{
						mState = eCupheadState::Shoot_Run_diag_Up_R;
						mAnimator->Play(L"ShootRun_diagonal_up_R", true);
					}
					if (Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
					{
						mState = eCupheadState::Shoot_UP_R;
						mAnimator->Play(L"ShootUp_R", true);
					}

					if (Input::GetKeyUp(eKeyCode::UP) && Input::GetKeyUp(eKeyCode::RIGHT)
						&& Input::GetKeyUp(eKeyCode::LEFT))
					{
						mState = eCupheadState::Shoot_R;
						mAnimator->Play(L"ShootStraight_Shoot_R", true);
					}
				}
			}
			else if (!mbGroundCheck)
			{
				mState = eCupheadState::Jump_R;
			}
			else if (mbGroundCheck)
			{
				mState = eCupheadState::Idle_R;
			}
		}
		tr->SetPos(pos);
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