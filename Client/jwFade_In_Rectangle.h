#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Fade_In_Rectangle : public GameObject
	{
	public:

		Fade_In_Rectangle();
		~Fade_In_Rectangle();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetEnd(bool end);

	private:
		Image* mImage;
		Vector2 scale;
		bool isEnd;
		int mAlpha;
		float mTime;

	};
}
