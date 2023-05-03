#include "jwLazar.h"
#include "jwTime.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwAnimator.h"
#include "jwCollider.h"
#include "jwObject.h"
#include "jwCuphead.h"


namespace jw
{
	Lazar::Lazar()
	{
	}
	Lazar::~Lazar()
	{
	}
	void Lazar::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\lazar\\lazar_start" , Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\lazar\\lazar_loop" , Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Stage3_pirate\\WhaleBoat_B\\lazar\\lazar_end" , Vector2::Zero, 0.05f, eImageFormat::PNG, eAnimationDir::R);
		
		mAnimator->GetCompleteEvent(L"lazarlazar_start") = std::bind(&Lazar::StartAnimCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"lazarlazar_end") = std::bind(&Lazar::EndAnimCompleteEvent, this);

		mAnimator->Play(L"lazarlazar_start", false);
		mLazarState = eLazarState::Start;

		mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-80.0f, -100.0f));
		mCollider->SetSize(Vector2(100.0f, 100.0f));

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetScale(Vector2(1.6f, 1.9f));

		mLayerType = Lazar::GetLayerType();

		GameObject::Initialize();
	}
	void Lazar::Update()
	{
		GameObject::Update();

		switch (mLazarState)
		{
		case jw::Lazar::eLazarState::Start:
			start();
			break;
		case jw::Lazar::eLazarState::Loop:
			loop();
			break;
		case jw::Lazar::eLazarState::End:
			end();
			break;
		default:
			break;
		}
	}
	void Lazar::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Lazar::Release()
	{
		GameObject::Release();
	}
	void Lazar::OnCollisionEnter(Collider* other)
	{
		
	}
	void Lazar::OnCollisionStay(Collider* other)
	{

	}
	void Lazar::OnCollisionExit(Collider* other)
	{
	}
	void Lazar::start()
	{
	}
	void Lazar::loop()
	{
		if (mAtkEnd)
		{
			mAnimator->Play(L"lazarlazar_end", true);
			mLazarState = eLazarState::End;
		}

		
	}
	void Lazar::end()
	{
	}
	void Lazar::StartAnimCompleteEvent()
	{
		mAnimator->Play(L"lazarlazar_loop", true);
		mLazarState = eLazarState::Loop;
		mCollider->SetCenter(Vector2(-800.0f, -250.0f));
		mCollider->SetSize(Vector2(1500.0f, 200.0f));
	}
	void Lazar::EndAnimCompleteEvent()
	{
		object::Destroy(this);
	}
	
}