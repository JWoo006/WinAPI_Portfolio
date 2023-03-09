#pragma once
#include "JongEngine.h"

namespace jw
{
	class GameObject;
	class Camera
	{
	public:
		static void Initialize();
		static void Update();

		static void SetTarget(GameObject* target) { mTarget = target; }
		//카메라 좌표계로 변경
		static Vector2 CalculatePos(Vector2 pos) { return pos - mDistance; }

	private:
		static Vector2 mResolution; //해상도
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;

	};
}



