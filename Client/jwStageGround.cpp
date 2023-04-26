#include "jwStageGround.h"
#include "jwCollider.h"
#include "jwCuphead.h"
#include "jwRigidbody.h"
#include "jwTransform.h"

namespace jw
{
	StageGround::StageGround()
	{
	}
	StageGround::~StageGround()
	{
	}
	void StageGround::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(1800.0f, 150.0f));

		GameObject::Initialize();
	}
	void StageGround::Update()
	{
		GameObject::Update();
	}
	void StageGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void StageGround::Release()
	{
	}
	void StageGround::OnCollisionEnter(Collider* other)
	{
		/*Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
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


		if (fLen < fSize)
		{
			Transform* cupTr = cuphead->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();

			Vector2 cupPos = cupTr->GetPos();
			Vector2 grPos = grTr->GetPos();

			cupPos -= (fSize - fLen) - 1.0f;
			cupTr->SetPos(cupPos);
		}*/
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

		cupTr->SetPos(Vector2(cupPos.x, grPos.y));
	}
	void StageGround::OnCollisionStay(Collider* other)
	{

	}
	void StageGround::OnCollisionExit(Collider* other)
	{
	}
}

