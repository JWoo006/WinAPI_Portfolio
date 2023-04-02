#include "jwBaseBullet.h"
#include "jwTransform.h"
#include "jwTime.h"
#include "jwAnimator.h"
#include "jwSceneManager.h"
#include "jwInput.h"
#include "jwResources.h"
#include "jwCollider.h"
#include "jwScene.h"

namespace jw
{
	float BaseBullet::mDelay = 0.15f;
	BaseBullet::BaseBullet()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(0.7f, 1.0f));
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Image\\Weapon_peashot\\main_R", Vector2::Zero, 0.1f, eImageFormat::BMP, false);
		mAnimator->Play(L"Weapon_peashotmain_R", true);
		
	}
	BaseBullet::~BaseBullet()
	{
	}
	void BaseBullet::Initialize()
	{
	}
	void BaseBullet::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		float speed = 600.0f;
		pos.x += speed * Time::DeltaTime();
		tr->SetPos(pos);

	}
	void BaseBullet::Render(HDC hdc)
	{		
		GameObject::Render(hdc);	
	}
	void BaseBullet::Release()
	{
	}
}
