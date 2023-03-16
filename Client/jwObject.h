#pragma once
#include "jwGameObject.h"
#include "jwScene.h"
#include "jwSceneManager.h"
#include "jwTransform.h"

namespace jw::object
{
	template <typename T>
	static inline T* Instantiate(eLayerType type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObj, type);
		gameObj->Initialize();
		return gameObj;
	}

	template <typename T>
	static inline T* Instantiate(Vector2 pos, eLayerType type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObj, type);
		gameObj->GameObject::GetComponent<Transform>()->SetPos(pos);
		gameObj->Initialize();
		return gameObj;
	}

	static void Destroy(GameObject* obj)
	{
		obj->SetState(GameObject::eState::Death);
	}

}