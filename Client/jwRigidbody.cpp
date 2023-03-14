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

		mVelocity += mAccelation * Time::DeltaTime();

		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector2 pos = tr->GetPos();
		pos += mVelocity * Time::DeltaTime();
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