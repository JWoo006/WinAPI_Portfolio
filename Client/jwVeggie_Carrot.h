#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class Veggie_Carrot : public GameObject
	{
	public:
		enum class eVeggie_CarrotState
		{
			Idle,
			Attack1,
			Attack2,
			OnHit,
			Death,
		};

		Veggie_Carrot();
		Veggie_Carrot(Cuphead* cuphead);
		~Veggie_Carrot();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void idle();
		void attack1();
		void attack2();
		void onhit();
		void death();

		void IntroAnimCompleteEvent();
		void Hypno_ReadyAnimCompleteEvent();
		void Hypno_Ready_RAnimCompleteEvent();
		
		void SetShow(bool show) { mbShow = show; }

		eVeggie_CarrotState GetPotatoState() { return mCarrotState; }

		bool GetIsBossOut() { return mBossOut; }


	private:
		Animator* mCarrotAnimator;
		Collider* mCarrotCollider;
		Cuphead* mCuphead;

		eVeggie_CarrotState mCarrotState;

		class CarrotHypno_Eye* mHypno_eye;
		
		bool mbShow;
		bool mbOnHit;
		float OnHitChecker;

		int mCarrotHp;
		int mCarrotBombCnt;
		int mHypnoDelayCnt;
		int mHypnoCnt;

		float mCarrot_bombTimer;
		float mHypno_attackTimer;
		int mHypno_attackCnt;

		float mAttackTimeChecker;
		float mShootTimerChecker;
		float mDeathEffectTimer;
		float mLeaveTimer;

		bool mbAttacking;
		bool mCarrotDead;
		bool mBossOut;

	};
}

