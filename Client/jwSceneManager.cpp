#include "jwSceneManager.h"
#include "jwPlayScene.h"
#include "jwTitleScene.h"

namespace jw
{
    std::vector<Scene*> SceneManager::mScenes = {};
    Scene* SceneManager::mActiveScene = nullptr;

    void SceneManager::Initialize()
    {
        mScenes.resize((UINT)eSceneType::End);


        mScenes[(UINT)eSceneType::Title] = new TitleScene();
        mScenes[(UINT)eSceneType::Title]->SetName(L"TitleScene");
        mScenes[(UINT)eSceneType::Play] = new PlayScene();
        mScenes[(UINT)eSceneType::Play]->SetName(L"PlayScene");

        // ÇöÀç »ç¿ëÇÒ ¾À ¼³Á¤
        mActiveScene = mScenes[(UINT)eSceneType::Title];

        for (Scene* scene : mScenes)
        {
            if (scene == nullptr)
            {
                continue;
            }

            scene->Initialize();
        }
    }
    void SceneManager::Update()
    {
        mActiveScene->Update();
    }
    void SceneManager::Render(HDC hdc)
    {
        mActiveScene->Render(hdc);
    }
    void SceneManager::Release()
    {
        for (Scene* scene : mScenes)
        {
            if (scene == nullptr)
            {
                continue;
            }

            delete scene;
            scene = nullptr;
        }
    }
    void SceneManager::LoadScene(eSceneType type)
    {
        // ÇöÀç¾À
        mActiveScene->OnExit();

        // ´ÙÀ½¾À
        mActiveScene = mScenes[(UINT)type];
        mActiveScene->OnEnter();
    }
}