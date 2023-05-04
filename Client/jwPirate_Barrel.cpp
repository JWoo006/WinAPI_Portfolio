#include "jwPirate_Barrel.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwTime.h"
#include "jwObject.h"
#include "jwRigidbody.h"

#include "jwCuphead.h"
#include "jwBossExplosion.h"
#include "jwBarrel_Dust.h"
#include "jwBarrel_Fx.h"

#include "jwSound.h"

namespace jw
{
	Pirate_Barrel::Pirate_Barrel()
	{
	}
	Pirate_Barrel::Pirate_Barrel(Cuphead* cuphead, int* pBossHp)
		: mCuphead(cuphead)
		, mBossHp(pBossHp)
	{
	}
	Pirate_Barrel::~Pirate_Barrel()
	{
	}
	void Pirate_Barrel::Initialize()
	{
		mbShow = true;
		mbOnHit = false;
		OnHitChecker = 0.0f;
		mbAttacking = false;
		mBossOut = false;

		mBarrelDir = -1;

		mBarrelAnimator = AddComponent<Animator>();

		mBarrelAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Barrel\\idle", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mBarrelAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Barrel\\safe", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mBarrelAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Barrel\\drop", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mBarrelAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Barrel\\drop_loop", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mBarrelAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Barrel\\smash", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mBarrelAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Barrel\\smash_loop", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mBarrelAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Barrel\\up", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mBarrelAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Barrel\\up_loop", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		//mBarrelAnimator->GetCompleteEvent(L"WhaleBoat_AIdle") = std::bind(&Pirate_Barrel::IntroAnimCompleteEvent, this);
		mBarrelAnimator->GetCompleteEvent(L"Barreldrop") = std::bind(&Pirate_Barrel::DropAnimCompleteEvent, this);
		mBarrelAnimator->GetCompleteEvent(L"Barrelsmash") = std::bind(&Pirate_Barrel::SmashAnimCompleteEvent, this);
		mBarrelAnimator->GetCompleteEvent(L"Barrelup") = std::bind(&Pirate_Barrel::UpAnimCompleteEvent, this);

		mBarrelState = ePirate_Barrel_State::Idle;
		mBarrelAnimator->Play(L"Barrelidle", true);

		mBarrelCollider = AddComponent<Collider>();
		//mBarrelCollider->SetCenter(Vector2(-50.0f, -100.0f));
		mBarrelCollider->SetCenter(Vector2(0.0f, -100.0f));
		mBarrelCollider->SetSize(Vector2(10.0f, 1100.0f));

		mBarrelTr = GetComponent<Transform>();
		mBarrelTr->SetScale(Vector2(1.f, 1.f));


		GameObject::Initialize();
	}
	void Pirate_Barrel::Update()
	{
		GameObject::Update();

		switch (mBarrelState)
		{
		case jw::Pirate_Barrel::ePirate_Barrel_State::Intro:
			break;
		case jw::Pirate_Barrel::ePirate_Barrel_State::Idle:
			idle();
			break;
		case jw::Pirate_Barrel::ePirate_Barrel_State::Safe:
			safe();
			break;
		case jw::Pirate_Barrel::ePirate_Barrel_State::Attack:
			attack();
			break;
		case jw::Pirate_Barrel::ePirate_Barrel_State::Smash:
			Smash();
			break;
		case jw::Pirate_Barrel::ePirate_Barrel_State::Up:
			up();
			break;
		case jw::Pirate_Barrel::ePirate_Barrel_State::OnHit:
			break;
		case jw::Pirate_Barrel::ePirate_Barrel_State::Death:
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
				mBarrelAnimator->SetMatrixBase();
			}
		}


	}
	void Pirate_Barrel::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void Pirate_Barrel::Release()
	{
		GameObject::Release();
	}
	void Pirate_Barrel::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		if (other->GetOwner()->GetLayerType() == eLayerType::Player && !mbAttacking && GetBarrelState() == ePirate_Barrel_State::Idle)
		{
			mBarrelCollider->SetCenter(Vector2(-50.0f, -100.0f));
			mBarrelCollider->SetSize(Vector2(100.0f, 100.0f));
			

			mbAttacking = true;
			mBarrelState = ePirate_Barrel_State::Attack;
			mBarrelAnimator->Play(L"Barreldrop", false);
			
		}

		
	}
	void Pirate_Barrel::OnCollisionStay(Collider* other)
	{
		
	}
	void Pirate_Barrel::OnCollisionExit(Collider* other)
	{
		
	}
	void Pirate_Barrel::idle()
	{
		mBarrelPos = mBarrelTr->GetPos();
		Vector2 mcupheadPos = mCuphead->GetComponent<Transform>()->GetPos();

		mAtakTimer += Time::DeltaTime();

		if (mAtakTimer > 2.0f)
		{
			mBarrelState = ePirate_Barrel_State::Safe;
			mBarrelAnimator->Play(L"Barrelsafe", true);

			mAtakTimer = 0.0f;
		}

		if (mBarrelPos.x == mcupheadPos.x)
		{
			
		}

		if (mBarrelPos.x >= 1100.0f)
		{
			mBarrelDir = -1;
		}
		if (mBarrelPos.x <= 100.0f)
		{
			mBarrelDir = 1;
		}


		mBarrelPos.x += 100.0f * mBarrelDir * Time::DeltaTime();
		mBarrelTr->SetPos(mBarrelPos);
	}
	void Pirate_Barrel::safe()
	{
		mBarrelPos = mBarrelTr->GetPos();
		Vector2 mcupheadPos = mCuphead->GetComponent<Transform>()->GetPos();

		mAtakTimer += Time::DeltaTime();

		if (mAtakTimer > 2.0f)
		{
			mBarrelState = ePirate_Barrel_State::Idle;
			mBarrelAnimator->Play(L"Barrelidle", true);

			mAtakTimer = 0.0f;
		}

		if (mBarrelPos.x == mcupheadPos.x)
		{

		}

		if (mBarrelPos.x >= 1100.0f)
		{
			mBarrelDir = -1;
		}
		if (mBarrelPos.x <= 100.0f)
		{
			mBarrelDir = 1;
		}


		mBarrelPos.x += 100.0f * mBarrelDir * Time::DeltaTime();
		mBarrelTr->SetPos(mBarrelPos);
	}
	void Pirate_Barrel::attack()
	{
		mAtakTimer += Time::DeltaTime();

		this->SetLayerType(eLayerType::Monster);

		if (mAtakTimer > 1.5f)
		{
			
			if (mBarrelPos.y <= 800.0f)
			{
				mBarrelPos.y += 1000.0f * Time::DeltaTime();
			}
			else
			{
				mBarrelState = ePirate_Barrel_State::Smash;
				mBarrelAnimator->Play(L"Barrelsmash", false);
				object::Instantiate<Barrel_Dust>(Vector2(mBarrelPos), eLayerType::Effect);
				object::Instantiate<Barrel_Fx>(Vector2(mBarrelPos), eLayerType::Effect);
				mAtakTimer = 0.0f;
			}
		}
		
		mBarrelTr->SetPos(mBarrelPos);
	}

	void Pirate_Barrel::Smash()
	{
		mAtakTimer += Time::DeltaTime();

		if (mAtakTimer > 1.0f)
		{
			mBarrelState = ePirate_Barrel_State::Up;
			mBarrelAnimator->Play(L"Barrelup", false);
			mAtakTimer = 0.0f;
		}
	}

	void Pirate_Barrel::up()
	{
		if (mBarrelPos.y >= 200.0f)
		{
			mBarrelPos.y -= 700.0f * Time::DeltaTime();
		}
		else
		{
			mBarrelState = ePirate_Barrel_State::Safe;
			mBarrelAnimator->Play(L"Barrelsafe", true);

			mBarrelCollider->SetCenter(Vector2(0.0f, -100.0f));
			mBarrelCollider->SetSize(Vector2(10.0f, 1100.0f));

			this->SetLayerType(eLayerType::BG);
			mbAttacking = false;
			
			mAtakTimer = 0.0f;
		}

		mBarrelTr->SetPos(mBarrelPos);
	}

	void Pirate_Barrel::onhit()
	{
	}
	void Pirate_Barrel::death()
	{
		mBarrelPos = mBarrelTr->GetPos();
		Vector2 mcupheadPos = mCuphead->GetComponent<Transform>()->GetPos();

		if (mBarrelPos.x >= 1100.0f)
		{
			mBarrelDir = -1;
		}
		if (mBarrelPos.x <= 100.0f)
		{
			mBarrelDir = 1;
		}


		mBarrelPos.x += 100.0f * mBarrelDir * Time::DeltaTime();
		mBarrelTr->SetPos(mBarrelPos);
	}

	void Pirate_Barrel::IntroAnimCompleteEvent()
	{

	}

	void Pirate_Barrel::DropAnimCompleteEvent()
	{
		mBarrelAnimator->Play(L"Barreldrop_loop", true);
		Sound* mSound1 = Resources::Load<Sound>(L"sfx_pirate_barrel_drop_attack", L"..\\Resources\\Sound\\Pirate\\sfx_pirate_barrel_drop_attack.wav");
		mSound1->Play(false);
	}

	void Pirate_Barrel::SmashAnimCompleteEvent()
	{
		mBarrelAnimator->Play(L"Barrelsmash_loop", true);
	}

	void Pirate_Barrel::UpAnimCompleteEvent()
	{
		mBarrelAnimator->Play(L"Barrelup_loop", true);
	}


}