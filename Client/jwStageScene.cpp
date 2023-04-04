#include "jwStageScene.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwResources.h"
#include "jwCuphead_Stage.h"
#include "jwCamera.h"
#include "jwObject.h"
#include "jwSceneLoad_In.h"
#include "jwWorldMap1.h"
#include "jwVeggieWorldIcon.h"
#include "jwCollisionManager.h"
#include "jwSceneLoad.h"

namespace jw
{
	StageScene::StageScene()
		: mTime(0.0f)
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
		
		object::Instantiate<WorldMap1>(Vector2::Zero, eLayerType::BG);
		mVeggieWorldIcon = object::Instantiate<VeggieWorldIcon>(Vector2(700.0f, 900.0f), eLayerType::BG);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BG, true);

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

		if (mCuphead_Stage->GetIsShowIcon())
		{
			if (Input::GetKeyState(eKeyCode::Z) == eKeyState::Down)
			{
				mNextScene = (int)mVeggieWorldIcon->GetLoadSceneType();
				SceneManager::SetNextSceneType((eSceneType)mNextScene);

				Transform* tr = mCuphead_Stage->GetComponent<Transform>();
				object::Instantiate<SceneLoad>(Vector2(tr->GetPos().x, tr->GetPos().y + 450.0f), eLayerType::UI);

				//object::Instantiate<SceneLoad>(Vector2(800.0f, 1130.0f), eLayerType::UI);
			}
		}

		
		Scene::Update();
	}
	void StageScene::Render(HDC hdc)
	{
		Graphics graphic(hdc);
		Vector2 renderPos = Camera::CalculatePos(Vector2(-1000.0f, -700.0f));
		
		Scene::Render(hdc);

		Scene::SceneText(hdc);
	}
	void StageScene::Release()
	{
	}
	void StageScene::OnEnter()
	{
		//Scene::OnEnter();

		Transform* tr = mCuphead_Stage->GetComponent<Transform>();
		
		//Vector2 pos = Camera::GetLookPos();

		object::Instantiate<SceneLoad_In>(Vector2(tr->GetPos().x, tr->GetPos().y + 450.0f), eLayerType::UI);
		Camera::SetTarget(mCuphead_Stage);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BG, true);
	}
	void StageScene::OnExit()
	{
		
	}
}