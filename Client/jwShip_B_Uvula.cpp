#include "jwShip_B_Uvula.h"
#include "jwAnimator.h"
#include "jwObject.h"
#include "jwTime.h"

#include "jwBubble_Bullet.h"

namespace jw
{

	Ship_B_Uvula::Ship_B_Uvula()
	{
		mbShow = true;

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\Uvula\\Idle", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\Uvula\\Shoot_A", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\Uvula\\Shoot_B", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->GetCompleteEvent(L"UvulaShoot_A") = std::bind(&Ship_B_Uvula::Shoot_A_AnimCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"UvulaShoot_B") = std::bind(&Ship_B_Uvula::Shoot_B_AnimCompleteEvent, this);

		mUvulaState = eUvulaState::Idle;
		mAnimator->Play(L"UvulaIdle", true);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.3f, 1.5f));
	}
	Ship_B_Uvula::~Ship_B_Uvula()
	{
	}
	void Ship_B_Uvula::Update()
	{
		GameObject::Update();

		switch (mUvulaState)
		{
		case jw::Ship_B_Uvula::eUvulaState::Idle:
			idle();
			break;
		case jw::Ship_B_Uvula::eUvulaState::Attack:
			attack();
			break;
		case jw::Ship_B_Uvula::eUvulaState::Death:
			death();
			break;
		default:
			break;
		}
	}
	void Ship_B_Uvula::Render(HDC hdc)
	{
		if (mbShow)
		{
			GameObject::Render(hdc);
		}
	}
	void Ship_B_Uvula::Release()
	{
		GameObject::Release();
	}

	void Ship_B_Uvula::idle()
	{
		if (mBubble != nullptr)
		{
			//Transform* tr3 = mBubble->GetComponent<Transform>();
			//Vector2 pos3 = tr3->GetPos();
			//pos3.x -= 200.0f * Time::DeltaTime();
			//tr3->SetPos(pos3);
		}

		
	}

	void Ship_B_Uvula::attack()
	{
	}

	void Ship_B_Uvula::death()
	{
	}

	void Ship_B_Uvula::Shoot_A_AnimCompleteEvent()
	{
		mbShootBubble = true;
		mBubble = object::Instantiate<Bubble_Bullet>(Vector2(1300.0f, 600.0f), eLayerType::BossBullet);


		mAnimator->Play(L"UvulaShoot_B", false);
	}

	void Ship_B_Uvula::Shoot_B_AnimCompleteEvent()
	{
		mAnimator->Play(L"UvulaIdle", true);
	}

}