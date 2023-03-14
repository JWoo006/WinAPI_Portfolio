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
		float mMass; // ���� 
		Vector2 mForce; // ������Ʈ�� ������ ��
		Vector2 mAccelation; // ���ӵ�
		Vector2 mVelocity; // �ӵ�

	};

}


