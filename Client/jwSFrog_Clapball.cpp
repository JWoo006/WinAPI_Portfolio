#include "jwSFrog_Clapball.h"
#include "jwTime.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"

namespace jw
{
	SFrog_Clapball::SFrog_Clapball()
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(-65.0f)
	{
	}
	SFrog_Clapball::SFrog_Clapball(int attackCnt)
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(-65.0f)
		, mAttackCnt(attackCnt)
	{
	}
	SFrog_Clapball::~SFrog_Clapball()
	{
	}
	void SFrog_Clapball::Initialize()
	{
		mbChanged = false;

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fan\\clapball_down", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\SFrog\\fan\\clapball_up", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::L);

		mAnimator->Play(L"fanclapball_up", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));

		mLayerType = SFrog_Clapball::GetLayerType();

		GameObject::Initialize();
	}
	void SFrog_Clapball::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();


		if (pos.y <= 0.0f && !mbChanged)
		{
			mbChanged = true;
			mDegree = 65.0f;
			mAnimator->Play(L"fanclapball_down", true);
		}
		else if (pos.y >= 800.0f && mbChanged)
		{
			mbChanged = false;
			mDegree = -65.0f;
			mAnimator->Play(L"fanclapball_up", true);
		}


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
	void SFrog_Clapball::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void SFrog_Clapball::Release()
	{
		GameObject::Release();
	}
	void SFrog_Clapball::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
	}
	void SFrog_Clapball::OnCollisionStay(Collider* other)
	{

	}
	void SFrog_Clapball::OnCollisionExit(Collider* other)
	{
	}
}
