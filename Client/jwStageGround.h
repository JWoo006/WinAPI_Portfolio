#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class StageGround : public GameObject
	{
	public:
		StageGround();
		~StageGround();

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
