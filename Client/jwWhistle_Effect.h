#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Whistle_Effect : public GameObject
	{
	public:
		Whistle_Effect();
		~Whistle_Effect();

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

