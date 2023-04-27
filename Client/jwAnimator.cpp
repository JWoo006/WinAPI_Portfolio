#include "jwAnimator.h"
#include "jwResources.h"

namespace jw
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mSpriteSheet(nullptr)
		, mbLoop(false)
	{
	}
	Animator::~Animator()
	{
		for (auto animation : mAnimations)
		{
			delete animation.second;
			animation.second = nullptr;
		}
		for (auto events : mEvents)
		{
			delete events.second;
			events.second = nullptr;
		}
	}
	void Animator::Initialize()
	{
		SetMatrixBase();
	}
	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			if (mActiveAnimation->IsComplete())
			{
				Animator::Events* events
					= FindEvents(mActiveAnimation->GetAnimationName());

				if (events != nullptr)
					events->mCompleteEvent();
			}
			if (mbLoop && mActiveAnimation->IsComplete())
				mActiveAnimation->Reset();
		}
	}
	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Render(hdc);
		}
	}
	void Animator::Release()
	{
	}
	void Animator::CreateAnimation(const std::wstring& name, const std::wstring& path
		, Image* sheet, Vector2 leftTop, UINT coulmn, UINT row
		, UINT spriteLength, Vector2 offset, float duration, eImageFormat imgformat, eAnimationDir dir)
	{
		Animation* animation = FindAnimation(name);

		if (animation != nullptr)
		{
			return;
		}
		animation = new Animation();

		animation->Create(sheet, path, leftTop, coulmn, row, spriteLength, offset, duration, imgformat, dir);
		animation->SetAnimationName(name);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));

		// 애니메이션 생성될때 이벤트도 추가
		Events* event = new Events();
		mEvents.insert(std::make_pair(name, event));

	}
	void Animator::CreateAnimations(const std::wstring& path, Vector2 offset, float duration, eImageFormat imgformat, eAnimationDir dir)
	{
		// 파일 크기
		UINT width = 0;
		UINT height = 0;
		// 파일 개수
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<Image*> images = {};
		//폴더 내 파일 탐색
		for ( auto& p : std::filesystem::recursive_directory_iterator(path))
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

			images.push_back(image);

			// 스프라이트 최대 사이즈 구하기
			if (width < image->GetWidth())
			{
				width = image->GetWidth();
			}
			if (height < image->GetHeight())
			{
				height = image->GetHeight();
			}
			fileCount++;
		}

		std::wstring key = fs.parent_path().filename();
		key += fs.filename();

		mSpriteSheet = Image::Create(key, width * fileCount, height);


		int index = 0;
		for (Image* image : images)
		{
			int centerX = (width - image->GetWidth()) / 2;
			int centerY = (height - image->GetHeight());

			BitBlt(mSpriteSheet->GetHdc()
				, width * index + centerX
				, 0 + centerY
				, image->GetWidth()
				, image->GetHeight(), image->GetHdc(), 0, 0, SRCCOPY);

			index++;
		}

		CreateAnimation(key,path, mSpriteSheet, Vector2::Zero, index, 1
			, index, offset, duration, imgformat, dir);

	}
	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
		{
			return nullptr;
		}

		return iter->second;
	}
	void Animator::Play(const std::wstring& name, bool loop)
	{
		if (mActiveAnimation != nullptr)
		{
			Animator::Events* prevEvents
				= FindEvents(mActiveAnimation->GetAnimationName());

			if (prevEvents != nullptr)
				prevEvents->mEndEvent();
		}

		mActiveAnimation = FindAnimation(name);
		mActiveAnimation->Reset();
		mbLoop = loop;

		Animator::Events* events
			= FindEvents(mActiveAnimation->GetAnimationName());

		if (events != nullptr)
			events->mStartEvent();
		
	}
	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}
	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);

		Animator::Events* events
			= FindEvents(animation->GetAnimationName());

		return events->mStartEvent.mEvent;
	}
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);

		Animator::Events* events
			= FindEvents(animation->GetAnimationName());

		return events->mCompleteEvent.mEvent;
	}
	void Animator::SetMatrixBase()
	{
		mColorMatrix =
		{
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		};
	}
	void Animator::SetMatrixChangeAlpha(float change)
	{

		mColorMatrix =
		{
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f - change	, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		};
	}
	void Animator::SetMatrixHitFlash()
	{
		mColorMatrix =
		{
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.2f, 0.2f, 0.2f, 0.0f, 1.0f,
		};
	}
	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);

		Animator::Events* events
			= FindEvents(animation->GetAnimationName());

		return events->mEndEvent.mEvent;
	}
}