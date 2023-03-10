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
		//override를 써서 자식쪽으로 오지만 부모쪽 함수로 지정가능
		Scene::Initialize();
		
		mCuphead_Stage = object::Instantiate<Cuphead_Stage>(eLayerType::Player);

		Camera::SetTarget(mCuphead_Stage);
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