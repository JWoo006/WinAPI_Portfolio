#include "jwKnockout.h"
#include "jwScene.h"
#include "jwAnimator.h"
#include "jwSceneManager.h"
#include "jwObject.h"
#include "jwResources.h"
#include "jwSound.h"
#include "jwTime.h"

namespace jw
{
	Knockout::Knockout()
	{
		mSound = Resources::Load<Sound>(L"sfx_level_announcer_knockout_0004", L"..\\Resources\\Sound\\Announcer\\sfx_level_announcer_knockout_0004.wav");
		
		mbIsEnd = false;
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Effect\\Knockout", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"EffectKnockout") = std::bind(&Knockout::AnimCompleteEvent, this);
		mAnimator->Play(L"EffectKnockout", false);
	}
	Knockout::~Knockout()
	{
	}
	void Knockout::Update()
	{
		GameObject::Update();
		
		mTime += Time::DeltaTime();

		if (mTime > 1.0f && !mbTime)
		{
			mbTime = true;
			mSound->Play(false);
		}
	}
	void Knockout::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Knockout::Release()
	{
		GameObject::Release();
	}
	void Knockout::AnimCompleteEvent()
	{
		//mbIsEnd = true;
		object::Destroy(this);
	}
}