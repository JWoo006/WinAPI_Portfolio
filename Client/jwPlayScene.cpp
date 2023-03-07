#include "jwPlayScene.h"
#include "jwCuphead.h"
#include "jwBackground.h"
#include "jwBoss.h"
#include "jwVeggie_Onion.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwCollisionManager.h"

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
		mCuphead->SetName(L"Cuphead");
		AddGameObject(mCuphead, eLayerType::Player);

		mbackground = new Background();
		AddGameObject(mbackground, eLayerType::BG);

		/*mBoss = new Boss();
		AddGameObject(mBoss, eLayerType::Monster);*/
		Veggie_Onion* Onion = new Veggie_Onion();
		Onion->SetName(L"Veggie_Onion");
		AddGameObject(Onion, eLayerType::Monster);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);

		//override를 써서 자식쪽으로 오지만 부모쪽 함수로 지정가능
		Scene::Initialize();
	}
	void PlayScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			int next = (int)eSceneType::Play;
			next++;
			if (next == (int)eSceneType::End)
			{
				next = (int)eSceneType::Title;
			}

			SceneManager::LoadScene((eSceneType)next);
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