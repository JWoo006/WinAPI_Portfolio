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
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 1.8f));
		//tr->SetScale(Vector2(1.0f, 1.0f));
		scale = tr->GetScale();

		//mImage = Resources::Load<Image>(L"stage1_ground", L"..\\Resources\\Image\\Stage1_veggie\\BackGround\\veggie_bg_0003 #264656.bmp");
		mImage = Resources::Load<Image>(L"stage1_ground", L"..\\Resources\\Image\\Stage1_veggie\\BackGround\\veggie_bg.bmp");
		//mSkyImage = Resources::Load<Image>(L"stage1_sky", L"..\\Resources\\Image\\Stage1_veggie\\BackGround\\veggie_bg_0012 #264653.bmp");
		//mSkyImage = Resources::Load<Image>(L"stage1_sky", L"..\\Resources\\Image\\Stage1_veggie\\BackGround\\veggie_bg_0012 1111.bmp");

		GameObject::Initialize();
	}
	void Background::Update()
	{
	}
	void Background::Render(HDC hdc)
	{
		
		GameObject::Render(hdc);	

		/*TransparentBlt(hdc, 0, 0, mSkyImage->GetWidth() * scale.x, mSkyImage->GetHeight() * scale.y, mSkyImage->GetHdc(), 0, 0
			, mSkyImage->GetWidth(), mSkyImage->GetHeight(), RGB(255, 0, 255));*/
		TransparentBlt(hdc, -40, -90, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

	}
	void Background::Release()
	{
		//GameObject::Release();
	}
}
