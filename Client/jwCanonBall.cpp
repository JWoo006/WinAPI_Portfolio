#include "jwCanonBall.h"
#include "jwTime.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"

namespace jw
{
	CanonBall::CanonBall()
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(180.0f)
	{
	}
	CanonBall::~CanonBall()
	{
	}
	void CanonBall::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_A\\Cannonball", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		
		mAnimator->Play(L"WhaleBoat_ACannonball", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-150.0f, -100.0f));

		mLayerType = CanonBall::GetLayerType();

		GameObject::Initialize();
	}
	void CanonBall::Update()
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

		if (mTime > 5.0f)
		{
			object::Destroy(this);
		}
	}
	void CanonBall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CanonBall::Release()
	{
		GameObject::Release();
	}
	void CanonBall::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
	}
	void CanonBall::OnCollisionStay(Collider* other)
	{

	}
	void CanonBall::OnCollisionExit(Collider* other)
	{
	}
}