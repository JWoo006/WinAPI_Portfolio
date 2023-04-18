#include "jwWinscreen_Board.h"
#include "jwResources.h"
#include "jwTransform.h"

namespace jw
{
	Winscreen_Board::Winscreen_Board()
	{
	}
	Winscreen_Board::~Winscreen_Board()
	{
	}
	void Winscreen_Board::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.0f, 1.0f));
		scale = tr->GetScale();

		mImage = Resources::Load<Image>(L"Winscreen_Board", L"..\\Resources\\Image\\WinScreen\\Board\\winscreen_board_01.png");

		GameObject::Initialize();
	}
	void Winscreen_Board::Update()
	{
	}
	void Winscreen_Board::Render(HDC hdc)
	{

		GameObject::Render(hdc);

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

	}
	void Winscreen_Board::Release()
	{
	}
}
