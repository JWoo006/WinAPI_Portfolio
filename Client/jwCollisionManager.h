#pragma once
#include "CommonInclude.h"
#include "jwEnums.h"
#include "jwCollider.h"


namespace jw
{
	// ����ü
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
		// ������ �ɰ��� 32��Ʈ�� ����ϰų�
		// �� ����ü 64��Ʈ�� ������ id�� ����ϰų�
		static std::map<UINT64, bool> mCollisionMap;
	};
}


