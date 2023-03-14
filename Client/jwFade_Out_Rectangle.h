#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Fade_Out_Rectangle : public GameObject
	{
	public:

		Fade_Out_Rectangle();
		~Fade_Out_Rectangle();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetEnd(bool end);
		bool GetEndState() { return isEnd; }

	private:
		Image* mImage;
		Vector2 scale;
		bool isEnd;
		int mAlpha;
		float mTime;

	};
}
