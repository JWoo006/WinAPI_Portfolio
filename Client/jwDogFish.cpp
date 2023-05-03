#include "jwDogFish.h"
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
	DogFish::DogFish()
		: mTime(0.0f)
		, mSpeed(1000.0f)
		, mDegree(180.0f)
	{
	}
	DogFish::~DogFish()
	{
	}
	void DogFish::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\dogfish_intro", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\dogfish_introB", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\dogfish_move", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\Captain\\dogfish_death", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"Captaindogfish_intro") = std::bind(&DogFish::IntroAnimCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Captaindogfish_introB") = std::bind(&DogFish::IntroBAnimCompleteEvent, this);

		mAnimator->Play(L"Captaindogfish_intro", false);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-80.0f, -100.0f));

		mLayerType = DogFish::GetLayerType();

		GameObject::Initialize();
	}
	void DogFish::Update()
	{
		GameObject::Update();

		switch (mDogFishState)
		{
		case jw::DogFish::eDogFishState::Intro:
			intro();
			break;
		case jw::DogFish::eDogFishState::Move:
			move();
			break;
		case jw::DogFish::eDogFishState::Death:
			death();
			break;
		default:
			break;
		}
	}
	void DogFish::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void DogFish::Release()
	{
		GameObject::Release();
	}
	void DogFish::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());

		if (other->GetOwner()->GetLayerType() == eLayerType::Bullet && !mbDead)
		{
			mbDead = true;

			this->SetLayerType(eLayerType::Effect);

			mDogFishState = eDogFishState::Death;
			mAnimator->Play(L"Captaindogfish_death", true);
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			object::Instantiate<DogFish_Explosion>(Vector2(pos.x, 800.0f), eLayerType::Effect);
		}
	}
	void DogFish::OnCollisionStay(Collider* other)
	{

	}
	void DogFish::OnCollisionExit(Collider* other)
	{
	}
	void DogFish::intro()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mUpTime += Time::DeltaTime();

		mDegree = -100.0f;

		if (mUpTime > 0.4f)
		{
			mDegree = 100.0f;
		}


		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);

		pos.x += mSpeed * dir.x * Time::DeltaTime();
		pos.y += mSpeed * dir.y * Time::DeltaTime();

		tr->SetPos(pos);

		
	}
	void DogFish::move()
	{
		Transform* tr = GetComponent<Transform>();

		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);

		Vector2 pos = tr->GetPos();
		pos.x += mSpeed * dir.x * Time::DeltaTime();
		pos.y += mSpeed * dir.y * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();

		if (mTime > 10.0f)
		{
			object::Destroy(this);
		}
		
	}
	void DogFish::death()
	{
		Transform* tr = GetComponent<Transform>();

		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);

		Vector2 pos = tr->GetPos();

		mSpeed = 500.0f;
		pos.y -= mSpeed * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();

		if (mTime > 5.0f)
		{
			object::Destroy(this);
		}
	}
	void DogFish::IntroAnimCompleteEvent()
	{
		mDogFishState = eDogFishState::Move;
		mDegree = 180.0f;
		mAnimator->Play(L"Captaindogfish_introB", false);

		this->SetLayerType(eLayerType::BossBullet);

		Transform* tr = GetComponent<Transform>();

		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);

		Vector2 pos = tr->GetPos();
		pos.y = 800.0f;
		tr->SetPos(pos);

	}
	void DogFish::IntroBAnimCompleteEvent()
	{
		mAnimator->Play(L"Captaindogfish_move", true);
	}
}