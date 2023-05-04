#include "jwTFrog_Slot.h"
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
#include "jwSlot_Spit.h"
#include "jwSlot_Pic.h"
#include "jwSlot_CoinBullet.h"
#include "jwSlot_LeverParry.h"
#include "jwSlot_Snake.h"
#include "jwSlot_Fire.h"
#include "jwKnockout.h"

#include "jwSound.h"


namespace jw
{
	TFrog_Slot::TFrog_Slot()
	{
	}
	TFrog_Slot::TFrog_Slot(Cuphead* cuphead, int* pBossHp)
		: mCuphead(cuphead)
		, mTFrog_SlotHp(pBossHp)
	{
	}
	TFrog_Slot::~TFrog_Slot()
	{
	}
	void TFrog_Slot::Initialize()
	{
		mDeathSound = Resources::Load<Sound>(L"sfx_level_knockout_boom_01", L"..\\Resources\\Sound\\BossOut\\sfx_level_knockout_boom_01.wav");
		mSpitSound = Resources::Load<Sound>(L"sfx_frogs_morphed_mouth_01", L"..\\Resources\\Sound\\Frog\\sfx_frogs_morphed_mouth_01.wav");
		mLeverDownSound = Resources::Load<Sound>(L"sfx_frogs_morphed_arm_down_01", L"..\\Resources\\Sound\\Frog\\sfx_frogs_morphed_arm_down_01.wav");
		mSlotRollSound = Resources::Load<Sound>(L"sfx_level_frogs_morphed_dial_spin_loop_01", L"..\\Resources\\Sound\\Frog\\sfx_level_frogs_morphed_dial_spin_loop_01.wav");
		mSlotRollEndSound = Resources::Load<Sound>(L"sfx_frogs_morphed_spin_01", L"..\\Resources\\Sound\\Frog\\sfx_frogs_morphed_spin_01.wav");
		mPlatformSound = Resources::Load<Sound>(L"sfx_level_frogs_platform_loop_01", L"..\\Resources\\Sound\\Frog\\sfx_level_frogs_platform_loop_01.wav");

		mbShow = true;
		mbOnHit = false;
		OnHitChecker = 0.0f;

		mbAttacking = false;
		mTFrog_SlotDead = false;
		mBossOut = false;


		mSnakeAtkTimer = 0.0f;
		mSnakeAtkCnt = 15;
		mFireAtkTimer = 0.0f;
		mFireAtkCnt = 10;
		mbLeverOn = false;
		mbSnakeOn = true;
		mbFireOn = false;

		mTFrog_SlotAnimator = AddComponent<Animator>();

		mTFrog_SlotAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\intro", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mTFrog_SlotAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\idle", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mTFrog_SlotAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\leverstart", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		mTFrog_SlotAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\leverloop", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		mTFrog_SlotAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\leverback", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mTFrog_SlotAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\attack_start", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		mTFrog_SlotAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\attackloop", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mTFrog_SlotAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\death", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mTFrog_SlotAnimator->GetCompleteEvent(L"slotintro") = std::bind(&TFrog_Slot::IntroAnimCompleteEvent, this);
		mTFrog_SlotAnimator->GetCompleteEvent(L"slotleverstart") = std::bind(&TFrog_Slot::LeverStartAnimCompleteEvent, this);
		mTFrog_SlotAnimator->GetCompleteEvent(L"slotleverback") = std::bind(&TFrog_Slot::LeverBackAnimCompleteEvent, this);
		mTFrog_SlotAnimator->GetCompleteEvent(L"slotattack_start") = std::bind(&TFrog_Slot::AttackStartAnimCompleteEvent, this);

		mTFrog_SlotState = eTFrog_SlotState::Intro;
		mTFrog_SlotAnimator->Play(L"slotintro", true);

		mTFrog_SlotCollider = AddComponent<Collider>();
		mTFrog_SlotCollider->SetCenter(Vector2(-280.0f, -600.0f));
		mTFrog_SlotCollider->SetSize(Vector2(400.0f, 600.0f));

		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector2(1.2f, 1.2f));
		mPos = mTransform->GetPos();

		mSlot_Pic1 = object::Instantiate<Slot_Pic>(Vector2(mPos.x - 182.0f, mPos.y - 440.0f), eLayerType::Tile);
		mSlot_Pic2 = object::Instantiate<Slot_Pic>(Vector2(mPos.x - 120.0f, mPos.y - 440.0f), eLayerType::Tile);
	    mSlot_Pic3 = object::Instantiate<Slot_Pic>(Vector2(mPos.x - 50.0f, mPos.y - 440.0f), eLayerType::Tile);

		

