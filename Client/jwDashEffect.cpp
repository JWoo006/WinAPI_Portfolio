#include "jwDashEffect.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{
	DashEffect::DashEffect(eAnimationDir dir )
	{
		mAnimDir = dir;
	}
	DashEffect::~DashEffect()
	{
	}
	void DashEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();

		if (mAnimDir == eAnimationDir::L)
		{
			mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Dash\\Effect_L", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
			mAnimator->GetCompleteEvent(L"DashEffect_L") = std::bind(&DashEffect::AnimCompleteEvent, this);
			mAnimator->Play(L"DashEffect_L", false);
		}
		else
		{
			mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Dash\\Effect_R", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
			mAnimator->GetCompleteEvent(L"DashEffect_R") = std::bind(&DashEffect::AnimCompleteEvent, this);
			mAnimator->Play(L"DashEffect_R", false);
		}

		GameObject::Initialize();
	}
	void DashEffect::Update()
	{
		GameObject::Update();
	}
	void DashEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void DashEffect::Release()
	{
		GameObject::Release();
	}
	void DashEffect::AnimCompleteEvent()
	{
		object::Destroy(this);
	}
}