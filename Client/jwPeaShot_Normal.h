#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class PeaShot_Normal : public GameObject
	{
	public:
		enum class eBulletDirection
		{
			UP,
			LEFT,
			RIGHT,
		};

		PeaShot_Normal();
		PeaShot_Normal(Cuphead::eCupheadState state);
		~PeaShot_Normal();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		float GetDelay() { return mDelay; }

		void SetDegree(float degree) { mDegree = degree; }
		void SetState(eBulletDirection state) { mBulletdirection = state; }

	private:
		float mDelay;
		float mTime;
		float mDegree;
		Animator* mAnimator;
		eBulletDirection mBulletdirection;
		Cuphead::eCupheadState mCupheadState;

	};
}

