#pragma once
#include "jwEntity.h"
#include "jwComponent.h"

namespace jw
{
	class Collider;
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		/*virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);*/

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			//               탬플릿은 인텔리전스(자동완성)이 안됨
			//                아직 모르기 때문에
			UINT compType = (UINT)comp->GetType();
			mComponent[compType] = comp;
			comp->SetOwner(this);

			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			for (Component* comp : mComponent)
			{
				// 상속받은 부모자식간 캐스팅
				// 원하는걸 찾을시 참을 봔환 못찾을시 널반환
				if (dynamic_cast<T*>(comp))
				{
					return dynamic_cast<T*>(comp);
				}
			}

			return nullptr;
		}

	private:
		std::vector<Component*> mComponent;
		
	};

}