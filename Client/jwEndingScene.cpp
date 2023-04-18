#include "jwEndingScene.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwResources.h"
#include "jwObject.h"	

#include "jwSceneLoad.h"
#include "jwSceneLoad_In.h"
#include "jwWinscreen_BG1.h"
#include "jwWinscreen_Cuphead.h"
#include "jwWinscreen_Board.h"
#include "jwWinscreen_ResultAnim.h"
 
namespace jw
{
	EndingScene::EndingScene()
	{
	}
	EndingScene::~EndingScene()
	{
	}
	void EndingScene::Initialize()
	{
		//override를 써서 자식쪽으로 오지만 부모쪽 함수로 지정가능
		Scene::Initialize();

		object::Instantiate<Winscreen_BG1>( Vector2(-100.0f, -200.0f), eLayerType::BG);
		object::Instantiate<Winscreen_Cuphead>(Vector2(500.0f, 800.0f), eLayerType::BG);
		object::Instantiate<Winscreen_Board>(Vector2(700.0f, 300.0f), eLayerType::BG);
		object::Instantiate<Winscreen_ResultAnim>(Vector2(800.0f, 200.0f), eLayerType::BG);

	}
	void EndingScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			int next = (int)eSceneType::Ending;
			next++;
			if (next == (int)eSceneType::End)
			{
				next = (int)eSceneType::Title;
			}

			SceneManager::LoadScene((eSceneType)next);

		}

		Scene::Update();
	}
	void EndingScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		Scene::SceneText(hdc);
	}
	void EndingScene::Release()
	{
	}
	void EndingScene::OnEnter()
	{
		object::Instantiate<SceneLoad_In>(Vector2(800.0f, 900.0f), eLayerType::UI);
	}
	void EndingScene::OnExit()
	{
		//Fade_Out_Rectangle* fadeout = object::Instantiate<Fade_Out_Rectangle>(Vector2::Zero, eLayerType::Effect);
	}
}