#include "jwPeashotSpark.h"
#include "jwTransform.h"
#include "jwAnimator.h"

namespace jw
{
	PeashotSpark::PeashotSpark()
		: OnShot(false)
	{
	}
	PeashotSpark::~PeashotSpark()
	{
	}
	void PeashotSpark::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Weapon_peashot\\spark", Vector2(70.0f,-40.0f), 0.1f);
		mAnimator->Play(L"Weapon_peashotspark", true);
	}
	void PeashotSpark::Update()
	{
		GameObject::Update();
	}
	void PeashotSpark::Render(HDC hdc)
	{
		if (OnShot)
		{
			GameObject::Render(hdc);
		}
		
	}
	void PeashotSpark::Release()
	{
	}
}