#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Barrel_Fx : public GameObject
	{
	public:
		Barrel_Fx();
		~Barrel_Fx();

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

