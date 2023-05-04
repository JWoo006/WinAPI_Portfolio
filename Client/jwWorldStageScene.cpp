#include "jwWorldStageScene.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwResources.h"
#include "jwCamera.h"
#include "jwObject.h"
#include "jwCollisionManager.h"
#include "jwSceneLoad.h"

#include "jwSound.h"

#include "jwCuphead_Stage.h"
#include "jwSceneLoad_In.h"
#include "jwWorldMap1.h"
#include "jwVeggieWorldIcon.h"
#include "jwFrogWorldIcon.h"
#include "jwPirateWorldIcon.h"

namespace jw
{
	WorldStageScene::WorldStageScene()
		: mTime(0.0f)
	{
	}
	WorldStageScene::~WorldStageScene()
	{
	}
	void WorldStageScene::Initialize()
	{
		//override를 써서 자식쪽으로 오지만 부모쪽 함수로 지정가능
		Scene::Initialize();

		mainSound = Resources::Load<Sound>(L"WorldMapTheme", L"..\\Resources\\Sound\\WorldMap\\bgm_map_world_1.wav");

		mCuphead_Stage = object::Instantiate<Cuphead_Stage>(eLayerType::Player);
		
		object::Instantiate<WorldMap1>(Vector2::Zero, eLayerType::BG);
		mVeggieWorldIcon = object::Instantiate<VeggieWorldIcon>(Vector2(700.0f, 900.0f), eLayerType::BG);
		mFrogWorldIcon = object::Instantiate<FrogWorldIcon>(Vector2(330.0f, 730.0f), eLayerType::BG);
		mPirateWorldIcon = object::Instantiate<PirateWorldIcon>(Vector2(330.0f, 230.0f), eLayerType::BG);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BG, true);

		Camera::SetTarget(mCuphead_Stage);
	}
	void WorldStageScene::Update()
	{

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			int next = (int)eSceneType::WorldStage;
			next++;
			if (next == (int)eSceneType::End)
			{
				next = (int)eSceneType::Title;
			}

			next = (int)eSceneType::TestPlay;

			SceneManager::LoadScene((eSceneType)next);
		}

		if (mCuphead_Stage->GetIsShowIcon())
		{
			std::wstring iconName = mCuphead_Stage->GetIconName();

			if (Input::GetKeyState(eKeyCode::Z) == eKeyState::Down && iconName == L"VeggieIcon")
			{
				mainSound->Stop(true);

				mNextScene = (int)mVeggieWorldIcon->GetLoadSceneType();
				SceneManager::SetNextSceneType((eSceneType)mNextScene);

				Transform* tr = mCuphead_Stage->GetComponent<Transform>();
				object::Instantiate<SceneLoad>(Vector2(tr->GetPos().x, tr->GetPos().y + 450.0f), eLayerType::UI);
			}

			if (Input::GetKeyState(eKeyCode::Z) == eKeyState::Down && iconName == L"FrogIcon")
			{
				mainSound->Stop(true);

				mNextScene = (int)mFrogWorldIcon->GetLoadSceneType();
				SceneManager::SetNextSceneType((eSceneType)mNextScene);

				Transform* tr = mCuphead_Stage->GetComponent<Transform>();
				object::Instantiate<SceneLoad>(Vector2(tr->GetPos().x, tr->GetPos().y + 450.0f), eLayerType::UI);
			}

			if (Input::GetKeyState(eKeyCode::Z) == eKeyState::Down && iconName == L"PirateIcon")
			{
				mainSound->Stop(true);

				mNextScene = (int)mPirateWorldIcon->GetLoadSceneType();
				SceneManager::SetNextSceneType((eSceneType)mNextScene);

				Transform* tr = mCuphead_Stage->GetComponent<Transform>();
				object::Instantiate<SceneLoad>(Vector2(tr->GetPos().x, tr->GetPos().y + 450.0f), eLayerType::UI);
			}
		}

		
		Scene::Update();
	}
	void WorldStageScene::Render(HDC hdc)
	{
		Graphics graphic(hdc);
		Vector2 renderPos = Camera::CalculatePos(Vector2(-1000.0f, -700.0f));
		
		Scene::Render(hdc);

		Scene::SceneText(hdc);
	}
	void WorldStageScene::Release()
	{
	}
	void WorldStageScene::OnEnter()
	{
		//Scene::OnEnter();

		Transform* tr = mCuphead_Stage->GetComponent<Transform>();
		
		//Vector2 pos = Camera::GetLookPos();

		object::Instantiate<SceneLoad_In>(Vector2(tr->GetPos().x, tr->GetPos().y + 450.0f), eLayerType::UI);
		Camera::SetTarget(mCuphead_Stage);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BG, true);

		mainSound->Play(true);
	}
	void WorldStageScene::OnExit()
	{
		//mainSound->Stop(true);
	}
}