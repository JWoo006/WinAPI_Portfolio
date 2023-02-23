#pragma once
#include "jwResource.h"

namespace jw
{
	
	class Resources
	{
	public:
		// �̹� �ε�� �����͸� ã�� �Լ�
		template <typename T>
		static T* Find(const std::wstring& key)
		{
			//���ҽ��ʿ��� �����͸� ž���Ѵ�. �����Ͱ� �ִٸ� �ش� �����͸� ��ȯ�ϰ�
			//�����Ͱ� ���ٸ� end�� ��ȯ���ش�.
 			std::map<std::wstring, Resource*>::iterator iter 
				= mResources.find(key);

			// ���ͷ����Ͱ� end()�� �ƴϸ� �����Ͱ� ����
			if (iter != mResources.end())
			{
				// �ش� Ÿ������ ����ȯ�Ͽ� ��ȯ
				return dynamic_cast<T*>(iter->second); // ������ ��ȯ
			}

			//�����Ͱ� ���ٸ� �ι�ȯ
			return nullptr;
		}

		// �����͸� �ε��ؼ� �����ͷ� ��ȯ�ϴ� �Լ�
		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			// Ű������ Ž��
			T* resource = Resources::Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}
			
			// �ش� ���ҽ��� ���ٸ� 
			resource = new T();
			// ���ҽ� �ε��� �����ϸ� assert ȣ��
			if (FAILED(resource->Load(path)))
			{
				assert(false);
				return nullptr;
			}

			resource->SetKey(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return dynamic_cast<T*>(resource);
		}

		static void Release()
		{
			//  auto - �ڷ��� �߷��ؼ� �˾Ƽ� ������
			for (auto pair : mResources)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}

	private:
		static std::map<std::wstring, Resource*> mResources;
	};
}



