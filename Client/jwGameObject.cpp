#include "jwGameObject.h"
#include "jwTransform.h"

namespace jw
{
	GameObject::GameObject()
	{
		mComponent.resize((UINT)eComponentType::End);
		AddComponent<Transform>();
	}
	GameObject::~GameObject()
	{
		for (Component* comp : mComponent)
		{
			delete comp;
			comp = nullptr;
		}
	}
	void GameObject::Initialize()
	{
		for (Component* comp : mComponent)
		{
			if (comp == nullptr)
			{
				continue;
			}

			comp->Initialize();
		}
	}
	void GameObject::Update()
	{
		for (Component* comp : mComponent)
		{
			if (comp == nullptr)
			{
				continue;
			}

			comp->Update();
		}
	}
	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : mComponent)
		{
			if (comp == nullptr)
			{
				continue;
			}

			comp->Render(hdc);
		}
	}
	void GameObject::Release()
	{
		
	}
}
