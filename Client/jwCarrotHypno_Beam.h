#pragma once
#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class CarrotHypno_Beam : public GameObject
	{
	public:
		CarrotHypno_Beam();
		CarrotHypno_Beam(Cuphead* cuphead);
		~CarrotHypno_Beam();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void AnimCompleteEvent();
		void Hypno_ringAnimCompleteEvent();

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


