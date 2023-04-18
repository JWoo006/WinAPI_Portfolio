#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Winscreen_ResultAnim : public GameObject
	{
	public:
		Winscreen_ResultAnim();
		~Winscreen_ResultAnim();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Animator* mAnimator;

	};
}

