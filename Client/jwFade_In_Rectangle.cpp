#include "jwFade_In_Rectangle.h"
#include "jwResources.h"
#include "jwTime.h"
#include "jwTransform.h"
#include "jwObject.h"

namespace jw
{
	Fade_In_Rectangle::Fade_In_Rectangle()
		: mAlpha(255)
		, isEnd(false)
	{
	}
	Fade_In_Rectangle::~Fade_In_Rectangle()
	{
	}
	void Fade_In_Rectangle::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		mImage = Resources::Load<Image>(L"Fade_Rect", L"..\\Resources\\Image\\Effect\\Rectangle_Black.bmp");
		tr->SetScale(Vector2(1.1f, 1.2f));
		scale = tr->GetScale();

		GameObject::Initialize();

	}
	void Fade_In_Rectangle::Update()
	{
		if (!isEnd)
		{
			mTime += Time::DeltaTime();

			if (mTime > 0.01f)
			{
				mAlpha -= 2;
			}

			if (mAlpha <= 0)
			{
				isEnd = true;
			}
		}

		if (isEnd)
		{
			object::Destroy(this);
		}

		GameObject::Update();
	}
	void Fade_In_Rectangle::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		//알파 블렌딩
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = 0;
		func.SourceConstantAlpha = mAlpha; // 알파값 - 낮을수록 투명

		AlphaBlend(hdc, -1, -1, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), func);


	}
	void Fade_In_Rectangle::Release()
	{
	}
	void Fade_In_Rectangle::SetEnd(bool end)
	{
		isEnd = false;
		mAlpha = 255;
	}
}
