#include "jwSlot_CoinBullet.h"
#include "jwTime.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"

namespace jw
{
	Slot_CoinBullet::Slot_CoinBullet()
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(0.0f)
	{
	}
	Slot_CoinBullet::Slot_CoinBullet(Cuphead* cuphead)
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(180.0f)
		, mCuphead(cuphead)
	{
	}
	Slot_CoinBullet::~Slot_CoinBullet()
	{
	}
	void Slot_CoinBullet::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\coin", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::L);
		
		mAnimator->Play(L"slotcoin", true);

		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));

		mLayerType = Slot_CoinBullet::GetLayerType();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Transform* Cupheadtr = mCuphead->GetComponent<Transform>();
		Vector2 Cupheadpos = Cupheadtr->GetPos();

		mDegree = math::CalculateAngle(pos, Cupheadpos);

		

		GameObject::Initialize();
	}
	void Slot_CoinBullet::Update()
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
	void Slot_CoinBullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Slot_CoinBullet::Release()
	{
		GameObject::Release();
	}
	void Slot_CoinBullet::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());

		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			object::Destroy(this);
			mSpeed = 0.0f;
		}

	}
	void Slot_CoinBullet::OnCollisionStay(Collider* other)
	{

	}
	void Slot_CoinBullet::OnCollisionExit(Collider* other)
	{
	}
	
}
