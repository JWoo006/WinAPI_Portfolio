#pragma once

enum class eSceneType
{
	Title,
	WorldStage,
	Play_Veggie,
	Score,
	Tool,
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
	ParryObj,
	Player,
	BossBullet,
	Bullet,
	Ground,
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
	NONE,
};