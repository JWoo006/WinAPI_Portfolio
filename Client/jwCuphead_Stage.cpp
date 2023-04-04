#include "jwCuphead_Stage.h"
#include "jwTime.h"
#include "jwSceneManager.h"
#include "jwInput.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwImage.h"
#include "jwCollider.h"
#include "jwCamera.h"


namespace jw
{
	Cuphead_Stage::Cuphead_Stage()
		: mbShowIcon(false)
	{
		
	}
	Cuphead_Stage::~Cuphead_Stage()
	{
	}
	void Cuphead_Stage::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(800.0f, 450.0f));

		mImage = Resources::Load<Image>(L"Z_button", L"..\\Resources\\Image\\World_Map\\EnterIcon\\z-button-icon.png");


		mAnimator = AddComponent<Animator>();
		
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\diag_down_idle_L", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\diag_down_idle_R", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\diag_down_walk_L", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\diag_down_walk_R", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\diag_up_idle_L", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\diag_up_idle_R", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\diag_up_walk_L", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\diag_up_walk_R", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\side_idle_L", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\side_idle_R", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\side_walk_L", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::L);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\side_walk_R", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\down_idle", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\down_walk", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\up_idle", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Cuphead\\StageMove\\up_walk", Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);

		mAnimator->Play(L"StageMovedown_idle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -100.0f));

		mState = eCupheadState::Down_idle;

		GameObject::Initialize();
	}
	void Cuphead_Stage::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case jw::Cuphead_Stage::eCupheadState::Down_idle:
			idle();
			break;
		case jw::Cuphead_Stage::eCupheadState::Down_walk:
			move();
			break;
		case jw::Cuphead_Stage::eCupheadState::Up_idle:
			idle();
			break;
		case jw::Cuphead_Stage::eCupheadState::Up_walk:
			move();
			break;
		case jw::Cuphead_Stage::eCupheadState::Side_idle_L:
			idle();
			break;
		case jw::Cuphead_Stage::eCupheadState::Side_idle_R:
			idle();
			break;
		case jw::Cuphead_Stage::eCupheadState::Side_walk_L:
			move();
			break;
		case jw::Cuphead_Stage::eCupheadState::Side_walk_R:
			move();
			break;
		case jw::Cuphead_Stage::eCupheadState::diag_down_idle_L:
			idle();
			break;
		case jw::Cuphead_Stage::eCupheadState::diag_down_idle_R:
			idle();
			break;
		case jw::Cuphead_Stage::eCupheadState::diag_down_walk_L:
			move();
			break;
		case jw::Cuphead_Stage::eCupheadState::diag_down_walk_R:
			move();
			break;
		case jw::Cuphead_Stage::eCupheadState::diag_up_idle_L:
			idle();
			break;
		case jw::Cuphead_Stage::eCupheadState::diag_up_idle_R:
			idle();
			break;
		case jw::Cuphead_Stage::eCupheadState::diag_up_walk_L:
			move();
			break;
		case jw::Cuphead_Stage::eCupheadState::diag_up_walk_R:
			move();
			break;
		default:
			break;
		}

	}
	void Cuphead_Stage::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		if (mbShowIcon)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();

			Vector2 renderPos = Camera::CalculatePos(pos);

			Graphics graphic(hdc);
			graphic.DrawImage(mImage->GetImage(), renderPos.x - 25.0f, renderPos.y - 150.0f, mImage->GetWidth(), mImage->GetHeight());;
		}
	}
	void Cuphead_Stage::Release()
	{
		GameObject::Release();
	}
	void Cuphead_Stage::OnCollisionEnter(Collider* other)
	{
		int a = 0;

		if (other->GetOwner()->GetLayerType() == eLayerType::BG)
		{
			mbShowIcon = true;
		}
	}
	void Cuphead_Stage::OnCollisionStay(Collider* other)
	{
	}
	void Cuphead_Stage::OnCollisionExit(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::BG)
		{
			mbShowIcon = false;
		}
	}
	void Cuphead_Stage::move()
	{
		if (mState == eCupheadState::Side_walk_L && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mAnimator->Play(L"StageMoveside_idle_L", true);
			mState = eCupheadState::Side_idle_L;
		}
		if (mState == eCupheadState::Side_walk_R && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"StageMoveside_idle_R", true);
			mState = eCupheadState::Side_idle_R;
		}
		if (mState == eCupheadState::Up_walk && Input::GetKeyUp(eKeyCode::UP))
		{
			mAnimator->Play(L"StageMoveup_idle", true);
			mState = eCupheadState::Up_idle;
		}
		if (mState == eCupheadState::Down_walk && Input::GetKeyUp(eKeyCode::DOWN))
		{
			mAnimator->Play(L"StageMovedown_idle", true);
			mState = eCupheadState::Down_idle;
		}

		if (Input::GetKey(eKeyCode::LEFT) && Input::GetKey(eKeyCode::UP) && mState != eCupheadState::diag_up_walk_L)
		{
			mAnimator->Play(L"StageMovediag_up_walk_L", true);
			mState = eCupheadState::diag_up_walk_L;
		}
		if (Input::GetKey(eKeyCode::RIGHT) && Input::GetKey(eKeyCode::UP) && mState != eCupheadState::diag_up_walk_R)
		{
			mAnimator->Play(L"StageMovediag_up_walk_R", true);
			mState = eCupheadState::diag_up_walk_R;
		}
		if (Input::GetKey(eKeyCode::LEFT) && Input::GetKey(eKeyCode::DOWN) && mState != eCupheadState::diag_down_walk_L)
		{
			mAnimator->Play(L"StageMovediag_down_walk_L", true);
			mState = eCupheadState::diag_down_walk_L;
		}
		if (Input::GetKey(eKeyCode::RIGHT) && Input::GetKey(eKeyCode::DOWN) && mState != eCupheadState::diag_down_walk_R)
		{
			mAnimator->Play(L"StageMovediag_down_walk_R", true);
			mState = eCupheadState::diag_down_walk_R;
		}

		if (Input::GetKeyUp(eKeyCode::LEFT) || Input::GetKeyUp(eKeyCode::RIGHT)
			|| Input::GetKeyUp(eKeyCode::UP) || Input::GetKeyUp(eKeyCode::DOWN))
		{
			if (mState == eCupheadState::diag_up_walk_L)
			{
				mAnimator->Play(L"StageMovediag_up_idle_L", true);
				mState = eCupheadState::diag_up_idle_L;
			}
			if (mState == eCupheadState::diag_up_walk_R)
			{
				mAnimator->Play(L"StageMovediag_up_idle_R", true);
				mState = eCupheadState::diag_up_idle_R;
			}
			if (mState == eCupheadState::diag_down_walk_L)
			{
				mAnimator->Play(L"StageMovediag_down_idle_L", true);
				mState = eCupheadState::diag_down_idle_L;
			}
			if (mState == eCupheadState::diag_down_walk_R)
			{
				mAnimator->Play(L"StageMovediag_down_idle_R", true);
				mState = eCupheadState::diag_down_idle_R;
			}
		}
		


		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 200.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 200.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::UP))
		{
			pos.y -= 200.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y += 200.0f * Time::DeltaTime();
		}
		tr->SetPos(pos);
	}

	void Cuphead_Stage::idle()
	{
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mAnimator->Play(L"StageMoveside_walk_L", true);
			mState = eCupheadState::Side_walk_L;
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"StageMoveside_walk_R", true);
			mState = eCupheadState::Side_walk_R;
		}

		if (Input::GetKeyDown(eKeyCode::UP))
		{
			mAnimator->Play(L"StageMoveup_walk", true);
			mState = eCupheadState::Up_walk;
		}

		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			mAnimator->Play(L"StageMovedown_walk", true);
			mState = eCupheadState::Down_walk;
		}

	}
}
