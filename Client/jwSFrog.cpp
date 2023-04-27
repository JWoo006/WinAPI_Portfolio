#include "jwSFrog.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwRigidbody.h"
#include "jwTime.h"
#include "jwObject.h"

#include "jwTestPlayScene.h"
#include "jwCuphead.h"

#include "jwBossExplosion.h"
#include "jwSFrog_Fistobj.h"

namespace jw
{
	SFrog::SFrog()
	{
	}
	SFrog::SFrog(Cuphead* cuphead, int* pBossHp)
		: mCuphead(cuphead)
		, mSFrogHp(pBossHp)
	{
	}
	SFrog::~SFrog()
	{
	}
	void SFrog::Initialize()
	{
		mbShow = true;
		mbOnHit = false;
		OnHitChecker = 0.0f;
		mbFistOn = false;
		mbFireFlyOn = false;
		mbRollOn = false;
		

		mFistAtkCnt = 1;
		mClapAtkCnt = 3;

		mAtakTimer = 0.0f;
		mFistAtkTimer = 0.0f;
		mClapAtkTimer = 0.0f;

		mbAttacking = false;
		mSFrogDead = false;
		mBossOut = false;
		

		mSFrogAnimator = AddComponent<Animator>();

		mSFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\intro", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mSFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\idleL", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::L);
		mSFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\idle", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		
		mSFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fist\\fist_ready1", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		mSFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fist\\fist_ready2", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		mSFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fist\\fist_loop", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		mSFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fist\\fist_end", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mSFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fan\\roll", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		mSFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fan\\rolling", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		mSFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fan\\rollend", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::L);
		mSFrogAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fan\\clap", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::L);


		mSFrogAnimator->GetCompleteEvent(L"SFrogintro") = std::bind(&SFrog::IntroAnimCompleteEvent, this);
		mSFrogAnimator->GetCompleteEvent(L"fistfist_ready1") = std::bind(&SFrog::FistReady1AnimCompleteEvent, this);
		mSFrogAnimator->GetCompleteEvent(L"fistfist_ready2") = std::bind(&SFrog::FistReady2AnimCompleteEvent, this);
		mSFrogAnimator->GetCompleteEvent(L"fistfist_end") = std::bind(&SFrog::FistEndAnimCompleteEvent, this);
		mSFrogAnimator->GetCompleteEvent(L"fanroll") = std::bind(&SFrog::RollAnimCompleteEvent, this);
		mSFrogAnimator->GetCompleteEvent(L"fanrollend") = std::bind(&SFrog::RollEndAnimCompleteEvent, this);
		mSFrogAnimator->GetCompleteEvent(L"fanclap") = std::bind(&SFrog::ClapBEndAnimCompleteEvent, this);

		mSFrogState = eSFrogState::Intro;
		mSFrogAnimator->Play(L"SFrogidle", true);

