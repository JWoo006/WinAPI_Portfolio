#pragma once
#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class CarrotHypno_Eye : public GameObject
	{
	public:
		CarrotHypno_Eye();
		~CarrotHypno_Eye();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;



	private:
		Animator* mAnimator;
	};
}