		GameObject::Initialize();
	}
	void TFrog_Slot::Update()
	{
		GameObject::Update();

		switch (mTFrog_SlotState)
		{
		case jw::TFrog_Slot::eTFrog_SlotState::Intro:
			break;
		case jw::TFrog_Slot::eTFrog_SlotState::Idle:
			idle();
			break;
		case jw::TFrog_Slot::eTFrog_SlotState::Slotlever:
			slotlever();
			break;
		case jw::TFrog_Slot::eTFrog_SlotState::SlotRoll:
			slotroll();
			break;
		case jw::TFrog_Slot::eTFrog_SlotState::Attack_Coin:
			attack_coin();
			break;
		case jw::TFrog_Slot::eTFrog_SlotState::Attack_Snake:
			attack_snake();
			break;
		case jw::TFrog_Slot::eTFrog_SlotState::Attack_Fire:
			attack_fire();
			break;
		case jw::TFrog_Slot::eTFrog_SlotState::OnHit:
			onhit();
			break;
		case jw::TFrog_Slot::eTFrog_SlotState::Death:
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
				mTFrog_SlotAnimator->SetMatrixBase();
			}
		}
		// 사망효과
		if (!mbOnHit && mTFrog_SlotDead)
		{
			OnHitChecker += Time::DeltaTime();
			if (OnHitChecker > 0.05f)
			{
				OnHitChecker = 0.0f;
				mbOnHit = true;
				mTFrog_SlotAnimator->SetMatrixHitFlash();
			}
		}


	}
	void TFrog_Slot::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void TFrog_Slot::Release()
	{
		GameObject::Release();
	}
	void TFrog_Slot::OnCollisionEnter(Collider* other)
	{
		if (*mTFrog_SlotHp < 0 && !mTFrog_SlotDead)
		{
			mTFrog_SlotDead = true;
			mTFrog_SlotState = eTFrog_SlotState::Death;
			mTFrog_SlotAnimator->Play(L"slotdeath", true);
			mTFrog_SlotAnimator->SetMatrixHitFlash();

			object::Instantiate<Knockout>(Vector2(800.0f, 900.0f), eLayerType::UI);
			mDeathSound->Play(false);
			mPlatformSound->Stop(true);
		}

		mbOnHit = true;
		(*mTFrog_SlotHp) -= 1;
		mTFrog_SlotAnimator->SetMatrixHitFlash();

		

	}
	void TFrog_Slot::OnCollisionStay(Collider* other)
	{
	}
	void TFrog_Slot::OnCollisionExit(Collider* other)
	{
	}
	void TFrog_Slot::idle()
	{
		mAtkTimer += Time::DeltaTime();

		if (mAtkTimer > 2.0f)
		{
			mAtkTimer = 0.0f;
			mTFrog_SlotState = eTFrog_SlotState::Attack_Coin;
			mTFrog_SlotAnimator->Play(L"slotleverstart", false);	

			mLeverDownSound->Play(false);
		}

		
	}
	void TFrog_Slot::slotlever()
	{
		

	}
	void TFrog_Slot::slotroll()
	{
		mRollTimer += Time::DeltaTime();

		if (mPos.x <= 1395.0f)
		{
			mPos.x += 200.0f * Time::DeltaTime();
			mTransform->SetPos(mPos);
		}

		if (mRollTimer > 3.0f)
		{
			if (mbSnakeOn && mbLeverParryOn)
			{
				mSPic1_Pos.y = 360.0f;
				mSPic2_Pos.y = 360.0f;
				mSPic3_Pos.y = 360.0f;

				mSPic1_Tr->SetPos(mSPic1_Pos);
				mSPic2_Tr->SetPos(mSPic2_Pos);
				mSPic3_Tr->SetPos(mSPic3_Pos);

				if (mRollTimer > 5.0f)
				{
					mRollTimer = 0.0f;
					mTFrog_SlotState = eTFrog_SlotState::Attack_Snake;
					mTFrog_SlotAnimator->Play(L"slotattack_start", false);
					mbSnakeOn = false;
					mbFireOn = true;

					mSlotRollSound->Stop(true);
					mSlotRollEndSound->Play(false);
				}
				
			}

			if (mbFireOn && mbLeverParryOn)
			{
				mSPic1_Pos.y = 300.0f;
				mSPic2_Pos.y = 300.0f;
				mSPic3_Pos.y = 300.0f;

				mSPic1_Tr->SetPos(mSPic1_Pos);
				mSPic2_Tr->SetPos(mSPic2_Pos);
				mSPic3_Tr->SetPos(mSPic3_Pos);


				if (mRollTimer > 5.0f)
				{
					mRollTimer = 0.0f;
					mTFrog_SlotState = eTFrog_SlotState::Attack_Fire;
					mTFrog_SlotAnimator->Play(L"slotattack_start", false);
					mbSnakeOn = true;
					mbFireOn = false;

					mSlotRollSound->Stop(true);
					mSlotRollEndSound->Play(false);
				}
			}

		}
		else
		{
			mSPic1_Tr = mSlot_Pic1->GetComponent<Transform>();
			mSPic1_Pos = mSPic1_Tr->GetPos();

			mSPic2_Tr = mSlot_Pic2->GetComponent<Transform>();
			mSPic2_Pos = mSPic2_Tr->GetPos();

			mSPic3_Tr = mSlot_Pic3->GetComponent<Transform>();
			mSPic3_Pos = mSPic3_Tr->GetPos();


			if (mSPic1_Pos.y >= mPos.y - 585.0f)
			{
				mSPic1_Pos.y -= 500.0f * (Time::DeltaTime());
				mSPic2_Pos.y -= 500.0f * (Time::DeltaTime());
				mSPic3_Pos.y -= 500.0f * (Time::DeltaTime());
			}
			else
			{
				mSPic1_Pos.y = 360.0f;
				mSPic2_Pos.y = 360.0f;
				mSPic3_Pos.y = 360.0f;
			}

			mSPic1_Tr->SetPos(mSPic1_Pos);
			mSPic2_Tr->SetPos(mSPic2_Pos);
			mSPic3_Tr->SetPos(mSPic3_Pos);
		}

		
	}
	void TFrog_Slot::attack_coin()
	{
		mSpitAtkTimer += Time::DeltaTime();

		if (mPos.x >= 1280.0f)
		{
			mPos.x -= 200.0f * Time::DeltaTime();
			mTransform->SetPos(mPos);
		}

		if (mSpitAtkTimer > 2.0f)
		{
			mSpitAtkTimer = 0.0f;
			//object::Instantiate<Slot_Spit>(Vector2(mPos.x - 70.0f, mPos.y - 480.0f), eLayerType::Effect, mCuphead);
			object::Instantiate<Slot_Spit>(Vector2(mPos.x + 50.0f, mPos.y - 480.0f), eLayerType::Effect, mCuphead);

			mSpitSound->Play(false);
		}
	}
	void TFrog_Slot::attack_snake()
	{
		mSnakeAtkTimer += Time::DeltaTime();

		if (mSnakeAtkTimer > 0.8f && mSnakeAtkCnt > 0 && *mTFrog_SlotHp > 0)
		{
			mSnakeAtkTimer = 0.0f;

			object::Instantiate<Slot_Snake>(Vector2(mPos.x - 100.0f, mPos.y), eLayerType::BossBullet, mCuphead);

			mSnakeAtkCnt--;
		}
		else if (mSnakeAtkCnt <= 0)
		{
			mTFrog_SlotAnimator->Play(L"slotidle", true);
			mTFrog_SlotState = eTFrog_SlotState::Idle;
			mSnakeAtkCnt = 15;

			mPlatformSound->Stop(true);
		}
	}
	void TFrog_Slot::attack_fire()
	{
		mFireAtkTimer += Time::DeltaTime();

		if (mFireAtkTimer > 1.2f && mFireAtkCnt > 0 && *mTFrog_SlotHp > 0)
		{
			mFireAtkTimer = 0.0f;

			object::Instantiate<Slot_Fire>(Vector2(mPos.x - 100.0f, mPos.y), eLayerType::Ground);

			mFireAtkCnt--;
		}
		else if (mFireAtkCnt <= 0)
		{
			mTFrog_SlotAnimator->Play(L"slotidle", true);
			mTFrog_SlotState = eTFrog_SlotState::Idle;
			mFireAtkCnt = 10;

			mPlatformSound->Stop(true);
		}
	}
	void TFrog_Slot::onhit()
	{
	}
	void TFrog_Slot::death()
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

	void TFrog_Slot::IntroAnimCompleteEvent()
	{
		mTFrog_SlotAnimator->Play(L"slotidle", true);
		mTFrog_SlotState = eTFrog_SlotState::Idle;
	}

	void TFrog_Slot::LeverStartAnimCompleteEvent()
	{
		mTFrog_SlotAnimator->Play(L"slotleverloop", true);
		mbLeverParryOn = false;
		object::Instantiate<Slot_LeverParry>(Vector2(mPos.x - 350.0f, mPos.y - 300.0f), eLayerType::ParryObject, this);
	}

	void TFrog_Slot::LeverBackAnimCompleteEvent()
	{
		mSpitAtkTimer = 0.0f;
		mbLeverParryOn = true;
		mTFrog_SlotAnimator->Play(L"slotidle", true);

		mSlotRollSound->Play(true);
	}

	void TFrog_Slot::AttackStartAnimCompleteEvent()
	{
		mTFrog_SlotAnimator->Play(L"slotattackloop", true);
		mPlatformSound->Play(true);
	}

	

}