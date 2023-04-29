#include "jwVeggieScene.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwCollisionManager.h"
#include "jwObject.h"
#include "jwObject.h"
#include "jwAnimator.h"
#include "jwTime.h"

#include "jwCuphead.h"
#include "jwGround_Veggie.h"
#include "jwStage1_BG_header.h"
#include "jwVeggie_Potato.h"
#include "jwPotatoIntroEffect.h"
#include "jwVeggie_Onion.h"
#include "jwVeggie_Carrot.h"
#include "jwtestEnemy.h"
#include "jwFightText_WALLOP.h"
#include "jwSceneLoad_In.h"
#include "jwSceneLoad.h"
#include "jwCarrot_Bomb.h"


namespace jw
{
	VeggieScene::VeggieScene()
	{
	}
	VeggieScene::~VeggieScene()
	{
	}
	void VeggieScene::Initialize()
	{
		//override를 써서 자식쪽으로 오지만 부모쪽 함수로 지정가능
		Scene::Initialize();

		PotatoShow = false;
		OnionShow = false;
		CarrotShow = false;

		PotatoDeadChecker = false;
		OnionDeadChecker = false;
		CarrotDeadChecker = false;

		mTime = 0.0f;
		mbTimeStop = false;

		object::Instantiate<Stage1_BG1>(eLayerType::BG);
		//object::Instantiate<Stage1_BG2>(eLayerType::BG3);

		object::Instantiate<Ground_Veggie>(Vector2(-1.0f, 800.0f), eLayerType::Ground);
		
		//object::Instantiate<testEnemy>(Vector2(300.0f, 500.0f), eLayerType::ParryObj);
		


		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BossBullet, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::ParryBullet, true);
	}
	void VeggieScene::Update()
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

		if (mSceneLoad_In->EndCheck())
		{
			mSceneLoad_In->SetEndCheck(false);
			
			mCupheadAnimator->Play(L"CupheadIntro", false);
		}

		if (mTime > 1.0f && !mbTimeStop)
		{
			mTime = 0.0f;
			mbTimeStop = true;
			FightTextShow();
		}

		// 감자
		if (mBossPotatoEffect != nullptr && !PotatoShow && mBossPotatoEffect->GetisShow())
		{
			PotatoShow = true;
			mBossPotato = object::Instantiate<Veggie_Potato>(Vector2(1300.0f, 800.0f), eLayerType::Monster);
			mBossPotato->SetShow(true);
		}
		
		if (mBossPotato != nullptr && mBossPotato->GetIsBossOut())
		{
			PotatoDeadChecker = true;
			object::Destroy(mBossPotatoEffect);
		}


		// 양파
		if (!OnionShow && PotatoDeadChecker)
		{
			OnionShow = true;
			mBossOnionEffect = object::Instantiate<PotatoIntroEffect>(Vector2(800.0f, 850.0f), eLayerType::Effect);
		}
		if (OnionShow && PotatoDeadChecker && mBossOnionEffect->GetisShow() && !OnionDeadChecker)
		{
			mBossOnionEffect->SetShow(false);
			mBossOnion = object::Instantiate<Veggie_Onion>(Vector2(800.0f, 800.0f), eLayerType::Monster);
			mBossOnion->SetShow(true);
		}
		if (mBossOnion != nullptr && mBossOnion->GetIsBossOut())
		{
			OnionDeadChecker = true;
			object::Destroy(mBossOnionEffect);
		}

		// 당근
		if (!CarrotShow && OnionDeadChecker && PotatoDeadChecker)
		{
			CarrotShow = true;
			mBossCarrotEffect = object::Instantiate<PotatoIntroEffect>(Vector2(800.0f, 700.0f), eLayerType::BG22);
			Transform* tr = mBossCarrotEffect->GetComponent<Transform>();
			tr->SetScale(Vector2(1.0f, 1.0f));
		}
		if (CarrotShow && PotatoDeadChecker && PotatoDeadChecker && mBossCarrotEffect->GetisShow())
		{
			mBossCarrotEffect->SetShow(false);
			mBossCarrot = object::Instantiate<Veggie_Carrot>(Vector2(800.0f, 650.0f), eLayerType::Monster, mCuphead);
			//object::Destroy(mBossCarrotEffect);
			mBossCarrot->SetShow(true);

		}
		if (mBossCarrot != nullptr && mBossCarrot->GetIsBossOut() && !CarrotDeadChecker)
		{
			CarrotDeadChecker = true;
			SceneManager::SetNextSceneType(eSceneType::Score);
			//SceneManager::LoadScene((eSceneType)mNextScene);
			object::Instantiate<SceneLoad>(Vector2(800.0f, 900.0f), eLayerType::UI);
		}

		Scene::Update();
	}
	void VeggieScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		Scene::SceneText(hdc);
	}
	void VeggieScene::Release()
	{
		Scene::Release();
	}
	void VeggieScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BossBullet, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::BossBullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::ParryBullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::BossBullet, eLayerType::Ground, true);

		mCuphead = object::Instantiate<Cuphead>(Vector2(100.0f, 800.0f), eLayerType::Player);
		mCupheadAnimator = mCuphead->GetComponent<Animator>();
		mCupheadAnimator->GetCompleteEvent(L"CupheadIntro") = std::bind(&VeggieScene::CupheadIntroCompleteEvent, this);

		mSceneLoad_In = object::Instantiate<SceneLoad_In>(Vector2(800.0f, 900.0f), eLayerType::UI);

	}
	void VeggieScene::OnExit()
	{
		object::Destroy(mCuphead);
		mCuphead = nullptr;
	}

	void VeggieScene::CupheadIntroCompleteEvent()
	{
		mCupheadAnimator->Play(L"CupheadIdle_R", true);
	}

	void VeggieScene::BossIntroCompleteEvent()
	{
		
	}

	void VeggieScene::FightTextShow()
	{
		ftw = object::Instantiate<FightText_WALLOP>(Vector2(800.0f, 900.0f), eLayerType::UI);
		mFightTextAnimator = ftw->GetComponent<Animator>();
		mFightTextAnimator->GetCompleteEvent(L"ImageFightText") = std::bind(&VeggieScene::FightStart, this);

		//감자
		mBossPotatoEffect = object::Instantiate<PotatoIntroEffect>(Vector2(1300.0f, 850.0f), eLayerType::Effect);
		
		//당근 테스트
		//mBossCarrotEffect = object::Instantiate<PotatoIntroEffect>(Vector2(800.0f, 700.0f), eLayerType::Effect);
		//Transform* tr = mBossCarrotEffect->GetComponent<Transform>();
		//tr->SetScale(Vector2(1.0f, 1.0f));
	}

	void VeggieScene::FightStart()
	{
		object::Destroy(ftw);
		// 보스 공격 시작
	}
	
}