#include "jwPirate_Captain.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwTime.h"
#include "jwObject.h"
#include "jwRigidbody.h"

#include "jwCuphead.h"
#include "jwOctopus_Bullet.h"
#include "jwWhistle_Effect.h"
#include "jwWhistle_Scope.h"
#include "jwDogFish.h"
#include "jwDogFish_Splash.h"

#include "jwSound.h"

namespace jw
{
	Pirate_Captain::Pirate_Captain()
	{
	}
	Pirate_Captain::Pirate_Captain(Cuphead* cuphead, int* pBossHp)
		: mCuphead(cuphead)
		, mCaptainHp(pBossHp)
	{
	}
	Pirate_Captain::~Pirate_Captain()
	{
	}
	void Pirate_Captain::Initialize()
	{
		mIntroLaughSound = Resources::Load<Sound>(L"sfx_pirate_laugh 1", L"..\\Resources\\Sound\\Pirate\\sfx_pirate_laugh 1.wav");
		mOctopusStartSound = Resources::Load<Sound>(L"sfx_pirate_gun_start", L"..\\Resources\\Sound\\Pirate\\sfx_pirate_gun_start.wav");
		mOctopusFireSound = Resources::Load<Sound>(L"sfx_pirate_gun_shoot_01", L"..\\Resources\\Sound\\Pirate\\sfx_pirate_gun_shoot_01.wav");
		mOctopusEndSound = Resources::Load<Sound>(L"sfx_pirate_gun_end", L"..\\Resources\\Sound\\Pirate\\sfx_pirate_gun_end.wav");
		mWhistleSound = Resources::Load<Sound>(L"sfx_pirate_whistle", L"..\\Resources\\Sound\\Pirate\\sfx_pirate_whistle.wav");
		mScopeSound = Resources::Load<Sound>(L"sfx_pirate_periscope_warning", L"..\\Resources\\Sound\\Pirate\\sfx_pirate_periscope_warning.wav");
		mDogFishSound = Resources::Load<Sound>(L"sfx_pirate_dogfish_jump", L"..\\Resources\\Sound\\Pirate\\sfx_pirate_dogfish_jump.wav");

		mbShow = true;
		mbOnHit = false;
		OnHitChecker = 0.0f;
		mbAttacking = false;
		mBossOut = false;

		mOctoAtkTimer = 0.0f;
		mOctoAtkCnt = 2;
		mOctoBulletCnt = 2;

		mDogAtkCnt = 3;

		mCaptainAnimator = AddComponent<Animator>();

		mCaptainAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\idle", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mCaptainAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\intro_start", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mCaptainAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\intro_loop", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mCaptainAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\intro_end", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mCaptainAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\octopus_pick", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mCaptainAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\octopus_idle", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mCaptainAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\octopus_shoot", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mCaptainAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\octopus_down", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mCaptainAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\Whistle", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mCaptainAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\Whistle_B", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mCaptainAnimator->GetCompleteEvent(L"Captainintro_start") = std::bind(&Pirate_Captain::IntroStartAnimCompleteEvent, this);
		mCaptainAnimator->GetCompleteEvent(L"Captainintro_end") = std::bind(&Pirate_Captain::IntroEndAnimCompleteEvent, this);
		mCaptainAnimator->GetCompleteEvent(L"Captainoctopus_pick") = std::bind(&Pirate_Captain::octo_pickAnimCompleteEvent, this);
		mCaptainAnimator->GetCompleteEvent(L"Captainoctopus_shoot") = std::bind(&Pirate_Captain::octo_shootAnimCompleteEvent, this);
		mCaptainAnimator->GetCompleteEvent(L"Captainoctopus_down") = std::bind(&Pirate_Captain::octo_downAnimCompleteEvent, this);
		mCaptainAnimator->GetCompleteEvent(L"CaptainWhistle") = std::bind(&Pirate_Captain::whitsleAnimCompleteEvent, this);
		mCaptainAnimator->GetCompleteEvent(L"CaptainWhistle_B") = std::bind(&Pirate_Captain::whitsle_B_AnimCompleteEvent, this);

		mCaptainState = ePirate_Captain_State::Intro;
		mCaptainAnimator->Play(L"Captainidle", true);
		//mCaptainAnimator->Play(L"Captainintro_start", false);

		mCaptainCollider = AddComponent<Collider>();
		mCaptainCollider->SetCenter(Vector2(-150.0f, -450.0f));
		mCaptainCollider->SetSize(Vector2(400.0f, 450.0f));

		mCaptainTr = GetComponent<Transform>();
		mCaptainTr->SetScale(Vector2(1.2f, 1.2f));
		mCaptainPos = mCaptainTr->GetPos();

		GameObject::Initialize();
	}
	void Pirate_Captain::Update()
	{
		GameObject::Update();

		switch (mCaptainState)
		{
		case jw::Pirate_Captain::ePirate_Captain_State::Intro:
			intro();
			break;
		case jw::Pirate_Captain::ePirate_Captain_State::Idle:
			idle();
			break;
		case jw::Pirate_Captain::ePirate_Captain_State::Attack_Octopus:
			attack_octopus();
			break;
		case jw::Pirate_Captain::ePirate_Captain_State::Attack_Whistle:
			attack_whistle();
			break;
		case jw::Pirate_Captain::ePirate_Captain_State::OnHit:
			break;
		case jw::Pirate_Captain::ePirate_Captain_State::Death:
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
				mCaptainAnimator->SetMatrixBase();
			}
		}
		// 사망효과
		if (!mbOnHit && mBossDead)
		{
			OnHitChecker += Time::DeltaTime();
			if (OnHitChecker > 0.05f)
			{
				OnHitChecker = 0.0f;
				mbOnHit = true;
				mCaptainAnimator->SetMatrixHitFlash();
			}
		}


	}
	void Pirate_Captain::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void Pirate_Captain::Release()
	{
		GameObject::Release();
	}
	void Pirate_Captain::OnCollisionEnter(Collider* other)
	{
		if (*mCaptainHp < 0 && !mBossDead)
		{
			mBossDead = true;
			mCaptainState = ePirate_Captain_State::Death;
			//mCaptainAnimator->Play(L"morphstart", false);
		}

		mbOnHit = true;
		(*mCaptainHp) -= 1;
		mCaptainAnimator->SetMatrixHitFlash();

	}
	void Pirate_Captain::OnCollisionStay(Collider* other)
	{
	}
	void Pirate_Captain::OnCollisionExit(Collider* other)
	{
	}
	void Pirate_Captain::intro()
	{
		mAtkTimer += Time::DeltaTime();

		if (mAtkTimer > 5.0f)
		{
			mAtkTimer = 0.0f;

			mCaptainState = ePirate_Captain_State::Idle;
			mCaptainAnimator->Play(L"Captainintro_end", false);
		}
	}
	void Pirate_Captain::idle()
	{
		mAtkTimer += Time::DeltaTime();

		if (mAtkTimer > 3.0f && !mbAttacking && *mCaptainHp > 0 && *mCaptainHp > 100)
		{
			mbAttacking = true;	
		    mCaptainTr->SetPos(Vector2(mCaptainPos.x + 100.0f, mCaptainPos.y));
			mCaptainAnimator->Play(L"Captainoctopus_pick", false);

			mOctopusStartSound->Play(false);
		}

		if (mAtkTimer > 3.0f && !mbAttacking && *mCaptainHp > 0 && *mCaptainHp < 100 )
		{
			mbAttacking = true;

			mCaptainAnimator->Play(L"CaptainWhistle", false);

		}
	}
	void Pirate_Captain::attack()
	{
	}

	void Pirate_Captain::attack_octopus()
	{
		if (mOctoAtkCnt > 0)
		{
			if (!mbOctoFire)
			{
				mOctoAtkTimer += Time::DeltaTime();

				if (mOctoAtkTimer > 1.0f && mOctoBulletCnt > 0)
				{
					mOctoAtkTimer = 0.0f;

					//총알 발사
					mCaptainAnimator->Play(L"Captainoctopus_shoot", false);

					mbOctoFire = true;
					
				}
			}

			

			if (mOctoBulletCnt == 0)
			{
				mAtkTimer += Time::DeltaTime();

				if (mAtkTimer > 3.0f)
				{
					mAtkTimer = 0.0;
					mOctoBulletCnt = 2;
					mOctoAtkCnt--;
				}

				
			}
		}

		if (!mbOctoAtkEnd && mOctoAtkCnt == 0)
		{
			mbOctoAtkEnd = true;
			mCaptainAnimator->Play(L"Captainoctopus_down", false);

			mOctopusEndSound->Play(false);
		}
	}

	void Pirate_Captain::attack_whistle()
	{
		if (!mbScopeOut)
		{
			mScopeTimer += Time::DeltaTime();

			if (mScopeTimer > 5.0f)
			{
				mbScopeOut = true;
				
			}

			
		}

		mDogAtkTimer += Time::DeltaTime();

		if (mbScopeOut && mDogAtkTimer > 2.0f && mDogAtkCnt > 0)
		{
			mDogAtkTimer = 0.0f;

			mDogFishSound->Play(false);

			object::Instantiate<DogFish>(Vector2(1200.0f, 900.0f), eLayerType::Effect);
			object::Instantiate<DogFish_Splash>(Vector2(1200.0f, 900.0f), eLayerType::Effect);

			mDogAtkCnt--;
		}

		if (mDogAtkCnt == 0)
		{
			mCaptainState = ePirate_Captain_State::Idle;
			mCaptainAnimator->Play(L"Captainidle", true);

			mDogAtkCnt = 3;
			mDogAtkTimer = 0.0f;
			mbScopeOut = false;
			mbAttacking = false;
		}
		
	}

	void Pirate_Captain::onhit()
	{
	}
	void Pirate_Captain::death()
	{

	}

	void Pirate_Captain::IntroStartAnimCompleteEvent()
	{
		mCaptainAnimator->Play(L"Captainintro_loop", true);

		mIntroLaughSound->Play(true);
	}

	void Pirate_Captain::IntroEndAnimCompleteEvent()
	{
		mCaptainAnimator->Play(L"Captainidle", true);	

		mIntroLaughSound->Stop(true);
	}

	void Pirate_Captain::octo_pickAnimCompleteEvent()
	{
		mAtkTimer = 0.0;
		
		mCaptainState = ePirate_Captain_State::Attack_Octopus;
		mCaptainAnimator->Play(L"Captainoctopus_idle", true);
		
	}

	void Pirate_Captain::octo_shootAnimCompleteEvent()
	{
		//총알 발사
		mCaptainAnimator->Play(L"Captainoctopus_idle", true);

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mOctopusFireSound->Play(false);

		object::Instantiate<Octopus_Bullet>(Vector2(pos.x - 100.0f , pos.y - 100.0f), eLayerType::BossBullet, mCuphead);
		mbOctoFire = false;
		mOctoBulletCnt--;
	}

	void Pirate_Captain::octo_downAnimCompleteEvent()
	{
		mCaptainState = ePirate_Captain_State::Idle;
		mCaptainAnimator->Play(L"Captainidle", true);

		mOctoBulletCnt = 2;
		mOctoAtkCnt = 2;
		mbAttacking = false;
		mbOctoAtkEnd = false;
		//mCaptainTr->SetPos(Vector2(mCaptainPos.x, mCaptainPos.y));
		
	}

	void Pirate_Captain::whitsleAnimCompleteEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		object::Instantiate<Whistle_Effect>(Vector2(pos.x - 200.0f, pos.y - 300.0f), eLayerType::Effect);

		mWhistleSound->Play(false);

		mCaptainAnimator->Play(L"CaptainWhistle_B", false);
	}

	void Pirate_Captain::whitsle_B_AnimCompleteEvent()
	{
		mAtkTimer = 0.0;

		mCaptainState = ePirate_Captain_State::Attack_Whistle;
		object::Instantiate<Whistle_Scope>(Vector2(1400.0f, 900.0f), eLayerType::Effect);
		mCaptainAnimator->Play(L"Captainidle", true);

		//스코프 사운드
		mScopeSound->Play(false);
	}


}