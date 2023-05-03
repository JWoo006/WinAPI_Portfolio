#include "jwBarrel_Dust.h"
#include "jwAnimator.h"
#include "jwObject.h"
#include "jwVeggie_Potato.h"

namespace jw
{

	Barrel_Dust::Barrel_Dust()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Barrel\\sfx", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);
		
		mAnimator->GetCompleteEvent(L"Barrelsfx") = std::bind(&Barrel_Dust::AnimCompleteEvent, this);

		mAnimator->Play(L"Barrelsfx", false);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.2f, 1.2f));
	}
	Barrel_Dust::~Barrel_Dust()
	{
	}
	void Barrel_Dust::Update()
	{
		GameObject::Update();
	}
	void Barrel_Dust::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Barrel_Dust::Release()
	{
		GameObject::Release();
	}

	void Barrel_Dust::AnimCompleteEvent()
	{
		object::Destroy(this);
	}
	
}