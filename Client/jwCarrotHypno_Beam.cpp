#include "jwCarrotHypno_Beam.h"
#include "jwTime.h"
#include "jwInput.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"

#include "jwSound.h"

namespace jw
{
	CarrotHypno_Beam::CarrotHypno_Beam()
		: mTime(0.0f)
		, mSpeed(100.0f)
		, mDegree(0.0f)
		, mHp(3)
		, mbDeadChecker(false)
		, mbOnHit(false)
		, OnHitChecker(0.0f)
	{
	}
	CarrotHypno_Beam::CarrotHypno_Beam(Cuphead* cuphead)
		: mTime(0.0f)
		, mSpeed(500.0f)
		, mDegree(-270.0f)
		, mHp(2)
		, mbDeadChecker(false)
		, mbOnHit(false)
		, OnHitChecker(0.0f)
		, mCuphead(cuphead)
	{
	}
	CarrotHypno_Beam::~CarrotHypno_Beam()
	{
	}
	void CarrotHypno_Beam::Initialize()
	{

		Sound* mSound1
			= Resources::Load<Sound>(L"Carrot_MindMeld_BeamFire", L"..\\Resources\\Sound\\Veggie\\sfx_level_veggies_Carrot_MindMeld_BeamFire_01.wav");
		mSound1->Play(false);

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\carrot\\hypno_ring", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\carrot\\hypno_ring2", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\carrot\\hypno_death", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"carrothypno_death") = std::bind(&CarrotHypno_Beam::AnimCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"carrothypno_ring") = std::bind(&CarrotHypno_Beam::Hypno_ringAnimCompleteEvent, this);

		mAnimator->Play(L"carrothypno_ring", false);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-60.0f, -100.0f));
		collider->SetSize(Vector2(120.0f, 90.0f));

		mLayerType = CarrotHypno_Beam::GetLayerType();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Transform* Cupheadtr = mCuphead->GetComponent<Transform>();
		Vector2 Cupheadpos = Cupheadtr->GetPos();
		mDegree = math::CalculateAngle(pos, Cupheadpos);

		GameObject::Initialize();
	}
	void CarrotHypno_Beam::Update()
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

		if (mbOnHit)
		{
			OnHitChecker += Time::DeltaTime();
			if (OnHitChecker > 0.05f)
			{
				OnHitChecker = 0.0f;
				mbOnHit = false;
				mAnimator->SetMatrixBase();
			}
		}
	}
	void CarrotHypno_Beam::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CarrotHypno_Beam::Release()
	{
		GameObject::Release();
	}
	void CarrotHypno_Beam::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());

		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			mAnimator->Play(L"carrothypno_death", false);
			mSpeed = 0.0f;

		}
		if (other->GetOwner()->GetLayerType() == eLayerType::Ground)
		{
			mAnimator->Play(L"carrothypno_death", false);
			mSpeed = 0.0f;

		}
	}
	void CarrotHypno_Beam::OnCollisionStay(Collider* other)
	{
	}
	void CarrotHypno_Beam::OnCollisionExit(Collider* other)
	{
	}
	void CarrotHypno_Beam::AnimCompleteEvent()
	{
		object::Destroy(this);
	}
	void CarrotHypno_Beam::Hypno_ringAnimCompleteEvent()
	{
		mAnimator->Play(L"carrothypno_ring2", true);
	}
}