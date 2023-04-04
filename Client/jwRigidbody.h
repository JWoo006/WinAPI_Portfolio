#pragma once
#include "jwComponent.h"

namespace jw
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector2 force);
		void SetGround(bool ground) { mbGround = ground; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		Vector2 GetVelocity() { return mVelocity; }
		void TimeInit() { mTime = 0.0f; }

	private:
		float mMass; // 질량 
		Vector2 mForce; // 오브젝트를 움직일 힘
		Vector2 mAccelation; // 가속도
		Vector2 mVelocity; // 속도
		Vector2 mLimitedVelocity;
		Vector2 mGravity; // 중력
		float mTime;

		float mFriction; // 마찰력
		bool mbGround; // 지면에 접촉 체크

		//float mStaticFriction; // 정지 마찰력
		//float mKineticFriction; // 운동 마찰력
		//float mCoefficientFriction; // 마찰력 계수

	};

}


