#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class TitleBG2 : public GameObject
	{
	public:
		TitleBG2();
		~TitleBG2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
	};
}

