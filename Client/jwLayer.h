#pragma once
#include "jwEntity.h"
#include "jwGameObject.h"

namespace jw
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void AddGameObject(GameObject* gameObj);
		std::vector<GameObject*>& GetGameObjects() { return mGameObjects; }

	private:
		std::vector<GameObject*> mGameObjects;
		
	};
}

