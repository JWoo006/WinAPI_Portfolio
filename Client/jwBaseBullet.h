#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class BaseBullet : public GameObject
	{
	public:
		BaseBullet();
		~BaseBullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		static float GetDelay() { return mDelay; }

	private:
		static float mDelay;
		Animator* mAnimator;
	};
}



