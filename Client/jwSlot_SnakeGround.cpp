#include "jwSlot_SnakeGround.h"
#include "jwCollider.h"
#include "jwCuphead.h"
#include "jwRigidbody.h"
#include "jwTransform.h"

namespace jw
{
	Slot_SnakeGround::Slot_SnakeGround()
	{
	}
	Slot_SnakeGround::~Slot_SnakeGround()
	{
	}
	void Slot_SnakeGround::Initialize()
	{
		GameObject::Initialize();

		mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-90.0f, -160.0f));
		mCollider->SetSize(Vector2(180.0f, 50.0f));

		
	}
	void Slot_SnakeGround::Update()
	{
		GameObject::Update();
	}
	void Slot_SnakeGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Slot_SnakeGround::Release()
	{
	}
	void Slot_SnakeGround::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		Rigidbody* rb = cuphead->GetComponent<Rigidbody>();
		rb->SetGround(true);

		cuphead->SetGroundCheck(true);
		cuphead->SetJumpCount(1);

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

		cupTr->SetPos(Vector2(cupPos.x, collPos.y));

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
	void Slot_SnakeGround::OnCollisionStay(Collider* other)
	{

	}
	void Slot_SnakeGround::OnCollisionExit(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		Rigidbody* rb = cuphead->GetComponent<Rigidbody>();
		rb->SetGround(false);

		cuphead->SetGroundCheck(false);
		cuphead->SetJumpCount(0);
	}
}
