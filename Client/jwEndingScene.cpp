#include "jwEndingScene.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwResources.h"
#include "jwObject.h"
#include "jwFade_In_Rectangle.h"
#include "jwFade_Out_Rectangle.h"
 
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
		
		Fade_In_Rectangle* fadein = object::Instantiate<Fade_In_Rectangle>(Vector2::Zero, eLayerType::Effect);
		
	}
	void EndingScene::OnExit()
	{
		//Fade_Out_Rectangle* fadeout = object::Instantiate<Fade_Out_Rectangle>(Vector2::Zero, eLayerType::Effect);
	}
}