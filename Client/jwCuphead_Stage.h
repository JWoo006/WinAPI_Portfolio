#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Cuphead_Stage : public GameObject
	{
	public:
		enum class eCupheadState
		{
			Move,
			Shoot,
			Death,
			Idle,
		};

		Cuphead_Stage();
		~Cuphead_Stage();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		// 함수명이 소문자로 시작하는건 private의 접근지정자로 구분
		void move();
		void shoot();
		void death();
		void idle();

	private:
		eCupheadState mState;
		Animator* mAnimator;
		
	};
}

