#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Rigidbody;
	class Animator;
	class PeashotSpark;
	class Collider;
	class Cuphead : public GameObject
	{
	public:
		enum class eCupheadState
		{
			Move_L				,
			Move_R				,
			Jump_L				,
			Jump_R				,
			Duck_L				,
			Duck_R				,
			Duck_Shoot_L		,
			Duck_Shoot_R		,
			Dash_Ground_L		,
			Dash_Ground_R		,
			Dash_Air_L			,
			Dash_Air_R			,
			Parry_L				,
			Parry_R				,
			Aim_UP_L			,
			Aim_UP_R			,
			Shoot_L				,
			Shoot_R				,
			Shoot_UP_L			,
			Shoot_UP_R			,
			Shoot_Run_L			,
			Shoot_Run_R			,
			Shoot_Run_diag_Up_L	,
			Shoot_Run_diag_Up_R	,
			Shoot_Jump_L		,
			Shoot_Jump_R		,
			Shoot_Jump_Up_L		,
			Shoot_Jump_Up_R		,
			Shoot_Jump_diag_Up_L,
			Shoot_Jump_diag_Up_R,
			OnHit_L				,
			OnHit_R				,
			Death				,
			Idle_L				,
			Idle_R				,

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
		void jump();
		void duck();
		void dash();
		void parry();
		void aim_up();
		void shoot();
		void shoot_run();
		void shoot_duck();
		void shoot_up();
		void shoot_run_diag_up();
		void shoot_jump();
		void shoot_jump_up();
		void shoot_jump_diag_up();
		void Onhit();
		void death();

		void idleCompleteEvent();
		void duckLCompleteEvent();
		void duckRCompleteEvent();
		void parryStartEvent();
		void parryCompleteEvent();
		void OnhitCompleteEvent();

		void SetJumpCount(int cnt) { mJumpCount = cnt; }
		void SetGroundCheck(bool check) { mbGroundCheck = check; }
		void GroundInit();

		
		eCupheadState GetCupheadState() { return mState; }

		bool GetIsInvincibile() { return mbInvincibile; }
		void SetInvincibile(bool invin) { mbInvincibile = invin; }

		bool GetIsParrySucess() { return mbParrySuccess; }

	private:
		eCupheadState mState;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		PeashotSpark* spark;
		Collider* collider;
		float mSecond;
		float mDashTime;
		float mFiredelay;
		int mJumpCount;
		int mAirDashCount;
		int mParryCount;
		bool mbGroundCheck;
		bool mbDashEnd;
		bool mbParrying;
		bool mbParrySuccess;
		float mJumpScale;
		bool mbInvincibile;
		float mInvincibileTime;
		bool mbFlashCheck;
		float mFlashTime;
		

	};
}



