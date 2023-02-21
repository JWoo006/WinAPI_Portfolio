#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Cuphead : public GameObject
	{
	public:
		Cuphead();
		~Cuphead();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:

	};
}



