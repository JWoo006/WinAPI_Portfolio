#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Winscreen_Cuphead : public GameObject
	{
	public:
		Winscreen_Cuphead();
		~Winscreen_Cuphead();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Animator* mAnimator;

	};
}

