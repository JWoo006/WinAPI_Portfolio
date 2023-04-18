#include "jwFightText_WALLOP.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{

	FightText_WALLOP::FightText_WALLOP()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\FightText", Vector2::Zero, 0.06f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"ImageFightText") = std::bind(&FightText_WALLOP::AnimCompleteEvent, this);
		mAnimator->Play(L"ImageFightText", false);
	}
	FightText_WALLOP::~FightText_WALLOP()
	{
	}
	void FightText_WALLOP::Update()
	{
		GameObject::Update();
	}
	void FightText_WALLOP::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void FightText_WALLOP::Release()
	{
		GameObject::Release();
	}

	void FightText_WALLOP::AnimCompleteEvent()
	{
		object::Destroy(this);
	}
}