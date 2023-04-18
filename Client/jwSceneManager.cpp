#include "jwSceneManager.h"
#include "jwPlayScene.h"
#include "jwTitleScene.h"
#include "jwEndingScene.h"
#include "jwStageScene.h"
#include "jwToolScene.h"
#include "jwCollisionManager.h"
#include "jwCamera.h"

namespace jw
{
    std::vector<Scene*> SceneManager::mScenes = {};
    Scene* SceneManager::mActiveScene = nullptr;
    eSceneType SceneManager::mNextScene = eSceneType::End;

    void SceneManager::Initialize()
    {
        mScenes.resize((UINT)eSceneType::End);


        mScenes[(UINT)eSceneType::Title] = new TitleScene();
        mScenes[(UINT)eSceneType::Title]->SetName(L"TitleScene");
        mScenes[(UINT)eSceneType::Stage] = new StageScene();
        mScenes[(UINT)eSceneType::Stage]->SetName(L"StageScene");
        mScenes[(UINT)eSceneType::Play] = new PlayScene();
        mScenes[(UINT)eSceneType::Play]->SetName(L"PlayScene");
        mScenes[(UINT)eSceneType::Ending] = new EndingScene();
        mScenes[(UINT)eSceneType::Ending]->SetName(L"EndingScene");

        for (Scene* scene : mScenes)
        {
            if (scene == nullptr)
            {
                continue;
            }

            scene->Initialize();
        }

        // ÇöÀç »ç¿ëÇÒ ¾À ¼³Á¤
        mActiveScene = mScenes[(UINT)eSceneType::Title];
    }
    void SceneManager::Update()
    {
        mActiveScene->Update();
    }
    void SceneManager::Render(HDC hdc)
    {
        mActiveScene->Render(hdc);
    }
    void SceneManager::Destroy()
    {
        mActiveScene->Destroy();
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
        Camera::Clear();

        // ÇöÀç¾À
        mActiveScene->OnExit();
        CollisionManager::Clear();
        
        // ´ÙÀ½¾À
        mActiveScene = mScenes[(UINT)type];
        mActiveScene->OnEnter();
    }
}