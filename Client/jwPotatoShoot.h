#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class PotatoShoot : public GameObject
	{
	public:
		PotatoShoot();
		PotatoShoot(int attackCnt);
		~PotatoShoot();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void AnimCompleteEvent();

		void SetDegree(float degree) { mDegree = degree; }

	private:
		Animator* mAnimator;
		eLayerType mLayerType;
		float mTime;
		float mSpeed;
		float mDegree;
		int mAttackCnt;
	};
}
