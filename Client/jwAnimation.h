#pragma once
#include "jwEntity.h"

namespace jw
{
	class Image;
	class Animator;
	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset; // 기준
			float duration; // 애니메이션안의 스프라이트 넘어가는 시간

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, duration(0.0f)
			{

			}
		};

		Animation();
		~Animation();

		void Initialize();
		void Update();
		void Render(HDC hdc);
		void Create(Image* sheet, const std::wstring& path, Vector2 leftTop, UINT coulmn, UINT row , UINT spriteLength,  Vector2 offset
			, float duration, eImageFormat imgformat ,bool reverse);
		void Reset(); // 루프 애니메이션이 한바퀴 돌고 다시 돌아오게하는 함수

		bool IsComplete() { return mbComplete; }
		void SetAnimator(Animator* animator) { mAnimator = animator; }
		void SetAnimationName(const std::wstring& name) { mAnimationName = name; }
		std::wstring& GetAnimationName() { return mAnimationName; }

		Gdiplus::ColorMatrix GetMatrix() { return mColorMatrix; }

	private:
		Animator* mAnimator;
		Image* mSheetImage;
		std::vector<Sprite> mSpriteSheet;

		std::vector<Image*> mImages;
		UINT mImagesIndex;
		Vector2 size;
		Vector2 mImagesLeftTop;
		Vector2 mImagesSize;
		Vector2 mImagesOffset; // 기준
		float mImagesDuration; // 애니메이션안의 스프라이트 넘어가는 시간

		std::wstring mAnimationName;
		float mTime;
		bool mbComplete;
		int mSpriteIndex;
		eImageFormat mImageType;

		Gdiplus::ColorMatrix mColorMatrix;

	};
}



