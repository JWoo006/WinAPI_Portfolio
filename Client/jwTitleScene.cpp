#include "jwTitleScene.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwResources.h"
#include "jwTitleAnim1.h"
#include "jwTitleAnim2.h"
#include "jwTitleAnim3.h"
#include "jwTitleBG.h"
#include "jwTitleBG2.h"
#include "jwObject.h"
#include "jwCamera.h"
#include "jwSceneLoad.h"


namespace jw
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		//override를 써서 자식쪽으로 오지만 부모쪽 함수로 지정가능
		Scene::Initialize();

		object::Instantiate<TitleBG>(eLayerType::BG);
		object::Instantiate<TitleAnim1>(Vector2(800.0f, 800.0f), eLayerType::BG);
		object::Instantiate<TitleAnim2>(Vector2(500.0f, 800.0f), eLayerType::BG);
		object::Instantiate<TitleAnim3>(Vector2(1100.0f, 800.0f), eLayerType::BG);

		object::Instantiate<TitleBG2>(eLayerType::BG3);
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			mNextScene = (int)eSceneType::WorldStage;

			SceneManager::SetNextSceneType((eSceneType)mNextScene);
			//SceneManager::LoadScene((eSceneType)mNextScene);
			object::Instantiate<SceneLoad>(Vector2(800.0f, 900.0f), eLayerType::UI);
			//SceneLoad* sceneload = new SceneLoad();
		}
		Scene::Update();
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		Scene::SceneText(hdc);
	}
	void TitleScene::Release()
	{
		Scene::Release();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}