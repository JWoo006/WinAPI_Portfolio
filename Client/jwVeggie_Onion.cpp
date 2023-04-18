#include "jwVeggie_Onion.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwTime.h"
#include "jwObject.h"

#include "jwOnionTears.h"
#include "jwOnionBullet.h"
#include "jwBossExplosion.h"

namespace jw
{
	Veggie_Onion::Veggie_Onion()
	{
	}
	Veggie_Onion::~Veggie_Onion()
	{
	}
	void Veggie_Onion::Initialize()
	{
		mbShow = false;
		mbOnHit = false;
		OnHitChecker = 0.0f;

		mOnionHp = 30;
		mAttackCnt = 3;
		mAttackTimeChecker = 0.0f;

		mCryReadyTimer = 0.0f;
		mCryingTimer = 0.0f;

		mShootTimerChecker = 0.0f;
		mDeathEffectTimer = 0.0f;
		mLeaveTimer = 0.0f;
		mTearsTimer = 0.0f;
		mbAttacking = false;
		mOnionDead = false;
		mBossOut = false;

		mOnionAnimator = AddComponent<Animator>();

		mOnionAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\intro", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mOnionAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\idle", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);

		mOnionAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\cry_ready", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mOnionAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\cry_start", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::R);
		mOnionAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\cry_end", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::R);
		mOnionAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\cry_attacking", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mOnionAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\death", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);

		mOnionAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\leave", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);

		mOnionAnimator->GetCompleteEvent(L"onionintro") = std::bind(&Veggie_Onion::IntroAnimCompleteEvent, this);

		mOnionAnimator->GetStartEvent(L"onioncry_start") = std::bind(&Veggie_Onion::CryStartAnimStartEvent, this);
		mOnionAnimator->GetCompleteEvent(L"onioncry_start") = std::bind(&Veggie_Onion::CryStartAnimCompleteEvent, this);

		mOnionAnimator->GetStartEvent(L"onioncry_attacking") = std::bind(&Veggie_Onion::CryingAnimStartEvent, this);
		mOnionAnimator->GetCompleteEvent(L"onioncry_attacking") = std::bind(&Veggie_Onion::CryingAnimCompleteEvent, this);

		mOnionAnimator->GetStartEvent(L"onioncry_end") = std::bind(&Veggie_Onion::CryEndAnimStartEvent, this);
		mOnionAnimator->GetCompleteEvent(L"onioncry_end") = std::bind(&Veggie_Onion::CryEndAnimCompleteEvent, this);
		mOnionAnimator->GetCompleteEvent(L"onionleave") = std::bind(&Veggie_Onion::LeaveAnimCompleteEvent, this);

		mOnionState = eVeggie_OnionState::Idle;
		mOnionAnimator->Play(L"onionintro", true);

		mOnionCollider = AddComponent<Collider>();
		mOnionCollider->SetCenter(Vector2(-250.0f, -500.0f));
		mOnionCollider->SetSize(Vector2(500.0f, 500.0f));

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.2f, 1.2f));

		GameObject::Initialize();
	}
	void Veggie_Onion::Update()
	{
		GameObject::Update();

		mAttackTimeChecker += Time::DeltaTime();

		switch (mOnionState)
		{
		case jw::Veggie_Onion::eVeggie_OnionState::Idle:
			idle();
			break;
		case jw::Veggie_Onion::eVeggie_OnionState::Attack:
			attack();
			break;
		case jw::Veggie_Onion::eVeggie_OnionState::Attacking:
			attacking();
			break;
		case jw::Veggie_Onion::eVeggie_OnionState::OnHit:
			onhit();
			break;
		case jw::Veggie_Onion::eVeggie_OnionState::Death:
			death();
			break;
		case jw::Veggie_Onion::eVeggie_OnionState::Leave:
			leave();
			break;
		default:
			break;
		}

		if (mbOnHit)
		{
			OnHitChecker += Time::DeltaTime();
			if (OnHitChecker > 0.05f)
			{
				OnHitChecker = 0.0f;
				mbOnHit = false;
				mOnionAnimator->SetMatrixBase();
			}
		}

		if (!mbOnHit && mOnionDead)
		{
			OnHitChecker += Time::DeltaTime();
			if (OnHitChecker > 0.05f)
			{
				OnHitChecker = 0.0f;
				mbOnHit = true;
				mOnionAnimator->SetMatrixHitFlash();
			}
		}

	}
	void Veggie_Onion::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void Veggie_Onion::Release()
	{
		GameObject::Release();
	}
	void Veggie_Onion::OnCollisionEnter(Collider* other)
	{
		if (mOnionHp < 0 && !mOnionDead)
		{
			mOnionDead = true;
			mOnionState = eVeggie_OnionState::Death;
			mOnionAnimator->Play(L"oniondeath", true);
			mOnionAnimator->SetMatrixHitFlash();
		}

		mbOnHit = true;
		mOnionHp--;
		mOnionAnimator->SetMatrixHitFlash();
	}
	void Veggie_Onion::OnCollisionStay(Collider* other)
	{
	}
	void Veggie_Onion::OnCollisionExit(Collider* other)
	{
	}
	void Veggie_Onion::idle()
	{
		if (mOnionHp > 0 && mAttackTimeChecker > 2.0f && !mbAttacking)
		{
			mbAttacking = true;

			mOnionState = eVeggie_OnionState::Attack;
			mOnionAnimator->Play(L"onioncry_ready", true);
		}
	}
	void Veggie_Onion::attack()
	{
		mCryReadyTimer += Time::DeltaTime();

		if (mOnionHp > 0 && mCryReadyTimer > 2.0f)
		{
			mOnionState = eVeggie_OnionState::Attacking;
			mOnionAnimator->Play(L"onioncry_start", false);
		}

	}
	void Veggie_Onion::attacking()
	{
		mCryingTimer += Time::DeltaTime();
		mTearsTimer += Time::DeltaTime();


		if (mOnionHp > 0 && mTearsTimer > 0.5f)
		{
			mTearsTimer = 0.0f;

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();

			pos.y -= 50;

			pos = Vector2::Zero;
			int a = 0;
			a = rand() % 3;

			switch (rand() % 6)
			{
			case 0:
				pos += {100, 0};
				break;
			case 1:
				pos += {300, 0};
				break;
			case 2:
				pos += {500, 0};
				break;
			case 3:
				pos += {1100, 0};
				break;
			case 4:
				pos += {1300, 0};
				break;
			case 5:
				pos += {1500, 0};
				break;
			}

			if (a)
			{
				object::Instantiate<OnionBullet>(pos, eLayerType::BossBullet, a);
			}
			else
			{
				object::Instantiate<OnionBullet>(pos, eLayerType::ParryObj, a);
			}

			
		}


		if (mOnionHp > 0 && mCryingTimer > 6.0f && mbAttacking)
		{
			mbAttacking = false;

			mOnionAnimator->Play(L"onioncry_end", false);
		}
	}
	void Veggie_Onion::onhit()
	{
	}
	void Veggie_Onion::death()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mDeathEffectTimer += Time::DeltaTime();
		mLeaveTimer += Time::DeltaTime();

		if (mOnionTearsL != nullptr && mOnionTearsR != nullptr)
		{
			object::Destroy(mOnionTearsL);
			object::Destroy(mOnionTearsR);
		}

		if (mLeaveTimer > 4.0f)
		{
			mOnionState = eVeggie_OnionState::Leave;
			mOnionAnimator->Play(L"onionleave", true);
		}

		if (mDeathEffectTimer > 0.4f + (rand() % 5))
		{
			mDeathEffectTimer = 0.0f;
			pos.y -= 50;
			switch (rand() % 6)
			{
			case 0:
				pos += {60, 120};
				break;
			case 1:
				pos += {-150, 30};
				break;
			case 2:
				pos += {100, 50};
				break;
			case 3:
				pos += {-10, 250};
				break;
			case 4:
				pos += {-70, 40};
				break;
			case 5:
				pos += {100, 200};
				break;
			}

			BossExplosion* explo = object::Instantiate<BossExplosion>(pos, eLayerType::Effect);
		}
	}
	void Veggie_Onion::leave()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		mDeathEffectTimer += Time::DeltaTime();

		if (mDeathEffectTimer > 0.4f + (rand() % 5))
		{
			mDeathEffectTimer = 0.0f;
			pos.y -= 50;
			switch (rand() % 6)
			{
			case 0:
				pos += {60, 120};
				break;
			case 1:
				pos += {-150, 30};
				break;
			case 2:
				pos += {100, 50};
				break;
			case 3:
				pos += {-10, 250};
				break;
			case 4:
				pos += {-70, 40};
				break;
			case 5:
				pos += {100, 200};
				break;
			}

			BossExplosion* explo = object::Instantiate<BossExplosion>(pos, eLayerType::Effect);
		}

	}
	void Veggie_Onion::IntroAnimCompleteEvent()
	{
		mOnionAnimator->Play(L"onionidle", true);
	}
	void Veggie_Onion::CryStartAnimStartEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (mOnionHp > 0)
		{
			mOnionTearsL = object::Instantiate<OnionTears>(Vector2(pos.x - 450.0f, pos.y - 400.0f), eLayerType::Effect, 0);
			mOnionTearsLAnimator = mOnionTearsL->GetComponent<Animator>();
			mOnionTearsR = object::Instantiate<OnionTears>(Vector2(pos.x + 400.0f, pos.y - 400.0f), eLayerType::Effect, 1);
			mOnionTearsRAnimator = mOnionTearsR->GetComponent<Animator>();
		}

	}
	void Veggie_Onion::CryStartAnimCompleteEvent()
	{
		mOnionAnimator->Play(L"onioncry_attacking", true);
	}
	void Veggie_Onion::CryingAnimStartEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
	}
	void Veggie_Onion::CryingAnimCompleteEvent()
	{
		
	}
	void Veggie_Onion::CryEndAnimStartEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mOnionTearsLAnimator->Play(L"tearsoutro_L", false);
		mOnionTearsRAnimator->Play(L"tearsoutro_R", false);
	}
	void Veggie_Onion::CryEndAnimCompleteEvent()
	{
		object::Destroy(mOnionTearsL);
		object::Destroy(mOnionTearsR);

		if (mOnionHp > 0)
		{
			mOnionState = eVeggie_OnionState::Idle;
			mOnionAnimator->Play(L"onioncry_ready", true);

			mCryingTimer = 0.0f;
			mCryReadyTimer = 0.0f;
			mAttackTimeChecker = 0.0f;
		}
	}
	void Veggie_Onion::LeaveAnimCompleteEvent()
	{
		mBossOut = true;
		object::Destroy(this);
	}
}