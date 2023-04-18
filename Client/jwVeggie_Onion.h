#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Veggie_Onion : public GameObject
	{
	public:
		enum class eVeggie_OnionState
		{
			Idle,
			Attack,
			Attacking,
			OnHit,
			Death,
			Leave,
		};

		Veggie_Onion();
		~Veggie_Onion();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void idle();
		void attack();
		void attacking();
		void onhit();
		void death();
		void leave();

		void IntroAnimCompleteEvent();
		void CryStartAnimStartEvent();
		void CryStartAnimCompleteEvent();
		void CryingAnimStartEvent();
		void CryingAnimCompleteEvent();
		void CryEndAnimStartEvent();
		void CryEndAnimCompleteEvent();
		void LeaveAnimCompleteEvent();

		void SetShow(bool show) { mbShow = show; }

		eVeggie_OnionState GetPotatoState() { return mOnionState; }

		bool GetIsBossOut() { return mBossOut; }


	private:
		Animator* mOnionAnimator;
		Collider* mOnionCollider;

		eVeggie_OnionState mOnionState;

		class OnionTears* mOnionTearsL;
		Animator* mOnionTearsLAnimator;
		class OnionTears* mOnionTearsR;
		Animator* mOnionTearsRAnimator;

		bool mbShow;
		bool mbOnHit;
		float OnHitChecker;


		int mOnionHp;
		int mAttackCnt;

		float mCryReadyTimer;
		float mCryingTimer;

		float mAttackTimeChecker;
		float mShootTimerChecker;
		float mDeathEffectTimer;
		float mLeaveTimer;
		float mTearsTimer;

		bool mbAttacking;
		bool mOnionDead;
		bool mBossOut;

	};
}

