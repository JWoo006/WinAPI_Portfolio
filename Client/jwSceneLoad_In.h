#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Scene;
	class SceneLoad_In : public GameObject
	{
	public:
		SceneLoad_In();
		~SceneLoad_In();

		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void AnimCompleteEvent();
		bool EndCheck() { return mbIsEnd; }
		void SetEndCheck(bool state) { mbIsEnd = state; }

	private:
		Animator* mAnimator;
		Scene* mPrevScene;
		bool mbIsEnd;
	};
}



