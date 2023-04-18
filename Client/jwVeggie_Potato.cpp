#include "jwVeggie_Potato.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwTime.h"
#include "jwObject.h"

#include "jwPotatoShoot.h"
#include "jwPotatoAttackEffect.h"
#include "jwBossExplosion.h"

namespace jw
{
	Veggie_Potato::Veggie_Potato()
	{
	}
	Veggie_Potato::~Veggie_Potato()
	{
	}
	void Veggie_Potato::Initialize()
	{
		mbShow = false;
		mbOnHit = false;
		OnHitChecker = 0.0f;

		mPotatoHp = 30;
		mAttackCnt = 3;
		mAttackTimeChecker = 0.0f;
		mShootTimerChecker = 0.0f;
		mDeathEffectTimer = 0.0f;
		mLeaveTimer = 0.0f;
		mbAttacking = false;
		mPotatoDead = false;
		mBossOut = false;

		mPotatoAnimator = AddComponent<Animator>();

		mPotatoAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\potato\\Intro", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mPotatoAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\potato\\idle", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);

		mPotatoAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\potato\\attack", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mPotatoAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\potato\\attack2", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mPotatoAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\potato\\death", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);

		mPotatoAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\potato\\leave", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);

		mPotatoAnimator->GetCompleteEvent(L"potatoIntro") = std::bind(&Veggie_Potato::IntroAnimCompleteEvent, this);

		mPotatoAnimator->GetStartEvent(L"potatoattack2") = std::bind(&Veggie_Potato::Attack2AnimStartEvent, this);
		mPotatoAnimator->GetCompleteEvent(L"potatoattack") = std::bind(&Veggie_Potato::Attack1AnimCompleteEvent, this);
		mPotatoAnimator->GetCompleteEvent(L"potatoattack2") = std::bind(&Veggie_Potato::Attack2AnimCompleteEvent, this);
		mPotatoAnimator->GetCompleteEvent(L"potatoleave") = std::bind(&Veggie_Potato::LeaveAnimCompleteEvent, this);

		mPotatoState = eVeggie_PotatoState::Idle;
		mPotatoAnimator->Play(L"potatoIntro", true);

		mPotatoCollider = AddComponent<Collider>();
		mPotatoCollider->SetCenter(Vector2(-100.0f, -500.0f));
		mPotatoCollider->SetSize(Vector2(300.0f, 500.0f));

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.5f, 1.5f));

		GameObject::Initialize();
	}
	void Veggie_Potato::Update()
	{
		GameObject::Update();

		mAttackTimeChecker += Time::DeltaTime();

		switch (mPotatoState)
		{
		case jw::Veggie_Potato::eVeggie_PotatoState::Idle:
			idle();
			break;
		case jw::Veggie_Potato::eVeggie_PotatoState::Attack:
			attack();
			break;
		case jw::Veggie_Potato::eVeggie_PotatoState::OnHit:
			onhit();
			break;
		case jw::Veggie_Potato::eVeggie_PotatoState::Death:
			death();
			break;
		case jw::Veggie_Potato::eVeggie_PotatoState::Leave:
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
				mPotatoAnimator->SetMatrixBase();
			}
		}

		if (!mbOnHit && mPotatoDead)
		{
			OnHitChecker += Time::DeltaTime();
			if (OnHitChecker > 0.05f)
			{
				OnHitChecker = 0.0f;
				mbOnHit = true;
				mPotatoAnimator->SetMatrixHitFlash();
			}
		}

	}
	void Veggie_Potato::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void Veggie_Potato::Release()
	{
		GameObject::Release();
	}
	void Veggie_Potato::OnCollisionEnter(Collider* other)
	{
		if (mPotatoHp < 0 && !mPotatoDead)
		{
			mPotatoDead = true;
			mPotatoState = eVeggie_PotatoState::Death;
			mPotatoAnimator->Play(L"potatodeath", true);
			mPotatoAnimator->SetMatrixHitFlash();
		}

		mbOnHit = true;
		mPotatoHp--;
		mPotatoAnimator->SetMatrixHitFlash();
	}
	void Veggie_Potato::OnCollisionStay(Collider* other)
	{
	}
	void Veggie_Potato::OnCollisionExit(Collider* other)
	{
	}
	void Veggie_Potato::idle()
	{
		if (mPotatoHp > 0 && mAttackTimeChecker > 2.0f && !mbAttacking)
		{
			mbAttacking = true;
						 
			mPotatoState = eVeggie_PotatoState::Attack;
			mPotatoAnimator->Play(L"potatoattack", true);
		}
	}
	void Veggie_Potato::attack()
	{
	}
	void Veggie_Potato::onhit()
	{
	}
	void Veggie_Potato::death()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mDeathEffectTimer += Time::DeltaTime();
		mLeaveTimer += Time::DeltaTime();

		if (mLeaveTimer > 4.0f)
		{
			mPotatoState = eVeggie_PotatoState::Leave;
			mPotatoAnimator->Play(L"potatoleave", true);
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
	void Veggie_Potato::leave()
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
	void Veggie_Potato::IntroAnimCompleteEvent()
	{
		mPotatoAnimator->Play(L"potatoidle", true);
	}
	void Veggie_Potato::Attack2AnimStartEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		object::Instantiate<PotatoAttackEffect>(Vector2(pos.x - 400.0f, pos.y + 100.0f), eLayerType::Effect);
		
		if (mAttackCnt > 0)
		{
			PotatoShoot* shoot = object::Instantiate<PotatoShoot>(Vector2(pos.x - 400.0f, pos.y - 50.0f), eLayerType::BossBullet, mAttackCnt);
			shoot->SetDegree(180.0f);
		}
		else
		{
			PotatoShoot* shoot = object::Instantiate<PotatoShoot>(Vector2(pos.x - 400.0f, pos.y - 50.0f), eLayerType::ParryObj, mAttackCnt);
			shoot->SetDegree(180.0f);
		}

	}
	void Veggie_Potato::Attack1AnimCompleteEvent()
	{
		mPotatoAnimator->Play(L"potatoattack2", true);
	}
	void Veggie_Potato::Attack2AnimCompleteEvent()
	{
		if (mAttackCnt > 0)
		{
			mAttackCnt--;
			mPotatoState = eVeggie_PotatoState::Attack;
			mPotatoAnimator->Play(L"potatoattack", true);
		}
		else
		{
			mAttackCnt = 3;
			mPotatoState = eVeggie_PotatoState::Idle;
			mPotatoAnimator->Play(L"potatoidle", true);
			mbAttacking = false;
			mAttackTimeChecker = 0.0f;
		}
	}
	void Veggie_Potato::LeaveAnimCompleteEvent()
	{
		mBossOut = true;
		object::Destroy(this);
	}
}