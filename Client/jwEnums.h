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
	SpriteRenderer, //이미지 1장- 백그라운드
	Animator, //애니메이션이 있는 이미지들을 돌려줌
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