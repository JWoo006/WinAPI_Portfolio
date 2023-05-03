#include "jwPirate_BG.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{

	Pirate_BG::Pirate_BG()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\BG", Vector2::Zero, 0.06f, eImageFormat::BMP, eAnimationDir::R);
		
		mAnimator->Play(L"Stage3_pirateBG", true);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.7f, 1.2f));
	}
	Pirate_BG::~Pirate_BG()
	{
	}
	void Pirate_BG::Update()
	{
		GameObject::Update();
	}
	void Pirate_BG::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Pirate_BG::Release()
	{
		GameObject::Release();
	}

}