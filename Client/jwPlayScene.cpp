#include "jwPlayScene.h"
#include "jwCuphead.h"
#include "jwBackground.h"
#include "jwBoss.h"
#include "jwInput.h"
#include "jwSceneManager.h"

namespace jw
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		mCuphead = new Cuphead();
		//cuphead->SetPos(Vector2(0.0f, 0.0f));
		AddGameObject(mCuphead, eLayerType::Player);

		mbackground = new Background();
		AddGameObject(mbackground, eLayerType::BG);

		mBoss = new Boss();
		AddGameObject(mBoss, eLayerType::Monster);

		//override를 써서 자식쪽으로 오지만 부모쪽 함수로 지정가능
		Scene::Initialize();
	}
	void PlayScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		Scene::Update();
	}
	void PlayScene::Render(HDC hdc)
	{
		
		
		Scene::Render(hdc);

		Scene::SceneText(hdc);

		
	}
	void PlayScene::Release()
	{
		Scene::Release();
	}
	void PlayScene::OnEnter()
	{
	}
	void PlayScene::OnExit()
	{
		//mCuphead->SetPos(Vector2(0.0f, 0.0f));
	}
	
}