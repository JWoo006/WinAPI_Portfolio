#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class PotatoAttackEffect : public GameObject
	{
	public:
		PotatoAttackEffect();
		~PotatoAttackEffect();

		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void AnimCompleteEvent();

		void SetShow(bool show) { mbShow = show; }
		bool GetisShow() { return mbShow; }

	private:
		Animator* mAnimator;
		bool mbShow;
	};
}
