#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Rigidbody;
	class Animator;
	class PeashotSpark;
	class Cuphead : public GameObject
	{
	public:
		enum class eCupheadState
		{
			Move_L,
			Move_R,
			Duck_L,
			Duck_R,
			Duck_Shoot_L,
			Duck_Shoot_R,
			Aim_UP_L,
			Aim_UP_R,
			Shoot_L,
			Shoot_R,
			Shoot_UP_L,
			Shoot_UP_R,
			Shoot_Run_L,
			Shoot_Run_R,
			Shoot_Run_diag_Up_L,
			Shoot_Run_diag_Up_R,
			Death,
			Idle_L,
			Idle_R,

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

		void idle();
		void move();
		void duck();
		void aim_up();
		void shoot();
		void shoot_run();
		void shoot_duck();
		void shoot_up();
		void shoot_run_diag_up();
		void death();

		void idleCompleteEvent();
		void duckLCompleteEvent();
		void duckRCompleteEvent();
		
		eCupheadState GetCupheadState() { return mState; }

	private:
		eCupheadState mState;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		PeashotSpark* spark;
		float mSecond;
		float mFiredelay;

	};
}



