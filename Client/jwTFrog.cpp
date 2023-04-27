#include "jwTFrog.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwTime.h"
#include "jwObject.h"

#include "jwTestPlayScene.h"
#include "jwCuphead.h"

#include "jwBossExplosion.h"
#include "jwTFrog_Firefly.h"

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

		
		mFireflyAtkCnt = 1;


		mFireFlyAtkTimer = 0.0f;

		mbAttacking = false;
		mTFrogDead = false;
		mBossOut = false;

		mTFrogAnimator = AddComponent<Animator>();

		mTFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\intro", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mTFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\idle", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mTFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\firefly\\spit", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mTFrogAnimator->GetCompleteEvent(L"TFrogintro") = std::bind(&TFrog::IntroAnimCompleteEvent, this);
		mTFrogAnimator->GetCompleteEvent(L"fireflyspit") = std::bind(&TFrog::SpitAnimCompleteEvent, this);

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
		// 사망시 피격효과
		if (!mbOnHit && mTFrogDead)
		{
			OnHitChecker += Time::DeltaTime();
			if (OnHitChecker > 0.05f)
			{
				OnHitChecker = 0.0f;
				mbOnHit = true;
				mTFrogAnimator->SetMatrixHitFlash();
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
			//mTFrogAnimator->Play(L"TFrogdeath", true);
			mTFrogAnimator->SetMatrixHitFlash();
		}

		mbOnHit = true;
		(*mTFrogHp) -= 1;
		mTFrogAnimator->SetMatrixHitFlash();
	}
	void TFrog::OnCollisionStay(Collider* other)
	{
	}
	void TFrog::OnCollisionExit(Collider* other)
	{
	}
	void TFrog::idle()
	{
		if (*mTFrogHp >0 && mbFireFlyOn)
		{
			mTFrogState = eTFrogState::Attack_Firefly;
			mbFireFlyOn = false;
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
			//mTFrogAnimator->Play(L"TFrogidle", true);
		}
	}
	void TFrog::attack_fan()
	{

	}
	void TFrog::onhit()
	{
	}
	void TFrog::death()
	{

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

}