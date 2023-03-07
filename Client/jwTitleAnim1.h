#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class TitleAnim1 : public GameObject
	{
	public:
		TitleAnim1();
		~TitleAnim1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Animator* mAnimator;

	};
}
