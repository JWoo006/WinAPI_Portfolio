#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class TitleBG : public GameObject
	{
	public:
		TitleBG();
		~TitleBG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
	};
}

