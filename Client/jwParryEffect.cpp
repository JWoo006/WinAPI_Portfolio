#include "jwParryEffect.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{
	ParryEffect::ParryEffect()
	{
	}
	ParryEffect::~ParryEffect()
	{
	}
	void ParryEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Parry\\Effect", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->GetCompleteEvent(L"ParryEffect") = std::bind(&ParryEffect::AnimCompleteEvent, this);

		mAnimator->Play(L"ParryEffect", false);

		GameObject::Initialize();
	}
	void ParryEffect::Update()
	{
		GameObject::Update();
	}
	void ParryEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ParryEffect::Release()
	{
		GameObject::Release();
	}
	void ParryEffect::AnimCompleteEvent()
	{
		object::Destroy(this);
	}
}
