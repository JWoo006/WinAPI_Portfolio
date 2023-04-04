#include "jwTitleBG2.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwScene.h"
#include "jwObject.h"

namespace jw
{
	TitleBG2::TitleBG2()
	{
	}
	TitleBG2::~TitleBG2()
	{
	}
	void TitleBG2::Initialize()
	{
		mImage = Resources::Load<Image>(L"Background2", L"..\\Resources\\Image\\Title_Screen\\Background\\title_chips_left_0001 #262672.png");

		GameObject::Initialize();
	}
	void TitleBG2::Update()
	{
		GameObject::Update();
	}
	void TitleBG2::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Graphics graphic(hdc);
		graphic.DrawImage(mImage->GetImage(), 140, 720, mImage->GetWidth(), mImage->GetHeight());;
	}
	void TitleBG2::Release()
	{
		GameObject::Release();
	}
}