#pragma once
#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class Sound;
	class Pirate_Ship_B : public GameObject
	{
	public:
		enum class ePirate_Ship_B_State
		{
			Intro,
			Idle,
			Attack_Lazar,
			Attack_Bubble,
			OnHit,
			Death,
		};

		Pirate_Ship_B();
		Pirate_Ship_B(Cuphead* cuphead, int* pBossHp);
		~Pirate_Ship_B();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void idle();
		void attack_lazar();
		void attack_bubble();
		void onhit();
		void death();

		void IntroAnimCompleteEvent();
		void ChargeStartAnimCompleteEvent();
		void ChargeEndAnimCompleteEvent();

		void SetShow(bool show) { mbShow = show; }

		ePirate_Ship_B_State GetShip_B_State() { return mShipBState; }
		bool GetIsAttacking() { return mbAttacking; }
		void SetShip_B_State(ePirate_Ship_B_State state) { mShipBState = state; }

		bool GetIsBossOut() { return mBossOut; }


	private:
		Sound* mDeathSound;
		Sound* mBubbleShotSound;
		Sound* mLazarSound;

		Animator* mShipBAnimator;
		Collider* mShipBCollider;
		Cuphead* mCuphead;

		class Ship_B_jaw* mJaw;
		class Ship_B_Uvula* mUvula;
		Animator* mUvulaAnimator;

		class Lazar* mLazar;

		ePirate_Ship_B_State mShipBState;


		bool mbShow;
		bool mbOnHit;
		float OnHitChecker;
		float mDeathEffectTimer;
		float mLeaveTimer;
		bool mBossOut;
		bool mBossDead;

		int* mShipHp;

		bool mbAttacking;
		float mAtkTimer;

		float mBubbleAtkTimer;
		int mBubbleAtkCnt;

		float mLazarAtkTimer;
		bool mbLazarFire;


	};

};


