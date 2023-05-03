#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class Pirate_Captain : public GameObject
	{
	public:
		enum class ePirate_Captain_State
		{
			Intro,
			Idle,
			Attack_Octopus,
			Attack_Whistle,
			OnHit,
			Death,
		};

		Pirate_Captain();
		Pirate_Captain(Cuphead* cuphead, int* pBossHp);
		~Pirate_Captain();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void intro();
		void idle();
		void attack();
		void attack_octopus();
		void attack_whistle();
		void onhit();
		void death();

		void IntroStartAnimCompleteEvent();
		void IntroEndAnimCompleteEvent();
		void octo_pickAnimCompleteEvent();
		void octo_shootAnimCompleteEvent();
		void octo_downAnimCompleteEvent();
		void whitsleAnimCompleteEvent();
		void whitsle_B_AnimCompleteEvent();

		void SetShow(bool show) { mbShow = show; }

		ePirate_Captain_State GetSFrogState() { return mCaptainState; }
		bool GetIsAttacking() { return mbAttacking; }
		void SetSFrogState(ePirate_Captain_State state) { mCaptainState = state; }

		bool GetIsBossOut() { return mBossOut; }

	private:
		Animator* mCaptainAnimator;
		Collider* mCaptainCollider;
		class Transform* mCaptainTr;
		Vector2 mCaptainPos;
		Cuphead* mCuphead;

		ePirate_Captain_State mCaptainState;


		bool mbShow;
		bool mbOnHit;
		float OnHitChecker;
		float mDeathEffectTimer;
		float mLeaveTimer;
		bool mBossOut;
		bool mBossDead;

		int* mCaptainHp;

		bool mbAttacking;
		float mAtkTimer;

		int mOctoAtkCnt;
		int mOctoBulletCnt;
		bool mbOctoFire;
		bool mbOctoAtkEnd;
		float mOctoAtkTimer;

		bool mbScopeOut;
		float mScopeTimer;
		float mDogAtkTimer;
		int mDogAtkCnt;





	};

};
