#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class FightText_WALLOP : public GameObject
	{
	public:
		FightText_WALLOP();
		~FightText_WALLOP();

		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void AnimCompleteEvent();

	private:
		Animator* mAnimator;
	};
}
