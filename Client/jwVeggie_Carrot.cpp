#include "jwVeggie_Carrot.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwTime.h"
#include "jwObject.h"

#include "jwCarrot_Bomb.h"
#include "jwCarrotHypno_Beam.h"
#include "jwCarrotHypno_Eye.h"
#include "jwBossExplosion.h"
#include "jwKnockout.h"

#include "jwSound.h"


namespace jw
{
	Veggie_Carrot::Veggie_Carrot()
	{
	}
	Veggie_Carrot::Veggie_Carrot(Cuphead* cuphead)
		: mCuphead(cuphead)
	{
	}
	Veggie_Carrot::~Veggie_Carrot()
	{
	}
	void Veggie_Carrot::Initialize()
	{

		mDeathSound = Resources::Load<Sound>(L"sfx_level_knockout_boom_01", L"..\\Resources\\Sound\\BossOut\\sfx_level_knockout_boom_01.wav");
		mMindSound_start = Resources::Load<Sound>(L"sfx_level_veggies_Carrot_MindMeld_Start", L"..\\Resources\\Sound\\Veggie\\sfx_level_veggies_Carrot_MindMeld_Start.wav");;
		mMindSound_loop = Resources::Load<Sound>(L"sfx_level_veggies_Carrot_MindMeld_Loop", L"..\\Resources\\Sound\\Veggie\\sfx_level_veggies_Carrot_MindMeld_Loop.wav");;

		mbShow = false;
		mbOnHit = false;
		OnHitChecker = 0.0f;

		mCarrotHp = 30;
		mCarrotBombCnt = 4;
		mHypnoDelayCnt = 4;
		mHypnoCnt = 3;
		mAttackTimeChecker = 0.0f;

		mCarrot_bombTimer = 0.0f;
		mHypno_attackTimer = 0.0f;
		mHypno_attackCnt = 3;

		mShootTimerChecker = 0.0f;
		mDeathEffectTimer = 0.0f;
		mLeaveTimer = 0.0f;
		mbAttacking = false;
		mCarrotDead = false;
		mBossOut = false;

		mCarrotAnimator = AddComponent<Animator>();

		mCarrotAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\carrot\\intro", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		mCarrotAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\carrot\\idle", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mCarrotAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\carrot\\hypno_ready", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mCarrotAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\carrot\\hypno_ready_R", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mCarrotAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\carrot\\hypno_shoot", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);

		mCarrotAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\carrot\\death", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);

		mCarrotAnimator->GetCompleteEvent(L"carrotintro") = std::bind(&Veggie_Carrot::IntroAnimCompleteEvent, this);
		mCarrotAnimator->GetCompleteEvent(L"carrothypno_ready") = std::bind(&Veggie_Carrot::Hypno_ReadyAnimCompleteEvent, this);
		mCarrotAnimator->GetCompleteEvent(L"carrothypno_ready_R") = std::bind(&Veggie_Carrot::Hypno_Ready_RAnimCompleteEvent, this);

		
		mCarrotState = eVeggie_CarrotState::Idle;
		mCarrotAnimator->Play(L"carrotintro", true);

		mCarrotCollider = AddComponent<Collider>();
		mCarrotCollider->SetCenter(Vector2(-120.0f, -500.0f));
		mCarrotCollider->SetSize(Vector2(250.0f, 200.0f));

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.2f, 1.2f));

		GameObject::Initialize();
	}
	void Veggie_Carrot::Update()
	{
		GameObject::Update();

		mAttackTimeChecker += Time::DeltaTime();

		switch (mCarrotState)
		{
		case jw::Veggie_Carrot::eVeggie_CarrotState::Idle:
			idle();
			break;
		case jw::Veggie_Carrot::eVeggie_CarrotState::Attack1:
			attack1();
			break;
		case jw::Veggie_Carrot::eVeggie_CarrotState::Attack2:
			attack2();
			break;
		case jw::Veggie_Carrot::eVeggie_CarrotState::OnHit:
			onhit();
			break;
		case jw::Veggie_Carrot::eVeggie_CarrotState::Death:
			death();
			break;
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
				mCarrotAnimator->SetMatrixBase();
			}
		}

		if (!mbOnHit && mCarrotDead)
		{
			OnHitChecker += Time::DeltaTime();
			if (OnHitChecker > 0.05f)
			{
				OnHitChecker = 0.0f;
				mbOnHit = true;
				mCarrotAnimator->SetMatrixHitFlash();
			}
		}

	}
	void Veggie_Carrot::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void Veggie_Carrot::Release()
	{
		GameObject::Release();
	}
	void Veggie_Carrot::OnCollisionEnter(Collider* other)
	{
		if (mCarrotHp < 0 && !mCarrotDead)
		{
			if (mHypno_eye != nullptr)
			{
				object::Destroy(mHypno_eye);
				mHypno_eye = nullptr;
			}

			mCarrotDead = true;
			mCarrotState = eVeggie_CarrotState::Death;
			mCarrotAnimator->Play(L"carrotdeath", true);
			mCarrotAnimator->SetMatrixHitFlash();

			object::Instantiate<Knockout>(Vector2(800.0f, 900.0f), eLayerType::UI);
			mDeathSound->Play(false);
			mMindSound_start->Stop(true);
			mMindSound_loop->Stop(true);
		}

		mbOnHit = true;
		mCarrotHp--;
		mCarrotAnimator->SetMatrixHitFlash();
	}
	void Veggie_Carrot::OnCollisionStay(Collider* other)
	{
	}
	void Veggie_Carrot::OnCollisionExit(Collider* other)
	{
	}
	void Veggie_Carrot::idle()
	{
		if (mCarrotHp > 0 && mAttackTimeChecker > 2.0f && !mbAttacking)
		{
			mbAttacking = true;

			mCarrotState = eVeggie_CarrotState::Attack1;
		}
	}
	void Veggie_Carrot::attack1()
	{
		mCarrot_bombTimer += Time::DeltaTime();

		if (mCarrotHp > 0 && mCarrot_bombTimer > 2.0f && mCarrotBombCnt > 0)
		{
			mCarrot_bombTimer = 0.0f;

			mCarrotBombCnt--;

			if (mCarrotBombCnt % 2 == 1)
			{
				object::Instantiate<Carrot_Bomb>(Vector2(1200.0f, 100.0f), eLayerType::BossBullet, mCuphead);
			}
			else
			{
				object::Instantiate<Carrot_Bomb>(Vector2(400.0f, 100.0f), eLayerType::BossBullet, mCuphead);
			}
			
		}

		if (mCarrotHp > 0 && mCarrot_bombTimer > 2.0f && mCarrotBombCnt <= 0)
		{
			mCarrot_bombTimer = 0.0f; 
			mCarrotBombCnt = 4;

			mCarrotState = eVeggie_CarrotState::Attack2;
			mCarrotAnimator->Play(L"carrothypno_ready", false);
		}

		

	}
	void Veggie_Carrot::attack2()
	{
		mHypno_attackTimer += Time::DeltaTime();

		if (mCarrotHp > 0 && mHypno_attackTimer > 0.2f && mHypnoDelayCnt > 0)
		{
			mHypno_attackTimer = 0.0f;
			mHypnoDelayCnt--;

			

			object::Instantiate<CarrotHypno_Beam>(Vector2(800.0f, 300.0f), eLayerType::BossBullet, mCuphead);
		}
		if (mCarrotHp > 0 && mHypno_attackTimer > 3.0f && mHypnoDelayCnt <= 0)
		{
			mHypno_attackTimer = 0.0f;
			mHypnoDelayCnt = 4;
			mHypno_attackCnt--;

			if (mHypno_attackCnt <= 0)
			{
				mCarrotAnimator->Play(L"carrothypno_ready_R", true);
				object::Destroy(mHypno_eye);
				mHypno_eye = nullptr;
			}
		}

	}
	void Veggie_Carrot::onhit()
	{
	}
	void Veggie_Carrot::death()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mDeathEffectTimer += Time::DeltaTime();
		mLeaveTimer += Time::DeltaTime();

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

		if (mLeaveTimer > 5.0f)
		{
			mBossOut = true;
		}
	}
	
	void Veggie_Carrot::IntroAnimCompleteEvent()
	{
		mCarrotAnimator->Play(L"carrotidle", true);

		mMindSound_loop->Play(true);
	}

	void Veggie_Carrot::Hypno_ReadyAnimCompleteEvent()
	{
		mCarrotAnimator->Play(L"carrothypno_shoot", true);
		mHypno_eye = object::Instantiate<CarrotHypno_Eye>(Vector2(795.0f, 330.0f), eLayerType::Effect);;
	}

	void Veggie_Carrot::Hypno_Ready_RAnimCompleteEvent()
	{
		mCarrotState = eVeggie_CarrotState::Attack1;
		mCarrotAnimator->Play(L"carrotidle", true);

		mHypnoDelayCnt = 4;
		mHypnoCnt = 3;

		mMindSound_start->Play(false);
	}
	
}