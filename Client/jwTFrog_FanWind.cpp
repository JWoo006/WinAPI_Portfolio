#include "jwTFrog_FanWind.h"
#include "jwAnimator.h"
#include "jwObject.h"
#include "jwVeggie_Potato.h"

namespace jw
{

	TFrog_FanWind::TFrog_FanWind()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\fan\\wind_start", Vector2::Zero, 0.06f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage2_frog\\TFrog\\fan\\wind_loop", Vector2::Zero, 0.06f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"fanwind_start") = std::bind(&TFrog_FanWind::AnimCompleteEvent, this);
		mAnimator->Play(L"fanwind_start", false);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.2f, 1.2f));
	}
	TFrog_FanWind::~TFrog_FanWind()
	{
	}
	void TFrog_FanWind::Update()
	{
		GameObject::Update();
	}
	void TFrog_FanWind::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void TFrog_FanWind::Release()
	{
		GameObject::Release();
	}
	void TFrog_FanWind::AnimCompleteEvent()
	{
		mAnimator->Play(L"fanwind_loop", true);
	}
}