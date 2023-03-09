#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class TestBullet : public GameObject
	{
	public:
		TestBullet();
		~TestBullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		static float GetDelay() { return mDelay; }

		void SetDegree(float degree) { mDegree = degree; }

	private:
		static float mDelay;
		float mTime;
		float mDegree;
		Animator* mAnimator;
		
	};
}

