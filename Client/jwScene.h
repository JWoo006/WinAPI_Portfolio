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
		virtual void Release();

		void AddGameObject(GameObject* obj, eLayerType layer);

	private:
		std::vector<Layer> mLayers;
	};
}
