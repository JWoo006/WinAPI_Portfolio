#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class ParryEffect : public GameObject
	{
	public:
		ParryEffect();
		~ParryEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void AnimCompleteEvent();

	private:
		Animator* mAnimator;

	};
}

