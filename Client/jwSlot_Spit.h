#pragma once
#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class Slot_Spit : public GameObject
	{
	public:
		Slot_Spit();
		Slot_Spit(Cuphead* mcuphead);
		~Slot_Spit();

		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void AnimCompleteEvent();

		void SetShow(bool show) { mbShow = show; }
		bool GetisShow() { return mbShow; }

	private:
		Animator* mAnimator;
		Cuphead* mCuphead;
		bool mbShow;
	};
}


