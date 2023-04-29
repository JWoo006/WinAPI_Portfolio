#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Image;
	class Cuphead_Stage : public GameObject
	{
	public:
		enum class eCupheadState
		{
			Down_idle,
			Down_walk,
			Up_idle,
			Up_walk,
			Side_idle_L,
			Side_idle_R,
			Side_walk_L,
			Side_walk_R,
			diag_down_idle_L,
			diag_down_idle_R,
			diag_down_walk_L,
			diag_down_walk_R,
			diag_up_idle_L,
			diag_up_idle_R,
			diag_up_walk_L,
			diag_up_walk_R,
		};

		Cuphead_Stage();
		~Cuphead_Stage();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		bool GetIsShowIcon() { return mbShowIcon; }
		std::wstring GetIconName() { return mIconName; }

	private:
		// 함수명이 소문자로 시작하는건 private의 접근지정자로 구분
		void move();
		void idle();

	private:
		eCupheadState mState;
		Animator* mAnimator;
		Image* mImage;
		std::wstring mIconName;
		bool mbShowIcon;
	};
}

