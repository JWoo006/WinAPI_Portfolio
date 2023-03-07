#include "jwTitleAnim3.h"
#include "jwTitleAnim1.h"
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
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(1100.0f, 800.0f));
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Title_Screen\\Background\\mugman_title", Vector2::Zero, 0.06f);
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