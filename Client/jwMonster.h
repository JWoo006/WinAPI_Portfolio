#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Monster : public GameObject
	{
	public:
		
		Monster();
		~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		
	private:
		Animator* mAnimator;

	};
}


