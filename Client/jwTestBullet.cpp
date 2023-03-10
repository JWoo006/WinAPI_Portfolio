#include "jwTestBullet.h"
#include "jwTransform.h"
#include "jwTime.h"
#include "jwAnimator.h"
#include "jwSceneManager.h"
#include "jwCollider.h"
#include "jwScene.h"
#include "jwObject.h"
#include "jwCuphead.h"

namespace jw
{
	float TestBullet::mDelay = 0.15f;
	TestBullet::TestBullet()
		: mTime(0.0f)
		, mDegree(0.0f)
	{
		
	}
	TestBullet::~TestBullet()
	{

	}
	void TestBullet::Initialize()
	{
		int a = 0;
		mBulletdirection;

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(0.7f, 1.0f));
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Weapon_peashot\\main_R", Vector2::Zero, 0.1f);
		mAnimator->Play(L"Weapon_peashotmain_R", true);
	}
	void TestBullet::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		//Vector2 dir = Vector2(500.0f, 500.0f) - tr->GetPos();
		//dir.Normalize();
		
		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);
		//float x = cosf(PI / 4.0f); // 45µµ
		//float y = sinf(PI / 4.0f);
		//float x = dir.x * cosf(PI / 4.0f) - dir.y * sinf(PI / 4.0f);
		//float y = dir.x * sinf(PI / 4.0f) + dir.y * cos(PI / 4.0f);


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
	void TestBullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void TestBullet::Release()
	{
	}
}