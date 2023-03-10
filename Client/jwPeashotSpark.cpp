#include "jwPeashotSpark.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{
	PeashotSpark::PeashotSpark()
	{
	}
	PeashotSpark::~PeashotSpark()
	{
	}
	void PeashotSpark::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Weapon_peashot\\spark", Vector2::Zero, 0.02f);
		mAnimator->Play(L"Weapon_peashotspark", true);

		mAnimator->GetCompleteEvent(L"Weapon_peashotspark")
			= std::bind(&PeashotSpark::SparkCompleteEvent, this);
	}
	void PeashotSpark::Update()
	{
		GameObject::Update();
	}
	void PeashotSpark::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PeashotSpark::Release()
	{
	}
	void PeashotSpark::SparkCompleteEvent()
	{
		object::Destroy(this);
	}
}