#include "jwPirate_BG_Dock.h"
#include "jwResources.h"
#include "jwTransform.h"

namespace jw
{
	Pirate_BG_Dock::Pirate_BG_Dock()
	{
	}
	Pirate_BG_Dock::~Pirate_BG_Dock()
	{
	}
	void Pirate_BG_Dock::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.2f, 1.2f));
		scale = tr->GetScale();

		mImage = Resources::Load<Image>(L"Pirate_BG_Dock", L"..\\Resources\\Image\\Stage3_pirate\\BG_Dock\\pirateDockA.png");

		GameObject::Initialize();
	}
	void Pirate_BG_Dock::Update()
	{
	}
	void Pirate_BG_Dock::Render(HDC hdc)
	{

		GameObject::Render(hdc);

		Graphics graphic(hdc);

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		graphic.DrawImage(mImage->GetImage(), pos.x, pos.y, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y);

		//TransparentBlt(hdc, -110, -70, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0
		//	, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}
	void Pirate_BG_Dock::Release()
	{
	}
}