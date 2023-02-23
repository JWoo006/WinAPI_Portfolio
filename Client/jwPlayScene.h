#pragma once
#include "jwScene.h"

namespace jw
{
	class Cuphead;
	class Background;
	class Boss;
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;


	private:
		Cuphead* mCuphead;
		Background* mbackground;
		Boss* mBoss;
	};
}
