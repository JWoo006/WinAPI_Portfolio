#include "jwCanonball_sfx.h"
#include "jwAnimator.h"
#include "jwObject.h"
#include "jwVeggie_Potato.h"

namespace jw
{

	Canonball_sfx::Canonball_sfx()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_A\\Cannonball FX (A)", Vector2::Zero, 0.04f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"WhaleBoat_ACannonball FX (A)") = std::bind(&Canonball_sfx::AnimCompleteEvent, this);

		mAnimator->Play(L"WhaleBoat_ACannonball FX (A)", false);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.2f, 1.2f));
	}
	Canonball_sfx::~Canonball_sfx()
	{
	}
	void Canonball_sfx::Update()
	{
		GameObject::Update();
	}
	void Canonball_sfx::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Canonball_sfx::Release()
	{
		GameObject::Release();
	}

	void Canonball_sfx::AnimCompleteEvent()
	{
		object::Destroy(this);
	}

}