#pragma once
#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Pirate_BG_Sky : public GameObject
	{
	public:
		Pirate_BG_Sky();
		~Pirate_BG_Sky();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		Vector2 scale;
	};
}

