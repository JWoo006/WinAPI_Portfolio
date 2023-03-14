#pragma once

enum class eSceneType
{
	Title,
	Stage,
	Play,
	Ending,
	End,

};


enum class eLayerType
{
	BG,
	Monster,
	Player,
	Bullet,
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