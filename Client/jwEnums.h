#pragma once

enum class eSceneType
{
	Title,
	WorldStage,
	Play_Veggie,
	Play_Frog,
	Score,
	TestPlay,
	End,
};


enum class eLayerType
{
	BG,
	BG2,
	Tile,
	Monster,
	BG22,
	ParryObject,
	ParryBullet,
	Player,
	Ground,
	BossBullet,
	Bullet,
	Effect,
	BG3,
	UI,
	End,
};

enum class eComponentType
{
	Transform,
	SpriteRenderer, //�̹��� 1��- ��׶���
	Animator, //�ִϸ��̼��� �ִ� �̹������� ������
	Collider,
	Rigidbody,
	Audio,
	End,
};

enum class eImageFormat
{
	BMP,
	PNG,
	NONE,
};

enum class eAnimationDir
{
	L,
	R,
	Y,
	NONE,
};