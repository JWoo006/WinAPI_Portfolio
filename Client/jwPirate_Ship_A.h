#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class Pirate_Ship_A : public GameObject
	{
	public:
		enum class ePirate_Ship_A_State
		{
			Intro,
			Idle,
			Attack,
			OnHit,
			Death,
		};

		Pirate_Ship_A();
		Pirate_Ship_A(Cuphead* cuphead, int* pBossHp);
		~Pirate_Ship_A();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void idle();
		void attack();
		void onhit();
		void death();

		void IntroAnimCompleteEvent();
		void canonballAnimCompleteEvent();
		void canonballBAnimCompleteEvent();
		void WinceAnimCompleteEvent();
		void TransformAnimCompleteEvent();

		void SetShow(bool show) { mbShow = show; }

		ePirate_Ship_A_State GetSFrogState() { return mShipState; }
		bool GetIsAttacking() { return mbAttacking; }
		void SetSFrogState(ePirate_Ship_A_State state) { mShipState = state; }

		bool GetIsBossOut() { return mBossOut; }
		void SetBossOut(bool on) { mBossOut = on; }
		bool GetIsBossLeave() { return mBossLeave; }
		void SetBossLeave(bool on) { mBossLeave = on; }

	private:
		Animator* mShipAnimator;
		Collider* mShipCollider;
		Cuphead* mCuphead;

		ePirate_Ship_A_State mShipState;


		bool mbShow;
		bool mbOnHit;
		float OnHitChecker;
		float mDeathEffectTimer;
		float mLeaveTimer;
		bool mBossOut;
		bool mBossLeave;
		bool mBossDead;

		int* mShipHp;

		bool mbAttacking;
		float mAtakTimer;

		
		

	};

};
