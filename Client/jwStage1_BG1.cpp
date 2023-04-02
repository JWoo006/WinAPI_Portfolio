#include "jwStage1_BG1.h"
#include "jwResources.h"
#include "jwTransform.h"

namespace jw
{
	Stage1_BG1::Stage1_BG1()
	{
	}
	Stage1_BG1::~Stage1_BG1()
	{
	}
	void Stage1_BG1::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 1.8f));
		scale = tr->GetScale();

		mImage = Resources::Load<Image>(L"Stage1_BG1", L"..\\Resources\\Image\\Stage1_veggie\\BackGround\\veggie_bg1.bmp");

		GameObject::Initialize();
	}
	void Stage1_BG1::Update()
	{
	}
	void Stage1_BG1::Render(HDC hdc)
	{

		GameObject::Render(hdc);

 		TransparentBlt(hdc, -40, -20, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

	}
	void Stage1_BG1::Release()
	{
	}
	void Stage1_BG1::OnCollisionEnter(Collider* other)
	{
	}
	void Stage1_BG1::OnCollisionStay(Collider* other)
	{
	}
	void Stage1_BG1::OnCollisionExit(Collider* other)
	{
	}
}
