#include "jwPlayScene.h"
#include "jwCuphead.h"

namespace jw
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		Cuphead* cuphead = new Cuphead();
		//cuphead->SetPos(Vector2(0.0f, 0.0f));
		AddGameObject(cuphead, eLayerType::Player);

		//override를 써서 자식쪽으로 오지만 부모쪽 함수로 지정가능
		Scene::Initialize();
	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void PlayScene::Release()
	{
		Scene::Release();
	}
}