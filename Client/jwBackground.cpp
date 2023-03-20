#include "jwBackground.h"
#include "jwResources.h"
#include "jwTransform.h"

namespace jw
{
	Background::Background()
	{
	}
	Background::~Background()
	{
	}
	void Background::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 1.8f));
		scale = tr->GetScale();

		mImage = Resources::Load<Image>(L"Stage1_BG1", L"..\\Resources\\Image\\Stage1_veggie\\BackGround\\veggie_bg1.bmp");
		
		GameObject::Initialize();
	}
	void Background::Update()
	{
	}
	void Background::Render(HDC hdc)
	{
		
		GameObject::Render(hdc);	

		TransparentBlt(hdc, -40, -90, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

	}
	void Background::Release()
	{
	}
	void Background::OnCollisionEnter(Collider* other)
	{
	}
	void Background::OnCollisionStay(Collider* other)
	{
	}
	void Background::OnCollisionExit(Collider* other)
	{
	}
}
