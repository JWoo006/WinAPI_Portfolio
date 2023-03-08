#include "jwVeggie_Onion.h"
#include "jwTime.h"
#include "jwSceneManager.h"
#include "jwInput.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwBaseBullet.h"
#include "jwScene.h"

namespace jw
{
	Veggie_Onion::Veggie_Onion()
	{
	}
	Veggie_Onion::~Veggie_Onion()
	{
	}
	void Veggie_Onion::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(1100.0f, 700.0f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\idle", Vector2::Zero, 0.1f);
		mAnimator->Play(L"onionidle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));

		GameObject::Initialize();
	}
	void Veggie_Onion::Update()
	{
		GameObject::Update();
	}
	void Veggie_Onion::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Veggie_Onion::Release()
	{
		GameObject::Release();
	}
	void Veggie_Onion::OnCollisionEnter(Collider* other)
	{
		int a = 0;
	}
	void Veggie_Onion::OnCollisionStay(Collider* other)
	{
	}
	void Veggie_Onion::OnCollisionExit(Collider* other)
	{
	}
}