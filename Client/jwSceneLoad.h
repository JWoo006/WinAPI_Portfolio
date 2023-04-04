#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Scene;
	class SceneLoad : public GameObject
	{
	public:
		SceneLoad();
		~SceneLoad();

		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void AnimCompleteEvent();

	private:
		Animator* mAnimator;
		Scene* mPrevScene;

		eSceneType mNextScene;
	};
}



