#pragma once
#include "jwEntity.h"
#include "jwLayer.h"

namespace jw
{
	class Scene : public Entity
	{
	public :
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Destroy();
		virtual void Release();

		// 씬전환간 초기화를 위한 함수
		virtual void OnEnter();
		virtual void OnExit();

		// 씬이름 출력
		virtual void SceneText(HDC hdc);

		void AddGameObject(GameObject* obj, eLayerType layer);
		std::vector<GameObject*>& GetGameObjects(eLayerType layer);

	private:
		std::vector<Layer> mLayers;
	};
}
