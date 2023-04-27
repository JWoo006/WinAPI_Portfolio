#include "jwSFrog_Fistobj.h"
#include "jwTime.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"

namespace jw
{
	SFrog_Fistobj::SFrog_Fistobj()
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(0.0f)
	{
	}
	SFrog_Fistobj::SFrog_Fistobj(int attackCnt)
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(180.0f)
		, mAttackCnt(attackCnt)
	{
	}
	SFrog_Fistobj::~SFrog_Fistobj()
	{
	}
	void SFrog_Fistobj::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fist\\normal1", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fist\\normal2", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fist\\pink1", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fist\\pink2", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fist\\death", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);

		mAnimator->GetCompleteEvent(L"fistdeath") = std::bind(&SFrog_Fistobj::AnimCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"fistnormal1") = std::bind(&SFrog_Fistobj::n1AnimCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"fistpink1") = std::bind(&SFrog_Fistobj::p1AnimCOmpleteEvent, this);

		if (mAttackCnt % 3 == 0)
		{
			mAnimator->Play(L"fistpink1", false);
		}
		else
		{
			mAnimator->Play(L"fistnormal1", false);
		}



		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));

		mLayerType = SFrog_Fistobj::GetLayerType();

		GameObject::Initialize();
	}
	void SFrog_Fistobj::Update()
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
	void SFrog_Fistobj::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void SFrog_Fistobj::Release()
	{
		GameObject::Release();
	}
	void SFrog_Fistobj::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());

		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			bool ii = cuphead->GetIsInvincibile();

			mAnimator->Play(L"fistdeath", false);
			mSpeed = 0.0f;
		}
	}
	void SFrog_Fistobj::OnCollisionStay(Collider* other)
	{

	}
	void SFrog_Fistobj::OnCollisionExit(Collider* other)
	{
	}
	void SFrog_Fistobj::AnimCompleteEvent()
	{
		object::Destroy(this);
	}
	void SFrog_Fistobj::n1AnimCompleteEvent()
	{
		mAnimator->Play(L"fistnormal2", true);
	}
	void SFrog_Fistobj::p1AnimCOmpleteEvent()
	{
		mAnimator->Play(L"fistpink2", true);
	}
}
