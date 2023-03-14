#include "jwFadeInOut.h"
#include "jwResources.h"
#include "jwTime.h"
#include "jwTransform.h"

namespace jw
{
	FadeInOut::FadeInOut()
		: mAlpha(0)
		, reverse(false)
		, isEnd(false)
	{
	}
	FadeInOut::~FadeInOut()
	{
	}
	void FadeInOut::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		mImage = Resources::Load<Image>(L"Fade_Rect", L"..\\Resources\\Image\\Effect\\Rectangle_Black.bmp");
		tr->SetScale(Vector2(1.1f, 1.2f));
		scale = tr->GetScale();

		GameObject::Initialize();

	}
	void FadeInOut::Update()
	{
		if (!isEnd)
		{
			mTime += Time::DeltaTime();

			if (mTime > 0.01f && !reverse)
			{
				mAlpha += 5;
			}
			if (mTime > 0.01f && reverse)
			{
				mAlpha -= 5;
			}

			if (mAlpha >= 255)
			{
				reverse = true;
			}
			else if(mAlpha<=0 && reverse)
			{
				isEnd = true;
			}
		}
			
		

		GameObject::Update();
	}
	void FadeInOut::Render(HDC hdc)
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
	void FadeInOut::Release()
	{
	}
}
