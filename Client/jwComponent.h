#pragma once
#include "jwEntity.h"

namespace jw
{
	class Component : public Entity
	{
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:

	};
}
