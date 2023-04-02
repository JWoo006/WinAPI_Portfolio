#include "jwPeashot_Up.h"
#include "jwTransform.h"
#include "jwTime.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"

namespace jw
{
	float Peashot_Up::mDelay = 0.15f;
	Peashot_Up::Peashot_Up()
		: mTime(0.0f)
		, mDegree(0.0f)
	{

	}
	Peashot_Up::~Peashot_Up()
	{

	}
	void Peashot_Up::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.0f, 0.7f));
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Weapon_peashot\\Up", Vector2::Zero, 0.1f, eImageFormat::BMP, false);
		mAnimator->Play(L"Weapon_peashotUp", true);
	}
	void Peashot_Up::Update()
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
	void Peashot_Up::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Peashot_Up::Release()
	{
	}
}