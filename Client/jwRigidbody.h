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

	private:
		float mMass; // 질량 
		Vector2 mForce; // 오브젝트를 움직일 힘
		Vector2 mAccelation; // 가속도
		Vector2 mVelocity; // 속도

	};

}


