#include "jwJumpDust.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{
	JumpDust::JumpDust()
	{
	}
	JumpDust::~JumpDust()
	{
	}
	void JumpDust::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\Jump\\Dust", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->GetCompleteEvent(L"JumpDust") = std::bind(&JumpDust::AnimCompleteEvent, this);

		mAnimator->Play(L"JumpDust", false);

		GameObject::Initialize();
	}
	void JumpDust::Update()
	{
		GameObject::Update();
	}
	void JumpDust::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void JumpDust::Release()
	{
		GameObject::Release();
	}
	void JumpDust::AnimCompleteEvent()
	{
		object::Destroy(this);
	}
}