#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class Slot_Fire : public GameObject
	{
	public:
		Slot_Fire();
		Slot_Fire(Cuphead* mCuphead);
		~Slot_Fire();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetDegree(float degree) { mDegree = degree; }

	private:
		Animator* mAnimator;
		Cuphead* mCuphead;
		class Collider* mCollider;
		class Slot_FireFlame* mSlot_FireFlame;
		eLayerType mLayerType;

		float mTime;
		float mSpeed;
		float mDegree;
		int mAttackCnt;
		int mFlag;
	};
}
