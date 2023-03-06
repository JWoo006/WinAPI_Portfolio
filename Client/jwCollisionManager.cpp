#include "jwCollisionManager.h"
#include "jwScene.h"
#include "jwSceneManager.h"

namespace jw
{
    WORD CollisionManager::mMatrix[(UINT)eLayerType::End] = {};

    void CollisionManager::Update()
    {
        Scene* scene = SceneManager::GetActiveScene();

        for (UINT row = 0; row < (UINT)eLayerType::End; row++)
        {
            for (UINT col = 0; col < (UINT)eLayerType::End; col++)
            {
                if (mMatrix[row] & (1 << col))
                {
                    LayerCollision(scene, (eLayerType)row, (eLayerType)col);
                }

            }
        }
    }
    void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
    {
        const std::vector<GameObject*>& lefts = scene->GetGameObjects(left);
        const std::vector<GameObject*>& rights = scene->GetGameObjects(right);

        for (auto leftObject : lefts)
        {
            Collider* leftCollider = leftObject->GetComponent<Collider>();
            if (leftCollider == nullptr)
                continue;

            for (auto rightObject : rights)
            {
                Collider* rightCollider = rightObject->GetComponent<Collider>();
                if (rightCollider == nullptr)
                    continue;

                if (leftObject == rightObject)
                    continue;

                if (Intersect(leftCollider, rightCollider))
                {
                    // 충돌 O
                }
                else
                {
                    // 충돌 X
                }
            }
        }
    }
    bool CollisionManager::Intersect(Collider* left, Collider* right)
    {
        Vector2 leftPos = left->GetPos();
        Vector2 rightPos = right->GetPos();

        Vector2 leftSize = left->GetSize();
        Vector2 rightSize = right->GetSize();

        // 두 충돌체 간의 거리와, 각면적의 절반끼리의 합을 비교하면서
        // 거리가 더 길다면 충돌x, 거리가 더 짧다면 충돌O
        
        // fabs() - 절대값을 구해주는 함수
        if (fabs(leftPos.x - rightPos.x) < (leftSize.x / 2.0f) + (rightSize.x / 2.0f)
            && fabs(leftPos.y - rightPos.y) < (leftSize.y / 2.0f) + (rightSize.y / 2.0f))
        {
            return true;
        }

        return false;
    }
    void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool value)
    {
        UINT row = 0;
        UINT col = 0;

        UINT ileft = (UINT)left;
        UINT iright = (UINT)right;

        if (left <= right)
        {
            row = ileft;
            col = iright;
        }
        else
        {
            row = iright;
            col = ileft;
        }

        if (value == true)
            mMatrix[row] |= (1 << col);
        else
            mMatrix[row] &= ~(1 << col);
    }

    void CollisionManager::Clear()
    {

    }
}