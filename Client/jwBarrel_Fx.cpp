#include "jwBarrel_Fx.h"
#include "jwAnimator.h"
#include "jwObject.h"
#include "jwVeggie_Potato.h"

namespace jw
{

	Barrel_Fx::Barrel_Fx()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Barrel\\sfx2", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"Barrelsfx2") = std::bind(&Barrel_Fx::AnimCompleteEvent, this);

		mAnimator->Play(L"Barrelsfx2", false);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.2f, 1.2f));
	}
	Barrel_Fx::~Barrel_Fx()
	{
	}
	void Barrel_Fx::Update()
	{
		GameObject::Update();
	}
	void Barrel_Fx::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Barrel_Fx::Release()
	{
		GameObject::Release();
	}

	void Barrel_Fx::AnimCompleteEvent()
	{
		object::Destroy(this);
	}

}