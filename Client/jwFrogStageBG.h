#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class FrogStageBG : public GameObject
	{
	public:
		FrogStageBG();
		~FrogStageBG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		Vector2 scale;
	};
}
