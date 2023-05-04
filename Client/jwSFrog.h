#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class Sound;
	class SFrog : public GameObject
	{
	public:
		enum class eSFrogState
		{
			Intro,
			Idle,
			Roll,
			Attack_Fist,
			Attack_Clap,
			OnHit,
			Death,
		};

		SFrog();
		SFrog(Cuphead* cuphead, int* pBossHp);
		~SFrog();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void idle();
		void roll();
		void attack_fist();
		void attack_clap();
		void onhit();
		void death();

		void IntroAnimCompleteEvent();
		void FistReady1AnimCompleteEvent();
		void FistReady2AnimCompleteEvent();
		void FistEndAnimCompleteEvent();
		void RollAnimCompleteEvent();
		void RollEndAnimCompleteEvent();
		void Roll_LAnimCompleteEvent();
		void ClapAEndAnimCompleteEvent();
		void ClapBEndAnimCompleteEvent();
		void ClapCEndAnimCompleteEvent();
		void ClapDEndAnimCompleteEvent();


		void SetShow(bool show) { mbShow = show; }

		eSFrogState GetSFrogState() { return mSFrogState; }
		bool GetIsAttacking() { return mbAttacking; }
		void SetSFrogState(eSFrogState state) { mSFrogState = state; }

		bool GetIsBossOut() { return mBossOut; }

		bool GetisFistOn() { return mbFistOn; }
		void SetbFistOn(bool on) { mbFistOn = on; }
		bool GetisFireFlyOn() { return mbFireFlyOn; }
		void SetbFireFlyOn(bool on) { mbFireFlyOn = on; }
		bool GetRollOn() { return mbRollOn; }
		void SetRollOn(bool on) { mbRollOn = on; }
		bool GetFanOn() { return mbFanOn; }
		void SetFanOn(bool on) { mbFanOn = on; }

	private:
		Sound* mfistatkSound;
		Sound* mFistFireballSound;
		Sound* mRollingStartSound;
		Sound* mRollingLoopSound;
		Sound* mRollingCrashSound;
		Sound* mRollingEndSound;
		Sound* mClapAtkSound;

		Animator* mSFrogAnimator;
		Collider* mSFrogCollider;
		Cuphead* mCuphead;
		
		eSFrogState mSFrogState;


		bool mbShow;
		bool mbOnHit;
		bool mbFistOn;
		bool mbFireFlyOn;
		bool mbRollOn;
		bool mbFirstclap;
		bool mbFanOn;

		float OnHitChecker;

		int* mSFrogHp;
		int mFistAtkCnt;
		int mClapAtkCnt;

		float mAtakTimer;
		float mFistAtkTimer;
		float mClapAtkTimer;
		float mDeathEffectTimer;
		float mLeaveTimer;

		bool mbAttacking;
		bool mSFrogDead;
		bool mBossOut;

	};

};

