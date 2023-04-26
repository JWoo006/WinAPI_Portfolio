#pragma once
#pragma once
#include "jwScene.h"

namespace jw
{
	class Background;
	class Cuphead;
	class Boss;
	class TestPlayScene : public Scene
	{
	public:
		TestPlayScene();
		~TestPlayScene();

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

		class SceneLoad_In* mSceneLoad_In;

		float mTime;
		bool mbTimeStop;
		class Animator* mFightTextAnimator;
	};
}
