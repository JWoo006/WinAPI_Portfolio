#include "jwDogFish_Splash.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{

	DogFish_Splash::DogFish_Splash()
	{
		mbShow = true;

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\dogfishi_splash", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"Captaindogfishi_splash") = std::bind(&DogFish_Splash::AnimCompleteEvent, this);

		mAnimator->Play(L"Captaindogfishi_splash", false);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.2f, 1.2f));
	}
	DogFish_Splash::~DogFish_Splash()
	{
	}
	void DogFish_Splash::Update()
	{
		GameObject::Update();
	}
	void DogFish_Splash::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void DogFish_Splash::Release()
	{
		GameObject::Release();
	}

	void DogFish_Splash::AnimCompleteEvent()
	{
		object::Destroy(this);
	}

}