#pragma once
#include "jwScene.h"
#include "jwImage.h"

namespace jw
{
	class Cuphead_Stage;
	class VeggieWorldIcon;
	class WorldStageScene : public Scene
	{
	public:
		WorldStageScene();
		~WorldStageScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;


	private:
		Image* mImage;
		float mTime;
		int mNextScene;
		Cuphead_Stage* mCuphead_Stage;
		VeggieWorldIcon* mVeggieWorldIcon;
	};
}


