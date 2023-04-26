#include "jwAnimation.h"
#include "jwTime.h"
#include "jwImage.h"
#include "jwAnimator.h"
#include "jwTransform.h"
#include "jwGameObject.h"
#include "jwResources.h"
#include "jwCamera.h"

namespace jw
{
    Animation::Animation()
        : mAnimator(nullptr)
        , mSheetImage(nullptr)
        , mTime(0.0f)
        , mbComplete(false)
        , mSpriteIndex(0)
        , mAnimationName(L"")
    {
       
    }
    Animation::~Animation()
    {
    }
    void Animation::Initialize()
    {
    }
    void Animation::Update()
    {
        if (mbComplete == true)
        {
            return;
        }

        mTime += Time::DeltaTime();

        if (mImageType == eImageFormat::PNG)
        {
            if (mSpriteSheet[mImagesIndex].duration < mTime)
            {
                mTime = 0.0f;
                if (mImages.size() <= mImagesIndex + 1)
                {

                    int a = mImages.size();
                    mbComplete = true;
                }
                else
                {
                    mImagesIndex++;
                }
            }
        }
        else
        {
            if (mSpriteSheet[mSpriteIndex].duration < mTime)
            {
                mTime = 0.0f;

                if (mSpriteSheet.size() <= mSpriteIndex + 1)
                {
                    mbComplete = true;
                }
                else
                {
                    mSpriteIndex++;
                }
            }
        }

        
    }
    void Animation::Render(HDC hdc)
    {
        Transform* tr 
            = mAnimator->GetOwner()->GetComponent<Transform>();

        Vector2 scale = tr->GetScale();

        // 이미지가 그려질 좌표를 오브젝트 좌표의 위쪽 중간에 그림
        // 캐릭터의 발을 기준으로 포지션을 계산
        Vector2 pos = tr->GetPos();
        pos = Camera::CalculatePos(pos);
       
        Graphics graphic(hdc);
        if (mImageType == eImageFormat::PNG)
        {
            pos += mSpriteSheet[mImagesIndex].offset;
            pos.x -= (mSpriteSheet[mImagesIndex].size.x / 2.0f ) * scale.x;
            pos.y -= mSpriteSheet[mImagesIndex].size.y * scale.y;
         
            Gdiplus::RectF mRect(pos.x, pos.y, mImages[mImagesIndex]->GetWidth() * scale.x, mImages[mImagesIndex]->GetHeight() * scale.y);

            //mAnimator->SetMatrixChangeAlpha(1.0f);

            Gdiplus::ImageAttributes imgAttributes;
            Gdiplus::ColorMatrix mMatrix = mAnimator->GetMatrix();
            imgAttributes.SetColorMatrix(&mMatrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

            graphic.DrawImage(mImages[mImagesIndex]->GetImage(), mRect, 0, 0
                , mImages[mImagesIndex]->GetWidth(), mImages[mImagesIndex]->GetHeight()
                , Gdiplus::UnitPixel, &imgAttributes);

            //graphic.DrawImage(mImages[mImagesIndex]->GetImage(), pos.x, pos.y
            //, mImages[mImagesIndex]->GetWidth() * scale.x, mImages[mImagesIndex]->GetHeight() * scale.y);
        }
        else
        {
            pos += mSpriteSheet[mSpriteIndex].offset;
            pos.x -= ( mSpriteSheet[mSpriteIndex].size.x / 2.0f )* scale.x;
            pos.y -= mSpriteSheet[mSpriteIndex].size.y * scale.y;

            TransparentBlt(hdc, pos.x, pos.y
                , mSpriteSheet[mSpriteIndex].size.x * scale.x
                , mSpriteSheet[mSpriteIndex].size.y * scale.y
                , mSheetImage->GetHdc()
                , mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
                , mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y
                , RGB(255, 0, 255));
        }

        //알파 블렌딩
        //BLENDFUNCTION func = {};
        //func.BlendOp = AC_SRC_OVER;
        //func.BlendFlags = 0;
        //func.AlphaFormat = 0;
        //func.SourceConstantAlpha = 127; // 알파값 - 낮을수록 투명
        //AlphaBlend(hdc, pos.x, pos.y
        //    , mSpriteSheet[mSpriteIndex].size.x * scale.x 
        //    , mSpriteSheet[mSpriteIndex].size.y * scale.y
        //    , mSheetImage->GetHdc()
        //    , mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
        //    , mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y
        //    , func);

    }
    void Animation::Create(Image* sheet, const std::wstring& path, Vector2 leftTop
        , UINT coulmn, UINT row, UINT spriteLength
        , Vector2 offset, float duration, eImageFormat imgformat, eAnimationDir dir)
    {
        mImageType = imgformat;

        if (imgformat == eImageFormat::PNG)
        {
            for (auto& p : std::filesystem::recursive_directory_iterator(path))
            {
                auto a = std::filesystem::recursive_directory_iterator(path);

                std::wstring fileName = p.path().filename();
                std::wstring fullName = path + L"\\" + fileName;//전체경로 + 파일명

                // .png확장자 이미지는 continue
                const std::wstring ext = p.path().extension();
                if (ext == L".png")
                {
                    int a = 0;
                    //continue;
                }

                Image* image = Resources::Load<Image>(fileName, fullName);
                image->ImageFlipX();
                if (dir == eAnimationDir::L)
                {
                    
                }

                mImages.push_back(image);

                Sprite spriteInfo;
                spriteInfo.duration = duration;
                spriteInfo.offset = offset;
                spriteInfo.size.x = image->GetWidth();
                spriteInfo.size.y = image->GetHeight();

                mSpriteSheet.push_back(spriteInfo);

                /*size = Vector2::One;
                size.x = image->GetWidth();
                size.y = image->GetHeight();*/
            }
            /*mImagesSize = size;
            mImagesOffset = offset;
            mImagesDuration = duration;*/
        }
        else
        {
            mSheetImage = sheet;

            //UINT coulmn = mSheetImage->GetWidth() / size.x;
            Vector2 size = Vector2::One;
            size.x = mSheetImage->GetWidth() / (float)coulmn;
            size.y = mSheetImage->GetHeight() / (float)row;

            for (size_t i = 0; i < spriteLength; i++)
            {
                Sprite spriteInfo;
                spriteInfo.leftTop.x = leftTop.x + (size.x * i);
                spriteInfo.leftTop.y = leftTop.y;
                spriteInfo.size = size;
                spriteInfo.offset = offset;
                spriteInfo.duration = duration;

                mSpriteSheet.push_back(spriteInfo);
            }
        }
    }
    void Animation::Reset()
    {
        mSpriteIndex = 0;
        mImagesIndex = 0;
        mTime = 0.0f;
        mbComplete = false;
    }
}