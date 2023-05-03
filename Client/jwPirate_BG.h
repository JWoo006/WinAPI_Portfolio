#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Pirate_BG : public GameObject
	{
	public:
		Pirate_BG();
		~Pirate_BG();

		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		void SetShow(bool show) { mbShow = show; }
		bool GetisShow() { return mbShow; }

	private:
		Animator* mAnimator;
		bool mbShow;
	};
}
