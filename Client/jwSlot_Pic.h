#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Slot_Pic : public GameObject
	{
	public:
		Slot_Pic();
		~Slot_Pic();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		Vector2 scale;
	};
}


