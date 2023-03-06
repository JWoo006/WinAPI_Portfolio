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
			//               ���ø��� ���ڸ�����(�ڵ��ϼ�)�� �ȵ�
			//                ���� �𸣱� ������
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
				// ��ӹ��� �θ��ڽİ� ĳ����
				// ���ϴ°� ã���� ���� ��ȯ ��ã���� �ι�ȯ
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