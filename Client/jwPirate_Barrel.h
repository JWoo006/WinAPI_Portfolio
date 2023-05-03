#pragma once
#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class Transform;
	class Pirate_Barrel : public GameObject
	{
	public:
		enum class ePirate_Barrel_State
		{
			Intro,
			Idle,
			Safe,
			Attack,
			Smash,
			Up,
			OnHit,
			Death,
		};

		Pirate_Barrel();
		Pirate_Barrel(Cuphead* cuphead, int* pBossHp);
		~Pirate_Barrel();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void idle();
		void safe();
		void attack();
		void Smash();
		void up();
		void onhit();
		void death();

		void IntroAnimCompleteEvent();
		void DropAnimCompleteEvent();
		void SmashAnimCompleteEvent();
		void UpAnimCompleteEvent();

		void SetShow(bool show) { mbShow = show; }

		ePirate_Barrel_State GetBarrelState() { return mBarrelState; }
		bool GetIsAttacking() { return mbAttacking; }
		void SetBarrelState(ePirate_Barrel_State state) { mBarrelState = state; }

		bool GetIsBossOut() { return mBossOut; }

	private:
		Animator* mBarrelAnimator;
		Collider* mBarrelCollider;
		Transform* mBarrelTr;
		Vector2 mBarrelPos;
		Cuphead* mCuphead;

		ePirate_Barrel_State mBarrelState;


		bool mbShow;
		bool mbOnHit;
		float OnHitChecker;
		float mDeathEffectTimer;
		float mLeaveTimer;
		bool mBossOut;
		bool mBossDead;

		int mBarrelDir;

		int* mBossHp;

		bool mbAttacking;
		float mAtakTimer;




	};

};
