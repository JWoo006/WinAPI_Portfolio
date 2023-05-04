#include "jwPirateScene.h"
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

#include "jwPirate_BG.h"
#include "jwPirate_BG_Dock.h"
#include "jwPirate_BG_Sky.h"
#include "jwPirate_Ship_A.h"
#include "jwPirate_Barrel.h"
#include "jwPirate_Captain.h"
#include "jwPirate_Ship_B.h"

#include "jwResources.h"
#include "jwSound.h"


namespace jw
{
	PirateScene::PirateScene()
	{
	}
	PirateScene::~PirateScene()
	{
	}
	void PirateScene::Initialize()
	{
		//override를 써서 자식쪽으로 오지만 부모쪽 함수로 지정가능
		Scene::Initialize();

		mIntroSound1 = Resources::Load<Sound>(L"sfx_level_announcer_0001_c", L"..\\Resources\\Sound\\Announcer\\sfx_level_announcer_0001_c.wav");
		mIntroSound2 = Resources::Load<Sound>(L"sfx_level_announcer_0002_c", L"..\\Resources\\Sound\\Announcer\\sfx_level_announcer_0002_c.wav");
		mBGSound = Resources::Load<Sound>(L"MUS_Pirate", L"..\\Resources\\Sound\\Pirate\\MUS_Pirate.wav");

		object::Instantiate<Pirate_BG_Sky>(Vector2(-1.0f, 800.0f), eLayerType::BG);
		object::Instantiate<Pirate_BG>(Vector2(800.0f, 900.0f), eLayerType::BG);
		object::Instantiate<Pirate_BG_Dock>(Vector2(0.0f, 700.0f), eLayerType::BG);

		object::Instantiate<BasicGround>(Vector2(-1.0f, 800.0f), eLayerType::Ground);




		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BossBullet, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::ParryBullet, true);
	}
	void PirateScene::Update()
	{
		if (mbIntroSoundChecker)
		{
			mIntroSoundTimer += Time::DeltaTime();

			if (mIntroSoundTimer > 4.0f && mbIntroSoundChecker)
			{
				mbIntroSoundChecker = false;
				mIntroSound2->Play(false);
			}
		}

		mTime += Time::DeltaTime();

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			int next = (int)eSceneType::WorldStage;

			SceneManager::LoadScene((eSceneType)next);

		}


		if (mSceneLoad_In && mSceneLoad_In->EndCheck())
		{

			mSceneLoad_In->SetEndCheck(false);

			mCupheadAnimator->Play(L"CupheadIntro", false);
			mCaptain_Animator->Play(L"Captainintro_start", false);
			object::Destroy(mSceneLoad_In);
		}

		if (mTime > 1.0f && !mbTimeStop)
		{
			mTime = 0.0f;
			mbTimeStop = true;
			FightTextShow();
		}

		if (mCaptain && mShip_A && mShip_A->GetIsBossOut())
		{
			object::Destroy(mCaptain);
			mCaptain = nullptr;
			//object::Destroy(mShip_A);
			//mShip_A = nullptr;
		}

		if (mShip_A && mShip_A->GetIsBossLeave())
		{
			object::Destroy(mShip_A);
			mShip_A = nullptr;

			boss2HP = 40;
			StageInfo stageinfo2;
			stageinfo2.pBossHp = &boss2HP;
			stageinfo2.pCuphead = mCuphead;

			mShip_B = object::Instantiate<Pirate_Ship_B>(Vector2(1400.0f, 1000.0f), eLayerType::Monster, stageinfo2.pCuphead, stageinfo2.pBossHp);
		}

		if (mShip_B && mShip_B->GetIsBossOut() && !mbShip_B_DeadChecker)
		{
			mbShip_B_DeadChecker = true;

			mBarrel->SetBarrelState(Pirate_Barrel::ePirate_Barrel_State::Death);

			SceneManager::SetNextSceneType(eSceneType::Score);
			object::Instantiate<SceneLoad>(Vector2(800.0f, 900.0f), eLayerType::UI);
		}


		Scene::Update();
	}
	void PirateScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		Scene::SceneText(hdc);
	}
	void PirateScene::Release()
	{
		Scene::Release();
	}
	void PirateScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BG22, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BossBullet, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::BossBullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::ParryBullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::ParryObject, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::BossBullet, eLayerType::Ground, true);

		mSceneLoad_In = object::Instantiate<SceneLoad_In>(Vector2(800.0f, 900.0f), eLayerType::UI);

		mTime = 0.0f;
		mbTimeStop = false;

		if (mCuphead == nullptr)
		{
			mCuphead = object::Instantiate<Cuphead>(Vector2(100.0f, 800.0f), eLayerType::Player);
			mCupheadAnimator = mCuphead->GetComponent<Animator>();
			mCupheadAnimator->GetCompleteEvent(L"CupheadIntro") = std::bind(&PirateScene::CupheadIntroCompleteEvent, this);
		}

		bossHP = 150;
		StageInfo stageinfo;
		stageinfo.pBossHp = &bossHP;
		stageinfo.pCuphead = mCuphead;


		mShip_A = object::Instantiate<Pirate_Ship_A>(Vector2(1400.0f, 1000.0f), eLayerType::BG22, stageinfo.pCuphead, stageinfo.pBossHp);
		//mShip_A->SetBossLeave(true);
		//mShip_A->SetBossOut(true);
		mBarrel = object::Instantiate<Pirate_Barrel>(Vector2(1100.0f, 200.0f), eLayerType::BG22, stageinfo.pCuphead, stageinfo.pBossHp);

		mCaptain = object::Instantiate<Pirate_Captain>(Vector2(1400.0f, 550.0f), eLayerType::Monster, stageinfo.pCuphead, stageinfo.pBossHp);
		mCaptain_Animator = mCaptain->GetComponent<Animator>();

	}
	void PirateScene::OnExit()
	{
		object::Destroy(mCuphead);
		mCuphead = nullptr;
	}

	void PirateScene::CupheadIntroCompleteEvent()
	{
		mCupheadAnimator->Play(L"CupheadIdle_R", true);
		mBarrel->SetBarrelState(Pirate_Barrel::ePirate_Barrel_State::Idle);
	}

	void PirateScene::BossIntroCompleteEvent()
	{

	}

	void PirateScene::FightTextShow()
	{
		ftw = object::Instantiate<FightText_WALLOP>(Vector2(800.0f, 900.0f), eLayerType::UI);
		mFightTextAnimator = ftw->GetComponent<Animator>();
		mFightTextAnimator->GetCompleteEvent(L"ImageFightText") = std::bind(&PirateScene::FightStart, this);

		mIntroSound1->Play(false);
		mBGSound->Play(true);
		mbIntroSoundChecker = true;

	}

	void PirateScene::FightStart()
	{
		object::Destroy(ftw);
		// 보스 공격 시작
	}

}