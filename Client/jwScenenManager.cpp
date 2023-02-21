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
        //���� �ٲ��ٶ� ���
        /*for (size_t i = 0; i < (UINT)eSceneType::Max; i++)
        {
            if (mScenes[i] == nullptr)
                continue;
            
            mScenes[i]->Update();
        }*/

        // ������� for��
        // read only
        // �б⸸�Ҷ��� ��� ��ȸ
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