#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Slot_SnakeGround;
	class Slot_Snake : public GameObject
	{
	public:
		Slot_Snake();
		Slot_Snake(Cuphead* mCuphead);
		~Slot_Snake();

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
		class Cuphead* mCuphead;
		Slot_SnakeGround* mSlot_SnakeGround;
		eLayerType mLayerType;

		float mTime;
		float mSpeed;
		float mDegree;
		int mAttackCnt;
	};
}

