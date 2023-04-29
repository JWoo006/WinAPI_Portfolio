#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Slot_FireFlame : public GameObject
	{
	public:

		Slot_FireFlame();
		Slot_FireFlame(int flag);
		~Slot_FireFlame();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Flame_bAnimCompleteEvent();
		void Flame_b_DownAnimCompleteEvent();

		bool Getmbon() { return mbon; }

	private:
		Animator* mAnimator;
		eLayerType mLayerType;
		class Collider* collider;
		float mFlameTimer;
		float mTime;
		bool mbon;
		int mFlag;
		
	};
}


