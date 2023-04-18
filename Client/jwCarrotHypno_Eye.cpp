#include "jwCarrotHypno_Eye.h"
#include "jwTime.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{
	CarrotHypno_Eye::CarrotHypno_Eye()
	{
	}
	CarrotHypno_Eye::~CarrotHypno_Eye()
	{
	}
	void CarrotHypno_Eye::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\carrot\\hypno_eye", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::R);
		
		mAnimator->Play(L"carrothypno_eye", true);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.2f, 1.2f));

		GameObject::Initialize();
	}
	void CarrotHypno_Eye::Update()
	{
		GameObject::Update();
	}
	void CarrotHypno_Eye::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CarrotHypno_Eye::Release()
	{
		GameObject::Release();
	}
}