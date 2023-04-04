#include "jwTitleAnim3.h"
#include "jwSceneManager.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwScene.h"

namespace jw
{
	TitleAnim3::TitleAnim3()
	{
	}
	TitleAnim3::~TitleAnim3()
	{
	}
	void TitleAnim3::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Title_Screen\\Background\\mugman_title", Vector2::Zero, 0.06f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->Play(L"Backgroundmugman_title", true);

		GameObject::Initialize();
	}
	void TitleAnim3::Update()
	{
		GameObject::Update();
	}
	void TitleAnim3::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void TitleAnim3::Release()
	{
		GameObject::Release();
	}
}