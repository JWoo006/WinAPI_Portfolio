#include "jwCamera.h"
#include "jwApplication.h"
#include "jwGameObject.h"
#include "jwTransform.h"
#include "jwInput.h"
#include "jwTime.h"

extern jw::Application application;

namespace jw
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	void Camera::Initialize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = (mResolution / 2.0f); // 중앙
	}
	void Camera::Update()
	{
		if (Input::GetKey(eKeyCode::LEFT))
		{
			mLookPosition.x -= 400.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			mLookPosition.x += 400.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			mLookPosition.y -= 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			mLookPosition.y += 100.0f * Time::DeltaTime();
		}

		if (mTarget != nullptr)
		{
			// 해당 오브젝트 위치 구하기
			mLookPosition 
				= mTarget->GetComponent<Transform>()->GetPos();
		}

		mDistance = mLookPosition - (mResolution / 2.0f);
	}
	void Camera::Clear()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = (mResolution / 2.0f);
		mDistance = Vector2::Zero;
	}
}