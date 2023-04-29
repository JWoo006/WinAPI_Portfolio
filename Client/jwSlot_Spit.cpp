#include "jwSlot_Spit.h"
#include "jwAnimator.h"
#include "jwObject.h"
#include "jwSlot_CoinBullet.h"

namespace jw
{

	Slot_Spit::Slot_Spit()
	{
		
	}
	Slot_Spit::Slot_Spit(Cuphead* mcuphead)
		: mCuphead(mcuphead)
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\spit", Vector2::Zero, 0.06f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"slotspit") = std::bind(&Slot_Spit::AnimCompleteEvent, this);
		mAnimator->Play(L"slotspit", false);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.2f, 1.2f));
	}
	Slot_Spit::~Slot_Spit()
	{
	}
	void Slot_Spit::Update()
	{
		GameObject::Update();
	}
	void Slot_Spit::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Slot_Spit::Release()
	{
		GameObject::Release();
	}
	void Slot_Spit::AnimCompleteEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 mPos = tr->GetPos();

		object::Instantiate<Slot_CoinBullet>(Vector2(mPos), eLayerType::BossBullet, mCuphead);
		object::Destroy(this);
	}
}