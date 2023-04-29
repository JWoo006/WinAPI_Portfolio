#include "jwSlot_Pic.h"
#include "jwResources.h"
#include "jwTransform.h"

namespace jw
{
	Slot_Pic::Slot_Pic()
	{
	}
	Slot_Pic::~Slot_Pic()
	{
	}
	void Slot_Pic::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.0f, 1.0f));
		scale = tr->GetScale();
		Vector2 pos = tr->GetPos();
		mImage = Resources::Load<Image>(L"Slot_Pic", L"..\\Resources\\Image\\Stage2_frog\\TFrog\\slot\\slot\\tallfrog_slotman_slot_TEMP.png");

		GameObject::Initialize();
	}
	void Slot_Pic::Update()
	{
	}
	void Slot_Pic::Render(HDC hdc)
	{

		GameObject::Render(hdc);

		Graphics graphic(hdc);

		//graphic.DrawImage(mImage->GetImage(), 0.0f, 0.0f, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}
	void Slot_Pic::Release()
	{
	}
}
