#include "jwPlayScene.h"
#include "jwCuphead.h"
#include "jwBackground.h"
#include "jwBoss.h"
#include "jwVeggie_Onion.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwCollisionManager.h"
#include "jwObject.h"


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
		/*mCuphead = new Cuphead();
		mCuphead->SetName(L"Cuphead");
		AddGameObject(mCuphead, eLayerType::Player);*/

		object::Instantiate<Cuphead>(Vector2(100.0f, 700.0f), eLayerType::Player, eSceneType::Play);

		/*mbackground = new Background();
		AddGameObject(mbackground, eLayerType::BG);*/

		object::Instantiate<Background>(eLayerType::BG, eSceneType::Play);

		/*Veggie_Onion* Onion = new Veggie_Onion();
		Onion->SetName(L"Veggie_Onion");
		AddGameObject(Onion, eLayerType::Monster);*/

		object::Instantiate< Veggie_Onion>(Vector2(1100.0f, 700.0f), eLayerType::Monster, eSceneType::Play);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);

		//override를 써서 자식쪽으로 오지만 부모쪽 함수로 지정가능
		//Scene::Initialize();
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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
	}
	void PlayScene::OnExit()
	{
		//mCuphead->SetPos(Vector2(0.0f, 0.0f));
	}
	
}