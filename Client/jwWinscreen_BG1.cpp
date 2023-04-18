#include "jwWinscreen_BG1.h"
#include "jwResources.h"
#include "jwTransform.h"

namespace jw
{
	Winscreen_BG1::Winscreen_BG1()
	{
	}
	Winscreen_BG1::~Winscreen_BG1()
	{
	}
	void Winscreen_BG1::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.0f, 1.0f));
		scale = tr->GetScale();

		mImage = Resources::Load<Image>(L"Winscreen_BG1", L"..\\Resources\\Image\\WinScreen\\BackGround\\winscreen_bg.png");

		GameObject::Initialize();
	}
	void Winscreen_BG1::Update()
	{
	}
	void Winscreen_BG1::Render(HDC hdc)
	{

		GameObject::Render(hdc);

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

	}
	void Winscreen_BG1::Release()
	{
	}
}
