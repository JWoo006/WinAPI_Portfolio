#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Scene;
	class Sound;
	class Knockout : public GameObject
	{
	public:
		Knockout();
		~Knockout();

		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void AnimCompleteEvent();
		bool EndCheck() { return mbIsEnd; }
		void SetEndCheck(bool state) { mbIsEnd = state; }

	private:
		Animator* mAnimator;
		Sound* mSound;
		bool mbIsEnd;
		float mTime;
		bool mbTime;
	};
}

