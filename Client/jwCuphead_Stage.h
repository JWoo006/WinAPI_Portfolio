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
		// �Լ����� �ҹ��ڷ� �����ϴ°� private�� ���������ڷ� ����
		void move();
		void shoot();
		void death();
		void idle();

	private:
		eCupheadState mState;
		Animator* mAnimator;
		
	};
}

