#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class TitleAnim3 : public GameObject
	{
	public:
		TitleAnim3();
		~TitleAnim3();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Animator* mAnimator;

	};
}

class TitleAnim3
{
};

