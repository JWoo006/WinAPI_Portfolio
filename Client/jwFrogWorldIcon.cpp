#include "jwFrogWorldIcon.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"


namespace jw
{
	FrogWorldIcon::FrogWorldIcon()
	{
	}
	FrogWorldIcon::~FrogWorldIcon()
	{
	}
	void FrogWorldIcon::Initialize()
	{
		SetName(L"FrogIcon");

		mLoadSceneType = eSceneType::Play_Frog;

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\World_Map\\WorldIcon\\Frog_Stage", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->Play(L"WorldIconFrog_Stage", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-100.0f, -250.0f));
		collider->SetSize(Vector2(200.0f, 200.0f));

		GameObject::Initialize();
	}
	void FrogWorldIcon::Update()
	{
		GameObject::Update();
	}
	void FrogWorldIcon::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void FrogWorldIcon::Release()
	{
		GameObject::Release();
	}
	void FrogWorldIcon::OnCollisionEnter(Collider* other)
	{
		int a = 0;
	}
	void FrogWorldIcon::OnCollisionStay(Collider* other)
	{
	}
	void FrogWorldIcon::OnCollisionExit(Collider* other)
	{
	}
}