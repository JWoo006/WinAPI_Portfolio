#pragma once
#include "jwScene.h"

namespace jw
{
	class Background;
	class Cuphead;
	class Animator;
	class Sound;
	class TestPlayScene : public Scene
	{
	public:
		TestPlayScene();
		~TestPlayScene();

		struct StageInfo
		{
			int* pBossHp;
			Cuphead* pCuphead;
		};

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void CupheadIntroCompleteEvent();
		void BossIntroCompleteEvent();

		void FightTextShow();
		void FightStart();


	private:
		Background* mbackground;
		FightText_WALLOP* ftw;

		Cuphead* mCuphead;
		Animator* mCupheadAnimator;

		int bossHP;
		int boss2HP;
		int bossPattern;

		class Pirate_Ship_A* mShip_A;
		Animator* mShip_A_Animator;

		class Pirate_Ship_B* mShip_B;
		Animator* mShip_B_Animator;
		bool mbShip_B_DeadChecker;

		class Pirate_Captain* mCaptain;
		Animator* mCaptain_Animator;

		class Pirate_Barrel* mBarrel;

		float mIntroSoundTimer;
		bool mbIntroSoundChecker;
		Sound* mIntroSound1;
		Sound* mIntroSound2;
		Sound* mBGSound;

		class SceneLoad_In* mSceneLoad_In;

		float mTime;
		bool mbTimeStop;
		Animator* mFightTextAnimator;

		class Bubble_Bullet* mBubble;
	};
}
