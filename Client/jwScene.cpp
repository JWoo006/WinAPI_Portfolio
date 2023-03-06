#include "jwScene.h"
#include "jwApplication.h"

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
		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
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
	void Scene::Release()
	{
		
	}
	void Scene::OnEnter()
	{
		
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
	}
	const std::vector<GameObject*>& Scene::GetGameObjects(eLayerType layer)
	{
		return mLayers[(UINT)layer].GetGameObjects();
	}
}