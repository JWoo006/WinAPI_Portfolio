#include "jwGround_Veggie.h"
#include "jwCollider.h"
#include "jwCuphead.h"
#include "jwRigidbody.h"
#include "jwTransform.h"

namespace jw
{
	Ground_Veggie::Ground_Veggie()
	{
	}
	Ground_Veggie::~Ground_Veggie()
	{
	}
	void Ground_Veggie::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(1600.0f, 50.0f));

		GameObject::Initialize();
	}
	void Ground_Veggie::Update()
	{
		GameObject::Update();
	}
	void Ground_Veggie::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Ground_Veggie::Release()
	{
	}
	void Ground_Veggie::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		Rigidbody* rb = cuphead->GetComponent<Rigidbody>();
		rb->SetGround(true);

		Collider* cupheadCol = cuphead->GetComponent<Collider>();
		Vector2 cupheadPos = cupheadCol->GetPos();

		Collider* groundCol = this->GetComponent<Collider>();
		Vector2 groundPos = groundCol->GetPos();

		float fLen = fabs(cupheadPos.y - groundPos.y);
		float fSize = (cupheadCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

		if (fLen < fSize)
		{
			Transform* cupTr = cuphead->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();

			Vector2 cupPos = cupTr->GetPos();
			Vector2 grPos = grTr->GetPos();

			cupPos -= (fSize - fLen) - 1.0f;
			cupTr->SetPos(cupPos);
		}
	}
	void Ground_Veggie::OnCollisionStay(Collider* other)
	{
		
	}
	void Ground_Veggie::OnCollisionExit(Collider* other)
	{
	}
}
