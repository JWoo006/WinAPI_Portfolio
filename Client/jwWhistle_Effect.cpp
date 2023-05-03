#include "jwWhistle_Effect.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{

	Whistle_Effect::Whistle_Effect()
	{
		mbShow = true;

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\Whistle A", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"CaptainWhistle A") = std::bind(&Whistle_Effect::AnimCompleteEvent, this);

		mAnimator->Play(L"CaptainWhistle A", false);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.6f, 1.4f));
	}
	Whistle_Effect::~Whistle_Effect()
	{
	}
	void Whistle_Effect::Update()
	{
		GameObject::Update();
	}
	void Whistle_Effect::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void Whistle_Effect::Release()
	{
		GameObject::Release();
	}

	void Whistle_Effect::AnimCompleteEvent()
	{
		object::Destroy(this);
	}

}