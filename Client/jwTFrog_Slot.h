#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Transform;
	class Cuphead;
	class Slot_Pic;
	class Sound;
	class TFrog_Slot : public GameObject
	{
	public:
		enum class eTFrog_SlotState
		{
			Intro,
			Idle,
			Slotlever,
			SlotRoll,
			Attack_Coin,
			Attack_Snake,
			Attack_Fire,
			OnHit,
			Death,
		};

		TFrog_Slot();
		TFrog_Slot(Cuphead* cuphead, int* pBossHp);
		~TFrog_Slot();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void idle();
		void slotlever();
		void slotroll();
		void attack_coin();
		void attack_snake();
		void attack_fire();
		void onhit();
		void death();

		void IntroAnimCompleteEvent();
		void LeverStartAnimCompleteEvent();
		void LeverBackAnimCompleteEvent();
		void AttackStartAnimCompleteEvent();
		


		void SetShow(bool show) { mbShow = show; }

		eTFrog_SlotState GetTFrog_SlotState() { return mTFrog_SlotState; }
		bool GetIsAttacking() { return mbAttacking; }
		void SetTFrog_SlotState(eTFrog_SlotState state) { mTFrog_SlotState = state; }

		bool GetIsBossOut() { return mBossOut; }

		bool GetLeverOn() { return mbLeverOn; }
		void SetLeverOn(bool on) { mbLeverOn = on; }

		

	private:
		Sound* mDeathSound;
		Sound* mSpitSound;
		Sound* mLeverDownSound;
		Sound* mSlotRollSound;
		Sound* mSlotRollEndSound;
		Sound* mPlatformSound;

		Animator* mTFrog_SlotAnimator;
		Collider* mTFrog_SlotCollider;
		Transform* mTransform;
		Vector2 mPos;
		Cuphead* mCuphead;
		eTFrog_SlotState mTFrog_SlotState;
		
		

		Slot_Pic* mSlot_Pic1;
		Transform* mSPic1_Tr;
		Vector2 mSPic1_Pos;

		Slot_Pic* mSlot_Pic2;
		Transform* mSPic2_Tr;
		Vector2 mSPic2_Pos;

		Slot_Pic* mSlot_Pic3;
		Transform* mSPic3_Tr;
		Vector2 mSPic3_Pos;

		bool mbShow;
		bool mbOnHit;
		float OnHitChecker;
		float mDeathEffectTimer;
		float mLeaveTimer;
		
		int* mTFrog_SlotHp;
		float mAtkTimer;

		bool mbAttacking;
		bool mTFrog_SlotDead;
		bool mBossOut;


		float mSpitAtkTimer;
		float mRollTimer;
		float mSnakeAtkTimer;
		int mSnakeAtkCnt;
		float mFireAtkTimer;
		int mFireAtkCnt;
		bool mbLeverParryOn;
		bool mbLeverOn;
		bool mbSnakeOn;
		bool mbFireOn;


	};

};
