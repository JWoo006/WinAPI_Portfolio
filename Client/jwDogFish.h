#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class DogFish : public GameObject
	{
	public:
		enum class eDogFishState
		{
			Intro,
			Move,
			Death,
		};

		DogFish();
		~DogFish();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void intro();
		void move();
		void death();

		void SetDegree(float degree) { mDegree = degree; }

		void IntroAnimCompleteEvent();
		void IntroBAnimCompleteEvent();

	private:
		Animator* mAnimator;
		eLayerType mLayerType;
		float mTime;
		float mSpeed;
		float mDegree;

		eDogFishState mDogFishState;
		float mUpTime;
		bool mbDead;
	};
}

