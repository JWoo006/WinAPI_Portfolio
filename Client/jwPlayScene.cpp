#include "jwPlayScene.h"
#include "jwCuphead.h"
#include "jwBoss.h"
#include "jwVeggie_Onion.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwCollisionManager.h"
#include "jwObject.h"
#include "jwStage1_BG_header.h"
#include "jwGround_Veggie.h"
#include "jwObject.h"
#include "jwSceneLoad_In.h"
#include "jwtestEnemy.h"


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
		//override를 써서 자식쪽으로 오지만 부모쪽 함수로 지정가능
		Scene::Initialize();

		object::Instantiate<Cuphead>(Vector2(100.0f, 800.0f), eLayerType::Player);
		object::Instantiate<Stage1_BG1>(eLayerType::BG);
		//object::Instantiate<Stage1_BG2>(eLayerType::BG3);
		object::Instantiate<Veggie_Onion>(Vector2(1100.0f, 800.0f), eLayerType::Monster);
		object::Instantiate<Ground_Veggie>(Vector2(-1.0f, 800.0f), eLayerType::Ground);
		object::Instantiate<testEnemy>(Vector2(300.0f, 500.0f), eLayerType::ParryObj);


		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::ParryObj, true);
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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::ParryObj, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);

		object::Instantiate<SceneLoad_In>(Vector2(800.0f, 900.0f), eLayerType::UI);
	}
	void PlayScene::OnExit()
	{
	}
	
}