#pragma once
#include "JongEngine.h"

namespace jw
{
	class GameObject;
	class Camera
	{
	public:
		enum class eCameraEffectType
		{
			None,
			FadeIn,
			FadeOut,
			//Shake,
			End,
		};

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Clear();

		static void SetTarget(GameObject* target) { mTarget = target; }
		//카메라 좌표계로 변경
		static Vector2 CalculatePos(Vector2 pos) { return pos - mDistance; }
		static void SetCameraEffectType(eCameraEffectType Type){ mType = Type;}
		static void SetInit();


	private:
		static Vector2 mResolution; //해상도
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;

		static eCameraEffectType mType;
		static class Image* mCutton;
		static float mCuttonAlpha;
		static float mAlphaTime;
		static float mEndTime;
	};
}



