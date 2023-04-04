#include "jwTitleBG.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwScene.h"
#include "jwObject.h"

namespace jw
{
	TitleBG::TitleBG()
	{
	}
	TitleBG::~TitleBG()
	{
	}
	void TitleBG::Initialize()
	{
		mImage = Resources::Load<Image>(L"Background1", L"..\\Resources\\Image\\Title_Screen\\Background\\title_screen_background #262704.bmp");

		GameObject::Initialize();
	}
	void TitleBG::Update()
	{
		GameObject::Update();
	}
	void TitleBG::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		BitBlt(hdc, 0, 0, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}
	void TitleBG::Release()
	{
		GameObject::Release();
	}
}