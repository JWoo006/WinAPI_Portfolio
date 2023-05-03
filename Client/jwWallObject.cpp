#include "jwWallObject.h"
#include "jwCollider.h"
#include "jwCuphead.h"
#include "jwRigidbody.h"
#include "jwTransform.h"

namespace jw
{
	WallObject::WallObject()
	{
	}
	WallObject::~WallObject()
	{
	}
	void WallObject::Initialize()
	{
		GameObject::Initialize();

		mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-90.0f, -260.0f));
		mCollider->SetSize(Vector2(180.0f, 650.0f));


	}
	void WallObject::Update()
	{
		GameObject::Update();
	}
	void WallObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void WallObject::Release()
	{
	}
	void WallObject::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		Rigidbody* rb = cuphead->GetComponent<Rigidbody>();
		
		cuphead->SetRightSpeed(0.0f);

		Collider* cupheadCol = cuphead->GetComponent<Collider>();
		Vector2 cupheadPos = cupheadCol->GetPos();

		Collider* groundCol = this->GetComponent<Collider>();
		Vector2 groundPos = groundCol->GetPos();

		float fLen = fabs(cupheadPos.y - groundPos.y);
		float fSize = (cupheadCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

		Transform* cupTr = cuphead->GetComponent<Transform>();
		Transform* grTr = this->GetComponent<Transform>();

		Vector2 cupPos = cupTr->GetPos();
		Vector2 grPos = grTr->GetPos();

		Vector2 collPos = mCollider->GetPos();

		//cupTr->SetPos(Vector2(cupPos.x, collPos.y));
		//cupTr->SetPos(Vector2(collPos.x, cupPos.y));

		/*float fLen = fabs(cupheadPos.y - groundPos.y);
		float fSize = (cupheadCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

		if (fLen < fSize)
		{
			Transform* cupTr = cuphead->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();

			Vector2 cupPos = cupTr->GetPos();
			Vector2 grPos = grTr->GetPos();

			cupPos -= (fSize - fLen) - 1.0f;
			cupTr->SetPos(cupPos);
		}*/
	}
	void WallObject::OnCollisionStay(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		Rigidbody* rb = cuphead->GetComponent<Rigidbody>();

		cuphead->SetRightSpeed(0.0f);
	}
	void WallObject::OnCollisionExit(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		Rigidbody* rb = cuphead->GetComponent<Rigidbody>();

		cuphead->SetRightSpeed(400.0f);
	}
}
