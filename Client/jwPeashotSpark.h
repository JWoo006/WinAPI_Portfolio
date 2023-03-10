#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class PeashotSpark : public GameObject
	{
	public:
	
		PeashotSpark();
		~PeashotSpark();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SparkCompleteEvent();

	private:
		Animator* mAnimator;

	};
}


