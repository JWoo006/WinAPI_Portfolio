#include "jwVeggieWorldIcon.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"


namespace jw
{
	VeggieWorldIcon::VeggieWorldIcon()
	{
	}
	VeggieWorldIcon::~VeggieWorldIcon()
	{
	}
	void VeggieWorldIcon::Initialize()
	{
		/*Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(1100.0f, 700.0f));*/

		mLoadSceneType = eSceneType::Play_Veggie;

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\World_Map\\WorldIcon\\Veggie_Stage", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->Play(L"WorldIconVeggie_Stage", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-100.0f, -250.0f));
		collider->SetSize(Vector2(200.0f, 200.0f));

		GameObject::Initialize();
	}
	void VeggieWorldIcon::Update()
	{
		GameObject::Update();
	}
	void VeggieWorldIcon::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void VeggieWorldIcon::Release()
	{
		GameObject::Release();
	}
	void VeggieWorldIcon::OnCollisionEnter(Collider* other)
	{
		int a = 0;
	}
	void VeggieWorldIcon::OnCollisionStay(Collider* other)
	{
	}
	void VeggieWorldIcon::OnCollisionExit(Collider* other)
	{
	}
}