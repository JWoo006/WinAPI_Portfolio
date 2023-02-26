#include "jwTitleScene.h"
#include "jwInput.h"
#include "jwSceneManager.h"
#include "jwResources.h"

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
		mImage = Resources::Load<Image>(L"Background1", L"..\\Resources\\Image\\Title_Screen\\Background\\title_screen_background #262704.bmp");
		mImage2 = Resources::Load<Image>(L"Background2", L"..\\Resources\\Image\\Title_Screen\\Background\\cuphead_title_screen_0003 #262339.bmp");
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
		GdiTransparentBlt(hdc, 300, 270, mImage2->GetWidth(), mImage2->GetHeight()
			, mImage2->GetHdc(), 0, 0, mImage2->GetWidth(), mImage2->GetHeight(), RGB(255, 0, 255));

		//BitBlt(hdc, 0, 0, mImage2->GetWidth(), mImage2->GetHeight(), mImage2->GetHdc(), 0, 0, SRCCOPY);

		Scene::SceneText(hdc);
	}
	void TitleScene::Release()
	{
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}