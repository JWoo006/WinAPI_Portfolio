#include "jwStage1_BG2.h"
#include "jwResources.h"
#include "jwTransform.h"

namespace jw
{
	Stage1_BG2::Stage1_BG2()
	{
	}
	Stage1_BG2::~Stage1_BG2()
	{
	}
	void Stage1_BG2::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 1.8f));
		scale = tr->GetScale();

		mImage = Resources::Load<Image>(L"Stage1_BG2", L"..\\Resources\\Image\\Stage1_veggie\\BackGround\\veggie_bg2.bmp");

		GameObject::Initialize();
	}
	void Stage1_BG2::Update()
	{
	}
	void Stage1_BG2::Render(HDC hdc)
	{

		GameObject::Render(hdc);

		TransparentBlt(hdc, -40, -30, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

	}
	void Stage1_BG2::Release()
	{
	}
	void Stage1_BG2::OnCollisionEnter(Collider* other)
	{
	}
	void Stage1_BG2::OnCollisionStay(Collider* other)
	{
	}
	void Stage1_BG2::OnCollisionExit(Collider* other)
	{
	}
}
