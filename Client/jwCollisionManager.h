#pragma once
#include "CommonInclude.h"
#include "jwEnums.h"
#include "jwCollider.h"


namespace jw
{
	// 공용체
	union ColliderID
	{
		struct
		{
			UINT left;
			UINT right;
		};
		UINT64 id;
	};

	class Scene;
	class CollisionManager
	{
	public:
		static void Update();
		static void LayerCollision(Scene* scene, eLayerType left, eLayerType right);
		static void ColliderCollision(Collider* leftCol, Collider* rightCol, eLayerType left, eLayerType right);
		static bool Intersect(Collider* left, Collider* right);

		static void SetLayer(eLayerType left, eLayerType right, bool value);

		static void Clear();

	private:
		static WORD mMatrix[(UINT)eLayerType::End];
		// 반으로 쪼개서 32비트씩 사용하거나
		// 위 공용체 64비트의 숫자인 id로 사용하거나
		static std::map<UINT64, bool> mCollisionMap;
	};
}


