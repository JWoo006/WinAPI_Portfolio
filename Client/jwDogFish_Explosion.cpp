#include "jwDogFish_Explosion.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{

	DogFish_Explosion::DogFish_Explosion()
	{
		mbShow = true;

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\dogfish_explo", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"Captaindogfish_explo") = std::bind(&DogFish_Explosion::AnimCompleteEvent, this);

		mAnimator->Play(L"Captaindogfish_explo", false);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.2f, 1.2f));
	}
	DogFish_Explosion::~DogFish_Explosion()
	{
	}
	void DogFish_Explosion::Update()
	{
		GameObject::Update();
	}
	void DogFish_Explosion::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void DogFish_Explosion::Release()
	{
		GameObject::Release();
	}

	void DogFish_Explosion::AnimCompleteEvent()
	{
		object::Destroy(this);
	}

}