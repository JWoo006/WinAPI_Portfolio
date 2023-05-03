#include "jwShip_B_jaw.h"
#include "jwAnimator.h"
#include "jwObject.h"
#include "jwVeggie_Potato.h"

namespace jw
{

	Ship_B_jaw::Ship_B_jaw()
	{
		mbShow = true;

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\idle_jaw", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		//mAnimator->GetCompleteEvent(L"Barrelsfx") = std::bind(&Ship_B_jaw::AnimCompleteEvent, this);

		mAnimator->Play(L"WhaleBoat_Bidle_jaw", true);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.3f, 1.5f));
	}
	Ship_B_jaw::~Ship_B_jaw()
	{
	}
	void Ship_B_jaw::Update()
	{
		GameObject::Update();
	}
	void Ship_B_jaw::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void Ship_B_jaw::Release()
	{
		GameObject::Release();
	}

	void Ship_B_jaw::AnimCompleteEvent()
	{
		//object::Destroy(this);
	}

}