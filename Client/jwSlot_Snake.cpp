#include "jwSlot_Snake.h"
#include "jwTime.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"
#include "jwSlot_SnakeGround.h"
#include "jwCuphead.h"

namespace jw
{
	Slot_Snake::Slot_Snake()
		: mTime(0.0f)
		, mSpeed(100.0f)
		, mDegree(180.0f)
	{
	}
	Slot_Snake::Slot_Snake(Cuphead* cuphead)
		: mTime(0.0f)
		, mSpeed(500.0f)
		, mDegree(180.0f)
		, mCuphead(cuphead)
	{
	}
	Slot_Snake::~Slot_Snake()
	{
	}
	void Slot_Snake::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\Snake_Platform", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
		
		mAnimator->Play(L"slotSnake_Platform", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-120.0f, -100.0f));
		collider->SetSize(Vector2(200.0f, 100.0f));

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mSlot_SnakeGround = object::Instantiate<Slot_SnakeGround>(Vector2(pos.x, pos.y), eLayerType::Ground);

		mLayerType = Slot_Snake::GetLayerType();

		GameObject::Initialize();
	}
	void Slot_Snake::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();

		Transform* tr2 = mSlot_SnakeGround->GetComponent<Transform>();

		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);

		Vector2 pos = tr->GetPos();
		pos.x += mSpeed * dir.x * Time::DeltaTime();
		pos.y += mSpeed * dir.y * Time::DeltaTime();
		tr->SetPos(pos);
		tr2->SetPos(pos);

		mTime += Time::DeltaTime();

		if (mTime > 5.0f)
		{
			object::Destroy(this);

			Transform* cuptr = mCuphead->GetComponent<Transform>();
			Vector2 cuppos = cuptr->GetPos();
			if (cuppos.y > 800.0f)
			{
				mSlot_SnakeGround->OnCollisionExit(mCuphead->GetComponent<Collider>());
			}

			object::Destroy(mSlot_SnakeGround);
			mSlot_SnakeGround = nullptr;
			
		}
	}
	void Slot_Snake::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Slot_Snake::Release()
	{
		GameObject::Release();
	}
	void Slot_Snake::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());

		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			
		}
	}
	void Slot_Snake::OnCollisionStay(Collider* other)
	{

	}
	void Slot_Snake::OnCollisionExit(Collider* other)
	{
	}
}
