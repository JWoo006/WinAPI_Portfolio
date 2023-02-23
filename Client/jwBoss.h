#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Boss : public GameObject
	{
	public:
		Boss();
		~Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;

	};
}


