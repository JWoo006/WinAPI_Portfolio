#include "jwPirate_Ship_A.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwTime.h"
#include "jwObject.h"
#include "jwRigidbody.h"

#include "jwCuphead.h"
#include "jwCanonBall.h"
#include "jwCanonball_sfx.h"

#include "jwSound.h"

namespace jw
{
	Pirate_Ship_A::Pirate_Ship_A()
	{
	}
	Pirate_Ship_A::Pirate_Ship_A(Cuphead* cuphead, int* pBossHp)
		: mCuphead(cuphead)
		, mShipHp(pBossHp)
	{
	}
	Pirate_Ship_A::~Pirate_Ship_A()
	{
	}
	void Pirate_Ship_A::Initialize()
	{
		mCanonChewSound = Resources::Load<Sound>(L"sfx_pirate_boat_cannon_chew", L"..\\Resources\\Sound\\Pirate\\sfx_pirate_boat_cannon_chew.wav");
		mCanonFireSound = Resources::Load<Sound>(L"sfx_pirate_boat_cannon_fire", L"..\\Resources\\Sound\\Pirate\\sfx_pirate_boat_cannon_fire.wav");
		mTransformSound = Resources::Load<Sound>(L"sfx_pirate_boat_transform", L"..\\Resources\\Sound\\Pirate\\sfx_pirate_boat_transform.wav");
			 
		mbShow = true;
		mbOnHit = false;
		OnHitChecker = 0.0f;
		mbAttacking = false;
		mBossOut = false;

		mShipAnimator = AddComponent<Animator>();

		mShipAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_A\\Idle", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mShipAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_A\\Spits_cannonball", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mShipAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_A\\Spits_cannonball_b", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		
		mShipAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\Wince", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mShipAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\Wince_loop", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mShipAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\Transform", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		//mShipAnimator->GetCompleteEvent(L"WhaleBoat_AIdle") = std::bind(&Pirate_Ship_A::IntroAnimCompleteEvent, this);
		mShipAnimator->GetCompleteEvent(L"WhaleBoat_ASpits_cannonball") = std::bind(&Pirate_Ship_A::canonballAnimCompleteEvent, this);
		mShipAnimator->GetCompleteEvent(L"WhaleBoat_ASpits_cannonball_b") = std::bind(&Pirate_Ship_A::canonballBAnimCompleteEvent, this);
		mShipAnimator->GetCompleteEvent(L"WhaleBoat_BWince") = std::bind(&Pirate_Ship_A::WinceAnimCompleteEvent, this);
		mShipAnimator->GetCompleteEvent(L"WhaleBoat_BTransform") = std::bind(&Pirate_Ship_A::TransformAnimCompleteEvent, this);

		mShipState = ePirate_Ship_A_State::Idle;
		mShipAnimator->Play(L"WhaleBoat_AIdle", true);

		mShipCollider = AddComponent<Collider>();
		mShipCollider->SetCenter(Vector2(-280.0f, -700.0f));
		mShipCollider->SetSize(Vector2(200.0f, 600.0f));

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.3f, 1.3f));

		GameObject::Initialize();
	}
	void Pirate_Ship_A::Update()
	{
		GameObject::Update();

		switch (mShipState)
		{
		case jw::Pirate_Ship_A::ePirate_Ship_A_State::Intro:
			break;
		case jw::Pirate_Ship_A::ePirate_Ship_A_State::Idle:
			idle();
			break;
		case jw::Pirate_Ship_A::ePirate_Ship_A_State::Attack:
			attack();
			break;
		case jw::Pirate_Ship_A::ePirate_Ship_A_State::OnHit:
			break;
		case jw::Pirate_Ship_A::ePirate_Ship_A_State::Death:
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
				mShipAnimator->SetMatrixBase();
			}
		}


	}
	void Pirate_Ship_A::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void Pirate_Ship_A::Release()
	{
		GameObject::Release();
	}
	void Pirate_Ship_A::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
			if (cuphead == nullptr)
				return;

			Rigidbody* rb = cuphead->GetComponent<Rigidbody>();

			cuphead->SetRightSpeed(0.0f);
			cuphead->SetRightDashSpeed(0.0f);

			Collider* cupheadCol = cuphead->GetComponent<Collider>();
			Vector2 cupheadPos = cupheadCol->GetPos();

			Collider* groundCol = this->GetComponent<Collider>();
			Vector2 groundPos = groundCol->GetPos();

			float fLen = fabs(cupheadPos.y - groundPos.y);
			float fSize = (cupheadCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

			Transform* cupTr = cuphead->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();

			Vector2 cupPos = cupTr->GetPos();
			Vector2 grPos = grTr->GetPos();

			Vector2 collPos = mShipCollider->GetPos();
		}

		
	}
	void Pirate_Ship_A::OnCollisionStay(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
			if (cuphead == nullptr)
				return;

			Rigidbody* rb = cuphead->GetComponent<Rigidbody>();

			cuphead->SetRightSpeed(0.0f);
			cuphead->SetRightDashSpeed(0.0f);
		}

		
	}
	void Pirate_Ship_A::OnCollisionExit(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
			if (cuphead == nullptr)
				return;

			Rigidbody* rb = cuphead->GetComponent<Rigidbody>();

			cuphead->SetRightSpeed(400.0f);
			cuphead->SetRightDashSpeed(1000.0f);
		}

		
	}
	void Pirate_Ship_A::idle()
	{
		if (*mShipHp > 0 && *mShipHp < 100)
		{
			mShipState = ePirate_Ship_A_State::Attack;
		}

		if (*mShipHp < 0 && !mBossDead)
		{
			mBossDead = true;
			mShipState = ePirate_Ship_A_State::Death;
			mShipAnimator->Play(L"WhaleBoat_BWince", false);
			mAtakTimer = 0.0f;
		}
	}
	void Pirate_Ship_A::attack()
	{
		mAtakTimer += Time::DeltaTime();

		if (mAtakTimer > 5.0f)
		{
			mAtakTimer = 0.0f;

			mShipAnimator->Play(L"WhaleBoat_ASpits_cannonball", false);
			mCanonChewSound->Play(false);
		}

		if (*mShipHp < 0 && !mBossDead)
		{
			mBossDead = true;
			mShipState = ePirate_Ship_A_State::Death;
			mShipAnimator->Play(L"WhaleBoat_BWince", false);
			mAtakTimer = 0.0f;
		}
	}
	
	void Pirate_Ship_A::onhit()
	{
	}
	void Pirate_Ship_A::death()
	{
		mAtakTimer += Time::DeltaTime();

		if (mAtakTimer > 2.0f)
		{
			mShipState = ePirate_Ship_A_State::OnHit;
			Transform* tr = GetComponent<Transform>();
		    tr->SetScale(Vector2(1.3f, 1.5f));
			mShipAnimator->Play(L"WhaleBoat_BTransform", false);
			mBossOut = true;
		}
	}

	void Pirate_Ship_A::IntroAnimCompleteEvent()
	{
		
	}

	void Pirate_Ship_A::canonballAnimCompleteEvent()
	{
		mShipAnimator->Play(L"WhaleBoat_ASpits_cannonball_b", false);

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();


		mCanonFireSound->Play(false);
		object::Instantiate<CanonBall>(Vector2(pos.x - 100.0f, pos.y - 200.0f), eLayerType::BossBullet);

		object::Instantiate<Canonball_sfx>(Vector2(pos.x - 250.0f , pos.y - 150.0f), eLayerType::Effect);
	}

	void Pirate_Ship_A::canonballBAnimCompleteEvent()
	{
		mShipAnimator->Play(L"WhaleBoat_AIdle", true);
		mShipState = ePirate_Ship_A_State::Idle;
	}

	void Pirate_Ship_A::WinceAnimCompleteEvent()
	{
		
		mShipAnimator->Play(L"WhaleBoat_BWince_loop", true);

		mTransformSound->Play(false);
	}

	void Pirate_Ship_A::TransformAnimCompleteEvent()
	{
		mBossLeave = true;
	}


}