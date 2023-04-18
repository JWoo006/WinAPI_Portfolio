#include "jwWinscreen_ResultAnim.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"

namespace jw
{
	Winscreen_ResultAnim::Winscreen_ResultAnim()
	{
	}
	Winscreen_ResultAnim::~Winscreen_ResultAnim()
	{
	}
	void Winscreen_ResultAnim::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\WinScreen\\Result", Vector2::Zero, 0.06f, eImageFormat::BMP, eAnimationDir::R);
		mAnimator->Play(L"WinScreenResult", true);

		GameObject::Initialize();
	}
	void Winscreen_ResultAnim::Update()
	{
		GameObject::Update();
	}
	void Winscreen_ResultAnim::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Winscreen_ResultAnim::Release()
	{
		GameObject::Release();
	}
}