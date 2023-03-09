#include "jwStageScene.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwResources.h"
#include "jwCuphead_Stage.h"
#include "jwCamera.h"
#include "jwObject.h"

namespace jw
{
	StageScene::StageScene()
	{
	}
	StageScene::~StageScene()
	{
	}
	void StageScene::Initialize()
	{
		/*mCuphead_Stage = new Cuphead_Stage();
		AddGameObject(mCuphead_Stage, eLayerType::Player);*/

		object::Instantiate<Cuphead_Stage>(eLayerType::Player, eSceneType::Stage);

		Camera::SetTarget(mCuphead_Stage);

		//Scene::Initialize();

	}
	void StageScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			int next = (int)eSceneType::Stage;
			next++;
			if (next == (int)eSceneType::End)
			{
				next = (int)eSceneType::Title;
			}

			SceneManager::LoadScene((eSceneType)next);
		}

		Scene::Update();
	}
	void StageScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		Scene::SceneText(hdc);
	}
	void StageScene::Release()
	{
	}
	void StageScene::OnEnter()
	{

	}
	void StageScene::OnExit()
	{
	}
}