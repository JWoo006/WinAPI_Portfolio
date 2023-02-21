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

	private:
		// ��ü�� �̸� �޴� ����
		std::wstring mName;
	};
}
