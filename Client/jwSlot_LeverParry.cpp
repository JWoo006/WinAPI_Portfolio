#include "jwSlot_LeverParry.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"
#include "jwTFrog_Slot.h"

namespace jw
{
	Slot_LeverParry::Slot_LeverParry()
	{
	}
	Slot_LeverParry::Slot_LeverParry(TFrog_Slot* TFrog_Slot)
		: mTFrog_Slot(TFrog_Slot)
	{
	}
	Slot_LeverParry::~Slot_LeverParry()
	{
	}
	void Slot_LeverParry::Initialize()
	{
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));

		mLayerType = Slot_LeverParry::GetLayerType();

		GameObject::Initialize();
	}
	void Slot_LeverParry::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

	}
	void Slot_LeverParry::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Slot_LeverParry::Release()
	{
		GameObject::Release();
	}
	void Slot_LeverParry::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());

		if (other->GetOwner()->GetLayerType() == eLayerType::Player && cuphead->GetIsParrying())
		{
			mTFrog_Slot->SetLeverOn(true);
			mAnimator =  mTFrog_Slot->GetComponent<Animator>();
			mAnimator->Play(L"slotleverback", false);
			mTFrog_Slot->SetTFrog_SlotState(TFrog_Slot::eTFrog_SlotState::SlotRoll);

			object::Destroy(this);
		}
	}
	void Slot_LeverParry::OnCollisionStay(Collider* other)
	{

	}
	void Slot_LeverParry::OnCollisionExit(Collider* other)
	{
	}
}
