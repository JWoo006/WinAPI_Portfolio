#include "jwWinscreen_Cuphead.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"

namespace jw
{
	Winscreen_Cuphead::Winscreen_Cuphead()
	{
	}
	Winscreen_Cuphead::~Winscreen_Cuphead()
	{
	}
	void Winscreen_Cuphead::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\WinScreen\\cuphead", Vector2::Zero, 0.06f, eImageFormat::BMP, eAnimationDir::R);
		mAnimator->Play(L"WinScreencuphead", true);

		GameObject::Initialize();
	}
	void Winscreen_Cuphead::Update()
	{
		GameObject::Update();
	}
	void Winscreen_Cuphead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Winscreen_Cuphead::Release()
	{
		GameObject::Release();
	}
}