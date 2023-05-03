#include "jwPirate_BG_Sky.h"
#include "jwResources.h"
#include "jwTransform.h"

namespace jw
{
	Pirate_BG_Sky::Pirate_BG_Sky()
	{
	}
	Pirate_BG_Sky::~Pirate_BG_Sky()
	{
	}
	void Pirate_BG_Sky::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 1.8f));
		scale = tr->GetScale();

		mImage = Resources::Load<Image>(L"Pirate_BG_Sky", L"..\\Resources\\Image\\Stage3_pirate\\BG_Sky\\pirate_clouds_D.png");

		GameObject::Initialize();
	}
	void Pirate_BG_Sky::Update()
	{
	}
	void Pirate_BG_Sky::Render(HDC hdc)
	{

		GameObject::Render(hdc);

		Graphics graphic(hdc);

		//graphic.DrawImage(mImage->GetImage(), 0.0f, 0.0f, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y);

		TransparentBlt(hdc, -110, -70, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}
	void Pirate_BG_Sky::Release()
	{
	}
}