#include "jwWhistle_Scope.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{

	Whistle_Scope::Whistle_Scope()
	{
		mbShow = true;

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\Scope", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"CaptainScope") = std::bind(&Whistle_Scope::AnimCompleteEvent, this);

		mAnimator->Play(L"CaptainScope", false);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.2f, 1.2f));
	}
	Whistle_Scope::~Whistle_Scope()
	{
	}
	void Whistle_Scope::Update()
	{
		GameObject::Update();
	}
	void Whistle_Scope::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void Whistle_Scope::Release()
	{
		GameObject::Release();
	}

	void Whistle_Scope::AnimCompleteEvent()
	{
		object::Destroy(this);
	}

}