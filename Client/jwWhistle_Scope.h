#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Whistle_Scope : public GameObject
	{
	public:
		Whistle_Scope();
		~Whistle_Scope();

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
