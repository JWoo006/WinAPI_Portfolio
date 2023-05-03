#pragma once
#include "jwScene.h"
#include "jwImage.h"

namespace jw
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;


	private:
		Image* mImage;
		Image* mImage2;
		Image* mImage3;

		class Sound* mainSound;
		int mNextScene;
	};
}
