#include "jwBoss.h"
#include "jwResources.h"
#include "jwTransform.h"

namespace jw
{
	Boss::Boss()
	{
	}
	Boss::~Boss()
	{
	}
	void Boss::Initialize()
	{
		mImage = Resources::Load<Image>(L"stage1_Boss1", L"..\\Resources\\Image\\Stage1_veggie\\veggie_potato_idle_0001 #264515.bmp");


		GameObject::Initialize();
	}
	void Boss::Update()
	{
	}
	void Boss::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		GdiTransparentBlt(hdc, 1000, 300, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}
	void Boss::Release()
	{
		GameObject::Release();
	}
}
