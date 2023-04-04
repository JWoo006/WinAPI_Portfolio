#include "jwtestEnemy.h"
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
	testEnemy::testEnemy()
	{
	}
	testEnemy::~testEnemy()
	{
	}
	void testEnemy::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\pink", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->Play(L"Imagepink", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));

		mLayerType = testEnemy::GetLayerType();

		

		int a = 0;

		GameObject::Initialize();
	}
	void testEnemy::Update()
	{
		GameObject::Update();
	}
	void testEnemy::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void testEnemy::Release()
	{
		GameObject::Release();
	}
	void testEnemy::OnCollisionEnter(Collider* other)
	{
		int a = 0;
	}
	void testEnemy::OnCollisionStay(Collider* other)
	{
	}
	void testEnemy::OnCollisionExit(Collider* other)
	{
	}
}
