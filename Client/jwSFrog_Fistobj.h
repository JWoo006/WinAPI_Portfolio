#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class SFrog_Fistobj : public GameObject
	{
	public:
		SFrog_Fistobj();
		SFrog_Fistobj(int attackCnt);
		~SFrog_Fistobj();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void AnimCompleteEvent();
		void n1AnimCompleteEvent();
		void p1AnimCOmpleteEvent();

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
