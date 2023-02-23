#pragma once
#include "jwResource.h"

namespace jw
{
	
	class Resources
	{
	public:
		// 이미 로드된 데이터를 찾는 함수
		template <typename T>
		static T* Find(const std::wstring& key)
		{
			//리소스맵에서 데이터를 탑색한다. 데이터가 있다면 해당 데이터를 반환하고
			//데이터가 없다면 end를 반환해준다.
 			std::map<std::wstring, Resource*>::iterator iter 
				= mResources.find(key);

			// 이터레이터가 end()가 아니면 데이터가 존재
			if (iter != mResources.end())
			{
				// 해당 타입으로 형변환하여 반환
				return dynamic_cast<T*>(iter->second); // 데이터 반환
			}

			//데이터가 없다면 널반환
			return nullptr;
		}

		// 데이터를 로드해서 포인터로 반환하는 함수
		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			// 키값으로 탐색
			T* resource = Resources::Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}
			
			// 해당 리소스가 없다면 
			resource = new T();
			// 리소스 로딩에 실패하면 assert 호출
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
			//  auto - 자료형 추론해서 알아서 맞춰줌
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



