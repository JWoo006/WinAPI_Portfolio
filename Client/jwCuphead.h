#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class PeashotSpark;
	class Cuphead : public GameObject
	{
	public:
		enum class eCupheadState
		{
			Move,
			Shoot,
			Death,
			Idle,
		};
		Cuphead();
		~Cuphead();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void move();
		void shoot();
		void death();
		void idle();

		void idleCompleteEvent();

	private:
		eCupheadState mState;
		Animator* mAnimator;
		PeashotSpark* spark;
		float mSecond;
		float mFiredelay;

	};
}



