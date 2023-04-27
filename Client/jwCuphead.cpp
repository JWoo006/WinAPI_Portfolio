#include "jwCuphead.h"
#include "jwTime.h"
#include "jwSceneManager.h"
#include "jwInput.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwScene.h"
#include "jwPeaShot_Normal.h"
#include "jwPeashotSpark.h"
#include "jwObject.h"
#include "jwRigidbody.h"
#include "jwJumpDust.h"
#include "jwDashEffect.h"
#include "jwParryEffect.h"
#include "jwOnHitEffect.h"

namespace jw
{
	Cuphead::Cuphead()
		: mSecond(1.0f)
		, mDashTime(0.0f)
		, mJumpCount(1)
		, mAirDashCount(1)
		, mParryCount(1)
		, mbGroundCheck(true)
		, mbDashEnd(false)
		, mbParrying(false)
		, mbParrySuccess(false)
		, mJumpScale(1700.0f)
		, mbInvincibile(false)
		, mInvincibileTime(0.0f)
		, mbFlashCheck(false)
		, mFlashTime(0.0f)
	{
	}
	Cuphead::~Cuphead()
	{
	}
	void Cuphead::Initialize()
	{
		mFiredelay = PeaShot_Normal::GetDelay();

		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Intro", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Idle_L", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Idle_R", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Run\\Run_L", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Run\\Run_R", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Jump\\Jump_L", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Jump\\Jump_R", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Duck_start_L", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Duck_start_R", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Idle_L", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Idle_R", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Shoot_L", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Duck\\Shoot_R", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, eAnimationDir::R);


		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Straight_Shoot_L", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Straight_Shoot_R", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Up_L", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Up_R", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Run_L", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Run_R", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Run_diagonal_up_L", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Shoot\\Run_diagonal_up_R", Vector2::Zero, (mFiredelay * 0.3f), eImageFormat::PNG, eAnimationDir::R);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Aim\\Up_L", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Aim\\Up_R", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Dash\\Ground_L", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Dash\\Ground_R", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Dash\\Air_L", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Dash\\Air_R", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Parry\\Parry_L", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Parry\\Parry_R", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Hit\\Ground_L", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Hit\\Ground_R", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"DuckDuck_start_L")
			= std::bind(&Cuphead::duckLCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"DuckDuck_start_R")
			= std::bind(&Cuphead::duckRCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"CupheadIdle_R")
			= std::bind(&Cuphead::idleCompleteEvent, this);

		mAnimator->GetStartEvent(L"ParryParry_L") = std::bind(&Cuphead::parryStartEvent, this);
		mAnimator->GetStartEvent(L"ParryParry_R") = std::bind(&Cuphead::parryStartEvent, this);
		mAnimator->GetCompleteEvent(L"ParryParry_L") = std::bind(&Cuphead::parryCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"ParryParry_R") = std::bind(&Cuphead::parryCompleteEvent, this);

		mAnimator->GetCompleteEvent(L"HitGround_L") = std::bind(&Cuphead::OnhitCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"HitGround_R") = std::bind(&Cuphead::OnhitCompleteEvent, this);

		mAnimator->Play(L"CupheadIdle_R", true);
		
		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-35.0f, -145.0f));
		collider->SetSize(Vector2(90.0f, 150.0f));
		
		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		mState = eCupheadState::Idle_R;
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetScale(Vector2(1.0f, 1.0f));


		GameObject::Initialize();
	}
	void Cuphead::Update()
	{
		GameObject::Update();

		if (this->GetState() == eState::Death)
		{
			int a = 0;
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Onhit();

		switch (mState)
		{

		case jw::Cuphead::eCupheadState::Move_L:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			move();
			break;
		case jw::Cuphead::eCupheadState::Move_R:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			move();
			break;
		case jw::Cuphead::eCupheadState::Jump_L:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			jump();
			break;
		case jw::Cuphead::eCupheadState::Jump_R:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			jump();
			break;
		case jw::Cuphead::eCupheadState::Duck_L:
			collider->SetCenter(Vector2(-40.0f, -65.0f));
			collider->SetSize(Vector2(90.0f, 70.0f));
			duck();
			break;
		case jw::Cuphead::eCupheadState::Duck_R:
			collider->SetCenter(Vector2(-40.0f, -65.0f));
			collider->SetSize(Vector2(90.0f, 70.0f));
			duck();
			break;
		case jw::Cuphead::eCupheadState::Duck_Shoot_L:
			collider->SetCenter(Vector2(-40.0f, -65.0f));
			collider->SetSize(Vector2(90.0f, 70.0f));
			shoot_duck();
			break;
		case jw::Cuphead::eCupheadState::Duck_Shoot_R:
			collider->SetCenter(Vector2(-40.0f, -65.0f));
			collider->SetSize(Vector2(90.0f, 70.0f));
			shoot_duck();
			break;
		case jw::Cuphead::eCupheadState::Dash_Ground_L:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			dash();
			break;
		case jw::Cuphead::eCupheadState::Dash_Ground_R:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			dash();
			break;
		case jw::Cuphead::eCupheadState::Dash_Air_L:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			dash();
			break;
		case jw::Cuphead::eCupheadState::Dash_Air_R:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			dash();
			break;
		case jw::Cuphead::eCupheadState::Parry_L:
			parry();
			break;
		case jw::Cuphead::eCupheadState::Parry_R:
			parry();
			break;
		case jw::Cuphead::eCupheadState::Aim_UP_L:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			aim_up();
			break;
		case jw::Cuphead::eCupheadState::Aim_UP_R:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			aim_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_L:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			shoot();
			break;
		case jw::Cuphead::eCupheadState::Shoot_R:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			shoot();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Run_L:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			shoot_run();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Run_R:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			shoot_run();
			break;
		case jw::Cuphead::eCupheadState::Shoot_UP_L:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			shoot_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_UP_R:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			shoot_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Run_diag_Up_L:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			shoot_run_diag_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Run_diag_Up_R:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			shoot_run_diag_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Jump_L:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			shoot_jump();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Jump_R:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			shoot_jump();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Jump_Up_L:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			shoot_jump_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Jump_Up_R:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			shoot_jump_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Jump_diag_Up_L:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			shoot_jump_diag_up();
			break;
		case jw::Cuphead::eCupheadState::Shoot_Jump_diag_Up_R:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			shoot_jump_diag_up();
			break;
		case jw::Cuphead::eCupheadState::OnHit_L:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
		case jw::Cuphead::eCupheadState::OnHit_R:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
		case jw::Cuphead::eCupheadState::Death:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			death();
			break;
		case jw::Cuphead::eCupheadState::Idle_L:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			idle();
			break;
		case jw::Cuphead::eCupheadState::Idle_R:
			collider->SetCenter(Vector2(-40.0f, -125.0f));
			collider->SetSize(Vector2(90.0f, 130.0f));
			idle();
			break;
		default:
			break;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			if (mbInvincibile)
			{
				mbInvincibile = false;
			}
			else
			{
				mInvincibileTime = -9999.0;
				mbInvincibile = true;
			}
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
		if (!mbInvincibile)
		{
			// 패리 오브젝트 충돌 && 패링중
			if (other->GetOwner()->GetLayerType() == eLayerType::ParryObj && mbParrying)
			{
				mbParrySuccess = true;

				Transform* tr = other->GetOwner()->GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				object::Instantiate<ParryEffect>(Vector2(pos), eLayerType::Effect);


				Vector2 velocity;
				velocity.y -= 1600.0f;
				mRigidbody->SetVelocity(velocity);

				mParryCount = 1;
			}

			// 패리 오브젝트 충돌 && 패링중 X
			if (other->GetOwner()->GetLayerType() == eLayerType::ParryObj && !mbParrying && !mbInvincibile)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();

				mbInvincibile = true;

				wchar_t lastchar = mAnimator->GetActiveAnimation()->GetAnimationName().back();

				if (lastchar == L'L')
				{
					mRigidbody->SetGround(false);
					Vector2 velocity;
					velocity.y -= 800;
					velocity.x += 100;
					mRigidbody->SetVelocity(velocity);

					mState = eCupheadState::OnHit_L;
					mAnimator->Play(L"HitGround_L", true);

					pos.x += 50.0f;
					pos.y += 50.0f;
					object::Instantiate<OnHitEffect>(pos, eLayerType::Effect);
				}
				else if (lastchar == L'R')
				{
					mRigidbody->SetGround(false);
					Vector2 velocity;
					velocity.y -= 800;
					velocity.x -= 100;
					mRigidbody->SetVelocity(velocity);

					mState = eCupheadState::OnHit_R;
					mAnimator->Play(L"HitGround_R", true);

					pos.x -= 50.0f;
					pos.y += 50.0f;
					object::Instantiate<OnHitEffect>(pos, eLayerType::Effect);
				}
			}

			// 몬스터 충돌
			if (other->GetOwner()->GetLayerType() == eLayerType::Monster  && !mbInvincibile)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();

				mbInvincibile = true;

				wchar_t lastchar = mAnimator->GetActiveAnimation()->GetAnimationName().back();

				if (lastchar == L'L')
				{
					mRigidbody->SetGround(false);
					Vector2 velocity;
					velocity.y -= 800;
					velocity.x += 100;
					mRigidbody->SetVelocity(velocity);

					mState = eCupheadState::OnHit_L;
					mAnimator->Play(L"HitGround_L", true);

					pos.x += 50.0f;
					pos.y += 50.0f;
					object::Instantiate<OnHitEffect>(pos, eLayerType::Effect);
				}
				else if (lastchar == L'R')
				{
					mRigidbody->SetGround(false);
					Vector2 velocity;
					velocity.y -= 800;
					velocity.x -= 100;
					mRigidbody->SetVelocity(velocity);

					mState = eCupheadState::OnHit_R;
					mAnimator->Play(L"HitGround_R", true);

					pos.x -= 50.0f;
					pos.y += 50.0f;
					object::Instantiate<OnHitEffect>(pos, eLayerType::Effect);
				}
			}

			// 몬스터 총알 충돌
			if (other->GetOwner()->GetLayerType() == eLayerType::BossBullet && !mbInvincibile)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();

				mbInvincibile = true;

				wchar_t lastchar = mAnimator->GetActiveAnimation()->GetAnimationName().back();

				if (lastchar == L'L')
				{
					mRigidbody->SetGround(false);
					Vector2 velocity;
					velocity.y -= 800;
					velocity.x += 100;
					mRigidbody->SetVelocity(velocity);

					mState = eCupheadState::OnHit_L;
					mAnimator->Play(L"HitGround_L", true);

					pos.x += 50.0f;
					pos.y += 50.0f;
					object::Instantiate<OnHitEffect>(pos, eLayerType::Effect);
				}
				else if (lastchar == L'R')
				{
					mRigidbody->SetGround(false);
					Vector2 velocity;
					velocity.y -= 800;
					velocity.x -= 100;
					mRigidbody->SetVelocity(velocity);

					mState = eCupheadState::OnHit_R;
					mAnimator->Play(L"HitGround_R", true);

					pos.x -= 50.0f;
					pos.y += 50.0f;
					object::Instantiate<OnHitEffect>(pos, eLayerType::Effect);
				}
			}
		}

	}
	void Cuphead::OnCollisionStay(Collider* other)
	{
		if (mbInvincibile)
		{
			// 패리 오브젝트 충돌 && 패링중
			if (other->GetOwner()->GetLayerType() == eLayerType::ParryObj && mbParrying && !mbParrySuccess)
			{
				mbParrySuccess = true;

				Transform* tr = other->GetOwner()->GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				object::Instantiate<ParryEffect>(Vector2(pos), eLayerType::Effect);

				Vector2 velocity;
				velocity.y -= 1600.0f;
				mRigidbody->SetVelocity(velocity);

				mParryCount = 1;
			}

			if (other->GetOwner()->GetLayerType() == eLayerType::ParryObj && !mbParrying && !mbInvincibile)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();

				mbInvincibile = true;

				wchar_t lastchar = mAnimator->GetActiveAnimation()->GetAnimationName().back();

				if (lastchar == L'L')
				{
					mRigidbody->SetGround(false);
					Vector2 velocity;
					velocity.y -= 800;
					velocity.x += 100;
					mRigidbody->SetVelocity(velocity);

					mState = eCupheadState::OnHit_L;
					mAnimator->Play(L"HitGround_L", true);

					pos.x += 50.0f;
					pos.y += 50.0f;
					object::Instantiate<OnHitEffect>(pos, eLayerType::Effect);
				}
				else if (lastchar == L'R')
				{
					mRigidbody->SetGround(false);
					Vector2 velocity;
					velocity.y -= 800;
					velocity.x -= 100;
					mRigidbody->SetVelocity(velocity);

					mState = eCupheadState::OnHit_R;
					mAnimator->Play(L"HitGround_R", true);

					pos.x -= 50.0f;
					pos.y += 50.0f;
					object::Instantiate<OnHitEffect>(pos, eLayerType::Effect);
				}
			}
		}

		

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

		// 점프
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

		// 대시
		if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState==eCupheadState::Idle_L)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x -= 1000.0f;
			mRigidbody->SetVelocity(velocity);

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x -= 50.0f;
			object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::L);

			mState = eCupheadState::Dash_Ground_L;
			mAnimator->Play(L"DashGround_L", false);
		}
		else if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Idle_R)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x += 1000.0f;
			mRigidbody->SetVelocity(velocity);

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x += 50.0f;
			object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::R);

			mState = eCupheadState::Dash_Ground_R;
			mAnimator->Play(L"DashGround_R", false);
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

		
	}
	void Cuphead::move()
	{
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

		// 사격
		if (Input::GetKeyDown(eKeyCode::X) || Input::GetKey(eKeyCode::X))
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

		// 점프
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

		// 대시
		if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Move_L)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x -= 1000.0f;
			mRigidbody->SetVelocity(velocity);

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x -= 50.0f;
			object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::L);

			mState = eCupheadState::Dash_Ground_L;
			mAnimator->Play(L"DashGround_L", false);
		}
		else if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Move_R)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x += 1000.0f;
			mRigidbody->SetVelocity(velocity);

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x += 50.0f;
			object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::R);

			mState = eCupheadState::Dash_Ground_R;
			mAnimator->Play(L"DashGround_R", false);
		}
		
		tr->SetPos(pos);
	}

	void Cuphead::jump()
	{
		GroundInit();

		// 패리
		if (Input::GetKeyDown(eKeyCode::Z) && mParryCount > 0)
		{
			mParryCount--;

			if (mState == eCupheadState::Jump_L)
			{
				mState = eCupheadState::Parry_L;
				mAnimator->Play(L"ParryParry_L", false);
			}
			else if (mState == eCupheadState::Jump_R)
			{
				mState = eCupheadState::Parry_R;
				mAnimator->Play(L"ParryParry_R", false);
			}
		}

		// 대쉬
		if (mAirDashCount > 0)
		{
			if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Jump_L)
			{
				mAirDashCount--;

				mRigidbody->SetGround(true);
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.x -= 1000.0f;
				mRigidbody->SetVelocity(velocity);

				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				pos.x -= 50.0f;
				object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::L);

				mState = eCupheadState::Dash_Air_L;
				mAnimator->Play(L"DashAir_L", false);
			}
			else if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Jump_R)
			{
				mAirDashCount--;

				// 수평이동을 위해
				mRigidbody->SetGround(true);
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.x += 1000.0f;
				mRigidbody->SetVelocity(velocity);

				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				pos.x += 50.0f;
				object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::R);

				mState = eCupheadState::Dash_Air_R;
				mAnimator->Play(L"DashAir_R", false);
			}
		}	

		// 착지
		if (mbGroundCheck)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			object::Instantiate<JumpDust>(pos, eLayerType::Effect);

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

		// 사격
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

		// 사격
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

		// 점프
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

		// 대시
		if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Duck_L)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x -= 1000.0f;
			mRigidbody->SetVelocity(velocity);

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x -= 50.0f;
			object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::L);

			mState = eCupheadState::Dash_Ground_L;
			mAnimator->Play(L"DashGround_L", false);
		}
		else if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Duck_R)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x += 1000.0f;
			mRigidbody->SetVelocity(velocity);

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x += 50.0f;
			object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::R);

			mState = eCupheadState::Dash_Ground_R;
			mAnimator->Play(L"DashGround_R", false);
		}

	}
	void Cuphead::dash()
	{
		mDashTime += Time::DeltaTime();
		if (mDashTime >= 0.3f)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			mRigidbody->SetVelocity(Vector2::Zero);
			mDashTime = 0.0f;
			mbDashEnd = true;
		}

		if (mbDashEnd)
		{
			if (mState == eCupheadState::Dash_Ground_L)
			{
				mState = eCupheadState::Idle_L;
				mAnimator->Play(L"CupheadIdle_L", true);
				mbDashEnd = false;
			}
			else if(mState == eCupheadState::Dash_Ground_R)
			{
				mState = eCupheadState::Idle_R;
				mAnimator->Play(L"CupheadIdle_R", true);
				mbDashEnd = false;
			}
			else if (mState == eCupheadState::Dash_Air_L)
			{
				mState = eCupheadState::Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
				mRigidbody->SetGround(false);
				mbDashEnd = false;
			}
			else if (mState == eCupheadState::Dash_Air_R)
			{
				mState = eCupheadState::Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
				mRigidbody->SetGround(false);
				mbDashEnd = false;
			}

		}

	}
	void Cuphead::parry()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::LEFT))
		{
			pos.x -= 400.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::RIGHT))
		{
			pos.x += 400.0f * Time::DeltaTime();
		}

		if (mbGroundCheck)
		{
			if (mState == eCupheadState::Parry_L)
			{
				mState = eCupheadState::Idle_L;
				mAnimator->Play(L"CupheadIdle_L", true);
			}
			else if (mState == eCupheadState::Parry_R)
			{
				mState = eCupheadState::Idle_R;
				mAnimator->Play(L"CupheadIdle_R", true);
			}
		}

		tr->SetPos(pos);
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

		// 사격
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

		// 점프
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

		// 대시
		if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Aim_UP_L)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x -= 1000.0f;
			mRigidbody->SetVelocity(velocity);

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x -= 50.0f;
			object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::L);

			mState = eCupheadState::Dash_Ground_L;
			mAnimator->Play(L"DashGround_L", false);
		}
		else if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Aim_UP_R)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x += 1000.0f;
			mRigidbody->SetVelocity(velocity);

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x += 50.0f;
			object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::R);

			mState = eCupheadState::Dash_Ground_R;
			mAnimator->Play(L"DashGround_R", false);
		}
	}

	void Cuphead::shoot()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		// 사격
		if (GetCupheadState() == eCupheadState::Shoot_L)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					PeaShot_Normal* bullet;

					//bullet = object::Instantiate<Peashot_L>((pos + Vector2(-60.0f, -60.0f)), eLayerType::Bullet);
					bullet = object::Instantiate<PeaShot_Normal>((pos + Vector2(-60.0f, -60.0f)), eLayerType::Bullet, GetCupheadState());
					bullet->SetDegree(180.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(-70.0f, -40.0f)), eLayerType::Effect);

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

				if (Input::GetKeyDown(eKeyCode::DOWN) || Input::GetKey(eKeyCode::DOWN))
				{
					mState = eCupheadState::Duck_Shoot_L;
					mAnimator->Play(L"DuckShoot_L", true);
				}

				if (Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
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
					PeaShot_Normal* bullet;
					bullet = object::Instantiate<PeaShot_Normal>(pos + Vector2(60.0f, -60.0f), eLayerType::Bullet, GetCupheadState());

					bullet->SetDegree(0.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(50.0f, -40.0f)), eLayerType::Effect);

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

				if (Input::GetKeyDown(eKeyCode::DOWN) || Input::GetKey(eKeyCode::DOWN))
				{
					mState = eCupheadState::Duck_Shoot_R;
					mAnimator->Play(L"DuckShoot_R", true);
				}

				if (Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
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

		// 점프
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

		// 대시
		if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Shoot_L)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x -= 1000.0f;
			mRigidbody->SetVelocity(velocity);

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x -= 50.0f;
			object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::L);

			mState = eCupheadState::Dash_Ground_L;
			mAnimator->Play(L"DashGround_L", false);
		}
		else if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Shoot_R)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x += 1000.0f;
			mRigidbody->SetVelocity(velocity);

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x += 50.0f;
			object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::R);

			mState = eCupheadState::Dash_Ground_R;
			mAnimator->Play(L"DashGround_R", false);
		}

	}

	void Cuphead::shoot_run()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		// 사격
		if (GetCupheadState() == eCupheadState::Shoot_Run_L)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					PeaShot_Normal* bullet
						= object::Instantiate<PeaShot_Normal>((pos + Vector2(-60.0f, -50.0f)), eLayerType::Bullet, GetCupheadState());
					bullet->SetDegree(180.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(-100.0f, -30.0f)), eLayerType::Effect);

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
					PeaShot_Normal* bullet
						= object::Instantiate<PeaShot_Normal>((tr->GetPos() + Vector2(60.0f, -50.0f)), eLayerType::Bullet, GetCupheadState());
					bullet->SetDegree(0.0f);

					object::Instantiate<PeashotSpark>((tr->GetPos() + Vector2(80.0f, -30.0f)), eLayerType::Effect);

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

		// 점프
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

		// 대시
		if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Shoot_Run_L)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x -= 1000.0f;
			mRigidbody->SetVelocity(velocity);

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x -= 50.0f;
			object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::L);

			mState = eCupheadState::Dash_Ground_L;
			mAnimator->Play(L"DashGround_L", false);
		}
		else if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Shoot_Run_R)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x += 1000.0f;
			mRigidbody->SetVelocity(velocity);

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x += 50.0f;
			object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::R);

			mState = eCupheadState::Dash_Ground_R;
			mAnimator->Play(L"DashGround_R", false);
		}
	}

	void Cuphead::shoot_duck()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		// 사격
		if (GetCupheadState() == eCupheadState::Duck_Shoot_L)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					PeaShot_Normal* bullet
						= object::Instantiate<PeaShot_Normal>((tr->GetPos() + Vector2(-60.0f, -20.0f)), eLayerType::Bullet, GetCupheadState());
					bullet->SetDegree(180.0f);

					object::Instantiate<PeashotSpark>((tr->GetPos() + Vector2(-90.0f, -10.0f)), eLayerType::Effect);

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
					PeaShot_Normal* bullet
						= object::Instantiate<PeaShot_Normal>((tr->GetPos() + Vector2(60.0f, -20.0f)), eLayerType::Bullet, GetCupheadState());
					bullet->SetDegree(0.0f);

					object::Instantiate<PeashotSpark>((tr->GetPos() + Vector2(70.0f, -10.0f)), eLayerType::Effect);

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

		// 점프
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

		// 사격
		if (GetCupheadState() == eCupheadState::Shoot_UP_L)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					PeaShot_Normal* bullet
						= object::Instantiate<PeaShot_Normal>(pos + Vector2(-30.0f, -90.0f), eLayerType::Bullet, GetCupheadState());

					bullet->SetDegree(-90.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(-40.0f, -120.0f)), eLayerType::Effect);

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
					PeaShot_Normal* bullet
						= object::Instantiate<PeaShot_Normal>(pos + Vector2(30.0f, -90.0f), eLayerType::Bullet, GetCupheadState());

					bullet->SetDegree(-90.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(20.0f, -120.0f)), eLayerType::Effect);

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

		// 점프
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

		// 사격
		if (GetCupheadState() == eCupheadState::Shoot_Run_diag_Up_L)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					PeaShot_Normal* bullet
						= object::Instantiate<PeaShot_Normal>((pos + Vector2(-60.0f, -10.0f)), eLayerType::Bullet,GetCupheadState());
					bullet->SetDegree(-135.0f);

					object::Instantiate<PeashotSpark>((pos + Vector2(-90.0f, -90.0f)), eLayerType::Effect);

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
					PeaShot_Normal* bullet
						= object::Instantiate<PeaShot_Normal>((tr->GetPos() + Vector2(60.0f, -10.0f)), eLayerType::Bullet, GetCupheadState());
					bullet->SetDegree(-45.0f);

					object::Instantiate<PeashotSpark>((tr->GetPos() + Vector2(70.0f, -90.0f)), eLayerType::Effect);

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

		// 점프
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
		GroundInit();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		// 사격
		if (GetCupheadState() == eCupheadState::Shoot_Jump_L)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					PeaShot_Normal* bullet;

					bullet = object::Instantiate<PeaShot_Normal>((pos + Vector2(-60.0f, -60.0f)), eLayerType::Bullet, GetCupheadState());
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
					mState = eCupheadState::Shoot_L;
					mAnimator->Play(L"ShootStraight_Shoot_L", true);;
					object::Instantiate<JumpDust>(pos, eLayerType::Effect);

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

				}
			}
			else if(!mbGroundCheck)
			{
				mState = eCupheadState::Jump_L;
			}
			else if (mbGroundCheck)
			{
				object::Instantiate<JumpDust>(pos, eLayerType::Effect);
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
					PeaShot_Normal* bullet
						= object::Instantiate<PeaShot_Normal>(pos + Vector2(60.0f, -60.0f), eLayerType::Bullet, GetCupheadState());

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
					mState = eCupheadState::Shoot_R;
					mAnimator->Play(L"ShootStraight_Shoot_R", true);
					object::Instantiate<JumpDust>(pos, eLayerType::Effect);

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

				}
			}
			else if (!mbGroundCheck)
			{
				mState = eCupheadState::Jump_R;
			}
			else if (mbGroundCheck)
			{
				object::Instantiate<JumpDust>(pos, eLayerType::Effect);
				mState = eCupheadState::Idle_R;
			}
		
		}

		//대시
		if (mAirDashCount > 0)
		{
			if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Shoot_Jump_L)
			{
				mAirDashCount--;

				mRigidbody->SetGround(true);
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.x -= 1000.0f;
				mRigidbody->SetVelocity(velocity);

				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				pos.x -= 50.0f;
				object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::L);

				mState = eCupheadState::Dash_Air_L;
				mAnimator->Play(L"DashAir_L", false);
			}
			else if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Shoot_Jump_R)
			{
				mAirDashCount--;

				// 수평이동을 위해
				mRigidbody->SetGround(true);
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.x += 1000.0f;
				mRigidbody->SetVelocity(velocity);

				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				pos.x += 50.0f;
				object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::R);

				mState = eCupheadState::Dash_Air_R;
				mAnimator->Play(L"DashAir_R", false);
			}
		}

		// 패리
		if (Input::GetKeyDown(eKeyCode::Z) && mParryCount > 0)
		{
			mParryCount--;

			if (mState == eCupheadState::Shoot_Jump_L)
			{
				mState = eCupheadState::Shoot_Jump_L;
				mAnimator->Play(L"ParryParry_L", false);
			}
			else if (mState == eCupheadState::Shoot_Jump_R)
			{
				mState = eCupheadState::Shoot_Jump_R;
				mAnimator->Play(L"ParryParry_R", false);
			}
		}

		tr->SetPos(pos);
	}

	void Cuphead::shoot_jump_up()
	{
		GroundInit();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		// 사격
		if (GetCupheadState() == eCupheadState::Shoot_Jump_Up_L)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					PeaShot_Normal* bullet
						= object::Instantiate<PeaShot_Normal>(pos + Vector2(-30.0f, -90.0f), eLayerType::Bullet, GetCupheadState());

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
					object::Instantiate<JumpDust>(pos, eLayerType::Effect);

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
				object::Instantiate<JumpDust>(pos, eLayerType::Effect);
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
					PeaShot_Normal* bullet
						= object::Instantiate<PeaShot_Normal>(pos + Vector2(10.0f, -90.0f), eLayerType::Bullet, GetCupheadState());

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
					object::Instantiate<JumpDust>(pos, eLayerType::Effect);

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
				object::Instantiate<JumpDust>(pos, eLayerType::Effect);

				mState = eCupheadState::Idle_R;
			}
		}

		//대시
		if (mAirDashCount > 0)
		{
			if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Shoot_Jump_Up_L)
			{
				mAirDashCount--;

				mRigidbody->SetGround(true);
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.x -= 1000.0f;
				mRigidbody->SetVelocity(velocity);

				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				pos.x -= 50.0f;
				object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::L);

				mState = eCupheadState::Dash_Air_L;
				mAnimator->Play(L"DashAir_L", false);
			}
			else if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Shoot_Jump_Up_R)
			{
				mAirDashCount--;

				// 수평이동을 위해
				mRigidbody->SetGround(true);
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.x += 1000.0f;
				mRigidbody->SetVelocity(velocity);

				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				pos.x += 50.0f;
				object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::R);

				mState = eCupheadState::Dash_Air_R;
				mAnimator->Play(L"DashAir_R", false);
			}
		}

		// 패리
		if (Input::GetKeyDown(eKeyCode::Z) && mParryCount > 0)
		{
			mParryCount--;

			if (mState == eCupheadState::Shoot_Jump_Up_L)
			{
				mState = eCupheadState::Shoot_Jump_Up_L;
				mAnimator->Play(L"ParryParry_L", false);
			}
			else if (mState == eCupheadState::Shoot_Jump_Up_R)
			{
				mState = eCupheadState::Shoot_Jump_Up_R;
				mAnimator->Play(L"ParryParry_R", false);
			}
		}
	}

	void Cuphead::shoot_jump_diag_up()
	{
		GroundInit();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		// 사격
		if (GetCupheadState() == eCupheadState::Shoot_Jump_diag_Up_L)
		{
			if (Input::GetKey(eKeyCode::X))
			{
				mSecond += Time::DeltaTime();

				if (mSecond > mFiredelay)
				{
					PeaShot_Normal* bullet
						= object::Instantiate<PeaShot_Normal>((pos + Vector2(-60.0f, 0.0f)), eLayerType::Bullet, GetCupheadState());
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
					object::Instantiate<JumpDust>(pos, eLayerType::Effect);

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
				object::Instantiate<JumpDust>(pos, eLayerType::Effect);

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
					PeaShot_Normal* bullet
						= object::Instantiate<PeaShot_Normal>((tr->GetPos() + Vector2(60.0f, 0.0f)), eLayerType::Bullet, GetCupheadState());
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
					object::Instantiate<JumpDust>(pos, eLayerType::Effect);

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
				object::Instantiate<JumpDust>(pos, eLayerType::Effect);

				mState = eCupheadState::Idle_R;
			}
		}

		// 대시
		if (mAirDashCount > 0)
		{
			if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Shoot_Jump_diag_Up_L)
			{
				mAirDashCount--;

				mRigidbody->SetGround(true);
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.x -= 1000.0f;
				mRigidbody->SetVelocity(velocity);

				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				pos.x -= 50.0f;
				object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::L);

				mState = eCupheadState::Dash_Air_L;
				mAnimator->Play(L"DashAir_L", false);
			}
			else if (Input::GetKeyDown(eKeyCode::L_SHIFT) && mState == eCupheadState::Shoot_Jump_diag_Up_R)
			{
				mAirDashCount--;

				// 수평이동을 위해
				mRigidbody->SetGround(true);
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.x += 1000.0f;
				mRigidbody->SetVelocity(velocity);

				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				pos.x += 50.0f;
				object::Instantiate<DashEffect>(pos, eLayerType::Effect, eAnimationDir::R);

				mState = eCupheadState::Dash_Air_R;
				mAnimator->Play(L"DashAir_R", false);
			}
		}
		
		// 패리
		if (Input::GetKeyDown(eKeyCode::Z) && mParryCount > 0)
		{
			mParryCount--;

			if (mState == eCupheadState::Shoot_Jump_diag_Up_L)
			{
				mState = eCupheadState::Shoot_Jump_diag_Up_L;
				mAnimator->Play(L"ParryParry_L", false);
			}
			else if (mState == eCupheadState::Shoot_Jump_diag_Up_R)
			{
				mState = eCupheadState::Shoot_Jump_diag_Up_R;
				mAnimator->Play(L"ParryParry_R", false);
			}
		}

		tr->SetPos(pos);
	}

	void Cuphead::Onhit()
	{
		if (mbInvincibile)
		{
			
			if (!mbFlashCheck)
			{
				mFlashTime += Time::DeltaTime() * 8;
			}
			else
			{
				mFlashTime -= Time::DeltaTime() * 8;
			}

			if (mFlashTime > 1)
			{
				mbFlashCheck = true;
			}
			else if (mFlashTime < 0)
			{
				mbFlashCheck = false;
			}

			mAnimator->SetMatrixChangeAlpha(mFlashTime);

			mInvincibileTime += Time::DeltaTime();

			if (mInvincibileTime > 2.0f)
			{
				mInvincibileTime = 0.0f;
				mbInvincibile = false;
				mAnimator->SetMatrixBase();
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

	void Cuphead::parryStartEvent()
	{
		mbParrying = true;
		collider->SetCenter(Vector2(-100.0f, -145.0f));
		collider->SetSize(Vector2(200.0f, 150.0f));
	}

	void Cuphead::parryCompleteEvent()
	{
		mbParrying = false;
		mbParrySuccess = false;
		collider->SetCenter(Vector2(-40.0f, -125.0f));
		collider->SetSize(Vector2(90.0f, 130.0f));

		if (mbGroundCheck)
		{
			if (mState == eCupheadState::Parry_L)
			{
				mState = eCupheadState::Idle_L;
				mAnimator->Play(L"CupheadIdle_L", true);
			}
			else if (mState == eCupheadState::Parry_R)
			{
				mState = eCupheadState::Idle_R;
				mAnimator->Play(L"CupheadIdle_R", true);
			}
		}
		else
		{
			if (mState == eCupheadState::Parry_L)
			{
				mState = eCupheadState::Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else if (mState == eCupheadState::Parry_R)
			{
				mState = eCupheadState::Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
			else if (mState == eCupheadState::Shoot_Jump_L)
			{
				mState = eCupheadState::Shoot_Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else if (mState == eCupheadState::Shoot_Jump_R)
			{
				mState = eCupheadState::Shoot_Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
			else if (mState == eCupheadState::Shoot_Jump_diag_Up_L)
			{
				mState = eCupheadState::Shoot_Jump_diag_Up_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else if (mState == eCupheadState::Shoot_Jump_diag_Up_R)
			{
				mState = eCupheadState::Shoot_Jump_diag_Up_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
			else if (mState == eCupheadState::Shoot_Jump_Up_L)
			{
				mState = eCupheadState::Shoot_Jump_Up_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else if (mState == eCupheadState::Shoot_Jump_Up_R)
			{
				mState = eCupheadState::Shoot_Jump_Up_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
		}

	}

	void Cuphead::OnhitCompleteEvent()
	{
		Vector2 velocity;
		velocity.x = 0.0f;
		mRigidbody->SetVelocity(velocity);

		if (mbGroundCheck)
		{
			if (mState == eCupheadState::OnHit_L)
			{
				mState = eCupheadState::Idle_L;
				mAnimator->Play(L"CupheadIdle_L", true);
			}
			else if (mState == eCupheadState::OnHit_R)
			{
				mState = eCupheadState::Idle_R;
				mAnimator->Play(L"CupheadIdle_R", true);
			}
		}
		else
		{
			if (mState == eCupheadState::OnHit_L)
			{
				mState = eCupheadState::Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else if (mState == eCupheadState::OnHit_R)
			{
				mState = eCupheadState::Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
			else if (mState == eCupheadState::Shoot_Jump_L)
			{
				mState = eCupheadState::Shoot_Jump_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else if (mState == eCupheadState::Shoot_Jump_R)
			{
				mState = eCupheadState::Shoot_Jump_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
			else if (mState == eCupheadState::Shoot_Jump_diag_Up_L)
			{
				mState = eCupheadState::Shoot_Jump_diag_Up_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else if (mState == eCupheadState::Shoot_Jump_diag_Up_R)
			{
				mState = eCupheadState::Shoot_Jump_diag_Up_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
			else if (mState == eCupheadState::Shoot_Jump_Up_L)
			{
				mState = eCupheadState::Shoot_Jump_Up_L;
				mAnimator->Play(L"JumpJump_L", true);
			}
			else if (mState == eCupheadState::Shoot_Jump_Up_R)
			{
				mState = eCupheadState::Shoot_Jump_Up_R;
				mAnimator->Play(L"JumpJump_R", true);
			}
		}
	}

	void Cuphead::GroundInit()
	{
		if (mbGroundCheck)
		{
			mParryCount = 1;
			mAirDashCount = 1;
		}
	}

}