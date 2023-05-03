#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Animator;
	class Ship_B_Uvula : public GameObject
	{
	public:
		enum class eUvulaState
		{
			Idle,
			Attack,
			Death,
		};

		Ship_B_Uvula();
		~Ship_B_Uvula();

		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void idle();
		void attack();
		void death();

		void Shoot_A_AnimCompleteEvent();
		void Shoot_B_AnimCompleteEvent();

		void SetShow(bool show) { mbShow = show; }
		bool GetisShow() { return mbShow; }

		eUvulaState GetShip_B_State() { return mUvulaState; }
		void SetShip_B_State(eUvulaState state) { mUvulaState = state; }

		bool GetIsShootBubble() { return mbShootBubble; }
		void SetIsShootBubble(bool isshoot) { mbShootBubble = isshoot; }

	private:
		Animator* mAnimator;

		eUvulaState mUvulaState;

		bool mbShow;

		class Bubble_Bullet* mBubble;
		bool mbShootBubble;
	};
}

