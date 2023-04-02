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
			Vector2 offset; // ����
			float duration; // �ִϸ��̼Ǿ��� ��������Ʈ �Ѿ�� �ð�

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
		void Reset(); // ���� �ִϸ��̼��� �ѹ��� ���� �ٽ� ���ƿ����ϴ� �Լ�

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
		Vector2 mImagesOffset; // ����
		float mImagesDuration; // �ִϸ��̼Ǿ��� ��������Ʈ �Ѿ�� �ð�

		std::wstring mAnimationName;
		float mTime;
		bool mbComplete;
		int mSpriteIndex;
		eImageFormat mImageType;

		Gdiplus::ColorMatrix mColorMatrix;

	};
}



