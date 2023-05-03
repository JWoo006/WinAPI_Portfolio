#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Cuphead;
	class Octopus_Bullet : public GameObject
	{
	public:
		Octopus_Bullet();
		Octopus_Bullet(Cuphead* cuphead);
		~Octopus_Bullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void idle();
		void move();
		void attack();
		void death();

		void YellowAnimCompleteEvent();
		void PinkAnimCompleteEvent();

		void SetDegree(float degree) { mDegree = degree; }

	private:
		Animator* mAnimator;
		eLayerType mLayerType;
		Cuphead* mCuphead;
		class Collider* collider;
		Vector2 mDestPos;
		bool mbDeadChecker;
		float mTime;
		float mSpeed;
		float mDegree;

		int mFlag;
	};
}

