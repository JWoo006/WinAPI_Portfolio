#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class TFrog : public GameObject
	{
	public:
		enum class eTFrogState
		{
			Idle,
			Attack_Firefly,
			Attack_Fan,
			OnHit,
			Death,
		};

		TFrog();
		TFrog(Cuphead* cuphead, int* pBossHp);
		~TFrog();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void idle();
		void attack_firefly();
		void attack_fan();
		void onhit();
		void death();

		void IntroAnimCompleteEvent();
		void SpitAnimCompleteEvent();


		void SetShow(bool show) { mbShow = show; }

		eTFrogState GetTFrogState() { return mTFrogState; }
		bool GetIsAttacking() { return mbAttacking; }
		void SetTFrogState(eTFrogState state) { mTFrogState = state; }

		bool GetIsBossOut() { return mBossOut; }

		bool GetisFistOn() { return mbFistOn; }
		void SetbFistOn(bool on) { mbFistOn = on; }
		bool GetisFireFlyOn() { return mbFireFlyOn; }
		void SetbFireFlyOn(bool on) { mbFireFlyOn = on; }
		bool GetRollOn() { return mbRollOn; }
		void SetRollOn(bool on) { mbRollOn = on; }


	private:
		Animator* mTFrogAnimator;
		Collider* mTFrogCollider;
		Cuphead* mCuphead;

		eTFrogState mTFrogState;


		bool mbShow;
		bool mbOnHit;
		bool mbFistOn;
		bool mbFireFlyOn;
		bool mbRollOn;

		float OnHitChecker;

		int* mTFrogHp;
		int mFireflyAtkCnt;

		float mFireFlyAtkTimer;
		float mDeathEffectTimer;
		float mLeaveTimer;

		bool mbAttacking;
		bool mTFrogDead;
		bool mBossOut;

	};

};


