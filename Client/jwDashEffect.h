#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class DashEffect : public GameObject
	{
	public:
		DashEffect( eAnimationDir dir);
		~DashEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void AnimCompleteEvent();

	private:
		Animator* mAnimator;
		eAnimationDir mAnimDir;

	};
}
