#include "jwEndingScene.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwResources.h"
 
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
	}
	void EndingScene::OnExit()
	{
	}
}