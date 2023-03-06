#include "jwBackground.h"
#include "jwResources.h"
#include "jwTransform.h"

namespace jw
{
	Background::Background()
	{
	}
	Background::~Background()
	{
	}
	void Background::Initialize()
	{
		mImage = Resources::Load<Image>(L"stage1_ground", L"..\\Resources\\Image\\Stage1_veggie\\BackGround\\veggie_bg_0003 #264656.bmp");
		mSkyImage = Resources::Load<Image>(L"stage1_sky", L"..\\Resources\\Image\\Stage1_veggie\\BackGround\\veggie_bg_0012 #264653.bmp");

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.0f, 1.0f));


		GameObject::Initialize();
	}
	void Background::Update()
	{
	}
	void Background::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		BitBlt(hdc, 0, 0, mSkyImage->GetWidth(), mSkyImage->GetHeight(), mSkyImage->GetHdc(), 0, 0, SRCCOPY);

		TransparentBlt(hdc, 0, 400, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}
	void Background::Release()
	{
		GameObject::Release();
	}
}
