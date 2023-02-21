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

		//override�� �Ἥ �ڽ������� ������ �θ��� �Լ��� ��������
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