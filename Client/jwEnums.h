#pragma once

enum class eSceneType
{
	Title,
	Stage,
	Play,
	Ending,
	Tool,
	End,

};


enum class eLayerType
{
	BG,
	BG2,
	Tile,
	Monster,
	ParryObj,
	Player,
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