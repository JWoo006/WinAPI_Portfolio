#pragma once
#include "jwScene.h"

namespace jw
{
	class Background;
	class Cuphead;
	class Animator;
	class Sound;
	class FrogScene : public Scene
	{
	public:
		FrogScene();
		~FrogScene();

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
		float mIntroSoundTimer;
		bool mbIntroSoundChecker;
		Sound* mIntroSound1;
		Sound* mIntroSound2;
		Sound* mBGSound;

		Background* mbackground;
		class FightText_WALLOP* ftw;

		Cuphead* mCuphead;
		Animator* mCupheadAnimator;

		int bossHP;
		int bossPattern;

		class SFrog* mSFrog;
		Animator* mSFrogAnimator;

		class TFrog* mTFrog;
		Animator* mTFrogAnimator;

		class TFrog_Slot* mTFrog_Slot;
		Animator* mTFrog_SlotAnimator;
		bool mbTFrog_SlotDeadChecker;

		class SceneLoad_In* mSceneLoad_In;

		float mTime;
		bool mbTimeStop;
		bool mbIntroStart;
		Animator* mFightTextAnimator;
	};
}

