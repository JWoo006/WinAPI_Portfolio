#include "jwEntity.h"

namespace jw
{
	Entity::Entity()
		: mName(L"")
		, mID((UINT)this)
	{
	}
	Entity::~Entity()
	{
	}
}