#include "jwBubble_Bullet.h"
#include "jwTime.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"
#include "jwDogFish_Explosion.h"

namespace jw
{
	Bubble_Bullet::Bubble_Bullet()
		: mTime(0.0f)
		, mSpeed(700.0f)
		, mDegree(90.0f)
	{
	}
	Bubble_Bullet::~Bubble_Bullet()
	{
	}
	void Bubble_Bullet::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\Uvula\\Bubble", Vector2::Zero, 0.1f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->Play(L"UvulaBubble", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));

		mLayerType = Bubble_Bullet::GetLayerType();

		GameObject::Initialize();
	}
	void Bubble_Bullet::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();

		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);

		mDegree +=  10.0f;

		if (mDegree >= 360.0f)
		{
			mDegree = 0.0f;
		}


		Vector2 pos = tr->GetPos();
		pos.x += mSpeed * dir.x * Time::DeltaTime();
		pos.y += mSpeed * dir.y * Time::DeltaTime();

		pos.x -= 200.0f * Time::DeltaTime();

		tr->SetPos(Vector2(pos.x, pos.y));
		if (mDegree >= 180.0f && mDegree <= 360.0f)
		{
			
		}
		else
		{
		//	tr->SetPos(Vector2(pos.x, pos.y));
		}

		

		mTime += Time::DeltaTime();

		if (pos.x < 0.0f)
		{
			object::Destroy(this);
		}
	}
	void Bubble_Bullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Bubble_Bullet::Release()
	{
		GameObject::Release();
	}
	void Bubble_Bullet::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());

		if (other->GetOwner()->GetLayerType() == eLayerType::Player && !mbDead)
		{
			mbDead = true;
			mSpeed = 0.0f;

			this->SetLayerType(eLayerType::Effect);

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			object::Instantiate<DogFish_Explosion>(Vector2(pos), eLayerType::Effect);

			object::Destroy(this);
		}
	}
	void Bubble_Bullet::OnCollisionStay(Collider* other)
	{

	}
	void Bubble_Bullet::OnCollisionExit(Collider* other)
	{
	}
}