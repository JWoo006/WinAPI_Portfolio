#include "jwCarrot_Bomb.h"
#include "jwTime.h"
#include "jwInput.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"

#include "jwSound.h"

namespace jw
{
	Carrot_Bomb::Carrot_Bomb()
		: mTime(0.0f)
		, mSpeed(100.0f)
		, mDegree(0.0f)
		, mHp(3)
		, mbDeadChecker(false)
		, mbOnHit(false)
		, OnHitChecker(0.0f)
	{
	}
	Carrot_Bomb::Carrot_Bomb(Cuphead* cuphead)
		: mTime(0.0f)
		, mSpeed(200.0f)
		, mDegree(-270.0f)
		, mHp(2)
		, mbDeadChecker(false)
		, mbOnHit(false)
		, OnHitChecker(0.0f)
		, mCuphead(cuphead)
	{
	}
	Carrot_Bomb::~Carrot_Bomb()
	{
	}
	void Carrot_Bomb::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\carrot\\carrot_bomb", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage1_veggie\\carrot\\bomb_death", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		
		mAnimator->GetCompleteEvent(L"carrotbomb_death") = std::bind(&Carrot_Bomb::AnimCompleteEvent, this);
		
		mAnimator->Play(L"carrotcarrot_bomb", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-60.0f, -100.0f));
		collider->SetSize(Vector2(120.0f, 90.0f));

		mLayerType = Carrot_Bomb::GetLayerType();

		GameObject::Initialize();
	}
	void Carrot_Bomb::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Transform* Cupheadtr = mCuphead->GetComponent<Transform>();
		Vector2 Cupheadpos = Cupheadtr->GetPos();

		mDegree = math::CalculateAngle(pos, Cupheadpos);

		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);

		
		pos.x += mSpeed * dir.x * Time::DeltaTime();
		pos.y += mSpeed * dir.y * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();

		if (mTime > 5.0f)
		{
			object::Destroy(this);
		}

		if (mbOnHit)
		{
			OnHitChecker += Time::DeltaTime();
			if (OnHitChecker > 0.05f)
			{
				OnHitChecker = 0.0f;
				mbOnHit = false;
				mAnimator->SetMatrixBase();
			}
		}
	}
	void Carrot_Bomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Carrot_Bomb::Release()
	{
		GameObject::Release();
	}
	void Carrot_Bomb::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());

		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			mAnimator->Play(L"carrotbomb_death", false);
			mSpeed = 0.0f;

			Sound* mSound1 = Resources::Load<Sound>(L"Carrot_Bomb_Explode_01", L"..\\Resources\\Sound\\Veggie\\sfx_level_veggies_Carrot_Bomb_Explode_01.wav");
			mSound1->Play(false);
			
		}

		if (other->GetOwner()->GetLayerType() == eLayerType::Bullet && !mbDeadChecker)
		{
			object::Destroy(other->GetOwner());

			mHp--;
			mbOnHit = true;
			mAnimator->SetMatrixHitFlash();

			if (mHp < 0)
			{
				Sound* mSound1
					= Resources::Load<Sound>(L"Carrot_Bomb_Explode_01", L"..\\Resources\\Sound\\Veggie\\sfx_level_veggies_Carrot_Bomb_Explode_01.wav");
				mSound1->Play(false);

				mbDeadChecker = true;

				mAnimator->Play(L"carrotbomb_death", false);
				mSpeed = 0.0f;
			}
		}
	}
	void Carrot_Bomb::OnCollisionStay(Collider* other)
	{
	}
	void Carrot_Bomb::OnCollisionExit(Collider* other)
	{
	}
	void Carrot_Bomb::AnimCompleteEvent()
	{
		object::Destroy(this);
	}
}