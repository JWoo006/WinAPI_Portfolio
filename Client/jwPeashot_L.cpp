#include "jwPeashot_L.h"
#include "jwTransform.h"
#include "jwTime.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"

namespace jw
{
	float Peashot_L::mDelay = 0.15f;
	Peashot_L::Peashot_L()
		: mTime(0.0f)
		, mDegree(0.0f)
	{

	}
	Peashot_L::~Peashot_L()
	{

	}
	void Peashot_L::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(0.7f, 1.0f));
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Weapon_peashot\\main_L", Vector2::Zero, 0.1f);
		mAnimator->Play(L"Weapon_peashotmain_L", true);
	}
	void Peashot_L::Update()
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
	void Peashot_L::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Peashot_L::Release()
	{
	}
}