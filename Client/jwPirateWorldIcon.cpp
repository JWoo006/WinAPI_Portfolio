#include "jwPirateWorldIcon.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"


namespace jw
{
	PirateWorldIcon::PirateWorldIcon()
	{
	}
	PirateWorldIcon::~PirateWorldIcon()
	{
	}
	void PirateWorldIcon::Initialize()
	{
		SetName(L"PirateIcon");

		mLoadSceneType = eSceneType::Play_Pirate;

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\World_Map\\WorldIcon\\Pirate_Stage", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->Play(L"WorldIconPirate_Stage", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-100.0f, -250.0f));
		collider->SetSize(Vector2(200.0f, 200.0f));

		GameObject::Initialize();
	}
	void PirateWorldIcon::Update()
	{
		GameObject::Update();
	}
	void PirateWorldIcon::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PirateWorldIcon::Release()
	{
		GameObject::Release();
	}
	void PirateWorldIcon::OnCollisionEnter(Collider* other)
	{
		int a = 0;
	}
	void PirateWorldIcon::OnCollisionStay(Collider* other)
	{
	}
	void PirateWorldIcon::OnCollisionExit(Collider* other)
	{
	}
}