#include "jwScene.h"
#include "jwApplication.h"
#include "jwSceneManager.h"
#include "jwObject.h"
#include "jwSceneLoad_In.h"

extern jw::Application application;

namespace jw
{
	Scene::Scene()
	{
		mLayers.resize((UINT)eLayerType::End);
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
		SceneManager::SetActiveScene(this);
	}
	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}
	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : mLayers)
		{
			layer.Render(hdc);

			
		}
	}

	// death상태인 오브젝트 전부 모으고 삭제
	void Scene::Destroy()
	{
		std::vector<GameObject*> deleteGameObjects = {};

		for (Layer& layer : mLayers)
		{
			std::vector<GameObject*>& gameObjects
				= layer.GetGameObjects();

			for (std::vector<GameObject*>::iterator iter = gameObjects.begin()
				; iter != gameObjects.end()
				; )
			{
				if ((*iter)->GetState() == GameObject::eState::Death)
				{
					deleteGameObjects.push_back((*iter));

					iter = gameObjects.erase(iter); 
				}
				else
				{
					iter++;
				}
			}
		}

		// 죽은 위치에서 충돌중인 다른 충돌체가 있었다면 exit를
		// 호출 해준후에 삭제

		for (GameObject* deathObj : deleteGameObjects)
		{
			delete deathObj;
			deathObj = nullptr;
		}

	}
	void Scene::Release()
	{
		
	}
	void Scene::OnEnter()
	{
		object::Instantiate<SceneLoad_In>(Vector2(800.0f, 900.0f), eLayerType::UI);
	}
	void Scene::OnExit()
	{
	}

	void Scene::SceneText(HDC hdc)
	{
		std::wstring tmp = Scene::GetName();
		TextOut(hdc, 0, 0, tmp.c_str(), tmp.size());
	}
	void Scene::AddGameObject(GameObject* obj, eLayerType layer)
	{
		mLayers[(UINT)layer].AddGameObject(obj);
		obj->SetLayerType(layer);
	}
	std::vector<GameObject*>& Scene::GetGameObjects(eLayerType layer)
	{
		return mLayers[(UINT)layer].GetGameObjects();
	}
}