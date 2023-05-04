#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Collider;
	class Sound;
	class Veggie_Potato : public GameObject
	{
	public:
		enum class eVeggie_PotatoState
		{
			Idle,
			Attack,
			OnHit,
			Death,
			Leave,
		};


		Veggie_Potato();
		~Veggie_Potato();

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
		void leave();

		void IntroAnimCompleteEvent();
		void Attack2AnimStartEvent();
		void Attack1AnimCompleteEvent();
		void Attack2AnimCompleteEvent();
		void LeaveAnimCompleteEvent();

		void SetShow(bool show) { mbShow = show; }

		eVeggie_PotatoState GetPotatoState() { return mPotatoState; }

		bool GetIsBossOut() { return mBossOut; }


	private:
		Animator* mPotatoAnimator;
		Collider* mPotatoCollider;

		Sound* mAtkSound;
		Sound* mDeathSound;

		eVeggie_PotatoState mPotatoState;

		bool mbShow;
		bool mbOnHit;
		float OnHitChecker;


		int mPotatoHp;
		int mAttackCnt;
		float mAttackTimeChecker;
		float mShootTimerChecker;
		float mDeathEffectTimer;
		float mLeaveTimer;
		bool mbAttacking;
		bool mPotatoDead;
		bool mBossOut;

	};
}