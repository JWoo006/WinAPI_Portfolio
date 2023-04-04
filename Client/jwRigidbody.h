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
		float mMass; // ���� 
		Vector2 mForce; // ������Ʈ�� ������ ��
		Vector2 mAccelation; // ���ӵ�
		Vector2 mVelocity; // �ӵ�
		Vector2 mLimitedVelocity;
		Vector2 mGravity; // �߷�
		float mTime;

		float mFriction; // ������
		bool mbGround; // ���鿡 ���� üũ

		//float mStaticFriction; // ���� ������
		//float mKineticFriction; // � ������
		//float mCoefficientFriction; // ������ ���

	};

}


