#pragma once
#include "JongEngine.h"


namespace jw
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		std::wstring& GetName() { return mName; }
		void SetID(UINT64 id) { mID = id; }
		UINT64 GetID() { return mID; }

	private:
		// 객체의 이름 받는 변수
		std::wstring mName;
		UINT64 mID;

	};
}
