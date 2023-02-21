#include "jwScenenManager.h"
#include "jwPlayScene.h"

namespace jw
{
    std::vector<Scene*> ScenenManager::mScenes = {};

    void ScenenManager::Initialize()
    {
        mScenes.resize((UINT)eSceneType::Max);

        mScenes[(UINT)eSceneType::Play] = new PlayScene();
        //mScenes[(UINT)eSceneType::Play]->SetName(L"Player");

        for (Scene* scene : mScenes)
        {
            if (scene == nullptr)
            {
                continue;
            }

            scene->Initialize();
        }
    }
    void ScenenManager::Update()
    {
        //값을 바꿔줄때 사용
        /*for (size_t i = 0; i < (UINT)eSceneType::Max; i++)
        {
            if (mScenes[i] == nullptr)
                continue;
            
            mScenes[i]->Update();
        }*/

        // 범위기반 for문
        // read only
        // 읽기만할때만 사용 순회
        for (Scene* scene : mScenes)
        {
            if (scene == nullptr)
            {
                continue;
            }

            scene->Update();
        }
    }
    void ScenenManager::Render(HDC hdc)
    {
        for (Scene* scene : mScenes)
        {
            if (scene == nullptr)
            {
                continue;
            }

            scene->Render(hdc);
        }
    }
    void ScenenManager::Release()
    {
        for (Scene* scene : mScenes)
        {
            if (scene == nullptr)
            {
                continue;
            }

            scene->Release();
        }
    }
}