#include "jwTestPlayScene.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwCollisionManager.h"
#include "jwObject.h"
#include "jwObject.h"
#include "jwAnimator.h"
#include "jwTime.h"

#include "jwCuphead.h"
#include "jwGround_Veggie.h"
#include "jwStageGround.h"



namespace jw
{
	TestPlayScene::TestPlayScene()
	{
	}
	TestPlayScene::~TestPlayScene()
	{
	}
	void TestPlayScene::Initialize()
	{
		//override를 써서 자식쪽으로 오지만 부모쪽 함수로 지정가능
		Scene::Initialize();

		mTime = 0.0f;
		mbTimeStop = false;

		mCuphead = object::Instantiate<Cuphead>(Vector2(100.0f, 800.0f), eLayerType::Player);
		mCupheadAnimator = mCuphead->GetComponent<Animator>();
		mCupheadAnimator->GetCompleteEvent(L"CupheadIntro") = std::bind(&TestPlayScene::CupheadIntroCompleteEvent, this);

		object::Instantiate<StageGround>(Vector2(-1.0f, 800.0f), eLayerType::Ground);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BossBullet, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::ParryObj, true);
	}
	void TestPlayScene::Update()
	{
		mTime += Time::DeltaTime();

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			int next = (int)eSceneType::Play_Veggie;
			next++;
			if (next == (int)eSceneType::End)
			{
				next = (int)eSceneType::Title;
			}

			next = (int)eSceneType::Score;

			SceneManager::LoadScene((eSceneType)next);
		}

		if (mTime > 1.0f && !mbTimeStop)
		{
			mTime = 0.0f;
			mbTimeStop = true;
			FightTextShow();
		}

		Scene::Update();
	}
	void TestPlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		Scene::SceneText(hdc);
	}
	void TestPlayScene::Release()
	{
		Scene::Release();
	}
	void TestPlayScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BossBullet, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::BossBullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::ParryObj, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::BossBullet, eLayerType::Ground, true);


		mSceneLoad_In = object::Instantiate<SceneLoad_In>(Vector2(800.0f, 900.0f), eLayerType::UI);

	}
	void TestPlayScene::OnExit()
	{
	}

	void TestPlayScene::CupheadIntroCompleteEvent()
	{
		mCupheadAnimator->Play(L"CupheadIdle_R", true);
	}

	void TestPlayScene::BossIntroCompleteEvent()
	{

	}

	void TestPlayScene::FightTextShow()
	{
		//ftw = object::Instantiate<FightText_WALLOP>(Vector2(800.0f, 900.0f), eLayerType::UI);
		//mFightTextAnimator = ftw->GetComponent<Animator>();
		//mFightTextAnimator->GetCompleteEvent(L"ImageFightText") = std::bind(&TestPlayScene::FightStart, this);

		
	}

	void TestPlayScene::FightStart()
	{
		object::Destroy(ftw);
		// 보스 공격 시작
	}

}