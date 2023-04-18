#include "jwSceneLoad.h"
#include "jwScene.h"
#include "jwAnimator.h"
#include "jwSceneManager.h"
#include "jwObject.h"

namespace jw
{

	SceneLoad::SceneLoad()
	{
		mNextScene = SceneManager::getNextSceneType();

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Effect\\Circle_out", Vector2::Zero, 0.06f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"EffectCircle_out") = std::bind(&SceneLoad::AnimCompleteEvent, this);
		mAnimator->Play(L"EffectCircle_out", false);
	}
	SceneLoad::~SceneLoad()
	{
	}
	void SceneLoad::Update()
	{
		GameObject::Update();
	}
	void SceneLoad::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void SceneLoad::Release()
	{
		GameObject::Release();
	}
	void SceneLoad::AnimCompleteEvent()
	{
		SceneManager::LoadScene(mNextScene);
		object::Destroy(this);
	}
}