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

		mImage = Resources::Load<Image>(L"Stage1_BG2", L"..\\Resources\\Image\\Stage1_veggie\\BackGround\\veggie_bg2.png");

		GameObject::Initialize();
	}
	void Stage1_BG2::Update()
	{
	}
	void Stage1_BG2::Render(HDC hdc)
	{

		GameObject::Render(hdc);

		Graphics graphic(hdc);

	    //graphic.DrawImage(mImage->GetImage(), 0.0f, 700.0f, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y);
		int a = 0;
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
