#include "jwSceneLoad_In.h"
#include "jwScene.h"
#include "jwAnimator.h"
#include "jwSceneManager.h"
#include "jwObject.h"

namespace jw
{
	SceneLoad_In::SceneLoad_In()
	{
		mbIsEnd = false;
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Effect\\Circle_in", Vector2::Zero, 0.06f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"EffectCircle_in") = std::bind(&SceneLoad_In::AnimCompleteEvent, this);
		mAnimator->Play(L"EffectCircle_in", false);
	}
	SceneLoad_In::~SceneLoad_In()
	{
	}
	void SceneLoad_In::Update()
	{
		GameObject::Update();
	}
	void SceneLoad_In::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void SceneLoad_In::Release()
	{
		GameObject::Release();
	}
	void SceneLoad_In::AnimCompleteEvent()
	{
		mbIsEnd = true;
		object::Destroy(this);
	}
}