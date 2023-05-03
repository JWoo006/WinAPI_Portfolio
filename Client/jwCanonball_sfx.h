#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Canonball_sfx : public GameObject
	{
	public:
		Canonball_sfx();
		~Canonball_sfx();

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

