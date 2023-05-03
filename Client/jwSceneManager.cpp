#include "jwSceneManager.h"
#include "jwVeggieScene.h"
#include "jwFrogScene.h"
#include "jwPirateScene.h"
#include "jwTitleScene.h"
#include "jwScoreScene.h"
#include "jwWorldStageScene.h"
#include "jwTestPlayScene.h"
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
        mScenes[(UINT)eSceneType::WorldStage] = new WorldStageScene();
        mScenes[(UINT)eSceneType::WorldStage]->SetName(L"WorldStageScene");
        mScenes[(UINT)eSceneType::Play_Veggie] = new VeggieScene();
        mScenes[(UINT)eSceneType::Play_Veggie]->SetName(L"VeggieScene");
        mScenes[(UINT)eSceneType::Play_Frog] = new FrogScene();
        mScenes[(UINT)eSceneType::Play_Frog]->SetName(L"FrogScene");
        mScenes[(UINT)eSceneType::Play_Pirate] = new PirateScene();
        mScenes[(UINT)eSceneType::Play_Pirate]->SetName(L"PirateScene");
        mScenes[(UINT)eSceneType::Score] = new ScoreScene();
        mScenes[(UINT)eSceneType::Score]->SetName(L"ScoreScene");
        mScenes[(UINT)eSceneType::TestPlay] = new TestPlayScene();
        mScenes[(UINT)eSceneType::TestPlay]->SetName(L"TestPlayScene");

        for (Scene* scene : mScenes)
        {
            if (scene == nullptr)
            {
                continue;
            }

            scene->Initialize();
        }

        // ÇöÀç »ç¿ëÇÒ ¾À ¼³Á¤
        mActiveScene = mScenes[(UINT)eSceneType::WorldStage];
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