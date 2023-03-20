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
	Tile,
	Monster,
	Player,
	Bullet,
	Ground,
	Effect,
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