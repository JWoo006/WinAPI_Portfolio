#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class TFrog_Slot;
	class Slot_LeverParry : public GameObject
	{
	public:
		Slot_LeverParry();
		Slot_LeverParry(TFrog_Slot* mTFrog_Slot);
		~Slot_LeverParry();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		Animator* mAnimator;
		eLayerType mLayerType;
		TFrog_Slot* mTFrog_Slot;
	};
}

