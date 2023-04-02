#include "jwTitleAnim1.h"
#include "jwSceneManager.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwScene.h"

namespace jw
{
	TitleAnim1::TitleAnim1()
	{
	}
	TitleAnim1::~TitleAnim1()
	{
	}
	void TitleAnim1::Initialize()
	{
		/*Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(800.0f, 800.0f));*/
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Title_Screen\\Background\\chalice_title", Vector2::Zero, 0.06f, eImageFormat::PNG, false);
		mAnimator->Play(L"Backgroundchalice_title", true);
		
		GameObject::Initialize();
	}
	void TitleAnim1::Update()
	{
		GameObject::Update();
	}
	void TitleAnim1::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void TitleAnim1::Release()
	{
		GameObject::Release();
	}
}