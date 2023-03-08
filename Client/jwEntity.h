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
		// ��ü�� �̸� �޴� ����
		std::wstring mName;
		UINT64 mID;

	};
}
