#include "jwGameObject.h"

namespace jw
{
	GameObject::GameObject()
	{
	}
	GameObject::~GameObject()
	{
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
		for (Component* comp : mComponent)
		{
			if (comp == nullptr)
			{
				continue;
			}

			comp->Release();
		}
	}
}
