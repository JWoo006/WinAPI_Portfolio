#include "jwWorldMap1.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwScene.h"
#include "jwObject.h"
#include "jwCamera.h"

namespace jw
{
	WorldMap1::WorldMap1()
	{
	}
	WorldMap1::~WorldMap1()
	{
	}
	void WorldMap1::Initialize()
	{
		mImage = Resources::Load<Image>(L"WorldMap1", L"..\\Resources\\Image\\World_Map\\world1_large_island_main.bmp");

		GameObject::Initialize();
	}
	void WorldMap1::Update()
	{
		GameObject::Update();
	}
	void WorldMap1::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Vector2 renderPos = Camera::CalculatePos(Vector2(-1200.0f, -700.0f));
		BitBlt(hdc, renderPos.x, renderPos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}
	void WorldMap1::Release()
	{
		GameObject::Release();
	}
}