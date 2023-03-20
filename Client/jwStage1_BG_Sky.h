#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Stage1_BG_Sky : public GameObject
	{
	public:
		Stage1_BG_Sky();
		~Stage1_BG_Sky();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		Image* mImage;
		Vector2 scale;
	};
}

