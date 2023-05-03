#include "jwOctopus_Bullet.h"
#include "jwTime.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"

namespace jw
{
	Octopus_Bullet::Octopus_Bullet()
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(0.0f)
	{
	}
	Octopus_Bullet::Octopus_Bullet(Cuphead* cuphead)
		: mTime(0.0f)
		, mSpeed(800.0f)
		, mDegree(180.0f)
		, mCuphead(cuphead)
	{
	}
	Octopus_Bullet::~Octopus_Bullet()
	{
	}
	void Octopus_Bullet::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\Bullet(Yellow)", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\Bullet(Yellow)_death", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\Bullet(Pink)", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\Bullet(pink)_death", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);

		mAnimator->GetCompleteEvent(L"CaptainBullet(Yellow)_death") = std::bind(&Octopus_Bullet::YellowAnimCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"CaptainBullet(pink)_death") = std::bind(&Octopus_Bullet::PinkAnimCompleteEvent, this);


		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));

		mFlag = rand() % 2;

		if (mFlag)
		{
			mAnimator->Play(L"CaptainBullet(Pink)", true);
			this->SetLayerType(eLayerType::ParryBullet);
		}
		else
		{
			mAnimator->Play(L"CaptainBullet(Yellow)", true);
		}

		mLayerType = Octopus_Bullet::GetLayerType();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Transform* Cupheadtr = mCuphead->GetComponent<Transform>();
		Vector2 Cupheadpos = Cupheadtr->GetPos();

		mDegree = math::CalculateAngle(pos, Cupheadpos);

		GameObject::Initialize();
	}
	void Octopus_Bullet::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);

		pos.x += mSpeed * dir.x * Time::DeltaTime();
		pos.y += mSpeed * dir.y * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();

		if (mTime > 5.0f)
		{
			object::Destroy(this);
		}
	}
	void Octopus_Bullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Octopus_Bullet::Release()
	{
		GameObject::Release();
	}
	void Octopus_Bullet::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());

		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{			
			if (mFlag)
			{
				mAnimator->Play(L"CaptainBullet(pink)_death", false);
			}
			else
			{
				mAnimator->Play(L"CaptainBullet(Yellow)_death", false);
			}

			mSpeed = 0.0f;
		}

		if (other->GetOwner()->GetLayerType() == eLayerType::Bullet && !mbDeadChecker)
		{
			mbDeadChecker = true;

			object::Destroy(other->GetOwner());

			if (mFlag)
			{
				mAnimator->Play(L"CaptainBullet(pink)_death", false);
			}
			else
			{
				mAnimator->Play(L"CaptainBullet(Yellow)_death", false);
			}

			mSpeed = 0.0f;
		}
	}
	void Octopus_Bullet::OnCollisionStay(Collider* other)
	{

	}
	void Octopus_Bullet::OnCollisionExit(Collider* other)
	{
	}
	
	void Octopus_Bullet::YellowAnimCompleteEvent()
	{
		object::Destroy(this);
	}
	void Octopus_Bullet::PinkAnimCompleteEvent()
	{
		object::Destroy(this);
	}

}
