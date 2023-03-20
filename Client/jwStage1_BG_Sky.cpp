#include "jwStage1_BG_Sky.h"
#include "jwResources.h"
#include "jwTransform.h"

namespace jw
{
	Stage1_BG_Sky::Stage1_BG_Sky()
	{
	}
	Stage1_BG_Sky::~Stage1_BG_Sky()
	{
	}
	void Stage1_BG_Sky::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 1.8f));
		scale = tr->GetScale();

		mImage = Resources::Load<Image>(L"Stage1_BG1", L"..\\Resources\\Image\\Stage1_veggie\\BackGround\\veggie_bg_sky.bmp");

		GameObject::Initialize();
	}
	void Stage1_BG_Sky::Update()
	{
	}
	void Stage1_BG_Sky::Render(HDC hdc)
	{

		GameObject::Render(hdc);

		TransparentBlt(hdc, -40, -90, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

	}
	void Stage1_BG_Sky::Release()
	{
	}
	void Stage1_BG_Sky::OnCollisionEnter(Collider* other)
	{
	}
	void Stage1_BG_Sky::OnCollisionStay(Collider* other)
	{
	}
	void Stage1_BG_Sky::OnCollisionExit(Collider* other)
	{
	}
}
