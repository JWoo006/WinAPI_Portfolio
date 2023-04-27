#include "jwPotatoShoot.h"
#include "jwTime.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"

namespace jw
{
	PotatoShoot::PotatoShoot()
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(0.0f)
	{
	}
	PotatoShoot::PotatoShoot(int attackCnt)
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(0.0f)
		, mAttackCnt(attackCnt)
	{
	}
	PotatoShoot::~PotatoShoot()
	{
	}
	void PotatoShoot::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\potato\\bullet", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\potato\\bullet_death", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\potato\\bullet_pink", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\potato\\bullet_pink_death", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"potatobullet_death") = std::bind(&PotatoShoot::AnimCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"potatobullet_pink_death") = std::bind(&PotatoShoot::AnimCompleteEvent, this);

		if (mAttackCnt > 0)
		{
			mAnimator->Play(L"potatobullet", true);
		}
		else
		{
			mAnimator->Play(L"potatobullet_pink", true);
		}

		

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));

		mLayerType = PotatoShoot::GetLayerType();

		GameObject::Initialize();
	}
	void PotatoShoot::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();

		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);

		Vector2 pos = tr->GetPos();
		pos.x += mSpeed * dir.x * Time::DeltaTime();
		pos.y += mSpeed * dir.y * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();

		if (mTime > 1.0f)
		{
			object::Destroy(this);
		}
	}
	void PotatoShoot::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PotatoShoot::Release()
	{
		GameObject::Release();
	}
	void PotatoShoot::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());



		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			bool ii = cuphead->GetIsInvincibile();

			if (mAttackCnt > 0)
			{
				mAnimator->Play(L"potatobullet_death", false);
				mSpeed = 0.0f;
			}
			else
			{
				mAnimator->Play(L"potatobullet_pink_death", false);
				mSpeed = 0.0f;
			}
		}		
	}
	void PotatoShoot::OnCollisionStay(Collider* other)
	{

	}
	void PotatoShoot::OnCollisionExit(Collider* other)
	{
	}
	void PotatoShoot::AnimCompleteEvent()
	{
		object::Destroy(this);
	}
}