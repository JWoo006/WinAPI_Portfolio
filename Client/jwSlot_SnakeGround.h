#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Slot_SnakeGround : public GameObject
	{
	public:
		Slot_SnakeGround();
		~Slot_SnakeGround();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		class Collider* mCollider;
	};
}

