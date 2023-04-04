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

	private:
		Animator* mAnimator;
		Scene* mPrevScene;
	};
}



