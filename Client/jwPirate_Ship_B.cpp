#include "jwPirate_Ship_B.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwTime.h"
#include "jwObject.h"
#include "jwRigidbody.h"

#include "jwCuphead.h"
#include "jwBossExplosion.h"
#include "jwKnockout.h"
#include "jwShip_B_jaw.h"
#include "jwShip_B_Uvula.h"
#include "jwLazar.h"

#include "jwSound.h"


namespace jw
{
	Pirate_Ship_B::Pirate_Ship_B()
	{
	}
	Pirate_Ship_B::Pirate_Ship_B(Cuphead* cuphead, int* pBossHp)
		: mCuphead(cuphead)
		, mShipHp(pBossHp)
	{
	}
	Pirate_Ship_B::~Pirate_Ship_B()
	{
	}
	void Pirate_Ship_B::Initialize()
	{
		mDeathSound = Resources::Load<Sound>(L"sfx_level_knockout_boom_01", L"..\\Resources\\Sound\\BossOut\\sfx_level_knockout_boom_01.wav");
		mBubbleShotSound = Resources::Load<Sound>(L"sfx_pirate_boat_uvula_shoot_01", L"..\\Resources\\Sound\\Pirate\\sfx_pirate_boat_uvula_shoot_01.wav");
		mLazarSound = Resources::Load<Sound>(L"sfx_pirate_boat_beam_fire", L"..\\Resources\\Sound\\Pirate\\sfx_pirate_boat_beam_fire.wav");

		mbShow = true;
		mbOnHit = false;
		OnHitChecker = 0.0f;
		mbAttacking = false;
		mBossOut = false;	

		mBubbleAtkCnt = 2;

		mShipBAnimator = AddComponent<Animator>();

		mShipBAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\idle", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mShipBAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\lazar\\charge_start", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mShipBAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\lazar\\charge_loop", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mShipBAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\lazar\\charge_end", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mShipBAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\lazar\\fire", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mShipBAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\death", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mShipBAnimator->GetCompleteEvent(L"lazarcharge_start") = std::bind(&Pirate_Ship_B::ChargeStartAnimCompleteEvent, this);
		mShipBAnimator->GetCompleteEvent(L"lazarcharge_end") = std::bind(&Pirate_Ship_B::ChargeEndAnimCompleteEvent, this);

		mShipBState = ePirate_Ship_B_State::Idle;
		mShipBAnimator->Play(L"WhaleBoat_Bidle", true);

		mShipBCollider = AddComponent<Collider>();
		mShipBCollider->SetCenter(Vector2(-80.0f, -700.0f));
		mShipBCollider->SetSize(Vector2(200.0f, 400.0f));

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.3f, 1.5f));

		Vector2 jawPos = tr->GetPos();
		mJaw = object::Instantiate<Ship_B_jaw>(Vector2(jawPos.x, jawPos.y - 180.0f), eLayerType::BG);
		//mJaw->SetShow(false);

		mUvula = object::Instantiate<Ship_B_Uvula>(Vector2(jawPos.x, jawPos.y - 400.0f), eLayerType::BG);
		mUvulaAnimator = mUvula->GetComponent<Animator>();

		GameObject::Initialize();
	}
	void Pirate_Ship_B::Update()
	{
		GameObject::Update();

		switch (mShipBState)
		{
		case jw::Pirate_Ship_B::ePirate_Ship_B_State::Intro:
			break;
		case jw::Pirate_Ship_B::ePirate_Ship_B_State::Idle:
			idle();
			break;
		case jw::Pirate_Ship_B::ePirate_Ship_B_State::Attack_Lazar:
			attack_lazar();
			break;
		case jw::Pirate_Ship_B::ePirate_Ship_B_State::Attack_Bubble:
			attack_bubble();
			break;
		case jw::Pirate_Ship_B::ePirate_Ship_B_State::OnHit:
			break;
		case jw::Pirate_Ship_B::ePirate_Ship_B_State::Death:
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
				mShipBAnimator->SetMatrixBase();
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
				mShipBAnimator->SetMatrixHitFlash();
			}
		}


	}
	void Pirate_Ship_B::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void Pirate_Ship_B::Release()
	{
		GameObject::Release();
	}
	void Pirate_Ship_B::OnCollisionEnter(Collider* other)
	{
		if (*mShipHp < 0 && !mBossDead)
		{
			mBossDead = true;
			mShipBState = ePirate_Ship_B_State::Death;
			mShipBAnimator->Play(L"WhaleBoat_Bdeath", true);
			mShipBAnimator->SetMatrixHitFlash();

			object::Instantiate<Knockout>(Vector2(800.0f, 900.0f), eLayerType::UI);
			mDeathSound->Play(false);
		}

		mbOnHit = true;
		(*mShipHp) -= 1;
		mShipBAnimator->SetMatrixHitFlash();
	}
	void Pirate_Ship_B::OnCollisionStay(Collider* other)
	{
	}
	void Pirate_Ship_B::OnCollisionExit(Collider* other)
	{
	}
	void Pirate_Ship_B::idle()
	{
		mAtkTimer += Time::DeltaTime();

		if (mAtkTimer > 3.0f && !mbAttacking)
		{
			mbAttacking = true;
			mAtkTimer = 0.0f;

			mShipBState = ePirate_Ship_B_State::Attack_Bubble;
		}
	}

	void Pirate_Ship_B::attack_lazar()
	{
		if (mbLazarFire)
		{
			mLazarAtkTimer += Time::DeltaTime();

			if (mLazarAtkTimer > 3.0f)
			{
				mLazarAtkTimer = 0.0f;

				mLazar->SetLazarAtkEnd(true);

				mShipBState = ePirate_Ship_B_State::Idle;
				mShipBAnimator->Play(L"WhaleBoat_Bidle", true);


				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();

				tr->SetPos(Vector2(pos.x, pos.y + 100.0f));

				mbAttacking = false;
				mbLazarFire = false;
				mBubbleAtkCnt = 2;
			}
		}

		if (!mbLazarFire)
		{
			mLazarAtkTimer += Time::DeltaTime();

			if (mLazarAtkTimer > 3.0f)
			{
				mLazarAtkTimer = 0.0f;

				mShipBAnimator->Play(L"lazarcharge_end", false);

				mbLazarFire = true;
			}
		}

		
	}

	void Pirate_Ship_B::attack_bubble()
	{
		mBubbleAtkTimer += Time::DeltaTime();

		if (mBubbleAtkTimer > 3.0f && mBubbleAtkCnt > 0)
		{
			mBubbleAtkTimer = 0.0f;

			mUvulaAnimator->Play(L"UvulaShoot_A", false);

			mBubbleShotSound->Play(false);

			mBubbleAtkCnt--;
		}

		if (mBubbleAtkTimer > 5.0f && mBubbleAtkCnt  <= 0)
		{
			mBubbleAtkTimer = 0.0f;
			mShipBState = ePirate_Ship_B_State::Attack_Lazar;
			mShipBAnimator->Play(L"lazarcharge_start", false);
		}

	}

	void Pirate_Ship_B::onhit()
	{
	}
	void Pirate_Ship_B::death()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mJaw->SetShow(false);

		mUvula->SetShow(false);

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

	void Pirate_Ship_B::IntroAnimCompleteEvent()
	{

	}

	void Pirate_Ship_B::ChargeStartAnimCompleteEvent()
	{
		mShipBAnimator->Play(L"lazarcharge_loop", true);
		
	}

	void Pirate_Ship_B::ChargeEndAnimCompleteEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		tr->SetPos(Vector2(pos.x, pos.y - 100.0f));

		mShipBAnimator->Play(L"lazarfire", true);
		mLazar = object::Instantiate<Lazar>(Vector2(550.0f, 750.0f), eLayerType::BossBullet);

		mLazarSound->Play(false);
	}


}