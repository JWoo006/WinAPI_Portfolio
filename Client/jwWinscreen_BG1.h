#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Winscreen_BG1 : public GameObject
	{
	public:
		Winscreen_BG1();
		~Winscreen_BG1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		Vector2 scale;
	};
}

