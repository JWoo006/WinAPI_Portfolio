#include "jwPlayScene.h"
#include "jwCuphead.h"
#include "jwBackground.h"
#include "jwBoss.h"
#include "jwVeggie_Onion.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwCollisionManager.h"
#include "jwObject.h"
#include "jwFade_In_Rectangle.h"
#include "jwFade_Out_Rectangle.h"


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

		object::Instantiate<Cuphead>(Vector2(100.0f, 700.0f), eLayerType::Player);
		object::Instantiate<Background>(eLayerType::BG);
		object::Instantiate< Veggie_Onion>(Vector2(1100.0f, 700.0f), eLayerType::Monster);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
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
		Fade_In_Rectangle* fadein = object::Instantiate<Fade_In_Rectangle>(Vector2::Zero, eLayerType::Effect);

	}
	void PlayScene::OnExit()
	{
		//Fade_Out_Rectangle* fadeout = object::Instantiate<Fade_Out_Rectangle>(Vector2::Zero, eLayerType::Effect);
		//fadeout->SetEnd(false);
	}
	
}