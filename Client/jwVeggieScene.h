#pragma once
#include "jwScene.h"

namespace jw
{
	class Background;
	class Cuphead;
	class Boss;
	class VeggieScene : public Scene
	{
	public:
		VeggieScene();
		~VeggieScene();

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
		class FightText_WALLOP* ftw;

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
