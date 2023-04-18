#include "jwPotatoAttackEffect.h"
#include "jwAnimator.h"
#include "jwObject.h"
#include "jwVeggie_Potato.h"

namespace jw
{

	PotatoAttackEffect::PotatoAttackEffect()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\potato\\shootEffect", Vector2::Zero, 0.06f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"potatoshootEffect") = std::bind(&PotatoAttackEffect::AnimCompleteEvent, this);
		mAnimator->Play(L"potatoshootEffect", false);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.5f, 1.5f));
	}
	PotatoAttackEffect::~PotatoAttackEffect()
	{
	}
	void PotatoAttackEffect::Update()
	{
		GameObject::Update();
	}
	void PotatoAttackEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PotatoAttackEffect::Release()
	{
		GameObject::Release();
	}
	void PotatoAttackEffect::AnimCompleteEvent()
	{
		object::Destroy(this);
	}
}