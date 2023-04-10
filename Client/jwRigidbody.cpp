#include "jwRigidbody.h"
#include "jwTime.h"
#include "jwGameObject.h"
#include "jwTransform.h"

namespace jw
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(0.0f)
		, mForce(Vector2::Zero)
		, mAccelation(Vector2::Zero)
		, mVelocity(Vector2::Zero)
	{
		mLimitedVelocity.x = 200.0f;
		mLimitedVelocity.y = 3000000.f;
		mbGround = false;
		mGravity = Vector2(0.0f, 5000.0f);
		mFriction = 100.0f;
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initialize()
	{
	}
	void Rigidbody::Update()
	{
		// F = M * A
		// A = M / F
		mAccelation = mForce / mMass;

		// �ӵ��� ���ӵ��� �����ش�
		mVelocity += mAccelation * Time::DeltaTime();

		

		if (mbGround)
		{
			// ���鿡 ������
			Vector2 gravity = mGravity;
			gravity.Normalize(); // ���⸸ ����

			// ����� ��Ż�濡�� �̲������Բ� ����
			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else if(!mbGround)
		{
			// ���߿� �� ������
			mVelocity += mGravity * Time::DeltaTime();
		}
		

		//// �߷°��ӵ� �ִ� �ӵ� ����
		//Vector2 gravity = mGravity;
		//gravity.Normalize();
		//float dot = math::Dot(mVelocity, gravity);
		//gravity = gravity * dot;

		//Vector2 sideVelocity = mVelocity - gravity;
		//if (mLimitedVelocity.y < gravity.Length())
		//{
		//	gravity.Normalize();
		//	gravity *= mLimitedVelocity.y;
		//}

		//// ���� ���ӵ� �ִ� �ӵ� ����
		//if (mLimitedVelocity.x < sideVelocity.Length())
		//{
		//	sideVelocity.Normalize();
		//	sideVelocity *= mLimitedVelocity.y;
		//}

		//// ������
		//// ����� ���� ���� �ӵ��� 0�� �ƴҶ��� ����
		//if (!(mVelocity == Vector2::Zero))
		//{
		//	// �ӵ��� �ݴ�������� �������� ����
		//	Vector2 friction = -mVelocity;
		//	friction = friction.Normalize() * mFriction * mMass
		//		* Time::DeltaTime();

		//	// ���������� ���� �ӵ����Ұ� ���� �ӵ����� Ŭ ��
		//	if (mVelocity.Length() < friction.Length())
		//	{
		//		mVelocity = Vector2::Zero;
		//	}
		//	else
		//	{
		//		mVelocity += friction;
		//	}
		//}

		// ��ü�� �ӵ��� �°Բ� �̵�
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = pos + mVelocity * Time::DeltaTime();
		tr->SetPos(pos);
		mForce.Clear();

	}
	void Rigidbody::Render(HDC hdc)
	{
	}
	void Rigidbody::Release()
	{
	}
	void Rigidbody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}