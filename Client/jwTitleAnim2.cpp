#include "jwTitleAnim2.h"
#include "jwSceneManager.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwScene.h"

namespace jw
{
	TitleAnim2::TitleAnim2()
	{
	}
	TitleAnim2::~TitleAnim2()
	{
	}
	void TitleAnim2::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Title_Screen\\Background\\cuphead_title", Vector2::Zero, 0.06f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->Play(L"Backgroundcuphead_title", true);

		GameObject::Initialize();
	}
	void TitleAnim2::Update()
	{
		GameObject::Update();
	}
	void TitleAnim2::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void TitleAnim2::Release()
	{
		GameObject::Release();
	}
}