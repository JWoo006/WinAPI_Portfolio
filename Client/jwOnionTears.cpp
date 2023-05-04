#include "jwOnionTears.h"
#include "jwTime.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{
	OnionTears::OnionTears()
	{
	}
	OnionTears::OnionTears(int state)
		: mCryState((eCryState)state)
	{
	}
	OnionTears::~OnionTears()
	{
	}
	void OnionTears::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\tears\\intro_L", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\tears\\intro_R", Vector2::Zero, 0.07f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\tears\\loop_L", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\tears\\loop_R", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\tears\\outro_L", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\onion\\tears\\outro_R", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);
		
		mAnimator->GetCompleteEvent(L"tearsintro_L") = std::bind(&OnionTears::CryStart_L_AnimCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"tearsintro_R") = std::bind(&OnionTears::CryStart_R_AnimCompleteEvent, this);


		switch (mCryState)
		{
		case jw::OnionTears::eCryState::introL:
			mAnimator->Play(L"tearsintro_L", false);
			break;
		case jw::OnionTears::eCryState::introR:
			mAnimator->Play(L"tearsintro_R", false);
			break;
		case jw::OnionTears::eCryState::End:
			break;
		default:
			break;
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetScale(Vector2(1.2f, 1.2f));

		GameObject::Initialize();
	}
	void OnionTears::Update()
	{
		GameObject::Update();
	}
	void OnionTears::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void OnionTears::Release()
	{
		GameObject::Release();
	}
	void OnionTears::AnimCompleteEvent()
	{
		//object::Destroy(this);
	}
	void OnionTears::CryStart_L_AnimCompleteEvent()
	{
		mAnimator->Play(L"tearsloop_L", true);
	}
	void OnionTears::CryStart_R_AnimCompleteEvent()
	{
		mAnimator->Play(L"tearsloop_R", true);
	}
}