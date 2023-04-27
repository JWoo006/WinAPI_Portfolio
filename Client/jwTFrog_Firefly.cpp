#include "jwTFrog_Firefly.h"
#include "jwTime.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"

namespace jw
{
	TFrog_Firefly::TFrog_Firefly()
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(0.0f)
	{
	}
	TFrog_Firefly::TFrog_Firefly(Cuphead* cuphead, Vector2 dest)
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(180.0f)
		, mCuphead(cuphead)
		, mDestPos(dest)
	{
	}
	TFrog_Firefly::~TFrog_Firefly()
	{
	}
	void TFrog_Firefly::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\firefly\\idle", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\firefly\\move", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\firefly\\attack", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\firefly\\death", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
		
		mAnimator->GetCompleteEvent(L"fireflydeath") = std::bind(&TFrog_Firefly::AnimCompleteEvent, this);
		
		mFireFlyState = eFireFlyState::Move;
		mAnimator->Play(L"fireflymove", true);

		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));

		mLayerType = TFrog_Firefly::GetLayerType();

		GameObject::Initialize();
	}
	void TFrog_Firefly::Update()
	{
		GameObject::Update();

		switch (mFireFlyState)
		{
		case jw::TFrog_Firefly::eFireFlyState::Idle:
			collider->SetCenter(Vector2(-50.0f, -100.0f));
			idle();
			break;
		case jw::TFrog_Firefly::eFireFlyState::Move:
			collider->SetCenter(Vector2(-50.0f, -100.0f));
			//collider->SetCenter(Vector2(-2000.0f, -2000.0f));
			move();
			break;
		case jw::TFrog_Firefly::eFireFlyState::Attack:
			collider->SetCenter(Vector2(-50.0f, -100.0f));
			attack();
			break;
		case jw::TFrog_Firefly::eFireFlyState::Death:
			death();
			break;
		default:
			break;
		}

		
	}
	void TFrog_Firefly::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void TFrog_Firefly::Release()
	{
		GameObject::Release();
	}
	void TFrog_Firefly::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());

		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			mAnimator->Play(L"fireflydeath", false);
			mSpeed = 0.0f;

		}

		if (other->GetOwner()->GetLayerType() == eLayerType::Bullet && !mbDeadChecker)
		{
			mbDeadChecker = true;

			object::Destroy(other->GetOwner());

			mFireFlyState = eFireFlyState::Death;

			mAnimator->Play(L"fireflydeath", false);
			mSpeed = 0.0f;
		}
	}
	void TFrog_Firefly::OnCollisionStay(Collider* other)
	{

	}
	void TFrog_Firefly::OnCollisionExit(Collider* other)
	{
	}
	void TFrog_Firefly::idle()
	{
		mTime += Time::DeltaTime();

		if (mTime > 2.5f)
		{
			mFireFlyState = eFireFlyState::Attack;
			mAnimator->Play(L"fireflyattack", true);
		}
	}
	void TFrog_Firefly::move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mDegree = math::CalculateAngle(pos, mDestPos);

		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);


		pos.x += mSpeed * dir.x * Time::DeltaTime();
		pos.y += mSpeed * dir.y * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();

		if (mTime > 1.f)
		{
			mTime = 0.0f;
			mSpeed = 0.0f;
			mFireFlyState = eFireFlyState::Idle;
			mAnimator->Play(L"fireflyidle", true);
		}
	}
	void TFrog_Firefly::attack()
	{
		mSpeed = 800.0f;

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Transform* Cupheadtr = mCuphead->GetComponent<Transform>();
		Vector2 Cupheadpos = Cupheadtr->GetPos();

		mDegree = math::CalculateAngle(pos, Cupheadpos);

		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);


		pos.x += mSpeed * dir.x * Time::DeltaTime();
		pos.y += mSpeed * dir.y * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();

		if (mTime > 15.0f)
		{
			//object::Destroy(this);
		}
	}
	void TFrog_Firefly::death()
	{
	}
	void TFrog_Firefly::AnimCompleteEvent()
	{
		object::Destroy(this);
	}

}
