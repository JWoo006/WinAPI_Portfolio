#include "jwPlayScene.h"
#include "jwCuphead.h"
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

		//override�� �Ἥ �ڽ������� ������ �θ��� �Լ��� ��������
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