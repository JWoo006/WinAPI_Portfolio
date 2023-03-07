#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class TitleAnim2 : public GameObject
	{
	public:
		TitleAnim2();
		~TitleAnim2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Animator* mAnimator;

	};
}

