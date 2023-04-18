#include "jwOnionBullet.h"
#include "jwTime.h"
#include "jwInput.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"

namespace jw
{
	OnionBullet::OnionBullet()
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(0.0f)
	{
	}
	OnionBullet::OnionBullet(bool bullettype)
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(-270.0f)
		, mBulletType(bullettype)
	{
	}
	OnionBullet::~OnionBullet()
	{
	}
	void OnionBullet::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\normal_tear", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\tear_death", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\pink_tear", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\pink_tear_death", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"oniontear_death") = std::bind(&OnionBullet::AnimCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"onionpink_tear_death") = std::bind(&OnionBullet::AnimCompleteEvent, this);

		if (mBulletType)
		{
			mAnimator->Play(L"onionnormal_tear", true);
		}
		else
		{
			mAnimator->Play(L"onionpink_tear", true);
		}

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-20.0f, -50.0f));
		collider->SetSize(Vector2(50.0f, 90.0f));

		mLayerType = OnionBullet::GetLayerType();

		GameObject::Initialize();
	}
	void OnionBullet::Update()
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

		if (mTime > 2.0f)
		{
			object::Destroy(this);
		}
	}
	void OnionBullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void OnionBullet::Release()
	{
		GameObject::Release();
	}
	void OnionBullet::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());

		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			if (mBulletType)
			{
				mAnimator->Play(L"oniontear_death", false);
				mSpeed = 0.0f;
			}
			else
			{
				mAnimator->Play(L"onionpink_tear_death", false);
				mSpeed = 0.0f;
			}
		}
	}
	void OnionBullet::OnCollisionStay(Collider* other)
	{
	}
	void OnionBullet::OnCollisionExit(Collider* other)
	{
	}
	void OnionBullet::AnimCompleteEvent()
	{
		object::Destroy(this);
	}
}