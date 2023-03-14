#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class FadeInOut : public GameObject
	{
	public:

		FadeInOut();
		~FadeInOut();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		Vector2 scale;
		bool reverse;
		bool isEnd;
		int mAlpha;
		float mTime;

	};
}

