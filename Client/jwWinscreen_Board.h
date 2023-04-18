#pragma once
#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Winscreen_Board : public GameObject
	{
	public:
		Winscreen_Board();
		~Winscreen_Board();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		Vector2 scale;
	};
}
