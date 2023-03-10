#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Peashot_diagnal_R : public GameObject
	{
	public:
		enum class eBulletDirection
		{
			UP,
			LEFT,
			RIGHT,
		};

		Peashot_diagnal_R();
		~Peashot_diagnal_R();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		static float GetDelay() { return mDelay; }

		void SetDegree(float degree) { mDegree = degree; }
		void SetState(eBulletDirection state) { mBulletdirection = state; }

	private:
		static float mDelay;
		float mTime;
		float mDegree;
		Animator* mAnimator;
		eBulletDirection mBulletdirection;

	};
}
