#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class SFrog_Clapball : public GameObject
	{
	public:
		SFrog_Clapball();
		SFrog_Clapball(int attackCnt);
		~SFrog_Clapball();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetDegree(float degree) { mDegree = degree; }

	private:
		Animator* mAnimator;
		eLayerType mLayerType;
		bool mbChanged;
		float mTime;
		float mSpeed;
		float mDegree;
		int mAttackCnt;
	};
}
