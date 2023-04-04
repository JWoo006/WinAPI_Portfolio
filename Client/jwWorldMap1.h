#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class WorldMap1 : public GameObject
	{
	public:
		WorldMap1();
		~WorldMap1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
	};
}
