#include "jwSlot_FireFlame.h"
#include "jwTime.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"

namespace jw
{
	Slot_FireFlame::Slot_FireFlame()
	{
	}
	Slot_FireFlame::Slot_FireFlame(int flag)
		: mFlag(flag)
	{
	}
	Slot_FireFlame::~Slot_FireFlame()
	{
	}
	void Slot_FireFlame::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\flame_a", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\flame_b", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\flame_b_loop", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\flame_a_down", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\flame_b_down", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\flame_b_downloop", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"slotflame_b") = std::bind(&Slot_FireFlame::Flame_bAnimCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"slotflame_b_down") = std::bind(&Slot_FireFlame::Flame_b_DownAnimCompleteEvent, this);

		if (mFlag)
		{
			mAnimator->Play(L"slotflame_a", true);
			collider = AddComponent<Collider>();
			collider->SetCenter(Vector2(-50.0f, -100.0f));
		}
		else
		{
			mAnimator->Play(L"slotflame_a_down", true);
			collider = AddComponent<Collider>();
			collider->SetCenter(Vector2(-50.0f, -100.0f));
		}

		

		mLayerType = Slot_FireFlame::GetLayerType();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		GameObject::Initialize();
	}
	void Slot_FireFlame::Update()
	{
		GameObject::Update();

		mFlameTimer += Time::DeltaTime();

		if (mFlameTimer > 2.0f && !mbon)
		{
			mbon = true;
			if (mFlag)
			{
				mAnimator->Play(L"slotflame_b", false);
			}
			else
			{
				mAnimator->Play(L"slotflame_b_down", false);
			}
		}

		mTime += Time::DeltaTime();

		if (mTime > 5.0f)
		{
			object::Destroy(this);

			//object::Destroy(mSlot_FireFlame);
			//mSlot_FireFlame = nullptr;
		}


	}
	void Slot_FireFlame::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Slot_FireFlame::Release()
	{
		GameObject::Release();
	}
	void Slot_FireFlame::OnCollisionEnter(Collider* other)
	{
		
	}
	void Slot_FireFlame::OnCollisionStay(Collider* other)
	{

	}
	void Slot_FireFlame::OnCollisionExit(Collider* other)
	{
	}

	void Slot_FireFlame::Flame_bAnimCompleteEvent()
	{
		mAnimator->Play(L"slotflame_b_loop", true);
	}

	void Slot_FireFlame::Flame_b_DownAnimCompleteEvent()
	{
		mAnimator->Play(L"slotflame_b_downloop", true);
		collider->SetCenter(Vector2(-50.0f, -800.0f));
		collider->SetSize(Vector2(100.0f, 500.0f));
	}

}
