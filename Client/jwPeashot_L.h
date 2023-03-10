#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Peashot_L : public GameObject
	{
	public:
		enum class eBulletDirection
		{
			UP,
			LEFT,
			RIGHT,
		};

		Peashot_L();
		~Peashot_L();

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

