#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class TFrog_Firefly : public GameObject
	{
	public:
		enum class eFireFlyState
		{
			Idle,
			Move,
			Attack,
			Death,
		};

		TFrog_Firefly();
		TFrog_Firefly(Cuphead* cuphead, Vector2 dest);
		~TFrog_Firefly();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void idle();
		void move();
		void attack();
		void death();

		void AnimCompleteEvent();

		void SetDegree(float degree) { mDegree = degree; }

	private:
		Animator* mAnimator;
		eLayerType mLayerType;
		eFireFlyState mFireFlyState;
		Cuphead* mCuphead;
		class Collider* collider;
		Vector2 mDestPos;
		bool mbDeadChecker;
		float mTime;
		float mSpeed;
		float mDegree;
		int mAttackCnt;
	};
}