		mSFrogCollider = AddComponent<Collider>();
		mSFrogCollider->SetCenter(Vector2(-80.0f, -300.0f));
		mSFrogCollider->SetSize(Vector2(200.0f, 300.0f));

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.2f, 1.2f));

		GameObject::Initialize();
	}
	void SFrog::Update()
	{
		GameObject::Update();

		switch (mSFrogState)
		{
		case jw::SFrog::eSFrogState::Idle:
			idle();
			break;
		case jw::SFrog::eSFrogState::Roll:
			roll();
			break;
		case jw::SFrog::eSFrogState::Attack_Fist:
			attack_fist();
			break;
		case jw::SFrog::eSFrogState::Attack_Clap:
			attack_clap();
			break;
		case jw::SFrog::eSFrogState::OnHit:
			onhit();
			break;
		case jw::SFrog::eSFrogState::Death:
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
				mSFrogAnimator->SetMatrixBase();
			}
		}
		// 사망시 피격효과
		if (!mbOnHit && mSFrogDead)
		{
			OnHitChecker += Time::DeltaTime();
			if (OnHitChecker > 0.05f)
			{
				OnHitChecker = 0.0f;
				mbOnHit = true;
				mSFrogAnimator->SetMatrixHitFlash();
			}
		}

	}
	void SFrog::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void SFrog::Release()
	{
		GameObject::Release();
	}
	void SFrog::OnCollisionEnter(Collider* other)
	{
		if (*mSFrogHp < 0 && !mSFrogDead)
		{
			mSFrogDead = true;
			mSFrogState = eSFrogState::Death;
			//mSFrogAnimator->Play(L"SFrogdeath", true);
			mSFrogAnimator->SetMatrixHitFlash();
		}

		mbOnHit = true;
		(*mSFrogHp) -= 1;
		mSFrogAnimator->SetMatrixHitFlash();
	}
	void SFrog::OnCollisionStay(Collider* other)
	{
	}
	void SFrog::OnCollisionExit(Collider* other)
	{
	}
	void SFrog::idle()
	{
		mAtakTimer += Time::DeltaTime();

		if (*mSFrogHp > 0 && !mbAttacking && mAtakTimer > 2.0f && mbFistOn)
		{
			mAtakTimer = 0.0f;
			mbAttacking = true;
			mbFistOn = false;
			mSFrogState = eSFrogState::Attack_Fist;
			mSFrogAnimator->Play(L"fistfist_ready1", false);
		}

		if (*mSFrogHp > 0 && !mbAttacking && mAtakTimer > 2.0f && mbRollOn)
		{
			mAtakTimer = 0.0f;
			mbAttacking = true;
			mbRollOn = false;
			mSFrogState = eSFrogState::Roll;
			mSFrogAnimator->Play(L"fanroll", false);
		}
	}
	void SFrog::roll()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetScale(Vector2(1.f, 1.f));
		mSFrogCollider->SetCenter(Vector2(-280.0f, -150.0f));
		mSFrogCollider->SetSize(Vector2(200.0f, 150.0f));

		if (pos.x >= -200)
		{
			pos.x -= 400.0f * Time::DeltaTime();
		}
		else
		{
			mSFrogCollider->SetCenter(Vector2(-80.0f, -300.0f));
			mSFrogCollider->SetSize(Vector2(200.0f, 300.0f));

			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vector2(1.2f, 1.2f));
			pos.x = 100.0f;
			tr->SetPos(pos);
			mSFrogState = eSFrogState::Attack_Clap;
			mSFrogAnimator->Play(L"fanrollend", false);
		}
		tr->SetPos(pos);
	
	}
	void SFrog::attack_fist()
	{
		mFistAtkTimer += Time::DeltaTime();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		switch (mFistAtkCnt)
		{
		case 9:
			pos.y = 600.0f;
			break;
		case 8:
			pos.y = 700.0f;
			break;
		case 7:
			pos.y = 800.0f;
			break;
		case 6:
			pos.y = 700.0f;
			break;
		case 5:
			pos.y = 600.0f;
			break;
		case 4:
			pos.y = 700.0f;
			break;
		case 3:
			pos.y = 800.0f;
			break;
		case 2:
			pos.y = 700.0f;
			break;
		case 1:
			pos.y = 600.0f;
			break;
		default:
			break;
		}

		if (mFistAtkTimer > 1.5f && mFistAtkCnt % 3 == 0 && mFistAtkCnt > 0)
		{
			mFistAtkTimer = 0.0f;
			object::Instantiate<SFrog_Fistobj>(Vector2(pos), eLayerType::ParryObj, mFistAtkCnt);

			mFistAtkCnt--;
		}
		else if (mFistAtkTimer > 1.5f &&  mFistAtkCnt > 0)
		{
			mFistAtkTimer = 0.0f;
			object::Instantiate<SFrog_Fistobj>(Vector2(pos), eLayerType::BossBullet, mFistAtkCnt);

			mFistAtkCnt--;
		}
		else if (mFistAtkTimer > 1.5f && mFistAtkCnt <= 0)
		{
			mFistAtkTimer = 0.0f;
			mFistAtkCnt = 9;

			mbAttacking = false;
			mSFrogState = eSFrogState::Idle;
			mSFrogAnimator->Play(L"fistfist_end", false);
		}

		
	}
	void SFrog::attack_clap()
	{
		mClapAtkTimer += Time::DeltaTime();

		if (mClapAtkTimer > 1.5f)
		{
			mClapAtkTimer = 0.0f;

			mSFrogAnimator->Play(L"fanclap", false);
		}
	}
	void SFrog::onhit()
	{
	}
	void SFrog::death()
	{
		
	}

	void SFrog::IntroAnimCompleteEvent()
	{
		mSFrogAnimator->Play(L"SFrogidle", true);
		mSFrogState = eSFrogState::Idle;
	}

	void SFrog::FistReady1AnimCompleteEvent()
	{
		mSFrogAnimator->Play(L"fistfist_ready2", false);
	}

	void SFrog::FistReady2AnimCompleteEvent()
	{
		mSFrogAnimator->Play(L"fistfist_loop", true);
	}

	void SFrog::FistEndAnimCompleteEvent()
	{
		mSFrogAnimator->Play(L"SFrogidle", true);
		mbFireFlyOn = true;
	}

	void SFrog::RollAnimCompleteEvent()
	{
		mSFrogAnimator->Play(L"fanrolling", true);
	}

	void SFrog::RollEndAnimCompleteEvent()
	{
		mSFrogAnimator->Play(L"SFrogidleL", true);
	}

	void SFrog::ClapAEndAnimCompleteEvent()
	{
	}

	void SFrog::ClapBEndAnimCompleteEvent()
	{
		mSFrogAnimator->Play(L"SFrogidleL", true);
	}

}