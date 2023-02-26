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
	Effect,
	UI,
	End,
};

enum class eComponentType
{
	Transform,
	Collider,
	SpriteRenderer, //�̹��� 1��- ��׶���
	Animator, //�ִϸ��̼��� �ִ� �̹������� ������
	Audio,
	End,
};