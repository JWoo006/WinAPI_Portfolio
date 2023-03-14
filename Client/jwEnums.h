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
	SpriteRenderer, //이미지 1장- 백그라운드
	Animator, //애니메이션이 있는 이미지들을 돌려줌
	Collider,
	Rigidbody,
	Audio,
	End,
};