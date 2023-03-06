#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Veggie_Onion : public GameObject
	{
	public:

		Veggie_Onion();
		~Veggie_Onion();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Animator* mAnimator;

	};
}

