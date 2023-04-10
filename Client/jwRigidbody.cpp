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

		// 속도에 가속도를 더해준다
		mVelocity += mAccelation * Time::DeltaTime();

		

		if (mbGround)
		{
			// 지면에 있을시
			Vector2 gravity = mGravity;
			gravity.Normalize(); // 방향만 구함

			// 경사진 빗탈길에서 미끄러지게끔 구현
			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else if(!mbGround)
		{
			// 공중에 떠 있을시
			mVelocity += mGravity * Time::DeltaTime();
		}
		

		//// 중력가속도 최대 속도 제한
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

		//// 수평 가속도 최대 속도 제한
		//if (mLimitedVelocity.x < sideVelocity.Length())
		//{
		//	sideVelocity.Normalize();
		//	sideVelocity *= mLimitedVelocity.y;
		//}

		//// 마찰력
		//// 적용된 힘이 없고 속도가 0이 아닐때만 실행
		//if (!(mVelocity == Vector2::Zero))
		//{
		//	// 속도에 반대방향으로 마찰력이 적용
		//	Vector2 friction = -mVelocity;
		//	friction = friction.Normalize() * mFriction * mMass
		//		* Time::DeltaTime();

		//	// 마찰력으로 인한 속도감소가 현재 속도보다 클 때
		//	if (mVelocity.Length() < friction.Length())
		//	{
		//		mVelocity = Vector2::Zero;
		//	}
		//	else
		//	{
		//		mVelocity += friction;
		//	}
		//}

		// 물체를 속도에 맞게끔 이동
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