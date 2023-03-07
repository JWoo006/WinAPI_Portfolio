#include "jwTitleScene.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwResources.h"
#include "jwTitleAnim1.h"
#include "jwTitleAnim2.h"
#include "jwTitleAnim3.h"


namespace jw
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		TitleAnim1* mTitle1 = new TitleAnim1();
		AddGameObject(mTitle1, eLayerType::BG);

		TitleAnim2* mTitle2 = new TitleAnim2();
		AddGameObject(mTitle2, eLayerType::BG);

		TitleAnim3* mTitle3 = new TitleAnim3();
		AddGameObject(mTitle3, eLayerType::BG);


		mImage = Resources::Load<Image>(L"Background1", L"..\\Resources\\Image\\Title_Screen\\Background\\title_screen_background #262704.bmp");
		mImage2 = Resources::Load<Image>(L"Background2", L"..\\Resources\\Image\\Title_Screen\\Background\\title_chips_left_0001 #262672.bmp");

		Scene::Initialize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			int next = (int)eSceneType::Title;
			next++;
			if (next == (int)eSceneType::End)
			{
				next = (int)eSceneType::Title;
			}

			SceneManager::LoadScene((eSceneType)next);
		}

		Scene::Update();
	}
	void TitleScene::Render(HDC hdc)
	{
		BitBlt(hdc, 0, 0, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
		
		Scene::Render(hdc);

		GdiTransparentBlt(hdc, 140, 720, mImage2->GetWidth(), mImage2->GetHeight()
			, mImage2->GetHdc(), 0, 0, mImage2->GetWidth(), mImage2->GetHeight(), RGB(255, 0, 255));


		Scene::SceneText(hdc);
	}
	void TitleScene::Release()
	{
		Scene::Release();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}