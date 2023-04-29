#include "jwSlot_Fire.h"
#include "jwTime.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwRigidbody.h"
#include "jwObject.h"
#include "jwCuphead.h"
#include "jwSlot_FireFlame.h"

namespace jw
{
	Slot_Fire::Slot_Fire()
		: mTime(0.0f)
		, mSpeed(400.0f)
		, mDegree(180.0f)
	{
	}
	Slot_Fire::Slot_Fire(Cuphead* cuphead)
		: mTime(0.0f)
		, mSpeed(400.0f)
		, mDegree(180.0f)
		, mCuphead(cuphead)
	{
	}
	Slot_Fire::~Slot_Fire()
	{
	}
	void Slot_Fire::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\Fire_Platform", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->Play(L"slotFire_Platform", true);

		mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-120.0f, -150.0f));
		mCollider->SetSize(Vector2(200.0f, 80.0f));

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mFlag = rand() % 2;

		if (mFlag)
		{
			mSlot_FireFlame = object::Instantiate<Slot_FireFlame>(Vector2(pos.x, pos.y - 100.0f), eLayerType::BossBullet, mFlag);
		}
		else
		{
			mSlot_FireFlame = object::Instantiate<Slot_FireFlame>(Vector2(pos.x, pos.y + 100.0f), eLayerType::BossBullet, mFlag);
		}
		

		mLayerType = Slot_Fire::GetLayerType();

		GameObject::Initialize();
	}
	void Slot_Fire::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();

		Transform* tr2 = mSlot_FireFlame->GetComponent<Transform>();

		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);

		Vector2 pos = tr->GetPos();
		Vector2 pos2 = tr2->GetPos();

		if (pos.y >= 700.0f)
		{
			pos.x += mSpeed * dir.x * Time::DeltaTime();
			pos.y -= mSpeed * Time::DeltaTime();
		}
		else
		{
			pos.x += mSpeed * dir.x * Time::DeltaTime();
			pos.y += mSpeed * dir.y * Time::DeltaTime();
		}

		if (mFlag)
		{
			tr2->SetPos(Vector2(pos.x, pos.y - 100.0f));
		}
		else
		{
			if (mSlot_FireFlame->Getmbon())
			{
				if (pos2.y <= 1350.0f)
				{
					//pos2.y += 1500.0f * Time::DeltaTime();	
					tr2->SetPos(Vector2(pos.x, pos2.y + 100.0f));
				}
				else
				{
					tr2->SetPos(Vector2(pos.x, pos2.y));
				}
				
			}
			else
			{
				tr2->SetPos(Vector2(pos.x, pos.y + 70.0f));
			}
			
		}

		tr->SetPos(pos);
		

		mTime += Time::DeltaTime();

		if (mTime > 5.0f)
		{
			object::Destroy(this);

			//object::Destroy(mSlot_FireFlame);
			//mSlot_FireFlame = nullptr;
		}
	}
	void Slot_Fire::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Slot_Fire::Release()
	{
		GameObject::Release();
	}
	void Slot_Fire::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		Rigidbody* rb = cuphead->GetComponent<Rigidbody>();
		rb->SetGround(true);

		cuphead->SetGroundCheck(true);
		cuphead->SetJumpCount(1);

		Collider* cupheadCol = cuphead->GetComponent<Collider>();
		Vector2 cupheadPos = cupheadCol->GetPos();

		Collider* groundCol = this->GetComponent<Collider>();
		Vector2 groundPos = groundCol->GetPos();

		float fLen = fabs(cupheadPos.y - groundPos.y);
		float fSize = (cupheadCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

		Transform* cupTr = cuphead->GetComponent<Transform>();
		Transform* grTr = this->GetComponent<Transform>();

		Vector2 cupPos = cupTr->GetPos();
		Vector2 grPos = grTr->GetPos();

		Vector2 collPos = mCollider->GetPos();

		cupTr->SetPos(Vector2(cupPos.x, collPos.y));
	}
	void Slot_Fire::OnCollisionStay(Collider* other)
	{

	}
	void Slot_Fire::OnCollisionExit(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		Rigidbody* rb = cuphead->GetComponent<Rigidbody>();
		rb->SetGround(false);

		cuphead->SetGroundCheck(false);
		cuphead->SetJumpCount(0);
	}
}
