#include "jwFrogStageBG.h"
#include "jwResources.h"
#include "jwTransform.h"

namespace jw
{
	FrogStageBG::FrogStageBG()
	{
	}
	FrogStageBG::~FrogStageBG()
	{
	}
	void FrogStageBG::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 1.8f));
		scale = tr->GetScale();

		mImage = Resources::Load<Image>(L"FrogStageBG", L"..\\Resources\\Image\\Stage2_frog\\BG\\jazzbar_BG.png");

		GameObject::Initialize();
	}
	void FrogStageBG::Update()
	{
	}
	void FrogStageBG::Render(HDC hdc)
	{

		GameObject::Render(hdc);

		Graphics graphic(hdc);

		//graphic.DrawImage(mImage->GetImage(), 0.0f, 0.0f, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y);

		TransparentBlt(hdc, -110, -70, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}
	void FrogStageBG::Release()
	{
	}
}
