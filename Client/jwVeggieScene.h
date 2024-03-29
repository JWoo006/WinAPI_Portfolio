#pragma once
#include "jwScene.h"

namespace jw
{
	class Background;
	class Cuphead;
	class Boss;
	class Sound;
	class VeggieScene : public Scene
	{
	public:
		VeggieScene();
		~VeggieScene();

		struct stageInfo
		{
			int* BossHPptr;
			Cuphead* cupheadptr;
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
		FightText_WALLOP* ftw;

		Cuphead* mCuphead;
		class Animator* mCupheadAnimator;

		class Veggie_Potato* mBossPotato;
		class PotatoIntroEffect* mBossPotatoEffect;
		bool PotatoShow;
		bool PotatoDeadChecker;

		class Veggie_Onion* mBossOnion;
		class PotatoIntroEffect* mBossOnionEffect;
		bool OnionShow;
		bool OnionDeadChecker;

		class Veggie_Carrot* mBossCarrot;
		class PotatoIntroEffect* mBossCarrotEffect;
		bool CarrotShow;
		bool CarrotDeadChecker;

		class SceneLoad_In* mSceneLoad_In;

		float mTime;
		bool mbTimeStop;
		class Animator* mFightTextAnimator;
	};
}
