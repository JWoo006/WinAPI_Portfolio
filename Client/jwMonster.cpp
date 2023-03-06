#include "jwMonster.h"
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
	Monster::Monster()
	{
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(100.0f, 700.0f));

		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Aim\\Straight", Vector2::Zero, 0.1f);


		mAnimator->Play(L"CupheadIdle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));

		

		GameObject::Initialize();
	}
	void Monster::Update()
	{
	}
	void Monster::Render(HDC hdc)
	{
	}
	void Monster::Release()
	{
	}
}