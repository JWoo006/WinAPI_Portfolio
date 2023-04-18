#include "jwPotatoIntroEffect.h"
#include "jwAnimator.h"
#include "jwObject.h"
#include "jwVeggie_Potato.h"

namespace jw
{

	PotatoIntroEffect::PotatoIntroEffect()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\potato\\Intro_ground", Vector2::Zero, 0.06f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\potato\\intro_ground_burst", Vector2::Zero, 0.06f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"potatoIntro_ground") = std::bind(&PotatoIntroEffect::AnimCompleteEvent, this);
		mAnimator->Play(L"potatoIntro_ground", false);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.5f, 1.5f));
	}
	PotatoIntroEffect::~PotatoIntroEffect()
	{
	}
	void PotatoIntroEffect::Update()
	{
		GameObject::Update();
	}
	void PotatoIntroEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PotatoIntroEffect::Release()
	{
		GameObject::Release();
	}
	void PotatoIntroEffect::AnimCompleteEvent()
	{
		mbShow = true;

		mAnimator->Play(L"potatointro_ground_burst", false);
	}
}