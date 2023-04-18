#include "jwBossExplosion.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{
	BossExplosion::BossExplosion()
	{

	}
	BossExplosion::~BossExplosion()
	{
	}
	void BossExplosion::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\BossExplosion", Vector2::Zero, 0.05f, eImageFormat::BMP, eAnimationDir::R);
		mAnimator->GetCompleteEvent(L"ImageBossExplosion") = std::bind(&BossExplosion::AnimCompleteEvent, this);

		mAnimator->Play(L"ImageBossExplosion", false);

		GameObject::Initialize();
	}
	void BossExplosion::Update()
	{
		GameObject::Update();
	}
	void BossExplosion::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossExplosion::Release()
	{
		GameObject::Release();
	}
	void BossExplosion::AnimCompleteEvent()
	{
		object::Destroy(this);
	}
}