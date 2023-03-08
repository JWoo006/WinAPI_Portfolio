#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Background : public GameObject
	{
	public:
		Background();
		~Background();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		Image* mSkyImage;
		Vector2 scale;

	};
}



