#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class Collider;
	class Lazar : public GameObject
	{
	public:
		enum class eLazarState
		{
			Start,
			Loop,
			End,
		};

		Lazar();
		~Lazar();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void start();
		void loop();
		void end();

		void StartAnimCompleteEvent();
		void EndAnimCompleteEvent();

		void SetLazarAtkEnd(bool end) { mAtkEnd = end; }
		bool GetLazarAtkEnd() { return mAtkEnd; }

	private:
		Animator* mAnimator;
		Collider* mCollider;
		eLayerType mLayerType;

		eLazarState mLazarState;
		bool mAtkEnd;
		bool mbDead;
	};
}


