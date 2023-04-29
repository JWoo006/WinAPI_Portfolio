#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class FrogWorldIcon : public GameObject
	{
	public:

		FrogWorldIcon();
		~FrogWorldIcon();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		eSceneType GetLoadSceneType() { return mLoadSceneType; }


	private:
		Animator* mAnimator;
		eSceneType mLoadSceneType;

	};
}