#include "jwTitleScene.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwResources.h"
#include "jwTitleAnim1.h"
#include "jwTitleAnim2.h"
#include "jwTitleAnim3.h"
#include "jwObject.h"
#include "jwCamera.h"


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
		//override를 써서 자식쪽으로 오지만 부모쪽 함수로 지정가능
		Scene::Initialize();

		object::Instantiate<TitleAnim1>(Vector2(800.0f, 800.0f), eLayerType::BG);
		object::Instantiate<TitleAnim2>(Vector2(500.0f, 800.0f), eLayerType::BG);
		object::Instantiate<TitleAnim3>(Vector2(1100.0f, 800.0f), eLayerType::BG);

		mImage = Resources::Load<Image>(L"Background1", L"..\\Resources\\Image\\Title_Screen\\Background\\title_screen_background #262704.bmp");
		mImage2 = Resources::Load<Image>(L"Background2", L"..\\Resources\\Image\\Title_Screen\\Background\\title_chips_left_0001 #262672.bmp");
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			mNextScene = (int)eSceneType::Title;
			mNextScene++;
			if (mNextScene == (int)eSceneType::End)
			{
				mNextScene = (int)eSceneType::Title;
			}

			SceneManager::LoadScene((eSceneType)mNextScene);
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