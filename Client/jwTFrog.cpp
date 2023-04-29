#include "jwTFrog.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwTime.h"
#include "jwObject.h"
#include "jwRigidbody.h"

#include "jwTestPlayScene.h"
#include "jwCuphead.h"

#include "jwBossExplosion.h"
#include "jwTFrog_Firefly.h"
#include "jwTFrog_FanWind.h"

namespace jw
{
	TFrog::TFrog()
	{
	}
	TFrog::TFrog(Cuphead* cuphead, int* pBossHp)
		: mCuphead(cuphead)
		, mTFrogHp(pBossHp)
	{
	}
	TFrog::~TFrog()
	{
	}
	void TFrog::Initialize()
	{
		mbShow = true;
		mbOnHit = false;
		mbFistOn = false;
		mbFireFlyOn = false;
		OnHitChecker = 0.0f;
		
		mFireflyAtkCnt = 3;

		mFireFlyAtkTimer = 0.0f;
		mFanAtkTimer = 0.0f;

		mbAttacking = false;
		mTFrogDead = false;
		mBossOut = false;
		mbFanAttacking = false;

		mTFrogAnimator = AddComponent<Animator>();

		mTFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\intro", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mTFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\idle", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mTFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\firefly\\spit", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mTFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\fan\\start", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		mTFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\fan\\loop", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		mTFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\fan\\end", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mTFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\morph\\start", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		mTFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\morph\\loop", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		mTFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\morph\\end", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mTFrogAnimator->GetCompleteEvent(L"TFrogintro") = std::bind(&TFrog::IntroAnimCompleteEvent, this);
		mTFrogAnimator->GetCompleteEvent(L"fireflyspit") = std::bind(&TFrog::SpitAnimCompleteEvent, this);
		mTFrogAnimator->GetCompleteEvent(L"fanstart") = std::bind(&TFrog::FanStartAnimCompleteEvent, this);
		mTFrogAnimator->GetCompleteEvent(L"fanend") = std::bind(&TFrog::FanEndAnimCompleteEvent, this);
		mTFrogAnimator->GetCompleteEvent(L"morphstart") = std::bind(&TFrog::MorphStartAnimCompleteEvent, this);
		mTFrogAnimator->GetCompleteEvent(L"morphend") = std::bind(&TFrog::MorphEndAnimCompleteEvent, this);

		mTFrogState = eTFrogState::Idle;
		mTFrogAnimator->Play(L"TFrogidle", true);

		mTFrogCollider = AddComponent<Collider>();
		mTFrogCollider->SetCenter(Vector2(-80.0f, -600.0f));
		mTFrogCollider->SetSize(Vector2(200.0f, 600.0f));

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.2f, 1.2f));

		GameObject::Initialize();
	}
	void TFrog::Update()
	{
		GameObject::Update();

		switch (mTFrogState)
		{
		case jw::TFrog::eTFrogState::Idle:
			idle();
			break;
		case jw::TFrog::eTFrogState::Attack_Firefly:
			attack_firefly();
			break;
		case jw::TFrog::eTFrogState::Attack_Fan:
			attack_fan();
			break;
		case jw::TFrog::eTFrogState::OnHit:
			onhit();
			break;
		case jw::TFrog::eTFrogState::Death:
			death();
			break;
		default:
			break;
		}

		// 피격효과
		if (mbOnHit)
		{
			OnHitChecker += Time::DeltaTime();
			if (OnHitChecker > 0.05f)
			{
				OnHitChecker = 0.0f;
				mbOnHit = false;
				mTFrogAnimator->SetMatrixBase();
			}
		}
		

	}
	void TFrog::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void TFrog::Release()
	{
		GameObject::Release();
	}
	void TFrog::OnCollisionEnter(Collider* other)
	{
		if (*mTFrogHp < 0 && !mTFrogDead)
		{
			mTFrogDead = true;
			mTFrogState = eTFrogState::Death;
			mTFrogAnimator->Play(L"morphstart", false);
		}

		mbOnHit = true;
		(*mTFrogHp) -= 1;
		mTFrogAnimator->SetMatrixHitFlash();

		if (other->GetOwner()->GetLayerType() == eLayerType::Monster && *mTFrogHp < 0 && mTFrogDead)
		{
			mTFrogDead = false;
			mTFrogAnimator->Play(L"morphend", false);
		}

	}
	void TFrog::OnCollisionStay(Collider* other)
	{
	}
	void TFrog::OnCollisionExit(Collider* other)
	{
	}
	void TFrog::idle()
	{
		mAtkTimer += Time::DeltaTime();

		if (*mTFrogHp >0 && mbFireFlyOn)
		{
			mTFrogState = eTFrogState::Attack_Firefly;
			mbFireFlyOn = false;
		}

		if (*mTFrogHp > 0 && mbFanOn && mAtkTimer > 3.0f)
		{
			mAtkTimer = 0.0f;
			mTFrogState = eTFrogState::Attack_Fan;
			mTFrogAnimator->Play(L"fanstart", false);
			mbFanOn = false;
		}
	}
	void TFrog::attack_firefly()
	{
		mFireFlyAtkTimer += Time::DeltaTime();

		if (mFireFlyAtkTimer > 3.0f && mFireflyAtkCnt > 0 && !mbAttacking)
		{
			mbAttacking = true;
			mTFrogAnimator->Play(L"fireflyspit", false);			
		}
		else if (mFireFlyAtkTimer > 3.0f && mFireflyAtkCnt <= 0)
		{
			mbRollOn = true;
			mbAttacking = false;			
			mTFrogState = eTFrogState::Idle;
		}
	}
	void TFrog::attack_fan()
	{
		Rigidbody* rb = mCuphead->GetComponent<Rigidbody>();
		Vector2 velocity = rb->GetVelocity();
		velocity.x = -150.0f;
		rb->SetVelocity(velocity);

		mFanAtkTimer += Time::DeltaTime();

		if (mFanAtkTimer > 5.0f && mbFanAttacking)
		{
			mFanAtkTimer = 0.0f;
			mbFanAttacking = false;
			mTFrogAnimator->Play(L"fanend", false);
			mTFrogState = eTFrogState::Idle;

		}
	}
	void TFrog::onhit()
	{
	}
	void TFrog::death()
	{
		if (mTFrog_FanWind)
		{
			object::Destroy(mTFrog_FanWind);
			mTFrog_FanWind = nullptr;
		}
	}

	void TFrog::IntroAnimCompleteEvent()
	{
		mTFrogAnimator->Play(L"TFrogidle", true);
	}

	void TFrog::SpitAnimCompleteEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mFireFlyAtkTimer = 0.0f;
		object::Instantiate<TFrog_Firefly>(Vector2(pos.x, pos.y - 500.0f), eLayerType::BossBullet, mCuphead, Vector2(300.0f, 200.0f));
		object::Instantiate<TFrog_Firefly>(Vector2(pos.x, pos.y - 500.0f), eLayerType::BossBullet, mCuphead, Vector2(900.0f, 200.0f));
		mFireflyAtkCnt--;
		mbAttacking = false;
		mTFrogAnimator->Play(L"TFrogidle", true);
	}

	void TFrog::FanStartAnimCompleteEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mbFanAttacking = true;

		mTFrogAnimator->Play(L"fanloop", true);
		mTFrog_FanWind = object::Instantiate<TFrog_FanWind>(Vector2(pos.x - 500.0f, pos.y - 200.0f), eLayerType::Effect);
	
	}

	void TFrog::FanEndAnimCompleteEvent()
	{
		mTFrogAnimator->Play(L"TFrogidle", true);

		if (mTFrog_FanWind)
		{
			object::Destroy(mTFrog_FanWind);
			mTFrog_FanWind = nullptr;
		}
		
		mbFanOn = true;

		Rigidbody* rb = mCuphead->GetComponent<Rigidbody>();
		Vector2 velocity = rb->GetVelocity();
		velocity.x = 0.0f;
		rb->SetVelocity(velocity);
	}

	void TFrog::MorphStartAnimCompleteEvent()
	{
		mTFrogAnimator->Play(L"morphloop", true);

		Rigidbody* rb = mCuphead->GetComponent<Rigidbody>();
		Vector2 velocity = rb->GetVelocity();
		velocity.x = 0.0f;
		rb->SetVelocity(velocity);
	}

	void TFrog::MorphEndAnimCompleteEvent()
	{
		mBossOut = true;
	}

}