#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class Slot_CoinBullet : public GameObject
	{
	public:
		
		Slot_CoinBullet();
		Slot_CoinBullet(Cuphead* cuphead);
		~Slot_CoinBullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetDegree(float degree) { mDegree = degree; }

	private:
		Animator* mAnimator;
		eLayerType mLayerType;
		Cuphead* mCuphead;
		class Collider* collider;
		bool mbDeadChecker;
		float mTime;
		float mSpeed;
		float mDegree;
		int mAttackCnt;
	};
}

