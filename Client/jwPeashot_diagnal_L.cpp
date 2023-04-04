#include "jwPeashot_diagnal_L.h"
#include "jwTransform.h"
#include "jwTime.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"

namespace jw
{
	float Peashot_diagnal_L::mDelay = 0.15f;
	Peashot_diagnal_L::Peashot_diagnal_L()
		: mTime(0.0f)
		, mDegree(0.0f)
	{

	}
	Peashot_diagnal_L::~Peashot_diagnal_L()
	{

	}
	void Peashot_diagnal_L::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(0.9f, 0.6f));
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Weapon_peashot\\Diagonal_L", Vector2::Zero, 0.1f, eImageFormat::BMP, eAnimationDir::L);
		mAnimator->Play(L"Weapon_peashotDiagonal_L", true);
	}
	void Peashot_diagnal_L::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();

		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);

		Vector2 pos = tr->GetPos();
		float speed = 1000.0f;
		pos.x += speed * dir.x * Time::DeltaTime();
		pos.y += speed * dir.y * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();

		if (mTime > 1.0f)
		{
			object::Destroy(this);
		}
	}
	void Peashot_diagnal_L::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Peashot_diagnal_L::Release()
	{
	}
}