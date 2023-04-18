#include "jwPeaShot_Normal.h"
#include "jwTransform.h"
#include "jwTime.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"

namespace jw
{
	float PeaShot_Normal::mDelay = 0.15f;
	PeaShot_Normal::PeaShot_Normal()
		: mTime(0.0f)
		, mDegree(0.0f)
	{

	}
	PeaShot_Normal::PeaShot_Normal(Cuphead::eCupheadState state)
		: mTime(0.0f)
		, mDegree(0.0f)
		, mCupheadState(state)
	{
	}
	PeaShot_Normal::~PeaShot_Normal()
	{

	}
	void PeaShot_Normal::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(0.7f, 1.0f));
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Weapon_peashot\\main_L", Vector2::Zero, 0.1f, eImageFormat::BMP, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Weapon_peashot\\main_R", Vector2::Zero, 0.1f, eImageFormat::BMP, eAnimationDir::R);
		
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Weapon_peashot\\Diagonal_L", Vector2::Zero, 0.1f, eImageFormat::BMP, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Weapon_peashot\\Diagonal_R", Vector2::Zero, 0.1f, eImageFormat::BMP, eAnimationDir::R);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Weapon_peashot\\Up", Vector2::Zero, 0.1f, eImageFormat::BMP, eAnimationDir::R);

		mCollider = AddComponent<Collider>();
		

		if (mCupheadState == Cuphead::eCupheadState::Shoot_L 
			|| mCupheadState == Cuphead::eCupheadState::Shoot_Run_L
			|| mCupheadState == Cuphead::eCupheadState::Duck_Shoot_L
			|| mCupheadState == Cuphead::eCupheadState::Shoot_Jump_L)
		{
			mCollider->SetCenter(Vector2(-45.0f, -20.0f));
			mCollider->SetSize(Vector2(40.0f, 20.0f));
			mAnimator->Play(L"Weapon_peashotmain_L", true);
		}
		else if (mCupheadState == Cuphead::eCupheadState::Shoot_R
			|| mCupheadState == Cuphead::eCupheadState::Shoot_Run_R
			|| mCupheadState == Cuphead::eCupheadState::Duck_Shoot_R
			|| mCupheadState == Cuphead::eCupheadState::Shoot_Jump_R)
		{
			mCollider->SetCenter(Vector2(-5.0f, -20.0f));
			mCollider->SetSize(Vector2(40.0f, 20.0f));
			mAnimator->Play(L"Weapon_peashotmain_R", true);
		}
		else if (mCupheadState == Cuphead::eCupheadState::Shoot_UP_L
			|| mCupheadState == Cuphead::eCupheadState::Shoot_UP_R
			|| mCupheadState == Cuphead::eCupheadState::Shoot_Jump_Up_L
			|| mCupheadState == Cuphead::eCupheadState::Shoot_Jump_Up_R)
		{
			mCollider->SetCenter(Vector2(-15.0f, -20.0f));
			mCollider->SetSize(Vector2(20.0f, 40.0f));
			mAnimator->Play(L"Weapon_peashotmain_R", true);
			mAnimator->Play(L"Weapon_peashotUp", true);
		}
		else if (mCupheadState == Cuphead::eCupheadState::Shoot_Run_diag_Up_L
			|| mCupheadState == Cuphead::eCupheadState::Shoot_Jump_diag_Up_L)
		{
			mCollider->SetCenter(Vector2(-15.0f, -20.0f));
			mCollider->SetSize(Vector2(40.0f, 20.0f));
			mAnimator->Play(L"Weapon_peashotmain_R", true);
			tr->SetScale(Vector2(0.9f, 0.6f));
			mAnimator->Play(L"Weapon_peashotDiagonal_L", true);
		}
		else if (mCupheadState == Cuphead::eCupheadState::Shoot_Run_diag_Up_R
			|| mCupheadState == Cuphead::eCupheadState::Shoot_Jump_diag_Up_R)
		{
			mCollider->SetCenter(Vector2(-5.0f, -20.0f));
			mCollider->SetSize(Vector2(40.0f, 20.0f));
			mAnimator->Play(L"Weapon_peashotmain_R", true);
			tr->SetScale(Vector2(0.9f, 0.6f));
			mAnimator->Play(L"Weapon_peashotDiagonal_R", true);
		}

	}
	void PeaShot_Normal::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();

		Vector2 dir = Vector2(1.0f, 0.0f);
		dir = math::Rotate(dir, mDegree);

		Vector2 pos = tr->GetPos();
		float speed = 1500.0f;
		pos.x += speed * dir.x * Time::DeltaTime();
		pos.y += speed * dir.y * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();

		if (mTime > 1.0f)
		{
			object::Destroy(this);
		}
	}
	void PeaShot_Normal::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PeaShot_Normal::Release()
	{
	}
	void PeaShot_Normal::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			object::Destroy(this);
		}
	}
	void PeaShot_Normal::OnCollisionStay(Collider* other)
	{
	}
	void PeaShot_Normal::OnCollisionExit(Collider* other)
	{
	}
}