#include "jwOnHitEffect.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{
	OnHitEffect::OnHitEffect()
	{
		
	}
	OnHitEffect::~OnHitEffect()
	{
	}
	void OnHitEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Hit\\Dust", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->GetCompleteEvent(L"HitDust") = std::bind(&OnHitEffect::AnimCompleteEvent, this);

		mAnimator->Play(L"HitDust", false);

		GameObject::Initialize();
	}
	void OnHitEffect::Update()
	{
		GameObject::Update();
	}
	void OnHitEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void OnHitEffect::Release()
	{
		GameObject::Release();
	}
	void OnHitEffect::AnimCompleteEvent()
	{
		object::Destroy(this);
	}
}