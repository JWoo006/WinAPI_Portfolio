#include "jwTestPlayScene.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwCollisionManager.h"
#include "jwObject.h"
#include "jwObject.h"
#include "jwAnimator.h"
#include "jwRigidbody.h"
#include "jwTime.h"

#include "jwCuphead.h"
#include "jwBasicGround.h"
#include "jwGround_Veggie.h"
#include "jwFightText_WALLOP.h"
#include "jwSceneLoad_In.h"
#include "jwSceneLoad.h"

#include "jwFrogStageBG.h"
#include "jwSFrog.h"
#include "jwTFrog.h"
#include "jwTFrog_Slot.h"

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


		object::Instantiate<FrogStageBG>(eLayerType::BG);

		object::Instantiate<BasicGround>(Vector2(-1.0f, 800.0f), eLayerType::Ground);
		//object::Instantiate<Ground_Veggie>(Vector2(-1.0f, 800.0f), eLayerType::Ground);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BossBullet, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::ParryBullet, true);
	}
	void TestPlayScene::Update()
	{
		mTime += Time::DeltaTime();

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			int next = (int)eSceneType::WorldStage;
			
			SceneManager::LoadScene((eSceneType)next);	

		} 

		if (mSceneLoad_In && mSFrog && mTFrog && mSceneLoad_In->EndCheck())
		{

			mSceneLoad_In->SetEndCheck(false);

			mCupheadAnimator->Play(L"CupheadIntro", false);
			mTFrogAnimator->Play(L"TFrogintro", false);
			object::Destroy(mSceneLoad_In);
		}

		if (mTime > 1.0f && !mbTimeStop)
		{
			mTime = 0.0f;
			mbTimeStop = true;
			FightTextShow();
		}

		// 1페이즈 패턴 분기
		if (mSFrog && mTFrog && mSFrog->GetisFireFlyOn())
		{
			mSFrog->SetbFireFlyOn(false);
			mTFrog->SetbFireFlyOn(true);
		}
		if (mSFrog && mTFrog && mTFrog->GetRollOn())
		{
			mTFrog->SetRollOn(false);
			mSFrog->SetRollOn(true);
		}
		if (mSFrog && mTFrog && mSFrog->GetFanOn())
		{
			mSFrog->SetFanOn(false);
			mTFrog->SetFanOn(true);
		}

		if (mTFrog && mTFrog->GetTFrogState() == TFrog::eTFrogState::Death)
		{
			CollisionManager::SetLayer(eLayerType::Player, eLayerType::BossBullet, false);
		}

		if (mTFrog_Slot && mTFrog_Slot->GetTFrog_SlotState() == TFrog_Slot::eTFrog_SlotState::Death)
		{
			CollisionManager::SetLayer(eLayerType::Player, eLayerType::BossBullet, false);
		}

		if (mTFrog && mTFrog->GetIsBossOut() )
		{
			object::Destroy(mTFrog);
			mTFrog = nullptr;
			
			bossHP = 250;
			StageInfo stageinfo2;
			stageinfo2.pBossHp = &bossHP;
			stageinfo2.pCuphead = mCuphead;

			CollisionManager::SetLayer(eLayerType::Player, eLayerType::BossBullet, true);

			mTFrog_Slot = object::Instantiate<TFrog_Slot>(Vector2(1400.0f, 800.0f), eLayerType::Monster, stageinfo2.pCuphead, stageinfo2.pBossHp);
			mTFrog_SlotAnimator = mTFrog_Slot->GetComponent<Animator>();

		}

		if (mTFrog_Slot && mTFrog_Slot->GetIsBossOut() && !mbTFrog_SlotDeadChecker)
		{
			mbTFrog_SlotDeadChecker = true;
			SceneManager::SetNextSceneType(eSceneType::Score);
			object::Instantiate<SceneLoad>(Vector2(800.0f, 900.0f), eLayerType::UI);
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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::ParryBullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::ParryObject, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::BossBullet, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Monster, true);

		mSceneLoad_In = object::Instantiate<SceneLoad_In>(Vector2(800.0f, 900.0f), eLayerType::UI);

		mTime = 0.0f;
		mbTimeStop = false;

		if (mCuphead == nullptr)
		{
			mCuphead = object::Instantiate<Cuphead>(Vector2(100.0f, 800.0f), eLayerType::Player);
			mCupheadAnimator = mCuphead->GetComponent<Animator>();
			mCupheadAnimator->GetCompleteEvent(L"CupheadIntro") = std::bind(&TestPlayScene::CupheadIntroCompleteEvent, this);
		}

		// 보스 체력 설정
		bossHP = 200;
		StageInfo stageinfo;
		stageinfo.pBossHp = &bossHP;
		stageinfo.pCuphead = mCuphead;

		mTFrog = object::Instantiate<TFrog>(Vector2(1400.0f, 800.0f), eLayerType::Monster, stageinfo.pCuphead, stageinfo.pBossHp);
		mTFrogAnimator = mTFrog->GetComponent<Animator>();
		mTFrogAnimator->GetCompleteEvent(L"TFrogintro") = std::bind(&TestPlayScene::BossIntroCompleteEvent, this);

		//mTFrog->SetIsBossOut(true);

		mSFrog = object::Instantiate<SFrog>(Vector2(1200.0f, 800.0f), eLayerType::Monster, stageinfo.pCuphead, stageinfo.pBossHp);
		mSFrog->SetbFistOn(true);
		mSFrogAnimator = mSFrog->GetComponent<Animator>();

	}
	void TestPlayScene::OnExit()
	{
		object::Destroy(mCuphead);
		mCuphead = nullptr;
	}

	void TestPlayScene::CupheadIntroCompleteEvent()
	{
		mCupheadAnimator->Play(L"CupheadIdle_R", true);
	}

	void TestPlayScene::BossIntroCompleteEvent()
	{
		mSFrogAnimator->Play(L"SFrogintro", true);
		mTFrogAnimator->Play(L"TFrogidle", true);
	}

	void TestPlayScene::FightTextShow()
	{
		ftw = object::Instantiate<FightText_WALLOP>(Vector2(800.0f, 900.0f), eLayerType::UI);
		mFightTextAnimator = ftw->GetComponent<Animator>();
		mFightTextAnimator->GetCompleteEvent(L"ImageFightText") = std::bind(&TestPlayScene::FightStart, this);
	
	}

	void TestPlayScene::FightStart()
	{
		object::Destroy(ftw);
		// 보스 공격 시작
	}

}