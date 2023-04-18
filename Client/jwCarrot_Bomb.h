#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class Carrot_Bomb : public GameObject
	{
	public:
		Carrot_Bomb();
		Carrot_Bomb(Cuphead* cuphead);
		~Carrot_Bomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void AnimCompleteEvent();

		void SetDegree(float degree) { mDegree = degree; }

	private:
		Animator* mAnimator;
		Cuphead* mCuphead;
		eLayerType mLayerType;

		int mHp;

		float mTime;
		float mSpeed;
		float mDegree;
		bool mbDeadChecker;
		bool mbOnHit;
		float OnHitChecker;
	};
}

